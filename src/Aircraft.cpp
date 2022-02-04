/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 ******************************************************************************/

#include <Aircraft.h>

#include <iomanip>
#include <sstream>

#include <components/AllElse.h>
#include <components/Engine.h>
#include <components/Fuselage.h>
#include <components/GearMain.h>
#include <components/GearNose.h>
#include <components/RotorDrive.h>
#include <components/RotorHub.h>
#include <components/RotorMain.h>
#include <components/RotorTail.h>
#include <components/TailHor.h>
#include <components/TailVer.h>
#include <components/Wing.h>

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

        QDomElement nodeData = parentNode->firstChildElement( "data" );
        QDomElement nodeComponents = parentNode->firstChildElement( "components" );

        if ( !nodeData.isNull() && !nodeComponents.isNull() )
        {
            // data
            QDomElement nodeM_empty   = nodeData.firstChildElement( "m_empty"     );
            QDomElement nodeMTOW      = nodeData.firstChildElement( "m_max_to"    );
            QDomElement nodeM_maxLand = nodeData.firstChildElement( "m_max_land"  );
            QDomElement nodeNzMax     = nodeData.firstChildElement( "nz_max"      );
            QDomElement nodeNzMaxLand = nodeData.firstChildElement( "nz_max_land" );
            QDomElement nodeStallV    = nodeData.firstChildElement( "stall_v"     );
            QDomElement nodeCruiseH   = nodeData.firstChildElement( "h_cruise"    );
            QDomElement nodeCruiseV   = nodeData.firstChildElement( "v_cruise"    );
            QDomElement nodeMachMax   = nodeData.firstChildElement( "mach_max"    );
            QDomElement nodeNavyAC    = nodeData.firstChildElement( "navy_ac"     );

            QDomElement nodeCargoDoor  = nodeData.firstChildElement( "cargo_door"  );
            QDomElement nodeFuseL      = nodeData.firstChildElement( "fuse_l"      );
            QDomElement nodeFuseH      = nodeData.firstChildElement( "fuse_h"      );
            QDomElement nodeFuseW      = nodeData.firstChildElement( "fuse_w"      );
            QDomElement nodeNoseL      = nodeData.firstChildElement( "nose_l"      );
            QDomElement nodeWettedArea = nodeData.firstChildElement( "wetted_area" );
            QDomElement nodePressVol   = nodeData.firstChildElement( "press_vol"   );
            QDomElement nodeFuselageLG = nodeData.firstChildElement( "fuselage_lg" );
            QDomElement nodeCargoRamp  = nodeData.firstChildElement( "cargo_ramp"  );

            QDomElement nodeWingArea  = nodeData.firstChildElement( "wing_area"  );
            QDomElement nodeWingExp   = nodeData.firstChildElement( "wing_exp"   );
            QDomElement nodeWingSpan  = nodeData.firstChildElement( "wing_span"  );
            QDomElement nodeWingSweep = nodeData.firstChildElement( "wing_sweep" );
            QDomElement nodeWingCT    = nodeData.firstChildElement( "wing_c_t"   );
            QDomElement nodeWingCR    = nodeData.firstChildElement( "wing_c_r"   );
            QDomElement nodeWingAR    = nodeData.firstChildElement( "wing_ar"    );
            QDomElement nodeWingTR    = nodeData.firstChildElement( "wing_tr"    );
            QDomElement nodeWingTC    = nodeData.firstChildElement( "wing_tc"    );
            QDomElement nodeWingFule  = nodeData.firstChildElement( "wing_fuel"  );
            QDomElement nodeCtrlArea  = nodeData.firstChildElement( "ctrl_area"  );
            QDomElement nodeWingDelta = nodeData.firstChildElement( "wing_delta" );
            QDomElement nodeWingVar   = nodeData.firstChildElement( "wing_var"   );

            QDomElement nodeHorTailArea  = nodeData.firstChildElement( "h_tail_area"    );
            QDomElement nodeHorTailSpan  = nodeData.firstChildElement( "h_tail_span"    );
            QDomElement nodeHorTailSweep = nodeData.firstChildElement( "h_tail_sweep"   );
            QDomElement nodeHorTailCT    = nodeData.firstChildElement( "h_tail_c_t"     );
            QDomElement nodeHorTailCR    = nodeData.firstChildElement( "h_tail_c_r"     );
            QDomElement nodeHorTailTC    = nodeData.firstChildElement( "h_tail_tc"      );
            QDomElement nodeElevArea     = nodeData.firstChildElement( "elev_area"      );
            QDomElement nodeHorTailFW    = nodeData.firstChildElement( "h_tail_fw"      );
            QDomElement nodeHorTailArm   = nodeData.firstChildElement( "h_tail_arm"     );
            QDomElement nodeHorTailAR    = nodeData.firstChildElement( "h_tail_ar"      );
            QDomElement nodeHorTailTR    = nodeData.firstChildElement( "h_tail_tr"      );
            QDomElement nodeHorTailMoving  = nodeData.firstChildElement( "h_tail_moving"  );
            QDomElement nodeHorTailRolling = nodeData.firstChildElement( "h_tail_rolling" );

            QDomElement nodeVerTailArea   = nodeData.firstChildElement( "v_tail_area"   );
            QDomElement nodeVerTailHeight = nodeData.firstChildElement( "v_tail_height"  );
            QDomElement nodeVerTailSweep  = nodeData.firstChildElement( "v_tail_sweep"   );
            QDomElement nodeVerTailCT     = nodeData.firstChildElement( "v_tail_c_t"     );
            QDomElement nodeVerTailCR     = nodeData.firstChildElement( "v_tail_c_r"     );
            QDomElement nodeVerTailTC     = nodeData.firstChildElement( "v_tail_tc"      );
            QDomElement nodeVerTailArm    = nodeData.firstChildElement( "v_tail_arm"     );
            QDomElement nodeRuddArea      = nodeData.firstChildElement( "rudd_area"      );
            QDomElement nodeVerTailAR     = nodeData.firstChildElement( "v_tail_ar"      );
            QDomElement nodeVerTailTR     = nodeData.firstChildElement( "v_tail_tr"      );
            QDomElement nodeTailT         = nodeData.firstChildElement( "t_tail" );
            QDomElement nodeVerTailRotor  = nodeData.firstChildElement( "v_tail_rotor" );

            QDomElement nodeMainGearL      = nodeData.firstChildElement( "m_gear_l"      );
            QDomElement nodeNoseGearL      = nodeData.firstChildElement( "n_gear_l"      );
            QDomElement nodeMainGearWheels = nodeData.firstChildElement( "m_gear_wheels" );
            QDomElement nodeMainGearStruts = nodeData.firstChildElement( "m_gear_struts" );
            QDomElement nodeNoseGearWheels = nodeData.firstChildElement( "n_gear_wheels" );
            QDomElement nodeGearFixed      = nodeData.firstChildElement( "gear_fixed"    );
            QDomElement nodeGearCross      = nodeData.firstChildElement( "gear_cross"    );
            QDomElement nodeGearTripod     = nodeData.firstChildElement( "gear_tripod"   );
            QDomElement nodeMainGearKneel  = nodeData.firstChildElement( "m_gear_kneel"  );
            QDomElement nodeNoseGearKneel  = nodeData.firstChildElement( "n_gear_kneel"  );

            QDomElement nodeM_engine = nodeData.firstChildElement( "m_engine" );

            QDomElement nodeMainRotorRad    = nodeData.firstChildElement( "m_rotor_r"    );
            QDomElement nodeMainRotorChord  = nodeData.firstChildElement( "m_blades_c"   );
            QDomElement nodeMainRotorRPM    = nodeData.firstChildElement( "m_rotor_rpm"  );
            QDomElement nodeMainRotorGear   = nodeData.firstChildElement( "m_rotor_gear" );
            QDomElement nodeTailRotorRad    = nodeData.firstChildElement( "t_rotor_r"    );
            QDomElement nodePowerLimit      = nodeData.firstChildElement( "rotor_mcp"    );
            QDomElement nodeMainRotorTipVel = nodeData.firstChildElement( "m_rotor_tv"   );
            QDomElement nodeMainRotorBlades = nodeData.firstChildElement( "m_rotor_nb"   );

            if ( !nodeM_empty   .isNull()
              && !nodeMTOW      .isNull()
              && !nodeM_maxLand .isNull()
              && !nodeNzMax     .isNull()
              && !nodeNzMaxLand .isNull()
              && !nodeStallV    .isNull()
              && !nodeCruiseH   .isNull()
              && !nodeCruiseV   .isNull()
              && !nodeMachMax   .isNull()
              && !nodeNavyAC    .isNull()

              && !nodeCargoDoor  .isNull()
              && !nodeFuseL      .isNull()
              && !nodeFuseH      .isNull()
              && !nodeFuseW      .isNull()
              && !nodeNoseL      .isNull()
              && !nodeWettedArea .isNull()
              && !nodePressVol   .isNull()
              && !nodeFuselageLG .isNull()
              && !nodeCargoRamp  .isNull()

              && !nodeWingArea  .isNull()
              && !nodeWingExp   .isNull()
              && !nodeWingSpan  .isNull()
              && !nodeWingSweep .isNull()
              && !nodeWingCT    .isNull()
              && !nodeWingCR    .isNull()
              && !nodeWingAR    .isNull()
              && !nodeWingTR    .isNull()
              && !nodeWingTC    .isNull()
              && !nodeWingFule  .isNull()
              && !nodeCtrlArea  .isNull()
              && !nodeWingDelta .isNull()
              && !nodeWingVar   .isNull()

              && !nodeHorTailArea  .isNull()
              && !nodeHorTailSpan  .isNull()
              && !nodeHorTailSweep .isNull()
              && !nodeHorTailCT    .isNull()
              && !nodeHorTailCR    .isNull()
              && !nodeHorTailTC    .isNull()
              && !nodeElevArea     .isNull()
              && !nodeHorTailFW    .isNull()
              && !nodeHorTailArm   .isNull()
              && !nodeHorTailAR    .isNull()
              && !nodeHorTailTR    .isNull()
              && !nodeHorTailMoving  .isNull()
              && !nodeHorTailRolling .isNull()

              && !nodeVerTailArea   .isNull()
              && !nodeVerTailHeight .isNull()
              && !nodeVerTailSweep  .isNull()
              && !nodeVerTailCT     .isNull()
              && !nodeVerTailCR     .isNull()
              && !nodeVerTailTC     .isNull()
              && !nodeVerTailArm    .isNull()
              && !nodeRuddArea      .isNull()
              && !nodeVerTailAR     .isNull()
              && !nodeVerTailTR     .isNull()
              && !nodeTailT         .isNull()
              && !nodeVerTailRotor  .isNull()

              && !nodeMainGearL      .isNull()
              && !nodeNoseGearL      .isNull()
              && !nodeMainGearWheels .isNull()
              && !nodeMainGearStruts .isNull()
              && !nodeNoseGearWheels .isNull()
              && !nodeGearFixed      .isNull()
              && !nodeGearCross      .isNull()
              && !nodeGearTripod     .isNull()
              && !nodeMainGearKneel  .isNull()
              && !nodeNoseGearKneel  .isNull()

              && !nodeM_engine .isNull()

              && !nodeMainRotorRad    .isNull()
              && !nodeMainRotorChord  .isNull()
              && !nodeMainRotorRPM    .isNull()
              && !nodeMainRotorGear   .isNull()
              && !nodeTailRotorRad    .isNull()
              && !nodePowerLimit      .isNull()
              && !nodeMainRotorTipVel .isNull()
              && !nodeMainRotorBlades .isNull()
               )
            {
                // general
                _data.general.m_empty    = nodeM_empty   .text().toDouble();
                _data.general.mtow       = nodeMTOW      .text().toDouble();
                _data.general.m_maxLand  = nodeM_maxLand .text().toDouble();
                _data.general.nz_max     = nodeNzMax     .text().toDouble();
                _data.general.nz_maxLand = nodeNzMaxLand .text().toDouble();
                _data.general.stall_v    = nodeStallV    .text().toDouble();
                _data.general.h_cruise   = nodeCruiseH   .text().toDouble();
                _data.general.v_cruise   = nodeCruiseV   .text().toDouble();
                _data.general.mach_max   = nodeMachMax   .text().toDouble();

                _data.general.navy_ac = nodeNavyAC.text().toInt();

                // fuselage
                int cargo_door_temp = nodeCargoDoor.text().toInt();

                _data.fuselage.cargo_door = AircraftData::Fuselage::NoCargoDoors;

                switch ( cargo_door_temp )
                {
                    case AircraftData::Fuselage::NoCargoDoors       : _data.fuselage.cargo_door = AircraftData::Fuselage::NoCargoDoor       ; break;
                    case AircraftData::Fuselage::OneSideCargoDoors  : _data.fuselage.cargo_door = AircraftData::Fuselage::OneSideCargoDoor  ; break;
                    case AircraftData::Fuselage::TwoSideCargoDoors  : _data.fuselage.cargo_door = AircraftData::Fuselage::TwoSideCargoDoor  ; break;
                    case AircraftData::Fuselage::AftClamshellDoors  : _data.fuselage.cargo_door = AircraftData::Fuselage::AftClamshellDoor  ; break;
                    case AircraftData::Fuselage::TwoSideAndAftDoors : _data.fuselage.cargo_door = AircraftData::Fuselage::TwoSideAndAftDoor ; break;
                }

                _data.fuselage.l = nodeFuseL.text().toDouble();
                _data.fuselage.h = nodeFuseH.text().toDouble();
                _data.fuselage.w = nodeFuseW.text().toDouble();

                _data.fuselage.nl = nodeNoseL.text().toDouble();

                _data.fuselage.wetted_area = nodeWettedArea .text().toDouble();
                _data.fuselage.press_vol   = nodePressVol   .text().toDouble();
                _data.fuselage.mounted_lg  = nodeFuselageLG .text().toInt();
                _data.fuselage.cargo_ramp  = nodeCargoRamp  .text().toInt();

                // wing
                _wing_area  = nodeWingArea  .text().toDouble();
                _wing_exp   = nodeWingExp   .text().toDouble();
                _wing_span  = nodeWingSpan  .text().toDouble();
                _wing_sweep = nodeWingSweep .text().toDouble();
                _wing_c_t   = nodeWingCT    .text().toDouble();
                _wing_c_r   = nodeWingCR    .text().toDouble();
                _wing_ar    = nodeWingAR    .text().toDouble();
                _wing_tr    = nodeWingTR    .text().toDouble();
                _wing_tc    = nodeWingTC    .text().toDouble();
                _wing_fuel  = nodeWingFule  .text().toDouble();
                _ctrl_area  = nodeCtrlArea  .text().toDouble();
                _wing_delta = nodeWingDelta .text().toInt();
                _wing_var   = nodeWingVar   .text().toInt();

                // horizontal tail
                _h_tail_area  = nodeHorTailArea   .text().toDouble();
                _h_tail_span  = nodeHorTailSpan   .text().toDouble();
                _h_tail_sweep = nodeHorTailSweep  .text().toDouble();
                _h_tail_c_t   = nodeHorTailCT     .text().toDouble();
                _h_tail_c_r   = nodeHorTailCR     .text().toDouble();
                _h_tail_tc    = nodeHorTailTC     .text().toDouble();
                _elev_area    = nodeElevArea      .text().toDouble();
                _h_tail_fw    = nodeHorTailFW     .text().toDouble();
                _h_tail_arm   = nodeHorTailArm    .text().toDouble();
                _h_tail_ar    = nodeHorTailAR     .text().toDouble();
                _h_tail_tr    = nodeHorTailTR     .text().toDouble();

                _h_tail_moving  = nodeHorTailMoving  .text().toInt();
                _h_tail_rolling = nodeHorTailRolling .text().toInt();

                // vertical tail
                _v_tail_area   = nodeVerTailArea   .text().toDouble();
                _v_tail_height = nodeVerTailHeight .text().toDouble();
                _v_tail_sweep  = nodeVerTailSweep  .text().toDouble();
                _v_tail_c_t    = nodeVerTailCT     .text().toDouble();
                _v_tail_c_r    = nodeVerTailCR     .text().toDouble();
                _v_tail_tc     = nodeVerTailTC     .text().toDouble();
                _v_tail_arm    = nodeVerTailArm    .text().toDouble();
                _rudd_area     = nodeRuddArea      .text().toDouble();
                _v_tail_ar     = nodeVerTailAR     .text().toDouble();
                _v_tail_tr     = nodeVerTailTR     .text().toDouble();

                _t_tail = nodeTailT.text().toInt();

                _v_tail_rotor = nodeVerTailRotor.text().toInt();

                // landing gear
                _m_gear_l      = nodeMainGearL      .text().toDouble();
                _n_gear_l      = nodeNoseGearL      .text().toDouble();
                _m_gear_wheels = nodeMainGearWheels .text().toInt();
                _m_gear_struts = nodeMainGearStruts .text().toInt();
                _n_gear_wheels = nodeNoseGearWheels .text().toInt();
                _gear_fixed    = nodeGearFixed      .text().toInt();
                _gear_cross    = nodeGearCross      .text().toInt();
                _gear_tripod   = nodeGearTripod     .text().toInt();
                _m_gear_kneel  = nodeMainGearKneel  .text().toInt();
                _n_gear_kneel  = nodeNoseGearKneel  .text().toInt();

                // engine
                _m_engine = nodeM_engine.text().toDouble();

                // rotors
                _m_rotor_r    = nodeMainRotorRad    .text().toDouble();
                _m_blades_c   = nodeMainRotorChord  .text().toDouble();
                _m_rotor_rpm  = nodeMainRotorRPM    .text().toDouble();
                _m_rotor_gear = nodeMainRotorGear   .text().toDouble();
                _t_rotor_r    = nodeTailRotorRad    .text().toDouble();
                _rotor_mcp    = nodePowerLimit      .text().toDouble();
                _m_rotor_tv   = nodeMainRotorTipVel .text().toDouble();
                _m_rotor_nb   = nodeMainRotorBlades .text().toInt();

                // components
                QDomElement nodeComponent = nodeComponents.firstChildElement();

                while ( !nodeComponent.isNull() )
                {
                    Component *temp = NULLPTR;

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

                update();

                return true;
            }
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomAttr nodeType = doc->createAttribute( "type" );
    nodeType.setValue( QString::number( getType() ) );
    parentNode->setAttributeNode( nodeType );

    // data
    QDomElement nodeData = doc->createElement( "data" );
    parentNode->appendChild( nodeData );

    // data - general
    XmlUtils::saveTextNode( doc, &nodeData, "m_empty"     , _m_empty    );
    XmlUtils::saveTextNode( doc, &nodeData, "m_max_to"    , _m_maxTO    );
    XmlUtils::saveTextNode( doc, &nodeData, "m_max_land"  , _m_maxLand  );
    XmlUtils::saveTextNode( doc, &nodeData, "nz_max"      , _nz_max     );
    XmlUtils::saveTextNode( doc, &nodeData, "nz_max_land" , _nz_maxLand );
    XmlUtils::saveTextNode( doc, &nodeData, "stall_v"     , _stall_v    );
    XmlUtils::saveTextNode( doc, &nodeData, "h_cruise"    , _h_cruise   );
    XmlUtils::saveTextNode( doc, &nodeData, "v_cruise"    , _v_cruise   );
    XmlUtils::saveTextNode( doc, &nodeData, "mach_max"    , _mach_max   );

    XmlUtils::saveTextNode( doc, &nodeData, "navy_ac", _navy_ac );

    // data - fuselage
    XmlUtils::saveTextNode( doc, &nodeData, "cargo_door" , QString::number( _cargo_door ) );

    XmlUtils::saveTextNode( doc, &nodeData, "fuse_l" , _fuse_l );
    XmlUtils::saveTextNode( doc, &nodeData, "fuse_h" , _fuse_h );
    XmlUtils::saveTextNode( doc, &nodeData, "fuse_w" , _fuse_w );
    XmlUtils::saveTextNode( doc, &nodeData, "nose_l" , _nose_l );

    XmlUtils::saveTextNode( doc, &nodeData, "wetted_area" , _wetted_area );
    XmlUtils::saveTextNode( doc, &nodeData, "press_vol"   , _press_vol   );
    XmlUtils::saveTextNode( doc, &nodeData, "fuselage_lg" , _fuselage_lg );
    XmlUtils::saveTextNode( doc, &nodeData, "cargo_ramp"  , _cargo_ramp  );

    // data - wing
    XmlUtils::saveTextNode( doc, &nodeData, "wing_area"  , _wing_area  );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_exp"   , _wing_exp   );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_span"  , _wing_span  );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_sweep" , _wing_sweep );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_c_t"   , _wing_c_t   );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_c_r"   , _wing_c_r   );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_ar"    , _wing_ar    );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_tr"    , _wing_tr    );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_tc"    , _wing_tc    );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_fuel"  , _wing_fuel  );
    XmlUtils::saveTextNode( doc, &nodeData, "ctrl_area"  , _ctrl_area  );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_delta" , _wing_delta );
    XmlUtils::saveTextNode( doc, &nodeData, "wing_var"   , _wing_var   );

    // data - horizontal tail
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_area"  , _h_tail_area  );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_span"  , _h_tail_span  );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_sweep" , _h_tail_sweep );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_c_t"   , _h_tail_c_t   );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_c_r"   , _h_tail_c_r   );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_tc"    , _h_tail_tc    );
    XmlUtils::saveTextNode( doc, &nodeData, "elev_area"    , _elev_area    );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_fw"    , _h_tail_fw    );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_arm"   , _h_tail_arm   );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_ar"    , _h_tail_ar    );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_tr"    , _h_tail_tr    );

    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_moving"  , _h_tail_moving  );
    XmlUtils::saveTextNode( doc, &nodeData, "h_tail_rolling" , _h_tail_rolling );

    // data - vertical tail
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_area"   , _v_tail_area   );
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_height" , _v_tail_height );
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_sweep"  , _v_tail_sweep  );
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_c_t"    , _v_tail_c_t    );
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_c_r"    , _v_tail_c_r    );
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_tc"     , _v_tail_tc     );
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_arm"    , _v_tail_arm    );
    XmlUtils::saveTextNode( doc, &nodeData, "rudd_area"     , _rudd_area     );
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_ar"     , _v_tail_ar     );
    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_tr"     , _v_tail_tr     );

    XmlUtils::saveTextNode( doc, &nodeData, "t_tail", _t_tail );

    XmlUtils::saveTextNode( doc, &nodeData, "v_tail_rotor", _v_tail_rotor );

    // data - landing gear
    XmlUtils::saveTextNode( doc, &nodeData, "m_gear_l"      , _m_gear_l      );
    XmlUtils::saveTextNode( doc, &nodeData, "n_gear_l"      , _n_gear_l      );
    XmlUtils::saveTextNode( doc, &nodeData, "m_gear_wheels" , _m_gear_wheels );
    XmlUtils::saveTextNode( doc, &nodeData, "m_gear_struts" , _m_gear_struts );
    XmlUtils::saveTextNode( doc, &nodeData, "n_gear_wheels" , _n_gear_wheels );
    XmlUtils::saveTextNode( doc, &nodeData, "gear_fixed"    , _gear_fixed    );
    XmlUtils::saveTextNode( doc, &nodeData, "gear_cross"    , _gear_cross    );
    XmlUtils::saveTextNode( doc, &nodeData, "gear_tripod"   , _gear_tripod   );
    XmlUtils::saveTextNode( doc, &nodeData, "m_gear_kneel"  , _m_gear_kneel  );
    XmlUtils::saveTextNode( doc, &nodeData, "n_gear_kneel"  , _n_gear_kneel  );

    // data - engine
    XmlUtils::saveTextNode( doc, &nodeData, "m_engine"  , _m_engine );

    // rotors
    XmlUtils::saveTextNode( doc, &nodeData, "m_rotor_r"    , _m_rotor_r    );
    XmlUtils::saveTextNode( doc, &nodeData, "m_blades_c"   , _m_blades_c   );
    XmlUtils::saveTextNode( doc, &nodeData, "m_rotor_rpm"  , _m_rotor_rpm  );
    XmlUtils::saveTextNode( doc, &nodeData, "m_rotor_gear" , _m_rotor_gear );
    XmlUtils::saveTextNode( doc, &nodeData, "t_rotor_r"    , _t_rotor_r    );
    XmlUtils::saveTextNode( doc, &nodeData, "rotor_mcp"    , _rotor_mcp    );
    XmlUtils::saveTextNode( doc, &nodeData, "m_rotor_tv"   , _m_rotor_tv   );

    XmlUtils::saveTextNode( doc, &nodeData, "m_rotor_nb"  , _m_rotor_nb   );

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
    _type = FighterAttack;

    // general
    _m_empty    = 0.0;
    _m_maxTO    = 0.0;
    _m_maxLand  = 0.0;
    _nz_max     = 1.0;
    _nz_maxLand = 1.0;
    _stall_v    = 0.0;
    _h_cruise   = 0.0;
    _v_cruise   = 0.0;
    _mach_max   = 0.0;
    _navy_ac = false;

    // fuselage
    _cargo_door = NoCargoDoor;
    _fuse_l = 0.0;
    _fuse_h = 0.0;
    _fuse_w = 0.0;
    _nose_l = 0.0;
    _wetted_area = 0.0;
    _press_vol   = 0.0;
    _fuselage_lg = false;
    _cargo_ramp  = false;

    // wing
    _wing_area  = 0.0;
    _wing_exp   = 0.0;
    _wing_span  = 0.0;
    _wing_sweep = 0.0;
    _wing_c_t   = 0.0;
    _wing_c_r   = 0.0;
    _wing_ar    = 0.0;
    _wing_tr    = 0.0;
    _wing_tc    = 0.0;
    _wing_fuel  = 0.0;
    _ctrl_area  = 0.0;
    _wing_delta = false;
    _wing_var   = false;

    // horizontal tail
    _h_tail_area  = 0.0;
    _h_tail_span  = 0.0;
    _h_tail_sweep = 0.0;
    _h_tail_c_t   = 0.0;
    _h_tail_c_r   = 0.0;
    _h_tail_tc    = 0.0;
    _elev_area    = 0.0;
    _h_tail_fw    = 0.0;
    _h_tail_arm   = 0.0;
    _h_tail_ar    = 0.0;
    _h_tail_tr    = 0.0;
    _h_tail_moving  = false;
    _h_tail_rolling = false;

    // vertical tail
    _v_tail_area   = 0.0;
    _v_tail_height = 0.0;
    _v_tail_sweep  = 0.0;
    _v_tail_c_t    = 0.0;
    _v_tail_c_r    = 0.0;
    _v_tail_tc     = 0.0;
    _v_tail_arm    = 0.0;
    _rudd_area     = 0.0;
    _v_tail_ar     = 0.0;
    _v_tail_tr     = 0.0;
    _t_tail = false;
    _v_tail_rotor = false;

    // landing gear
    _m_gear_l = 0.0;
    _n_gear_l = 0.0;
    _m_gear_wheels = 0;
    _m_gear_struts = 0;
    _n_gear_wheels = 0;
    _gear_fixed   = false;
    _gear_cross   = false;
    _gear_tripod  = false;
    _m_gear_kneel = false;
    _n_gear_kneel = false;

    // engine
    _m_engine = 0.0;

    // rotors
    _m_rotor_r   = 0.0;
    _m_blades_c  = 0.0;
    _m_rotor_rpm = 0.0;
    _m_rotor_gear = 1.0;
    _t_rotor_r   = 0.0;
    _rotor_mcp   = 0.0;
    _m_rotor_tv  = 0.0;
    _m_rotor_nb = 0;

    // RESULTS
    _centerOfMass.set( 0.0, 0.0, 0.0 );

    _inertiaMatrix.set( 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0 );

    _massTotal = 0.0;

    deleteAllComponents();
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::update()
{
    double m = 0.0;
    Vector3 s;
    Matrix3x3 i;

    for ( Components::iterator it = _components.begin(); it != _components.end(); ++it )
    {
        m += (*it)->getMass();
        s += (*it)->getMass() * (*it)->getPosition();
        i += (*it)->getInertia();
    }

    _centerOfMass = ( m > 0.0 ) ? ( s * ( 1.0 / m ) ) : Vector3();
    _inertiaMatrix = i;
    _massTotal = m;
}

////////////////////////////////////////////////////////////////////////////////

Component* Aircraft::getComponent( int index )
{
    Components::iterator it = _components.begin() + index;

    if ( it != _components.end() )
    {
        return (*it);
    }

    return NULLPTR;
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

} // namespace mc
