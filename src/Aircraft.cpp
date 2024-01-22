/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
 *
 *  This file is part of MC-Mass.
 *
 *  MC-Mass is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MC-Mass is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <Aircraft.h>

#include <iomanip>
#include <sstream>

#include <mass/AllElse.h>
#include <mass/Engine.h>
#include <mass/Fuselage.h>
#include <mass/GearMain.h>
#include <mass/GearNose.h>
#include <mass/RotorDrive.h>
#include <mass/RotorHub.h>
#include <mass/RotorMain.h>
#include <mass/RotorTail.h>
#include <mass/TailHor.h>
#include <mass/TailVer.h>
#include <mass/Wing.h>

#include <utils/XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Aircraft::Aircraft()
{
    reset();
}

////////////////////////////////////////////////////////////////////////////////

Aircraft::~Aircraft()
{
    deleteAllComponents();
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::read( QDomElement *parentNode )
{
    if ( !parentNode->isNull() )
    {
        int type_temp = parentNode->attributeNode( "type" ).value().toInt();

        _data.type = AircraftData::FighterAttack;

        switch ( type_temp )
        {
            case AircraftData::FighterAttack   : _data.type = AircraftData::FighterAttack   ; break;
            case AircraftData::CargoTransport  : _data.type = AircraftData::CargoTransport  ; break;
            case AircraftData::GeneralAviation : _data.type = AircraftData::GeneralAviation ; break;
            case AircraftData::Helicopter      : _data.type = AircraftData::Helicopter      ; break;
        }

        QDomElement dataNode = parentNode->firstChildElement( "data" );
        QDomElement componentsNode = parentNode->firstChildElement( "components" );

        if ( !dataNode.isNull() && !componentsNode.isNull() )
        {
            bool result = true;

            if ( result ) result = readData( &dataNode );
            if ( result ) result = readComponents( &componentsNode );

            if ( result ) update();

            return result;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomAttr nodeType = doc->createAttribute( "type" );
    nodeType.setValue( QString::number( _data.type ) );
    parentNode->setAttributeNode( nodeType );

    // data
    QDomElement nodeData = doc->createElement( "data" );
    parentNode->appendChild( nodeData );

    // data - general
    QDomElement nodeGeneral = doc->createElement( "general" );
    nodeData.appendChild( nodeGeneral );
    saveDataGeneral( doc, &nodeGeneral );

    // data - fuselage
    QDomElement nodeFuselage = doc->createElement( "fuselage" );
    nodeData.appendChild( nodeFuselage );
    saveDataFuselage( doc, &nodeFuselage );

    // data - wing
    QDomElement nodeWing = doc->createElement( "wing" );
    nodeData.appendChild( nodeWing );
    saveDataWing( doc, &nodeWing );

    // data - horizontal tail
    QDomElement nodeHorTail = doc->createElement( "hor_tail" );
    nodeData.appendChild( nodeHorTail );
    saveDataHorTail( doc, &nodeHorTail );

    // data - vertical tail
    QDomElement nodeVerTail = doc->createElement( "ver_tail" );
    nodeData.appendChild( nodeVerTail );
    saveDataVerTail( doc, &nodeVerTail );

    // data - landing gear
    QDomElement nodeLandingGear = doc->createElement( "landing_gear" );
    nodeData.appendChild( nodeLandingGear );
    saveDataLandingGear( doc, &nodeLandingGear );

    // data - engine
    QDomElement nodeEngine = doc->createElement( "engine" );
    nodeData.appendChild( nodeEngine );
    saveDataEngine( doc, &nodeEngine );

    // rotors
    QDomElement nodeRotors = doc->createElement( "rotors" );
    nodeData.appendChild( nodeRotors );
    saveDataRotors( doc, &nodeRotors );

    // components
    QDomElement componentsNode = doc->createElement( "components" );
    parentNode->appendChild( componentsNode );

    for ( Aircraft::Components::iterator it = _components.begin(); it != _components.end(); ++it )
    {
        (*it)->save( doc, &componentsNode );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::reset()
{
    _data.type = AircraftData::FighterAttack;

    // general
    _data.general.m_empty    = 0.0;
    _data.general.mtow       = 0.0;
    _data.general.m_maxLand  = 0.0;
    _data.general.nz_max     = 1.0;
    _data.general.nz_maxLand = 1.0;
    _data.general.v_stall    = 0.0;
    _data.general.h_cruise   = 0.0;
    _data.general.v_cruise   = 0.0;
    _data.general.mach_max   = 0.0;
    _data.general.navy_ac    = false;

    // fuselage
    _data.fuselage.cargo_door   = AircraftData::Fuselage::NoCargoDoor;
    _data.fuselage.l            = 0.0;
    _data.fuselage.h            = 0.0;
    _data.fuselage.w            = 0.0;
    _data.fuselage.l_n          = 0.0;
    _data.fuselage.wetted_area  = 0.0;
    _data.fuselage.press_vol    = 0.0;
    _data.fuselage.landing_gear = false;
    _data.fuselage.cargo_ramp   = false;
    _data.fuselage.wetted_area_override = false;

    // wing
    _data.wing.area      = 0.0;
    _data.wing.area_exp  = 0.0;
    _data.wing.span      = 0.0;
    _data.wing.sweep     = 0.0;
    _data.wing.c_tip      = 0.0;
    _data.wing.c_root    = 0.0;
    _data.wing.ar        = 0.0;
    _data.wing.tr        = 0.0;
    _data.wing.t_c       = 0.0;
    _data.wing.fuel      = 0.0;
    _data.wing.ctrl_area = 0.0;
    _data.wing.delta     = false;
    _data.wing.var_sweep = false;

    // horizontal tail
    _data.hor_tail.area      = 0.0;
    _data.hor_tail.span      = 0.0;
    _data.hor_tail.sweep     = 0.0;
    _data.hor_tail.c_tip     = 0.0;
    _data.hor_tail.c_root    = 0.0;
    _data.hor_tail.t_c       = 0.0;
    _data.hor_tail.elev_area = 0.0;
    _data.hor_tail.w_f       = 0.0;
    _data.hor_tail.arm       = 0.0;
    _data.hor_tail.ar        = 0.0;
    _data.hor_tail.tr        = 0.0;
    _data.hor_tail.moving    = false;
    _data.hor_tail.rolling   = false;

    // vertical tail
    _data.ver_tail.area      = 0.0;
    _data.ver_tail.height    = 0.0;
    _data.ver_tail.sweep     = 0.0;
    _data.ver_tail.c_tip     = 0.0;
    _data.ver_tail.c_root    = 0.0;
    _data.ver_tail.t_c       = 0.0;
    _data.ver_tail.arm       = 0.0;
    _data.ver_tail.rudd_area = 0.0;
    _data.ver_tail.ar        = 0.0;
    _data.ver_tail.tr        = 0.0;
    _data.ver_tail.t_tail    = false;
    _data.ver_tail.rotor     = false;

    // landing gear
    _data.landing_gear.main_l      = 0.0;
    _data.landing_gear.nose_l      = 0.0;
    _data.landing_gear.main_wheels = 0;
    _data.landing_gear.main_struts = 0;
    _data.landing_gear.nose_wheels = 0;
    _data.landing_gear.fixed       = false;
    _data.landing_gear.cross       = false;
    _data.landing_gear.tripod      = false;
    _data.landing_gear.main_kneel  = false;
    _data.landing_gear.nose_kneel  = false;

    // engine
    _data.engine.mass = 0.0;

    // rotors
    _data.rotors.main_r          = 0.0;
    _data.rotors.main_cb         = 0.0;
    _data.rotors.main_rpm        = 0.0;
    _data.rotors.main_gear_ratio = 1.0;
    _data.rotors.tail_r          = 0.0;
    _data.rotors.mcp             = 0.0;
    _data.rotors.main_tip_vel    = 0.0;
    _data.rotors.main_blades     = 0;

    // RESULTS
    _centerOfMass.Set( 0.0, 0.0, 0.0 );

    _inertiaMatrix.Set( 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0 );

    _massTotal = 0.0;

    deleteAllComponents();
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::update()
{
    mass::kilogram_t m = 0.0_kg;
    Vector3 s;
    Matrix3x3 i;

    for ( Components::iterator it = _components.begin(); it != _components.end(); ++it )
    {
        m += (*it)->mass();
        s += (*it)->mass()() * (*it)->getPosition();
        i += (*it)->getInertia();
    }

    _centerOfMass = ( m > 0.0_kg ) ? ( s / m() ) : Vector3();
    _inertiaMatrix = i;
    _massTotal = m();
}

////////////////////////////////////////////////////////////////////////////////

Component* Aircraft::getComponent( int index )
{
    Components::iterator it = _components.begin() + index;

    if ( it != _components.end() )
    {
        return (*it);
    }

    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::addComponent( Component *component )
{
    _components.push_back( component );
    update();
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::delComponent( int index )
{
    Components::iterator it = _components.begin() + index;

    if ( it != _components.end() )
    {
        DELPTR( *it );
        _components.erase( it );
    }

    update();
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::setData( const AircraftData &data )
{
    _data = data;
}

////////////////////////////////////////////////////////////////////////////////

std::string Aircraft::toString() const
{
    std::stringstream ss;

    ss.setf( std::ios_base::showpoint );
    ss.setf( std::ios_base::fixed );

    ss << "empty mass [kg]: ";
    ss << std::setprecision( 1 ) << _massTotal;
    ss << std::endl;

    ss << "center of mass [m]: ";
    ss << std::setfill(' ') << std::setw( 8 ) << std::setprecision( 2 ) << _centerOfMass.x();
    ss << " ";
    ss << std::setfill(' ') << std::setw( 8 ) << std::setprecision( 2 ) << _centerOfMass.y();
    ss << " ";
    ss << std::setfill(' ') << std::setw( 8 ) << std::setprecision( 2 ) << _centerOfMass.z();
    ss << std::endl;

    ss << "inertia [kg*m^2]:";
    ss << std::endl;

    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.xx();
    ss << " ";
    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.xy();
    ss << " ";
    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.xz();
    ss << std::endl;

    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.yx();
    ss << " ";
    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.yy();
    ss << " ";
    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.yz();
    ss << std::endl;

    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.zx();
    ss << " ";
    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.zy();
    ss << " ";
    ss << std::setfill(' ') << std::setw( 12 ) << std::setprecision( 1 ) << _inertiaMatrix.zz();
    ss << std::endl;

    ss << std::endl;

    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::deleteAllComponents()
{
    Components::iterator it = _components.begin();

    while ( it != _components.end() )
    {
        DELPTR( *it );
        it = _components.erase( it );
    }

    update();
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readData( QDomElement *dataNode )
{
    QDomElement nodeGeneral     = dataNode->firstChildElement( "general"      );
    QDomElement nodeFuselage    = dataNode->firstChildElement( "fuselage"     );
    QDomElement nodeWing        = dataNode->firstChildElement( "wing"         );
    QDomElement nodeHorTail     = dataNode->firstChildElement( "hor_tail"     );
    QDomElement nodeVerTail     = dataNode->firstChildElement( "ver_tail"     );
    QDomElement nodeLandingGear = dataNode->firstChildElement( "landing_gear" );
    QDomElement nodeEngine      = dataNode->firstChildElement( "engine"       );
    QDomElement nodeRotors      = dataNode->firstChildElement( "rotors"       );

    if (   !nodeGeneral     .isNull()
        && !nodeFuselage    .isNull()
        && !nodeWing        .isNull()
        && !nodeHorTail     .isNull()
        && !nodeVerTail     .isNull()
        && !nodeLandingGear .isNull()
        && !nodeEngine      .isNull()
        && !nodeRotors      .isNull()
       )
    {
        bool result = true;

        if ( result ) result = readDataGeneral     ( &nodeGeneral     );
        if ( result ) result = readDataFuselage    ( &nodeFuselage    );
        if ( result ) result = readDataWing        ( &nodeWing        );
        if ( result ) result = readDataHorTail     ( &nodeHorTail     );
        if ( result ) result = readDataVerTail     ( &nodeVerTail     );
        if ( result ) result = readDataLandingGear ( &nodeLandingGear );
        if ( result ) result = readDataEngine      ( &nodeEngine      );
        if ( result ) result = readDataRotors      ( &nodeRotors      );

        return result;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readDataGeneral( QDomElement *parentNode )
{
    QDomElement nodeM_empty   = parentNode->firstChildElement( "m_empty"     );
    QDomElement nodeMTOW      = parentNode->firstChildElement( "mtow"        );
    QDomElement nodeM_maxLand = parentNode->firstChildElement( "m_max_land"  );
    QDomElement nodeNzMax     = parentNode->firstChildElement( "nz_max"      );
    QDomElement nodeNzMaxLand = parentNode->firstChildElement( "nz_max_land" );
    QDomElement nodeStallV    = parentNode->firstChildElement( "stall_v"     );
    QDomElement nodeCruiseH   = parentNode->firstChildElement( "h_cruise"    );
    QDomElement nodeCruiseV   = parentNode->firstChildElement( "v_cruise"    );
    QDomElement nodeMachMax   = parentNode->firstChildElement( "mach_max"    );
    QDomElement nodeNavyAC    = parentNode->firstChildElement( "navy_ac"     );

    if (   !nodeM_empty   .isNull()
        && !nodeMTOW      .isNull()
        && !nodeM_maxLand .isNull()
        && !nodeNzMax     .isNull()
        && !nodeNzMaxLand .isNull()
        && !nodeStallV    .isNull()
        && !nodeCruiseH   .isNull()
        && !nodeCruiseV   .isNull()
        && !nodeMachMax   .isNull()
        && !nodeNavyAC    .isNull()
       )
    {
        _data.general.m_empty    = nodeM_empty   .text().toDouble();
        _data.general.mtow       = nodeMTOW      .text().toDouble();
        _data.general.m_maxLand  = nodeM_maxLand .text().toDouble();
        _data.general.nz_max     = nodeNzMax     .text().toDouble();
        _data.general.nz_maxLand = nodeNzMaxLand .text().toDouble();
        _data.general.v_stall    = nodeStallV    .text().toDouble();
        _data.general.h_cruise   = nodeCruiseH   .text().toDouble();
        _data.general.v_cruise   = nodeCruiseV   .text().toDouble();
        _data.general.mach_max   = nodeMachMax   .text().toDouble();

        _data.general.navy_ac = nodeNavyAC.text().toInt();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readDataFuselage( QDomElement *parentNode )
{
    QDomElement nodeCargoDoor  = parentNode->firstChildElement( "cargo_door"   );
    QDomElement nodeFuseL      = parentNode->firstChildElement( "lenght"       );
    QDomElement nodeFuseH      = parentNode->firstChildElement( "height"       );
    QDomElement nodeFuseW      = parentNode->firstChildElement( "width"        );
    QDomElement nodeNoseL      = parentNode->firstChildElement( "nose_length"  );
    QDomElement nodeWettedArea = parentNode->firstChildElement( "wetted_area"  );
    QDomElement nodePressVol   = parentNode->firstChildElement( "press_vol"    );
    QDomElement nodeFuselageLG = parentNode->firstChildElement( "landing_gear" );
    QDomElement nodeCargoRamp  = parentNode->firstChildElement( "cargo_ramp"   );
    QDomElement nodeWettedAreaOverride  = parentNode->firstChildElement( "wetted_area_override" );

    if (   !nodeCargoDoor  .isNull()
        && !nodeFuseL      .isNull()
        && !nodeFuseH      .isNull()
        && !nodeFuseW      .isNull()
        && !nodeNoseL      .isNull()
        && !nodeWettedArea .isNull()
        && !nodePressVol   .isNull()
        && !nodeFuselageLG .isNull()
        && !nodeCargoRamp  .isNull()
        && !nodeWettedAreaOverride.isNull()
       )
    {
        int cargo_door_temp = nodeCargoDoor.text().toInt();

        _data.fuselage.cargo_door = AircraftData::Fuselage::NoCargoDoor;

        switch ( cargo_door_temp )
        {
            case AircraftData::Fuselage::NoCargoDoor       : _data.fuselage.cargo_door = AircraftData::Fuselage::NoCargoDoor       ; break;
            case AircraftData::Fuselage::OneSideCargoDoor  : _data.fuselage.cargo_door = AircraftData::Fuselage::OneSideCargoDoor  ; break;
            case AircraftData::Fuselage::TwoSideCargoDoor  : _data.fuselage.cargo_door = AircraftData::Fuselage::TwoSideCargoDoor  ; break;
            case AircraftData::Fuselage::AftClamshellDoor  : _data.fuselage.cargo_door = AircraftData::Fuselage::AftClamshellDoor  ; break;
            case AircraftData::Fuselage::TwoSideAndAftDoor : _data.fuselage.cargo_door = AircraftData::Fuselage::TwoSideAndAftDoor ; break;
        }

        _data.fuselage.l = nodeFuseL.text().toDouble();
        _data.fuselage.h = nodeFuseH.text().toDouble();
        _data.fuselage.w = nodeFuseW.text().toDouble();

        _data.fuselage.l_n = nodeNoseL.text().toDouble();

        _data.fuselage.wetted_area  = nodeWettedArea .text().toDouble();
        _data.fuselage.press_vol    = nodePressVol   .text().toDouble();
        _data.fuselage.landing_gear = nodeFuselageLG .text().toInt();
        _data.fuselage.cargo_ramp   = nodeCargoRamp  .text().toInt();
        _data.fuselage.wetted_area_override = nodeWettedAreaOverride.text().toInt();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readDataWing( QDomElement *parentNode )
{
    QDomElement nodeWingArea     = parentNode->firstChildElement( "area"      );
    QDomElement nodeWingAreaExp  = parentNode->firstChildElement( "area_exp"  );
    QDomElement nodeWingSpan     = parentNode->firstChildElement( "span"      );
    QDomElement nodeWingSweep    = parentNode->firstChildElement( "sweep"     );
    QDomElement nodeWingCTip     = parentNode->firstChildElement( "c_tip"     );
    QDomElement nodeWingCRoot    = parentNode->firstChildElement( "c_root"    );
    QDomElement nodeWingAR       = parentNode->firstChildElement( "ar"        );
    QDomElement nodeWingTR       = parentNode->firstChildElement( "tr"        );
    QDomElement nodeWingTC       = parentNode->firstChildElement( "t_c"       );
    QDomElement nodeWingFuel     = parentNode->firstChildElement( "fuel"      );
    QDomElement nodeCtrlArea     = parentNode->firstChildElement( "ctrl_area" );
    QDomElement nodeWingDelta    = parentNode->firstChildElement( "delta"     );
    QDomElement nodeWingVarSweep = parentNode->firstChildElement( "var_sweep" );

    if (   !nodeWingArea     .isNull()
        && !nodeWingAreaExp  .isNull()
        && !nodeWingSpan     .isNull()
        && !nodeWingSweep    .isNull()
        && !nodeWingCTip     .isNull()
        && !nodeWingCRoot    .isNull()
        && !nodeWingAR       .isNull()
        && !nodeWingTR       .isNull()
        && !nodeWingTC       .isNull()
        && !nodeWingFuel     .isNull()
        && !nodeCtrlArea     .isNull()
        && !nodeWingDelta    .isNull()
        && !nodeWingVarSweep .isNull()
       )
    {
        _data.wing.area      = nodeWingArea     .text().toDouble();
        _data.wing.area_exp  = nodeWingAreaExp  .text().toDouble();
        _data.wing.span      = nodeWingSpan     .text().toDouble();
        _data.wing.sweep     = nodeWingSweep    .text().toDouble();
        _data.wing.c_tip     = nodeWingCTip     .text().toDouble();
        _data.wing.c_root    = nodeWingCRoot    .text().toDouble();
        _data.wing.ar        = nodeWingAR       .text().toDouble();
        _data.wing.tr        = nodeWingTR       .text().toDouble();
        _data.wing.t_c       = nodeWingTC       .text().toDouble();
        _data.wing.fuel      = nodeWingFuel     .text().toDouble();
        _data.wing.ctrl_area = nodeCtrlArea     .text().toDouble();
        _data.wing.delta     = nodeWingDelta    .text().toInt();
        _data.wing.var_sweep = nodeWingVarSweep .text().toInt();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readDataHorTail( QDomElement *parentNode )
{
    QDomElement nodeHorTailArea    = parentNode->firstChildElement( "area"      );
    QDomElement nodeHorTailSpan    = parentNode->firstChildElement( "span"      );
    QDomElement nodeHorTailSweep   = parentNode->firstChildElement( "sweep"     );
    QDomElement nodeHorTailCTip    = parentNode->firstChildElement( "c_tip"     );
    QDomElement nodeHorTailCRoot   = parentNode->firstChildElement( "c_root"    );
    QDomElement nodeHorTailTC      = parentNode->firstChildElement( "t_c"       );
    QDomElement nodeElevArea       = parentNode->firstChildElement( "elev_area" );
    QDomElement nodeHorTailWF      = parentNode->firstChildElement( "w_f"       );
    QDomElement nodeHorTailArm     = parentNode->firstChildElement( "arm"       );
    QDomElement nodeHorTailAR      = parentNode->firstChildElement( "ar"        );
    QDomElement nodeHorTailTR      = parentNode->firstChildElement( "tr"        );
    QDomElement nodeHorTailMoving  = parentNode->firstChildElement( "moving"    );
    QDomElement nodeHorTailRolling = parentNode->firstChildElement( "rolling"   );

    if (   !nodeHorTailArea    .isNull()
        && !nodeHorTailSpan    .isNull()
        && !nodeHorTailSweep   .isNull()
        && !nodeHorTailCTip    .isNull()
        && !nodeHorTailCRoot   .isNull()
        && !nodeHorTailTC      .isNull()
        && !nodeElevArea       .isNull()
        && !nodeHorTailWF      .isNull()
        && !nodeHorTailArm     .isNull()
        && !nodeHorTailAR      .isNull()
        && !nodeHorTailTR      .isNull()
        && !nodeHorTailMoving  .isNull()
        && !nodeHorTailRolling .isNull()
       )
    {
        _data.hor_tail.area      = nodeHorTailArea   .text().toDouble();
        _data.hor_tail.span      = nodeHorTailSpan   .text().toDouble();
        _data.hor_tail.sweep     = nodeHorTailSweep  .text().toDouble();
        _data.hor_tail.c_tip     = nodeHorTailCTip   .text().toDouble();
        _data.hor_tail.c_root    = nodeHorTailCRoot  .text().toDouble();
        _data.hor_tail.t_c       = nodeHorTailTC     .text().toDouble();
        _data.hor_tail.elev_area = nodeElevArea      .text().toDouble();
        _data.hor_tail.w_f       = nodeHorTailWF     .text().toDouble();
        _data.hor_tail.arm       = nodeHorTailArm    .text().toDouble();
        _data.hor_tail.ar        = nodeHorTailAR     .text().toDouble();
        _data.hor_tail.tr        = nodeHorTailTR     .text().toDouble();

        _data.hor_tail.moving  = nodeHorTailMoving  .text().toInt();
        _data.hor_tail.rolling = nodeHorTailRolling .text().toInt();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readDataVerTail( QDomElement *parentNode )
{
    QDomElement nodeVerTailArea   = parentNode->firstChildElement( "area"      );
    QDomElement nodeVerTailHeight = parentNode->firstChildElement( "height"    );
    QDomElement nodeVerTailSweep  = parentNode->firstChildElement( "sweep"     );
    QDomElement nodeVerTailCTip   = parentNode->firstChildElement( "c_tip"     );
    QDomElement nodeVerTailCRoot  = parentNode->firstChildElement( "c_root"    );
    QDomElement nodeVerTailTC     = parentNode->firstChildElement( "t_c"       );
    QDomElement nodeVerTailArm    = parentNode->firstChildElement( "arm"       );
    QDomElement nodeRuddArea      = parentNode->firstChildElement( "rudd_area" );
    QDomElement nodeVerTailAR     = parentNode->firstChildElement( "ar"        );
    QDomElement nodeVerTailTR     = parentNode->firstChildElement( "tr"        );
    QDomElement nodeTailT         = parentNode->firstChildElement( "t_tail"    );
    QDomElement nodeVerTailRotor  = parentNode->firstChildElement( "rotor"     );

    if (   !nodeVerTailArea   .isNull()
        && !nodeVerTailHeight .isNull()
        && !nodeVerTailSweep  .isNull()
        && !nodeVerTailCTip   .isNull()
        && !nodeVerTailCRoot  .isNull()
        && !nodeVerTailTC     .isNull()
        && !nodeVerTailArm    .isNull()
        && !nodeRuddArea      .isNull()
        && !nodeVerTailAR     .isNull()
        && !nodeVerTailTR     .isNull()
        && !nodeTailT         .isNull()
        && !nodeVerTailRotor  .isNull()
       )
    {
        _data.ver_tail.area      = nodeVerTailArea   .text().toDouble();
        _data.ver_tail.height    = nodeVerTailHeight .text().toDouble();
        _data.ver_tail.sweep     = nodeVerTailSweep  .text().toDouble();
        _data.ver_tail.c_tip     = nodeVerTailCTip   .text().toDouble();
        _data.ver_tail.c_root    = nodeVerTailCRoot  .text().toDouble();
        _data.ver_tail.t_c       = nodeVerTailTC     .text().toDouble();
        _data.ver_tail.arm       = nodeVerTailArm    .text().toDouble();
        _data.ver_tail.rudd_area = nodeRuddArea      .text().toDouble();
        _data.ver_tail.ar        = nodeVerTailAR     .text().toDouble();
        _data.ver_tail.tr        = nodeVerTailTR     .text().toDouble();

        _data.ver_tail.t_tail = nodeTailT.text().toInt();

        _data.ver_tail.rotor = nodeVerTailRotor.text().toInt();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readDataLandingGear( QDomElement *parentNode )
{
    QDomElement nodeMainGearL      = parentNode->firstChildElement( "main_gear_l"      );
    QDomElement nodeNoseGearL      = parentNode->firstChildElement( "nose_gear_l"      );
    QDomElement nodeMainGearWheels = parentNode->firstChildElement( "main_gear_wheels" );
    QDomElement nodeMainGearStruts = parentNode->firstChildElement( "main_gear_struts" );
    QDomElement nodeNoseGearWheels = parentNode->firstChildElement( "nose_gear_wheels" );
    QDomElement nodeGearFixed      = parentNode->firstChildElement( "fixed"            );
    QDomElement nodeGearCross      = parentNode->firstChildElement( "cross"            );
    QDomElement nodeGearTripod     = parentNode->firstChildElement( "tripod"           );
    QDomElement nodeMainGearKneel  = parentNode->firstChildElement( "main_gear_kneel"  );
    QDomElement nodeNoseGearKneel  = parentNode->firstChildElement( "nose_gear_kneel"  );

    if (   !nodeMainGearL      .isNull()
        && !nodeNoseGearL      .isNull()
        && !nodeMainGearWheels .isNull()
        && !nodeMainGearStruts .isNull()
        && !nodeNoseGearWheels .isNull()
        && !nodeGearFixed      .isNull()
        && !nodeGearCross      .isNull()
        && !nodeGearTripod     .isNull()
        && !nodeMainGearKneel  .isNull()
        && !nodeNoseGearKneel  .isNull()
       )
    {
        _data.landing_gear.main_l      = nodeMainGearL      .text().toDouble();
        _data.landing_gear.nose_l      = nodeNoseGearL      .text().toDouble();
        _data.landing_gear.main_wheels = nodeMainGearWheels .text().toInt();
        _data.landing_gear.main_struts = nodeMainGearStruts .text().toInt();
        _data.landing_gear.nose_wheels = nodeNoseGearWheels .text().toInt();
        _data.landing_gear.fixed       = nodeGearFixed      .text().toInt();
        _data.landing_gear.cross       = nodeGearCross      .text().toInt();
        _data.landing_gear.tripod      = nodeGearTripod     .text().toInt();
        _data.landing_gear.main_kneel  = nodeMainGearKneel  .text().toInt();
        _data.landing_gear.nose_kneel  = nodeNoseGearKneel  .text().toInt();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readDataEngine( QDomElement *parentNode )
{
    QDomElement nodeEngineMass = parentNode->firstChildElement( "mass" );

    if ( !nodeEngineMass .isNull() )
    {
        _data.engine.mass = nodeEngineMass.text().toDouble();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readDataRotors( QDomElement *parentNode )
{
    QDomElement nodeMainRotorR      = parentNode->firstChildElement( "main_rotor_radius"      );
    QDomElement nodeMainRotorCB     = parentNode->firstChildElement( "main_rotor_blade_chord" );
    QDomElement nodeMainRotorRPM    = parentNode->firstChildElement( "main_rotor_rpm"         );
    QDomElement nodeMainRotorGR     = parentNode->firstChildElement( "main_rotor_gear_ratio"  );
    QDomElement nodeTailRotorR      = parentNode->firstChildElement( "tail_rotor_radius"      );
    QDomElement nodePowerLimit      = parentNode->firstChildElement( "mcp"                    );
    QDomElement nodeMainRotorTipVel = parentNode->firstChildElement( "main_rotor_tip_vel"     );
    QDomElement nodeMainRotorBlades = parentNode->firstChildElement( "main_rotor_blades"      );

    if (   !nodeMainRotorR      .isNull()
        && !nodeMainRotorCB     .isNull()
        && !nodeMainRotorRPM    .isNull()
        && !nodeMainRotorGR     .isNull()
        && !nodeTailRotorR      .isNull()
        && !nodePowerLimit      .isNull()
        && !nodeMainRotorTipVel .isNull()
        && !nodeMainRotorBlades .isNull()
       )
    {
        _data.rotors.main_r          = nodeMainRotorR      .text().toDouble();
        _data.rotors.main_cb         = nodeMainRotorCB     .text().toDouble();
        _data.rotors.main_rpm        = nodeMainRotorRPM    .text().toDouble();
        _data.rotors.main_gear_ratio = nodeMainRotorGR     .text().toDouble();
        _data.rotors.tail_r          = nodeTailRotorR      .text().toDouble();
        _data.rotors.mcp             = nodePowerLimit      .text().toDouble();
        _data.rotors.main_tip_vel    = nodeMainRotorTipVel .text().toDouble();

        _data.rotors.main_blades = nodeMainRotorBlades.text().toInt();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::readComponents( QDomElement *componentsNode )
{
    QDomElement nodeComponent = componentsNode->firstChildElement();

    while ( !nodeComponent.isNull() )
    {
        Component *temp = nullptr;

        if      ( nodeComponent.tagName() == AllElse::xmlTagName )
        {
            temp = new AllElse( &_data );
        }
        else if ( nodeComponent.tagName() == Engine::xmlTagName )
        {
            temp = new Engine( &_data );
        }
        else if ( nodeComponent.tagName() == Fuselage::xmlTagName )
        {
            temp = new Fuselage( &_data );
        }
        else if ( nodeComponent.tagName() == GearMain::xmlTagName )
        {
            temp = new GearMain( &_data );
        }
        else if ( nodeComponent.tagName() == GearNose::xmlTagName )
        {
            temp = new GearNose( &_data );
        }
        else if ( nodeComponent.tagName() == RotorDrive::xmlTagName )
        {
            temp = new RotorDrive( &_data );
        }
        else if ( nodeComponent.tagName() == RotorHub::xmlTagName )
        {
            temp = new RotorHub( &_data );
        }
        else if ( nodeComponent.tagName() == RotorMain::xmlTagName )
        {
            temp = new RotorMain( &_data );
        }
        else if ( nodeComponent.tagName() == RotorTail::xmlTagName )
        {
            temp = new RotorTail( &_data );
        }
        else if ( nodeComponent.tagName() == TailHor::xmlTagName )
        {
            temp = new TailHor( &_data );
        }
        else if ( nodeComponent.tagName() == TailVer::xmlTagName )
        {
            temp = new TailVer( &_data );
        }
        else if ( nodeComponent.tagName() == Wing::xmlTagName )
        {
            temp = new Wing( &_data );
        }

        if ( temp )
        {
            temp->read( &nodeComponent );
            _components.push_back( temp );
        }

        nodeComponent = nodeComponent.nextSiblingElement();
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::saveDataGeneral( QDomDocument *doc, QDomElement *parentNode )
{
    XmlUtils::saveTextNode( doc, parentNode, "m_empty"     , _data.general.m_empty    );
    XmlUtils::saveTextNode( doc, parentNode, "mtow"        , _data.general.mtow       );
    XmlUtils::saveTextNode( doc, parentNode, "m_max_land"  , _data.general.m_maxLand  );
    XmlUtils::saveTextNode( doc, parentNode, "nz_max"      , _data.general.nz_max     );
    XmlUtils::saveTextNode( doc, parentNode, "nz_max_land" , _data.general.nz_maxLand );
    XmlUtils::saveTextNode( doc, parentNode, "stall_v"     , _data.general.v_stall    );
    XmlUtils::saveTextNode( doc, parentNode, "h_cruise"    , _data.general.h_cruise   );
    XmlUtils::saveTextNode( doc, parentNode, "v_cruise"    , _data.general.v_cruise   );
    XmlUtils::saveTextNode( doc, parentNode, "mach_max"    , _data.general.mach_max   );

    XmlUtils::saveTextNode( doc, parentNode, "navy_ac", _data.general.navy_ac );
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::saveDataFuselage( QDomDocument *doc, QDomElement *parentNode )
{
    XmlUtils::saveTextNode( doc, parentNode, "cargo_door" , QString::number( _data.fuselage.cargo_door ) );

    XmlUtils::saveTextNode( doc, parentNode, "lenght" , _data.fuselage.l );
    XmlUtils::saveTextNode( doc, parentNode, "height" , _data.fuselage.h );
    XmlUtils::saveTextNode( doc, parentNode, "width"  , _data.fuselage.w );

    XmlUtils::saveTextNode( doc, parentNode, "nose_length" , _data.fuselage.l_n );

    XmlUtils::saveTextNode( doc, parentNode, "wetted_area"  , _data.fuselage.wetted_area  );
    XmlUtils::saveTextNode( doc, parentNode, "press_vol"    , _data.fuselage.press_vol    );
    XmlUtils::saveTextNode( doc, parentNode, "landing_gear" , _data.fuselage.landing_gear );
    XmlUtils::saveTextNode( doc, parentNode, "cargo_ramp"   , _data.fuselage.cargo_ramp   );

    XmlUtils::saveTextNode( doc, parentNode, "wetted_area_override", _data.fuselage.wetted_area_override );
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::saveDataWing( QDomDocument *doc, QDomElement *parentNode )
{
    XmlUtils::saveTextNode( doc, parentNode, "area"      , _data.wing.area      );
    XmlUtils::saveTextNode( doc, parentNode, "area_exp"  , _data.wing.area_exp  );
    XmlUtils::saveTextNode( doc, parentNode, "span"      , _data.wing.span      );
    XmlUtils::saveTextNode( doc, parentNode, "sweep"     , _data.wing.sweep     );
    XmlUtils::saveTextNode( doc, parentNode, "c_tip"     , _data.wing.c_tip     );
    XmlUtils::saveTextNode( doc, parentNode, "c_root"    , _data.wing.c_root    );
    XmlUtils::saveTextNode( doc, parentNode, "ar"        , _data.wing.ar        );
    XmlUtils::saveTextNode( doc, parentNode, "tr"        , _data.wing.tr        );
    XmlUtils::saveTextNode( doc, parentNode, "t_c"       , _data.wing.t_c       );
    XmlUtils::saveTextNode( doc, parentNode, "fuel"      , _data.wing.fuel      );
    XmlUtils::saveTextNode( doc, parentNode, "ctrl_area" , _data.wing.ctrl_area );
    XmlUtils::saveTextNode( doc, parentNode, "delta"     , _data.wing.delta     );
    XmlUtils::saveTextNode( doc, parentNode, "var_sweep" , _data.wing.var_sweep );
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::saveDataHorTail( QDomDocument *doc, QDomElement *parentNode )
{
    XmlUtils::saveTextNode( doc, parentNode, "area"      , _data.hor_tail.area      );
    XmlUtils::saveTextNode( doc, parentNode, "span"      , _data.hor_tail.span      );
    XmlUtils::saveTextNode( doc, parentNode, "sweep"     , _data.hor_tail.sweep     );
    XmlUtils::saveTextNode( doc, parentNode, "c_tip"     , _data.hor_tail.c_tip     );
    XmlUtils::saveTextNode( doc, parentNode, "c_root"    , _data.hor_tail.c_root    );
    XmlUtils::saveTextNode( doc, parentNode, "t_c"       , _data.hor_tail.t_c       );
    XmlUtils::saveTextNode( doc, parentNode, "elev_area" , _data.hor_tail.elev_area );
    XmlUtils::saveTextNode( doc, parentNode, "w_f"       , _data.hor_tail.w_f       );
    XmlUtils::saveTextNode( doc, parentNode, "arm"       , _data.hor_tail.arm       );
    XmlUtils::saveTextNode( doc, parentNode, "ar"        , _data.hor_tail.ar        );
    XmlUtils::saveTextNode( doc, parentNode, "tr"        , _data.hor_tail.tr        );

    XmlUtils::saveTextNode( doc, parentNode, "moving"  , _data.hor_tail.moving  );
    XmlUtils::saveTextNode( doc, parentNode, "rolling" , _data.hor_tail.rolling );
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::saveDataVerTail( QDomDocument *doc, QDomElement *parentNode )
{
    XmlUtils::saveTextNode( doc, parentNode, "area"      , _data.ver_tail.area      );
    XmlUtils::saveTextNode( doc, parentNode, "height"    , _data.ver_tail.height    );
    XmlUtils::saveTextNode( doc, parentNode, "sweep"     , _data.ver_tail.sweep     );
    XmlUtils::saveTextNode( doc, parentNode, "c_tip"     , _data.ver_tail.c_tip     );
    XmlUtils::saveTextNode( doc, parentNode, "c_root"    , _data.ver_tail.c_root    );
    XmlUtils::saveTextNode( doc, parentNode, "t_c"       , _data.ver_tail.t_c       );
    XmlUtils::saveTextNode( doc, parentNode, "arm"       , _data.ver_tail.arm       );
    XmlUtils::saveTextNode( doc, parentNode, "rudd_area" , _data.ver_tail.rudd_area );
    XmlUtils::saveTextNode( doc, parentNode, "ar"        , _data.ver_tail.ar        );
    XmlUtils::saveTextNode( doc, parentNode, "tr"        , _data.ver_tail.tr        );

    XmlUtils::saveTextNode( doc, parentNode, "t_tail", _data.ver_tail.t_tail );

    XmlUtils::saveTextNode( doc, parentNode, "rotor", _data.ver_tail.rotor );
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::saveDataLandingGear( QDomDocument *doc, QDomElement *parentNode )
{
    XmlUtils::saveTextNode( doc, parentNode, "main_gear_l"      , _data.landing_gear.main_l      );
    XmlUtils::saveTextNode( doc, parentNode, "nose_gear_l"      , _data.landing_gear.nose_l      );
    XmlUtils::saveTextNode( doc, parentNode, "main_gear_wheels" , _data.landing_gear.main_wheels );
    XmlUtils::saveTextNode( doc, parentNode, "main_gear_struts" , _data.landing_gear.main_struts );
    XmlUtils::saveTextNode( doc, parentNode, "nose_gear_wheels" , _data.landing_gear.nose_wheels );
    XmlUtils::saveTextNode( doc, parentNode, "fixed"            , _data.landing_gear.fixed       );
    XmlUtils::saveTextNode( doc, parentNode, "cross"            , _data.landing_gear.cross       );
    XmlUtils::saveTextNode( doc, parentNode, "tripod"           , _data.landing_gear.tripod      );
    XmlUtils::saveTextNode( doc, parentNode, "main_gear_kneel"  , _data.landing_gear.main_kneel  );
    XmlUtils::saveTextNode( doc, parentNode, "nose_gear_kneel"  , _data.landing_gear.nose_kneel  );
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::saveDataEngine( QDomDocument *doc, QDomElement *parentNode )
{
    XmlUtils::saveTextNode( doc, parentNode, "mass"  , _data.engine.mass );
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::saveDataRotors( QDomDocument *doc, QDomElement *parentNode )
{
    XmlUtils::saveTextNode( doc, parentNode, "main_rotor_radius"      , _data.rotors.main_r          );
    XmlUtils::saveTextNode( doc, parentNode, "main_rotor_blade_chord" , _data.rotors.main_cb         );
    XmlUtils::saveTextNode( doc, parentNode, "main_rotor_rpm"         , _data.rotors.main_rpm        );
    XmlUtils::saveTextNode( doc, parentNode, "main_rotor_gear_ratio"  , _data.rotors.main_gear_ratio );
    XmlUtils::saveTextNode( doc, parentNode, "tail_rotor_radius"      , _data.rotors.tail_r          );
    XmlUtils::saveTextNode( doc, parentNode, "mcp"                    , _data.rotors.mcp             );
    XmlUtils::saveTextNode( doc, parentNode, "main_rotor_tip_vel"     , _data.rotors.main_tip_vel    );

    XmlUtils::saveTextNode( doc, parentNode, "main_rotor_blades", _data.rotors.main_blades );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
