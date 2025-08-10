/****************************************************************************//*
 *  Copyright (C) 2024 Marek M. Cel
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

#include <utils/units_extra.h>

#include <utils/ParallelAxisInertia.h>
#include <utils/XmlUtils.h>

using namespace units::literals;

template<typename ME, typename CG, typename IM>
std::string AircraftToString(ME me,
                             CG cg_x, CG cg_y, CG cg_z,
                             IM i_xx, IM i_xy, IM i_xz,
                             IM i_yx, IM i_yy, IM i_yz,
                             IM i_zx, IM i_zy, IM i_zz)
{
    auto me_abv = units::abbreviation(me);
    auto cg_abv = units::abbreviation(cg_x);
    auto im_abv = units::abbreviation(i_xx);

    std::stringstream ss;

    ss.setf(std::ios_base::showpoint);
    ss.setf(std::ios_base::fixed);

    ss << "empty mass [" << me_abv << "] : ";
    ss << std::setprecision(1) << me();
    ss << std::endl;

    ss << "center of mass [" << cg_abv << "] : ";
    ss << std::setfill(' ') << std::setw(8) << std::setprecision(2) << cg_x();
    ss << " ";
    ss << std::setfill(' ') << std::setw(8) << std::setprecision(2) << cg_y();
    ss << " ";
    ss << std::setfill(' ') << std::setw(8) << std::setprecision(2) << cg_z();
    ss << std::endl;

    ss << "moment of inertia [" << im_abv << "] : ";
    ss << std::endl;

    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_xx();
    ss << " ";
    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_xy();
    ss << " ";
    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_xz();
    ss << std::endl;

    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_yx();
    ss << " ";
    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_yy();
    ss << " ";
    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_yz();
    ss << std::endl;

    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_zx();
    ss << " ";
    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_zy();
    ss << " ";
    ss << std::setfill(' ') << std::setw(12) << std::setprecision(1) << i_zz();
    ss << std::endl;

    ss << std::endl;

    return ss.str();
}

Aircraft::Aircraft()
{
    reset();
}

Aircraft::~Aircraft()
{
    deleteAllComponents();
}

bool Aircraft::read(QDomElement* parentNode)
{
    if ( !parentNode->isNull() )
    {
        int type_temp = parentNode->attributeNode("type").value().toInt();

        _data.type = AircraftData::FighterAttack;

        switch ( type_temp )
        {
        case AircraftData::FighterAttack:
            _data.type = AircraftData::FighterAttack;
            break;
        case AircraftData::CargoTransport:
            _data.type = AircraftData::CargoTransport;
            break;
        case AircraftData::GeneralAviation:
            _data.type = AircraftData::GeneralAviation;
            break;
        case AircraftData::Helicopter:
            _data.type = AircraftData::Helicopter;
            break;
        }

        QDomElement dataNode = parentNode->firstChildElement("data");
        QDomElement componentsNode = parentNode->firstChildElement("components");

        if ( !dataNode.isNull() && !componentsNode.isNull() )
        {
            bool result = true;

            if ( result ) result = readData(&dataNode);
            if ( result ) result = readComponents(&componentsNode);

            if ( result ) update();

            return result;
        }
    }

    return false;
}

void Aircraft::save(QDomDocument* doc, QDomElement* parentNode)
{
    QDomAttr nodeType = doc->createAttribute("type");
    nodeType.setValue(QString::number(_data.type));
    parentNode->setAttributeNode(nodeType);

    // data
    QDomElement nodeData = doc->createElement("data");
    parentNode->appendChild(nodeData);

    // data - general
    QDomElement nodeGeneral = doc->createElement("general");
    nodeData.appendChild(nodeGeneral);
    saveDataGeneral(doc, &nodeGeneral);

    // data - fuselage
    QDomElement nodeFuselage = doc->createElement("fuselage");
    nodeData.appendChild(nodeFuselage);
    saveDataFuselage(doc, &nodeFuselage);

    // data - wing
    QDomElement nodeWing = doc->createElement("wing");
    nodeData.appendChild(nodeWing);
    saveDataWing(doc, &nodeWing);

    // data - horizontal tail
    QDomElement nodeHorTail = doc->createElement("hor_tail");
    nodeData.appendChild(nodeHorTail);
    saveDataHorTail(doc, &nodeHorTail);

    // data - vertical tail
    QDomElement nodeVerTail = doc->createElement("ver_tail");
    nodeData.appendChild(nodeVerTail);
    saveDataVerTail(doc, &nodeVerTail);

    // data - landing gear
    QDomElement nodeLandingGear = doc->createElement("landing_gear");
    nodeData.appendChild(nodeLandingGear);
    saveDataLandingGear(doc, &nodeLandingGear);

    // data - engine
    QDomElement nodeEngine = doc->createElement("engine");
    nodeData.appendChild(nodeEngine);
    saveDataEngine(doc, &nodeEngine);

    // rotors
    QDomElement nodeRotors = doc->createElement("rotors");
    nodeData.appendChild(nodeRotors);
    saveDataRotors(doc, &nodeRotors);

    // model 3D
    QDomElement nodeModel3D = doc->createElement("model3d");
    nodeData.appendChild(nodeModel3D);
    saveDataModel3D(doc, &nodeModel3D);

    // components
    QDomElement componentsNode = doc->createElement("components");
    parentNode->appendChild(componentsNode);

    for ( auto component : _components )
    {
        component->Save(doc, &componentsNode);
    }
}

void Aircraft::reset()
{
    _data.type = AircraftData::FighterAttack;

    // general
    _data.general.m_empty    = 0.0_kg;
    _data.general.mtow       = 0.0_kg;
    _data.general.m_maxLand  = 0.0_kg;
    _data.general.nz_max     = 1.0;
    _data.general.nz_maxLand = 1.0;
    _data.general.v_stall    = 0.0_kts;
    _data.general.h_cruise   = 0.0_ft;
    _data.general.v_cruise   = 0.0_kts;
    _data.general.mach_max   = 0.0;
    _data.general.navy_ac    = false;

    // fuselage
    _data.fuselage.cargo_door   = AircraftData::Fuselage::NoCargoDoor;
    _data.fuselage.l            = 0.0_m;
    _data.fuselage.h            = 0.0_m;
    _data.fuselage.w            = 0.0_m;
    _data.fuselage.l_n          = 0.0_m;
    _data.fuselage.wetted_area  = 0.0_sq_m;
    _data.fuselage.press_vol    = 0.0_cu_m;
    _data.fuselage.landing_gear = false;
    _data.fuselage.cargo_ramp   = false;
    _data.fuselage.wetted_area_override = false;

    // wing
    _data.wing.area      = 0.0_sq_m;
    _data.wing.area_exp  = 0.0_sq_m;
    _data.wing.span      = 0.0_m;
    _data.wing.sweep     = 0.0_deg;
    _data.wing.c_tip     = 0.0_m;
    _data.wing.c_root    = 0.0_m;
    _data.wing.ar        = 0.0;
    _data.wing.tr        = 0.0;
    _data.wing.tc        = 0.0;
    _data.wing.fuel      = 0.0_kg;
    _data.wing.ctrl_area = 0.0_sq_m;
    _data.wing.delta     = false;
    _data.wing.var_sweep = false;

    // horizontal tail
    _data.hor_tail.area      = 0.0_sq_m;
    _data.hor_tail.span      = 0.0_m;
    _data.hor_tail.sweep     = 0.0_deg;
    _data.hor_tail.c_tip     = 0.0_m;
    _data.hor_tail.c_root    = 0.0_m;
    _data.hor_tail.tc        = 0.0;
    _data.hor_tail.elev_area = 0.0_sq_m;
    _data.hor_tail.w_f       = 0.0_m;
    _data.hor_tail.arm       = 0.0_m;
    _data.hor_tail.ar        = 0.0;
    _data.hor_tail.tr        = 0.0;
    _data.hor_tail.moving    = false;
    _data.hor_tail.rolling   = false;

    // vertical tail
    _data.ver_tail.area      = 0.0_sq_m;
    _data.ver_tail.height    = 0.0_m;
    _data.ver_tail.sweep     = 0.0_deg;
    _data.ver_tail.c_tip     = 0.0_m;
    _data.ver_tail.c_root    = 0.0_m;
    _data.ver_tail.tc        = 0.0;
    _data.ver_tail.arm       = 0.0_m;
    _data.ver_tail.rudd_area = 0.0_sq_m;
    _data.ver_tail.ar        = 0.0;
    _data.ver_tail.tr        = 0.0;
    _data.ver_tail.t_tail    = false;
    _data.ver_tail.rotor     = false;

    // landing gear
    _data.landing_gear.main_l      = 0.0_m;
    _data.landing_gear.nose_l      = 0.0_m;
    _data.landing_gear.main_wheels = 0;
    _data.landing_gear.main_struts = 0;
    _data.landing_gear.nose_wheels = 0;
    _data.landing_gear.fixed       = false;
    _data.landing_gear.cross       = false;
    _data.landing_gear.tripod      = false;
    _data.landing_gear.main_kneel  = false;
    _data.landing_gear.nose_kneel  = false;

    // engine
    _data.engine.mass = 0.0_kg;

    // rotors
    _data.rotors.main_r          = 0.0_m;
    _data.rotors.main_cb         = 0.0_m;
    _data.rotors.main_rpm        = 0.0_rpm;
    _data.rotors.main_gear_ratio = 1.0;
    _data.rotors.tail_r          = 0.0_m;
    _data.rotors.mcp             = 0.0_hp;
    _data.rotors.main_tip_vel    = 0.0_fps;
    _data.rotors.main_blades     = 0;

    // 3D model
    _data.model3d.file = "";
    _data.model3d.offset_x = 0.0_m;
    _data.model3d.offset_y = 0.0_m;
    _data.model3d.offset_z = 0.0_m;
    _data.model3d.rotation_x = 0.0_deg;
    _data.model3d.rotation_y = 0.0_deg;
    _data.model3d.rotation_z = 0.0_deg;
    _data.model3d.scale = 1.0;

    // RESULTS
    _centerOfMass.x() = 0.0_m;
    _centerOfMass.y() = 0.0_m;
    _centerOfMass.z() = 0.0_m;

    _inertiaMatrix.ixx() = 0.0_kg_m2;
    _inertiaMatrix.ixy() = 0.0_kg_m2;
    _inertiaMatrix.ixz() = 0.0_kg_m2;
    _inertiaMatrix.iyx() = 0.0_kg_m2;
    _inertiaMatrix.iyy() = 0.0_kg_m2;
    _inertiaMatrix.iyz() = 0.0_kg_m2;
    _inertiaMatrix.izx() = 0.0_kg_m2;
    _inertiaMatrix.izy() = 0.0_kg_m2;
    _inertiaMatrix.izz() = 0.0_kg_m2;

    _totalEmptyMass = 0.0_kg;

    deleteAllComponents();
}

void Aircraft::update()
{
    units::mass::kilogram_t m = 0.0_kg;
    FirstMomentOfMass s;
    InertiaMatrix i;

    if ( _verbose )
    {
        std::cout << std::endl;
    }

    for ( auto component : _components )
    {
        units::mass::kilogram_t mc = component->GetMass();
        PositionVector rc = component->GetPosition();
        FirstMomentOfMass sc = component->GetMass() * rc;
        InertiaMatrix ic = component->GetInertia();

        if ( _verbose )
        {
            std::cout << "\"" << component->GetName() << "\"\t";
            std::cout << mc() << "\t";
            std::cout << rc.x()() << "\t";
            std::cout << rc.y()() << "\t";
            std::cout << rc.z()() << "\t";
            std::cout << sc.sx()() << "\t";
            std::cout << sc.sy()() << "\t";
            std::cout << sc.sz()() << "\t";
            std::cout << ic.ixx()() << "\t";
            std::cout << ic.iyy()() << "\t";
            std::cout << ic.izz()() << "\t";
            std::cout << ic.ixy()() << "\t";
            std::cout << ic.ixz()() << "\t";
            std::cout << ic.iyz()() << "\t";
            std::cout << std::endl;
        }

        m += mc;
        s += sc;
        i += getParallelAxisInertia(mc, ic, rc);
    }

    _centerOfMass = ( m > 0.0_kg ) ? (s / m) : PositionVector();
    _inertiaMatrix = i;
    _totalEmptyMass = m;
}

Component* Aircraft::getComponent(int index)
{
    Components::iterator it = _components.begin() + index;

    if ( it != _components.end() )
    {
        return (*it);
    }

    return nullptr;
}

void Aircraft::addComponent(Component* component)
{
    _components.push_back(component);
    update();
}

void Aircraft::deleteComponent(int index)
{
    Components::iterator it = _components.begin() + index;

    if ( it != _components.end() )
    {
        if ( *it ) { delete *it; } *it = nullptr;
        _components.erase(it);
    }

    update();
}

void Aircraft::setData(const AircraftData& data)
{
    _data = data;
}

std::string Aircraft::toString() const
{
    std::string metric = toStringMetric();
    std::string imperial = toStringImperial();
    return metric + imperial;
}

void Aircraft::deleteAllComponents()
{
    Components::iterator it = _components.begin();

    while ( it != _components.end() )
    {
        if ( *it ) { delete *it; } *it = nullptr;
        it = _components.erase(it);
    }

    update();
}

bool Aircraft::readData( QDomElement *dataNode )
{
    QDomElement nodeGeneral     = dataNode->firstChildElement("general");
    QDomElement nodeFuselage    = dataNode->firstChildElement("fuselage");
    QDomElement nodeWing        = dataNode->firstChildElement("wing");
    QDomElement nodeHorTail     = dataNode->firstChildElement("hor_tail");
    QDomElement nodeVerTail     = dataNode->firstChildElement("ver_tail");
    QDomElement nodeLandingGear = dataNode->firstChildElement("landing_gear");
    QDomElement nodeEngine      = dataNode->firstChildElement("engine");
    QDomElement nodeRotors      = dataNode->firstChildElement("rotors");
    QDomElement nodeModel3D     = dataNode->firstChildElement("model3d");

    if ( !nodeGeneral.isNull()
      && !nodeFuselage.isNull()
      && !nodeWing.isNull()
      && !nodeHorTail.isNull()
      && !nodeVerTail.isNull()
      && !nodeLandingGear.isNull()
      && !nodeEngine.isNull()
      && !nodeRotors.isNull()
      && !nodeModel3D.isNull()
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
        if ( result ) result = readDataModel3D     ( &nodeModel3D     );

        return result;
    }

    return false;
}

bool Aircraft::readDataGeneral(QDomElement* parentNode)
{
    QDomElement nodeM_empty   = parentNode->firstChildElement("m_empty");
    QDomElement nodeMTOW      = parentNode->firstChildElement("mtow");
    QDomElement nodeM_maxLand = parentNode->firstChildElement("m_max_land");
    QDomElement nodeMaxFuel   = parentNode->firstChildElement("max_fuel");
    QDomElement nodeNzMax     = parentNode->firstChildElement("nz_max");
    QDomElement nodeNzMaxLand = parentNode->firstChildElement("nz_max_land");
    QDomElement nodeStallV    = parentNode->firstChildElement("stall_v");
    QDomElement nodeCruiseH   = parentNode->firstChildElement("h_cruise");
    QDomElement nodeCruiseV   = parentNode->firstChildElement("v_cruise");
    QDomElement nodeMachMax   = parentNode->firstChildElement("mach_max");
    QDomElement nodeNavyAC    = parentNode->firstChildElement("navy_ac");

    if ( !nodeM_empty.isNull()
      && !nodeMTOW.isNull()
      && !nodeM_maxLand.isNull()
      && !nodeMaxFuel.isNull()
      && !nodeNzMax.isNull()
      && !nodeNzMaxLand.isNull()
      && !nodeStallV.isNull()
      && !nodeCruiseH.isNull()
      && !nodeCruiseV.isNull()
      && !nodeMachMax.isNull()
      && !nodeNavyAC.isNull()
       )
    {
        _data.general.m_empty    = units::mass::kilogram_t(nodeM_empty.text().toDouble());
        _data.general.mtow       = units::mass::kilogram_t(nodeMTOW.text().toDouble());
        _data.general.m_maxLand  = units::mass::kilogram_t(nodeM_maxLand.text().toDouble());
        _data.general.m_maxFuel  = units::mass::kilogram_t(nodeMaxFuel.text().toDouble());
        _data.general.nz_max     = nodeNzMax.text().toDouble();
        _data.general.nz_maxLand = nodeNzMaxLand.text().toDouble();
        _data.general.v_stall    = units::velocity::knot_t(nodeStallV.text().toDouble());
        _data.general.h_cruise   = units::length::foot_t(nodeCruiseH.text().toDouble());
        _data.general.v_cruise   = units::velocity::knot_t(nodeCruiseV.text().toDouble());
        _data.general.mach_max   = nodeMachMax.text().toDouble();
        _data.general.navy_ac    = nodeNavyAC.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::readDataFuselage(QDomElement* parentNode)
{
    QDomElement nodeCargoDoor  = parentNode->firstChildElement("cargo_door");
    QDomElement nodeFuseL      = parentNode->firstChildElement("lenght");
    QDomElement nodeFuseH      = parentNode->firstChildElement("height");
    QDomElement nodeFuseW      = parentNode->firstChildElement("width");
    QDomElement nodeNoseL      = parentNode->firstChildElement("nose_length");
    QDomElement nodeWettedArea = parentNode->firstChildElement("wetted_area");
    QDomElement nodePressVol   = parentNode->firstChildElement("press_vol");
    QDomElement nodeFuselageLG = parentNode->firstChildElement("landing_gear");
    QDomElement nodeCargoRamp  = parentNode->firstChildElement("cargo_ramp");
    QDomElement nodeWettedAreaOverride = parentNode->firstChildElement("wetted_area_override");

    if ( !nodeCargoDoor.isNull()
      && !nodeFuseL.isNull()
      && !nodeFuseH.isNull()
      && !nodeFuseW.isNull()
      && !nodeNoseL.isNull()
      && !nodeWettedArea.isNull()
      && !nodePressVol.isNull()
      && !nodeFuselageLG.isNull()
      && !nodeCargoRamp.isNull()
      && !nodeWettedAreaOverride.isNull()
       )
    {
        int cargo_door_temp = nodeCargoDoor.text().toInt();

        _data.fuselage.cargo_door = AircraftData::Fuselage::NoCargoDoor;

        switch ( cargo_door_temp )
        {
        case AircraftData::Fuselage::NoCargoDoor:
            _data.fuselage.cargo_door = AircraftData::Fuselage::NoCargoDoor;
            break;
        case AircraftData::Fuselage::OneSideCargoDoor:
            _data.fuselage.cargo_door = AircraftData::Fuselage::OneSideCargoDoor;
            break;
        case AircraftData::Fuselage::TwoSideCargoDoor:
            _data.fuselage.cargo_door = AircraftData::Fuselage::TwoSideCargoDoor;
            break;
        case AircraftData::Fuselage::AftClamshellDoor:
            _data.fuselage.cargo_door = AircraftData::Fuselage::AftClamshellDoor;
            break;
        case AircraftData::Fuselage::TwoSideAndAftDoor:
            _data.fuselage.cargo_door = AircraftData::Fuselage::TwoSideAndAftDoor;
            break;
        }

        _data.fuselage.l = units::length::meter_t(nodeFuseL.text().toDouble());
        _data.fuselage.h = units::length::meter_t(nodeFuseH.text().toDouble());
        _data.fuselage.w = units::length::meter_t(nodeFuseW.text().toDouble());
        _data.fuselage.l_n = units::length::meter_t(nodeNoseL.text().toDouble());
        _data.fuselage.wetted_area = units::area::square_meter_t(nodeWettedArea.text().toDouble());
        _data.fuselage.press_vol = units::volume::cubic_meter_t(nodePressVol.text().toDouble());
        _data.fuselage.landing_gear = nodeFuselageLG .text().toInt();
        _data.fuselage.cargo_ramp = nodeCargoRamp  .text().toInt();
        _data.fuselage.wetted_area_override = nodeWettedAreaOverride.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::readDataWing(QDomElement* parentNode)
{
    QDomElement nodeWingArea    = parentNode->firstChildElement("area");
    QDomElement nodeWingAreaExp = parentNode->firstChildElement("area_exp");
    QDomElement nodeWingSpan    = parentNode->firstChildElement("span");
    QDomElement nodeWingSweep   = parentNode->firstChildElement("sweep");
    QDomElement nodeWingCTip    = parentNode->firstChildElement("c_tip");
    QDomElement nodeWingCRoot   = parentNode->firstChildElement("c_root");
    QDomElement nodeWingAR      = parentNode->firstChildElement("ar");
    QDomElement nodeWingTR      = parentNode->firstChildElement("tr");
    QDomElement nodeWingTC      = parentNode->firstChildElement("tc");
    QDomElement nodeWingFuel    = parentNode->firstChildElement("fuel");
    QDomElement nodeCtrlArea    = parentNode->firstChildElement("ctrl_area");
    QDomElement nodeWingDelta   = parentNode->firstChildElement("delta");
    QDomElement nodeWingVarSweep = parentNode->firstChildElement("var_sweep");

    if ( !nodeWingArea.isNull()
      && !nodeWingAreaExp.isNull()
      && !nodeWingSpan.isNull()
      && !nodeWingSweep.isNull()
      && !nodeWingCTip.isNull()
      && !nodeWingCRoot.isNull()
      && !nodeWingAR.isNull()
      && !nodeWingTR.isNull()
      && !nodeWingTC.isNull()
      && !nodeWingFuel.isNull()
      && !nodeCtrlArea.isNull()
      && !nodeWingDelta.isNull()
      && !nodeWingVarSweep.isNull()
       )
    {
        _data.wing.area = units::area::square_meter_t(nodeWingArea.text().toDouble());
        _data.wing.area_exp = units::area::square_meter_t(nodeWingAreaExp.text().toDouble());
        _data.wing.span = units::length::meter_t(nodeWingSpan.text().toDouble());
        _data.wing.sweep = units::angle::degree_t(nodeWingSweep.text().toDouble());
        _data.wing.c_tip = units::length::meter_t(nodeWingCTip.text().toDouble());
        _data.wing.c_root = units::length::meter_t(nodeWingCRoot.text().toDouble());
        _data.wing.ar = nodeWingAR.text().toDouble();
        _data.wing.tr = nodeWingTR.text().toDouble();
        _data.wing.tc = nodeWingTC.text().toDouble();
        _data.wing.fuel = units::mass::kilogram_t(nodeWingFuel.text().toDouble());
        _data.wing.ctrl_area = units::area::square_meter_t(nodeCtrlArea.text().toDouble());
        _data.wing.delta = nodeWingDelta.text().toInt();
        _data.wing.var_sweep = nodeWingVarSweep .text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::readDataHorTail(QDomElement* parentNode)
{
    QDomElement nodeHorTailArea = parentNode->firstChildElement("area");
    QDomElement nodeHorTailSpan = parentNode->firstChildElement("span");
    QDomElement nodeHorTailSweep = parentNode->firstChildElement("sweep");
    QDomElement nodeHorTailCTip = parentNode->firstChildElement("c_tip");
    QDomElement nodeHorTailCRoot = parentNode->firstChildElement("c_root");
    QDomElement nodeHorTailTC = parentNode->firstChildElement("tc");
    QDomElement nodeElevArea = parentNode->firstChildElement("elev_area");
    QDomElement nodeHorTailWF = parentNode->firstChildElement("w_f");
    QDomElement nodeHorTailArm = parentNode->firstChildElement("arm");
    QDomElement nodeHorTailAR = parentNode->firstChildElement("ar");
    QDomElement nodeHorTailTR = parentNode->firstChildElement("tr");
    QDomElement nodeHorTailMoving = parentNode->firstChildElement("moving");
    QDomElement nodeHorTailRolling = parentNode->firstChildElement("rolling");

    if ( !nodeHorTailArea.isNull()
      && !nodeHorTailSpan.isNull()
      && !nodeHorTailSweep.isNull()
      && !nodeHorTailCTip.isNull()
      && !nodeHorTailCRoot.isNull()
      && !nodeHorTailTC.isNull()
      && !nodeElevArea.isNull()
      && !nodeHorTailWF.isNull()
      && !nodeHorTailArm.isNull()
      && !nodeHorTailAR.isNull()
      && !nodeHorTailTR.isNull()
      && !nodeHorTailMoving.isNull()
      && !nodeHorTailRolling.isNull()
       )
    {
        _data.hor_tail.area = area::square_meter_t(nodeHorTailArea.text().toDouble());
        _data.hor_tail.span = length::meter_t(nodeHorTailSpan.text().toDouble());
        _data.hor_tail.sweep = angle::degree_t(nodeHorTailSweep.text().toDouble());
        _data.hor_tail.c_tip = length::meter_t(nodeHorTailCTip.text().toDouble());
        _data.hor_tail.c_root = length::meter_t(nodeHorTailCRoot.text().toDouble());
        _data.hor_tail.tc = nodeHorTailTC.text().toDouble();
        _data.hor_tail.elev_area = area::square_meter_t(nodeElevArea.text().toDouble());
        _data.hor_tail.w_f = length::meter_t(nodeHorTailWF.text().toDouble());
        _data.hor_tail.arm = length::meter_t(nodeHorTailArm.text().toDouble());
        _data.hor_tail.ar = nodeHorTailAR.text().toDouble();
        _data.hor_tail.tr = nodeHorTailTR.text().toDouble();
        _data.hor_tail.moving = nodeHorTailMoving.text().toInt();
        _data.hor_tail.rolling = nodeHorTailRolling.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::readDataVerTail(QDomElement* parentNode)
{
    QDomElement nodeVerTailArea = parentNode->firstChildElement("area");
    QDomElement nodeVerTailHeight = parentNode->firstChildElement("height");
    QDomElement nodeVerTailSweep = parentNode->firstChildElement("sweep");
    QDomElement nodeVerTailCTip = parentNode->firstChildElement("c_tip");
    QDomElement nodeVerTailCRoot = parentNode->firstChildElement("c_root");
    QDomElement nodeVerTailTC = parentNode->firstChildElement("tc");
    QDomElement nodeVerTailArm = parentNode->firstChildElement("arm");
    QDomElement nodeRuddArea = parentNode->firstChildElement("rudd_area");
    QDomElement nodeVerTailAR = parentNode->firstChildElement("ar");
    QDomElement nodeVerTailTR = parentNode->firstChildElement("tr");
    QDomElement nodeTailT = parentNode->firstChildElement("t_tail");
    QDomElement nodeVerTailRotor = parentNode->firstChildElement("rotor");

    if ( !nodeVerTailArea.isNull()
      && !nodeVerTailHeight.isNull()
      && !nodeVerTailSweep.isNull()
      && !nodeVerTailCTip.isNull()
      && !nodeVerTailCRoot.isNull()
      && !nodeVerTailTC.isNull()
      && !nodeVerTailArm.isNull()
      && !nodeRuddArea.isNull()
      && !nodeVerTailAR.isNull()
      && !nodeVerTailTR.isNull()
      && !nodeTailT.isNull()
      && !nodeVerTailRotor.isNull()
       )
    {
        _data.ver_tail.area = area::square_meter_t(nodeVerTailArea.text().toDouble());
        _data.ver_tail.height = length::meter_t(nodeVerTailHeight.text().toDouble());
        _data.ver_tail.sweep = angle::degree_t(nodeVerTailSweep.text().toDouble());
        _data.ver_tail.c_tip = length::meter_t(nodeVerTailCTip.text().toDouble());
        _data.ver_tail.c_root = length::meter_t(nodeVerTailCRoot.text().toDouble());
        _data.ver_tail.tc = nodeVerTailTC.text().toDouble();
        _data.ver_tail.arm = length::meter_t(nodeVerTailArm.text().toDouble());
        _data.ver_tail.rudd_area = area::square_meter_t(nodeRuddArea.text().toDouble());
        _data.ver_tail.ar = nodeVerTailAR.text().toDouble();
        _data.ver_tail.tr = nodeVerTailTR.text().toDouble();
        _data.ver_tail.t_tail = nodeTailT.text().toInt();
        _data.ver_tail.rotor = nodeVerTailRotor.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::readDataLandingGear(QDomElement* parentNode)
{
    QDomElement nodeMainGearL = parentNode->firstChildElement("main_gear_l");
    QDomElement nodeNoseGearL = parentNode->firstChildElement("nose_gear_l");
    QDomElement nodeMainGearWheels = parentNode->firstChildElement("main_gear_wheels");
    QDomElement nodeMainGearStruts = parentNode->firstChildElement("main_gear_struts");
    QDomElement nodeNoseGearWheels = parentNode->firstChildElement("nose_gear_wheels");
    QDomElement nodeGearFixed = parentNode->firstChildElement("fixed");
    QDomElement nodeGearCross = parentNode->firstChildElement("cross");
    QDomElement nodeGearTripod = parentNode->firstChildElement("tripod");
    QDomElement nodeMainGearKneel = parentNode->firstChildElement("main_gear_kneel");
    QDomElement nodeNoseGearKneel = parentNode->firstChildElement("nose_gear_kneel");

    if ( !nodeMainGearL.isNull()
      && !nodeNoseGearL.isNull()
      && !nodeMainGearWheels.isNull()
      && !nodeMainGearStruts.isNull()
      && !nodeNoseGearWheels.isNull()
      && !nodeGearFixed.isNull()
      && !nodeGearCross.isNull()
      && !nodeGearTripod.isNull()
      && !nodeMainGearKneel.isNull()
      && !nodeNoseGearKneel.isNull()
       )
    {
        _data.landing_gear.main_l = length::meter_t(nodeMainGearL.text().toDouble());
        _data.landing_gear.nose_l = length::meter_t(nodeNoseGearL.text().toDouble());
        _data.landing_gear.main_wheels = nodeMainGearWheels.text().toInt();
        _data.landing_gear.main_struts = nodeMainGearStruts.text().toInt();
        _data.landing_gear.nose_wheels = nodeNoseGearWheels.text().toInt();
        _data.landing_gear.fixed = nodeGearFixed.text().toInt();
        _data.landing_gear.cross = nodeGearCross.text().toInt();
        _data.landing_gear.tripod = nodeGearTripod.text().toInt();
        _data.landing_gear.main_kneel = nodeMainGearKneel.text().toInt();
        _data.landing_gear.nose_kneel = nodeNoseGearKneel.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::readDataEngine(QDomElement* parentNode)
{
    QDomElement nodeEngineMass = parentNode->firstChildElement("mass");

    if ( !nodeEngineMass.isNull() )
    {
        _data.engine.mass = mass::kilogram_t(nodeEngineMass.text().toDouble());

        return true;
    }

    return false;
}

bool Aircraft::readDataRotors(QDomElement* parentNode)
{
    QDomElement nodeMainRotorR = parentNode->firstChildElement("main_rotor_radius");
    QDomElement nodeMainRotorCB = parentNode->firstChildElement("main_rotor_blade_chord");
    QDomElement nodeMainRotorRPM = parentNode->firstChildElement("main_rotor_rpm");
    QDomElement nodeMainRotorGR = parentNode->firstChildElement("main_rotor_gear_ratio");
    QDomElement nodeTailRotorR = parentNode->firstChildElement("tail_rotor_radius");
    QDomElement nodePowerLimit = parentNode->firstChildElement("mcp");
    QDomElement nodeMainRotorTipVel = parentNode->firstChildElement("main_rotor_tip_vel");
    QDomElement nodeMainRotorBlades = parentNode->firstChildElement("main_rotor_blades");

    if ( !nodeMainRotorR.isNull()
      && !nodeMainRotorCB.isNull()
      && !nodeMainRotorRPM.isNull()
      && !nodeMainRotorGR.isNull()
      && !nodeTailRotorR.isNull()
      && !nodePowerLimit.isNull()
      && !nodeMainRotorTipVel.isNull()
      && !nodeMainRotorBlades.isNull()
       )
    {
        _data.rotors.main_r = length::meter_t(nodeMainRotorR.text().toDouble());
        _data.rotors.main_cb = length::meter_t(nodeMainRotorCB.text().toDouble());
        _data.rotors.main_rpm = angular_velocity::rpm_t(nodeMainRotorRPM.text().toDouble());
        _data.rotors.main_gear_ratio = nodeMainRotorGR.text().toDouble();
        _data.rotors.tail_r = length::meter_t(nodeTailRotorR.text().toDouble());
        _data.rotors.mcp = power::horsepower_t(nodePowerLimit.text().toDouble());
        _data.rotors.main_tip_vel = velocity::meters_per_second_t(nodeMainRotorTipVel.text().toDouble());
        _data.rotors.main_blades = nodeMainRotorBlades.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::readDataModel3D(QDomElement* parentNode)
{
    QDomElement nodeModelFile = parentNode->firstChildElement("model_file");
    QDomElement nodeOffsetX = parentNode->firstChildElement("offset_x");
    QDomElement nodeOffsetY = parentNode->firstChildElement("offset_y");
    QDomElement nodeOffsetZ = parentNode->firstChildElement("offset_z");
    QDomElement nodeRotationX = parentNode->firstChildElement("rotation_x");
    QDomElement nodeRotationY = parentNode->firstChildElement("rotation_y");
    QDomElement nodeRotationZ = parentNode->firstChildElement("rotation_z");
    QDomElement nodeScale = parentNode->firstChildElement("scale");

    if ( !nodeModelFile.isNull()
      && !nodeOffsetX.isNull()
      && !nodeOffsetY.isNull()
      && !nodeOffsetZ.isNull()
      && !nodeRotationX.isNull()
      && !nodeRotationY.isNull()
      && !nodeRotationZ.isNull()
      && !nodeScale.isNull()
       )
    {
        _data.model3d.file = nodeModelFile.text();
        _data.model3d.offset_x = length::meter_t(nodeOffsetX.text().toDouble());
        _data.model3d.offset_y = length::meter_t(nodeOffsetY.text().toDouble());
        _data.model3d.offset_z = length::meter_t(nodeOffsetZ.text().toDouble());
        _data.model3d.rotation_x = angle::degree_t(nodeRotationX.text().toDouble());
        _data.model3d.rotation_y = angle::degree_t(nodeRotationY.text().toDouble());
        _data.model3d.rotation_z = angle::degree_t(nodeRotationZ.text().toDouble());
        _data.model3d.scale = nodeScale.text().toDouble();

        return true;
    }

    return false;
}

bool Aircraft::readComponents(QDomElement* componentsNode)
{
    QDomElement nodeComponent = componentsNode->firstChildElement();

    while ( !nodeComponent.isNull() )
    {
        Component* temp = nullptr;

        if ( nodeComponent.tagName() == AllElse::kXmlTagName )
        {
            temp = new AllElse(&_data);
        }
        else if ( nodeComponent.tagName() == Engine::kXmlTagName )
        {
            temp = new Engine(&_data);
        }
        else if ( nodeComponent.tagName() == Fuselage::kXmlTagName )
        {
            temp = new Fuselage(&_data);
        }
        else if ( nodeComponent.tagName() == GearMain::kXmlTagName )
        {
            temp = new GearMain(&_data);
        }
        else if ( nodeComponent.tagName() == GearNose::kXmlTagName )
        {
            temp = new GearNose(&_data);
        }
        else if ( nodeComponent.tagName() == RotorDrive::kXmlTagName )
        {
            temp = new RotorDrive(&_data);
        }
        else if ( nodeComponent.tagName() == RotorHub::kXmlTagName )
        {
            temp = new RotorHub(&_data);
        }
        else if ( nodeComponent.tagName() == RotorMain::kXmlTagName )
        {
            temp = new RotorMain(&_data);
        }
        else if ( nodeComponent.tagName() == RotorTail::kXmlTagName )
        {
            temp = new RotorTail(&_data);
        }
        else if ( nodeComponent.tagName() == TailHor::kXmlTagName )
        {
            temp = new TailHor(&_data);
        }
        else if ( nodeComponent.tagName() == TailVer::kXmlTagName )
        {
            temp = new TailVer(&_data);
        }
        else if ( nodeComponent.tagName() == Wing::kXmlTagName )
        {
            temp = new Wing(&_data);
        }

        if ( temp )
        {
            temp->Read(&nodeComponent);
            _components.push_back(temp);
        }

        nodeComponent = nodeComponent.nextSiblingElement();
    }

    return true;
}

void Aircraft::saveDataGeneral(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "m_empty"     , _data.general.m_empty());
    XmlUtils::saveTextNode(doc, parentNode, "mtow"        , _data.general.mtow());
    XmlUtils::saveTextNode(doc, parentNode, "m_max_land"  , _data.general.m_maxLand());
    XmlUtils::saveTextNode(doc, parentNode, "max_fuel"    , _data.general.m_maxFuel());
    XmlUtils::saveTextNode(doc, parentNode, "nz_max"      , _data.general.nz_max);
    XmlUtils::saveTextNode(doc, parentNode, "nz_max_land" , _data.general.nz_maxLand);
    XmlUtils::saveTextNode(doc, parentNode, "stall_v"     , _data.general.v_stall());
    XmlUtils::saveTextNode(doc, parentNode, "h_cruise"    , _data.general.h_cruise());
    XmlUtils::saveTextNode(doc, parentNode, "v_cruise"    , _data.general.v_cruise());
    XmlUtils::saveTextNode(doc, parentNode, "mach_max"    , _data.general.mach_max);
    XmlUtils::saveTextNode(doc, parentNode, "navy_ac"     , _data.general.navy_ac);
}

void Aircraft::saveDataFuselage(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "cargo_door", QString::number(_data.fuselage.cargo_door));
    XmlUtils::saveTextNode(doc, parentNode, "lenght"               , _data.fuselage.l());
    XmlUtils::saveTextNode(doc, parentNode, "height"               , _data.fuselage.h());
    XmlUtils::saveTextNode(doc, parentNode, "width"                , _data.fuselage.w());
    XmlUtils::saveTextNode(doc, parentNode, "nose_length"          , _data.fuselage.l_n());
    XmlUtils::saveTextNode(doc, parentNode, "wetted_area"          , _data.fuselage.wetted_area());
    XmlUtils::saveTextNode(doc, parentNode, "press_vol"            , _data.fuselage.press_vol());
    XmlUtils::saveTextNode(doc, parentNode, "landing_gear"         , _data.fuselage.landing_gear);
    XmlUtils::saveTextNode(doc, parentNode, "cargo_ramp"           , _data.fuselage.cargo_ramp);
    XmlUtils::saveTextNode(doc, parentNode, "wetted_area_override" , _data.fuselage.wetted_area_override);
}

void Aircraft::saveDataWing(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "area"      , _data.wing.area());
    XmlUtils::saveTextNode(doc, parentNode, "area_exp"  , _data.wing.area_exp());
    XmlUtils::saveTextNode(doc, parentNode, "span"      , _data.wing.span());
    XmlUtils::saveTextNode(doc, parentNode, "sweep"     , _data.wing.sweep());
    XmlUtils::saveTextNode(doc, parentNode, "c_tip"     , _data.wing.c_tip());
    XmlUtils::saveTextNode(doc, parentNode, "c_root"    , _data.wing.c_root());
    XmlUtils::saveTextNode(doc, parentNode, "ar"        , _data.wing.ar);
    XmlUtils::saveTextNode(doc, parentNode, "tr"        , _data.wing.tr);
    XmlUtils::saveTextNode(doc, parentNode, "tc"        , _data.wing.tc);
    XmlUtils::saveTextNode(doc, parentNode, "fuel"      , _data.wing.fuel());
    XmlUtils::saveTextNode(doc, parentNode, "ctrl_area" , _data.wing.ctrl_area());
    XmlUtils::saveTextNode(doc, parentNode, "delta"     , _data.wing.delta);
    XmlUtils::saveTextNode(doc, parentNode, "var_sweep" , _data.wing.var_sweep);
}

void Aircraft::saveDataHorTail(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "area"      , _data.hor_tail.area());
    XmlUtils::saveTextNode(doc, parentNode, "span"      , _data.hor_tail.span());
    XmlUtils::saveTextNode(doc, parentNode, "sweep"     , _data.hor_tail.sweep());
    XmlUtils::saveTextNode(doc, parentNode, "c_tip"     , _data.hor_tail.c_tip());
    XmlUtils::saveTextNode(doc, parentNode, "c_root"    , _data.hor_tail.c_root());
    XmlUtils::saveTextNode(doc, parentNode, "tc"        , _data.hor_tail.tc);
    XmlUtils::saveTextNode(doc, parentNode, "elev_area" , _data.hor_tail.elev_area());
    XmlUtils::saveTextNode(doc, parentNode, "w_f"       , _data.hor_tail.w_f());
    XmlUtils::saveTextNode(doc, parentNode, "arm"       , _data.hor_tail.arm());
    XmlUtils::saveTextNode(doc, parentNode, "ar"        , _data.hor_tail.ar);
    XmlUtils::saveTextNode(doc, parentNode, "tr"        , _data.hor_tail.tr);
    XmlUtils::saveTextNode(doc, parentNode, "moving"    , _data.hor_tail.moving);
    XmlUtils::saveTextNode(doc, parentNode, "rolling"   , _data.hor_tail.rolling);
}

void Aircraft::saveDataVerTail(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "area"      , _data.ver_tail.area());
    XmlUtils::saveTextNode(doc, parentNode, "height"    , _data.ver_tail.height());
    XmlUtils::saveTextNode(doc, parentNode, "sweep"     , _data.ver_tail.sweep());
    XmlUtils::saveTextNode(doc, parentNode, "c_tip"     , _data.ver_tail.c_tip());
    XmlUtils::saveTextNode(doc, parentNode, "c_root"    , _data.ver_tail.c_root());
    XmlUtils::saveTextNode(doc, parentNode, "tc"        , _data.ver_tail.tc);
    XmlUtils::saveTextNode(doc, parentNode, "arm"       , _data.ver_tail.arm());
    XmlUtils::saveTextNode(doc, parentNode, "rudd_area" , _data.ver_tail.rudd_area());
    XmlUtils::saveTextNode(doc, parentNode, "ar"        , _data.ver_tail.ar);
    XmlUtils::saveTextNode(doc, parentNode, "tr"        , _data.ver_tail.tr);
    XmlUtils::saveTextNode(doc, parentNode, "t_tail"    , _data.ver_tail.t_tail);
    XmlUtils::saveTextNode(doc, parentNode, "rotor"     , _data.ver_tail.rotor);
}

void Aircraft::saveDataLandingGear(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "main_gear_l"      , _data.landing_gear.main_l());
    XmlUtils::saveTextNode(doc, parentNode, "nose_gear_l"      , _data.landing_gear.nose_l());
    XmlUtils::saveTextNode(doc, parentNode, "main_gear_wheels" , static_cast<int>(_data.landing_gear.main_wheels));
    XmlUtils::saveTextNode(doc, parentNode, "main_gear_struts" , static_cast<int>(_data.landing_gear.main_struts));
    XmlUtils::saveTextNode(doc, parentNode, "nose_gear_wheels" , static_cast<int>(_data.landing_gear.nose_wheels));
    XmlUtils::saveTextNode(doc, parentNode, "fixed"            , _data.landing_gear.fixed);
    XmlUtils::saveTextNode(doc, parentNode, "cross"            , _data.landing_gear.cross);
    XmlUtils::saveTextNode(doc, parentNode, "tripod"           , _data.landing_gear.tripod);
    XmlUtils::saveTextNode(doc, parentNode, "main_gear_kneel"  , _data.landing_gear.main_kneel);
    XmlUtils::saveTextNode(doc, parentNode, "nose_gear_kneel"  , _data.landing_gear.nose_kneel);
}

void Aircraft::saveDataEngine(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "mass", _data.engine.mass());
}

void Aircraft::saveDataRotors(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "main_rotor_radius"      , _data.rotors.main_r());
    XmlUtils::saveTextNode(doc, parentNode, "main_rotor_blade_chord" , _data.rotors.main_cb());
    XmlUtils::saveTextNode(doc, parentNode, "main_rotor_rpm"         , _data.rotors.main_rpm());
    XmlUtils::saveTextNode(doc, parentNode, "main_rotor_gear_ratio"  , _data.rotors.main_gear_ratio);
    XmlUtils::saveTextNode(doc, parentNode, "tail_rotor_radius"      , _data.rotors.tail_r());
    XmlUtils::saveTextNode(doc, parentNode, "mcp"                    , _data.rotors.mcp());
    XmlUtils::saveTextNode(doc, parentNode, "main_rotor_tip_vel"     , _data.rotors.main_tip_vel());
    XmlUtils::saveTextNode(doc, parentNode, "main_rotor_blades", static_cast<int>(_data.rotors.main_blades));
}

void Aircraft::saveDataModel3D(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::saveTextNode(doc, parentNode, "model_file" , _data.model3d.file);
    XmlUtils::saveTextNode(doc, parentNode, "offset_x"   , _data.model3d.offset_x());
    XmlUtils::saveTextNode(doc, parentNode, "offset_y"   , _data.model3d.offset_y());
    XmlUtils::saveTextNode(doc, parentNode, "offset_z"   , _data.model3d.offset_z());
    XmlUtils::saveTextNode(doc, parentNode, "rotation_x" , _data.model3d.rotation_x());
    XmlUtils::saveTextNode(doc, parentNode, "rotation_y" , _data.model3d.rotation_y());
    XmlUtils::saveTextNode(doc, parentNode, "rotation_z" , _data.model3d.rotation_z());
    XmlUtils::saveTextNode(doc, parentNode, "scale"      , _data.model3d.scale);
}

std::string Aircraft::toStringMetric() const
{
    units::mass::kilogram_t me = _totalEmptyMass;

    units::length::meter_t cg_x = _centerOfMass.x();
    units::length::meter_t cg_y = _centerOfMass.y();
    units::length::meter_t cg_z = _centerOfMass.z();

    units::moment_of_inertia::kilogram_square_meter_t i_xx = _inertiaMatrix.ixx();
    units::moment_of_inertia::kilogram_square_meter_t i_xy = _inertiaMatrix.ixy();
    units::moment_of_inertia::kilogram_square_meter_t i_xz = _inertiaMatrix.ixz();

    units::moment_of_inertia::kilogram_square_meter_t i_yx = _inertiaMatrix.iyx();
    units::moment_of_inertia::kilogram_square_meter_t i_yy = _inertiaMatrix.iyy();
    units::moment_of_inertia::kilogram_square_meter_t i_yz = _inertiaMatrix.iyz();

    units::moment_of_inertia::kilogram_square_meter_t i_zx = _inertiaMatrix.izx();
    units::moment_of_inertia::kilogram_square_meter_t i_zy = _inertiaMatrix.izy();
    units::moment_of_inertia::kilogram_square_meter_t i_zz = _inertiaMatrix.izz();

    return AircraftToString(me,
                            cg_x, cg_y, cg_z,
                            i_xx, i_xy, i_xz,
                            i_yx, i_yy, i_yz,
                            i_zx, i_zy, i_zz);
}

std::string Aircraft::toStringImperial() const
{
    units::mass::pound_t me = _totalEmptyMass;

    units::length::inch_t cg_x = _centerOfMass.x();
    units::length::inch_t cg_y = _centerOfMass.y();
    units::length::inch_t cg_z = _centerOfMass.z();

    units::moment_of_inertia::slug_square_feet_t i_xx = _inertiaMatrix.ixx();
    units::moment_of_inertia::slug_square_feet_t i_xy = _inertiaMatrix.ixy();
    units::moment_of_inertia::slug_square_feet_t i_xz = _inertiaMatrix.ixz();

    units::moment_of_inertia::slug_square_feet_t i_yx = _inertiaMatrix.iyx();
    units::moment_of_inertia::slug_square_feet_t i_yy = _inertiaMatrix.iyy();
    units::moment_of_inertia::slug_square_feet_t i_yz = _inertiaMatrix.iyz();

    units::moment_of_inertia::slug_square_feet_t i_zx = _inertiaMatrix.izx();
    units::moment_of_inertia::slug_square_feet_t i_zy = _inertiaMatrix.izy();
    units::moment_of_inertia::slug_square_feet_t i_zz = _inertiaMatrix.izz();

    return AircraftToString(me,
                            cg_x, cg_y, cg_z,
                            i_xx, i_xy, i_xz,
                            i_yx, i_yy, i_yz,
                            i_zx, i_zy, i_zz);
}
