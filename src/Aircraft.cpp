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
    Reset();
}

Aircraft::~Aircraft()
{
    DeleteAllComponents();
}

bool Aircraft::Read(QDomElement* parentNode)
{
    if ( !parentNode->isNull() )
    {
        int type_temp = parentNode->attributeNode("type").value().toInt();

        data_.type = AircraftData::FighterAttack;

        switch ( type_temp )
        {
        case AircraftData::FighterAttack:
            data_.type = AircraftData::FighterAttack;
            break;
        case AircraftData::CargoTransport:
            data_.type = AircraftData::CargoTransport;
            break;
        case AircraftData::GeneralAviation:
            data_.type = AircraftData::GeneralAviation;
            break;
        case AircraftData::Helicopter:
            data_.type = AircraftData::Helicopter;
            break;
        }

        QDomElement dataNode = parentNode->firstChildElement("data");
        QDomElement componentsNode = parentNode->firstChildElement("components");

        if ( !dataNode.isNull() && !componentsNode.isNull() )
        {
            bool result = true;

            if ( result ) result = ReadData(&dataNode);
            if ( result ) result = ReadComponents(&componentsNode);

            if ( result ) Update();

            return result;
        }
    }

    return false;
}

void Aircraft::Save(QDomDocument* doc, QDomElement* parentNode)
{
    QDomAttr nodeType = doc->createAttribute("type");
    nodeType.setValue(QString::number(data_.type));
    parentNode->setAttributeNode(nodeType);

    // data
    QDomElement nodeData = doc->createElement("data");
    parentNode->appendChild(nodeData);

    // data - general
    QDomElement nodeGeneral = doc->createElement("general");
    nodeData.appendChild(nodeGeneral);
    SaveDataGeneral(doc, &nodeGeneral);

    // data - fuselage
    QDomElement nodeFuselage = doc->createElement("fuselage");
    nodeData.appendChild(nodeFuselage);
    SaveDataFuselage(doc, &nodeFuselage);

    // data - wing
    QDomElement nodeWing = doc->createElement("wing");
    nodeData.appendChild(nodeWing);
    SaveDataWing(doc, &nodeWing);

    // data - horizontal tail
    QDomElement nodeHorTail = doc->createElement("hor_tail");
    nodeData.appendChild(nodeHorTail);
    SaveDataHorTail(doc, &nodeHorTail);

    // data - vertical tail
    QDomElement nodeVerTail = doc->createElement("ver_tail");
    nodeData.appendChild(nodeVerTail);
    SaveDataVerTail(doc, &nodeVerTail);

    // data - landing gear
    QDomElement nodeLandingGear = doc->createElement("landing_gear");
    nodeData.appendChild(nodeLandingGear);
    SaveDataLandingGear(doc, &nodeLandingGear);

    // data - engine
    QDomElement nodeEngine = doc->createElement("engine");
    nodeData.appendChild(nodeEngine);
    SaveDataEngine(doc, &nodeEngine);

    // rotors
    QDomElement nodeRotors = doc->createElement("rotors");
    nodeData.appendChild(nodeRotors);
    SaveDataRotors(doc, &nodeRotors);

    // model 3D
    QDomElement nodeModel3D = doc->createElement("model3d");
    nodeData.appendChild(nodeModel3D);
    SaveDataModel3D(doc, &nodeModel3D);

    // components
    QDomElement componentsNode = doc->createElement("components");
    parentNode->appendChild(componentsNode);

    for ( auto component : components_ )
    {
        component->Save(doc, &componentsNode);
    }
}

void Aircraft::Reset()
{
    data_.type = AircraftData::FighterAttack;

    // general
    data_.general.m_empty    = 0.0_kg;
    data_.general.mtow       = 0.0_kg;
    data_.general.m_maxLand  = 0.0_kg;
    data_.general.nz_max     = 1.0;
    data_.general.nz_maxLand = 1.0;
    data_.general.v_stall    = 0.0_kts;
    data_.general.h_cruise   = 0.0_ft;
    data_.general.v_cruise   = 0.0_kts;
    data_.general.mach_max   = 0.0;
    data_.general.navy_ac    = false;

    // fuselage
    data_.fuselage.cargo_door   = AircraftData::Fuselage::NoCargoDoor;
    data_.fuselage.l            = 0.0_m;
    data_.fuselage.h            = 0.0_m;
    data_.fuselage.w            = 0.0_m;
    data_.fuselage.l_n          = 0.0_m;
    data_.fuselage.wetted_area  = 0.0_sq_m;
    data_.fuselage.press_vol    = 0.0_cu_m;
    data_.fuselage.landing_gear = false;
    data_.fuselage.cargo_ramp   = false;
    data_.fuselage.wetted_area_override = false;

    // wing
    data_.wing.area      = 0.0_sq_m;
    data_.wing.area_exp  = 0.0_sq_m;
    data_.wing.span      = 0.0_m;
    data_.wing.sweep     = 0.0_deg;
    data_.wing.c_tip     = 0.0_m;
    data_.wing.c_root    = 0.0_m;
    data_.wing.ar        = 0.0;
    data_.wing.tr        = 0.0;
    data_.wing.tc        = 0.0;
    data_.wing.fuel      = 0.0_kg;
    data_.wing.ctrl_area = 0.0_sq_m;
    data_.wing.delta     = false;
    data_.wing.var_sweep = false;

    // horizontal tail
    data_.hor_tail.area      = 0.0_sq_m;
    data_.hor_tail.span      = 0.0_m;
    data_.hor_tail.sweep     = 0.0_deg;
    data_.hor_tail.c_tip     = 0.0_m;
    data_.hor_tail.c_root    = 0.0_m;
    data_.hor_tail.tc        = 0.0;
    data_.hor_tail.elev_area = 0.0_sq_m;
    data_.hor_tail.w_f       = 0.0_m;
    data_.hor_tail.arm       = 0.0_m;
    data_.hor_tail.ar        = 0.0;
    data_.hor_tail.tr        = 0.0;
    data_.hor_tail.moving    = false;
    data_.hor_tail.rolling   = false;

    // vertical tail
    data_.ver_tail.area      = 0.0_sq_m;
    data_.ver_tail.height    = 0.0_m;
    data_.ver_tail.sweep     = 0.0_deg;
    data_.ver_tail.c_tip     = 0.0_m;
    data_.ver_tail.c_root    = 0.0_m;
    data_.ver_tail.tc        = 0.0;
    data_.ver_tail.arm       = 0.0_m;
    data_.ver_tail.rudd_area = 0.0_sq_m;
    data_.ver_tail.ar        = 0.0;
    data_.ver_tail.tr        = 0.0;
    data_.ver_tail.t_tail    = false;
    data_.ver_tail.rotor     = false;

    // landing gear
    data_.landing_gear.main_l      = 0.0_m;
    data_.landing_gear.nose_l      = 0.0_m;
    data_.landing_gear.main_wheels = 0;
    data_.landing_gear.main_struts = 0;
    data_.landing_gear.nose_wheels = 0;
    data_.landing_gear.fixed       = false;
    data_.landing_gear.cross       = false;
    data_.landing_gear.tripod      = false;
    data_.landing_gear.main_kneel  = false;
    data_.landing_gear.nose_kneel  = false;

    // engine
    data_.engine.mass = 0.0_kg;

    // rotors
    data_.rotors.main_r          = 0.0_m;
    data_.rotors.main_cb         = 0.0_m;
    data_.rotors.main_rpm        = 0.0_rpm;
    data_.rotors.main_gear_ratio = 1.0;
    data_.rotors.tail_r          = 0.0_m;
    data_.rotors.mcp             = 0.0_hp;
    data_.rotors.main_tip_vel    = 0.0_fps;
    data_.rotors.main_blades     = 0;

    // 3D model
    data_.model3d.file = "";
    data_.model3d.offset_x = 0.0_m;
    data_.model3d.offset_y = 0.0_m;
    data_.model3d.offset_z = 0.0_m;
    data_.model3d.rotation_x = 0.0_deg;
    data_.model3d.rotation_y = 0.0_deg;
    data_.model3d.rotation_z = 0.0_deg;
    data_.model3d.scale = 1.0;

    // RESULTS
    centerOfMass_.x() = 0.0_m;
    centerOfMass_.y() = 0.0_m;
    centerOfMass_.z() = 0.0_m;

    inertiaMatrix_.ixx() = 0.0_kg_m2;
    inertiaMatrix_.ixy() = 0.0_kg_m2;
    inertiaMatrix_.ixz() = 0.0_kg_m2;
    inertiaMatrix_.iyx() = 0.0_kg_m2;
    inertiaMatrix_.iyy() = 0.0_kg_m2;
    inertiaMatrix_.iyz() = 0.0_kg_m2;
    inertiaMatrix_.izx() = 0.0_kg_m2;
    inertiaMatrix_.izy() = 0.0_kg_m2;
    inertiaMatrix_.izz() = 0.0_kg_m2;

    totalEmptyMass_ = 0.0_kg;

    DeleteAllComponents();
}

void Aircraft::Update()
{
    units::mass::kilogram_t m = 0.0_kg;
    FirstMomentOfMass s;
    InertiaMatrix i;

    if ( verbose_ )
    {
        std::cout << std::endl;
    }

    for ( auto component : components_ )
    {
        units::mass::kilogram_t mc = component->GetMass();
        PositionVector rc = component->GetPosition();
        FirstMomentOfMass sc = component->GetMass() * rc;
        InertiaMatrix ic = component->GetInertia();

        if ( verbose_ )
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
        i += GetParallelAxisInertia(mc, ic, rc);
    }

    centerOfMass_ = ( m > 0.0_kg ) ? ( s / m ) : PositionVector();
    inertiaMatrix_ = i;
    totalEmptyMass_ = m;
}

Component* Aircraft::GetComponent(int index)
{
    Components::iterator it = components_.begin() + index;

    if ( it != components_.end() )
    {
        return (*it);
    }

    return nullptr;
}

void Aircraft::AddComponent(Component* component)
{
    components_.push_back(component);
    Update();
}

void Aircraft::DeleteComponent(int index)
{
    Components::iterator it = components_.begin() + index;

    if ( it != components_.end() )
    {
        if ( *it ) { delete *it; } *it = nullptr;
        components_.erase(it);
    }

    Update();
}

void Aircraft::SetData(const AircraftData& data)
{
    data_ = data;
}

std::string Aircraft::ToString() const
{
    std::string metric = ToStringMetric();
    std::string imperial = ToStringImperial();
    return metric + imperial;
}

void Aircraft::DeleteAllComponents()
{
    Components::iterator it = components_.begin();

    while ( it != components_.end() )
    {
        if ( *it ) { delete *it; } *it = nullptr;
        it = components_.erase(it);
    }

    Update();
}

bool Aircraft::ReadData( QDomElement *dataNode )
{
    QDomElement nodeGeneral = dataNode->firstChildElement("general");
    QDomElement nodeFuselage = dataNode->firstChildElement("fuselage");
    QDomElement nodeWing = dataNode->firstChildElement("wing");
    QDomElement nodeHorTail = dataNode->firstChildElement("hor_tail");
    QDomElement nodeVerTail = dataNode->firstChildElement("ver_tail");
    QDomElement nodeLandingGear = dataNode->firstChildElement("landing_gear");
    QDomElement nodeEngine = dataNode->firstChildElement("engine");
    QDomElement nodeRotors = dataNode->firstChildElement("rotors");
    QDomElement nodeModel3D = dataNode->firstChildElement("model3d");

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

        if ( result ) result = ReadDataGeneral     ( &nodeGeneral     );
        if ( result ) result = ReadDataFuselage    ( &nodeFuselage    );
        if ( result ) result = ReadDataWing        ( &nodeWing        );
        if ( result ) result = ReadDataHorTail     ( &nodeHorTail     );
        if ( result ) result = ReadDataVerTail     ( &nodeVerTail     );
        if ( result ) result = ReadDataLandingGear ( &nodeLandingGear );
        if ( result ) result = ReadDataEngine      ( &nodeEngine      );
        if ( result ) result = ReadDataRotors      ( &nodeRotors      );
        if ( result ) result = ReadDataModel3D     ( &nodeModel3D     );

        return result;
    }

    return false;
}

bool Aircraft::ReadDataGeneral(QDomElement* parentNode)
{
    QDomElement nodeM_empty = parentNode->firstChildElement("m_empty");
    QDomElement nodeMTOW = parentNode->firstChildElement("mtow");
    QDomElement nodeM_maxLand = parentNode->firstChildElement("m_max_land");
    QDomElement nodeMaxFuel = parentNode->firstChildElement("max_fuel");
    QDomElement nodeNzMax = parentNode->firstChildElement("nz_max");
    QDomElement nodeNzMaxLand = parentNode->firstChildElement("nz_max_land");
    QDomElement nodeStallV = parentNode->firstChildElement("stall_v");
    QDomElement nodeCruiseH = parentNode->firstChildElement("h_cruise");
    QDomElement nodeCruiseV = parentNode->firstChildElement("v_cruise");
    QDomElement nodeMachMax = parentNode->firstChildElement("mach_max");
    QDomElement nodeNavyAC = parentNode->firstChildElement("navy_ac");

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
        data_.general.m_empty = units::mass::kilogram_t(nodeM_empty.text().toDouble());
        data_.general.mtow = units::mass::kilogram_t(nodeMTOW.text().toDouble());
        data_.general.m_maxLand = units::mass::kilogram_t(nodeM_maxLand.text().toDouble());
        data_.general.m_maxFuel = units::mass::kilogram_t(nodeMaxFuel.text().toDouble());
        data_.general.nz_max = nodeNzMax.text().toDouble();
        data_.general.nz_maxLand = nodeNzMaxLand.text().toDouble();
        data_.general.v_stall = units::velocity::knot_t(nodeStallV.text().toDouble());
        data_.general.h_cruise = units::length::foot_t(nodeCruiseH.text().toDouble());
        data_.general.v_cruise = units::velocity::knot_t(nodeCruiseV.text().toDouble());
        data_.general.mach_max = nodeMachMax.text().toDouble();
        data_.general.navy_ac = nodeNavyAC.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::ReadDataFuselage(QDomElement* parentNode)
{
    QDomElement nodeCargoDoor = parentNode->firstChildElement("cargo_door");
    QDomElement nodeFuseL = parentNode->firstChildElement("lenght");
    QDomElement nodeFuseH = parentNode->firstChildElement("height");
    QDomElement nodeFuseW = parentNode->firstChildElement("width");
    QDomElement nodeNoseL = parentNode->firstChildElement("nose_length");
    QDomElement nodeWettedArea = parentNode->firstChildElement("wetted_area");
    QDomElement nodePressVol = parentNode->firstChildElement("press_vol");
    QDomElement nodeFuselageLG = parentNode->firstChildElement("landing_gear");
    QDomElement nodeCargoRamp = parentNode->firstChildElement("cargo_ramp");
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

        data_.fuselage.cargo_door = AircraftData::Fuselage::NoCargoDoor;

        switch ( cargo_door_temp )
        {
        case AircraftData::Fuselage::NoCargoDoor:
            data_.fuselage.cargo_door = AircraftData::Fuselage::NoCargoDoor;
            break;
        case AircraftData::Fuselage::OneSideCargoDoor:
            data_.fuselage.cargo_door = AircraftData::Fuselage::OneSideCargoDoor;
            break;
        case AircraftData::Fuselage::TwoSideCargoDoor:
            data_.fuselage.cargo_door = AircraftData::Fuselage::TwoSideCargoDoor;
            break;
        case AircraftData::Fuselage::AftClamshellDoor:
            data_.fuselage.cargo_door = AircraftData::Fuselage::AftClamshellDoor;
            break;
        case AircraftData::Fuselage::TwoSideAndAftDoor:
            data_.fuselage.cargo_door = AircraftData::Fuselage::TwoSideAndAftDoor;
            break;
        }

        data_.fuselage.l = units::length::meter_t(nodeFuseL.text().toDouble());
        data_.fuselage.h = units::length::meter_t(nodeFuseH.text().toDouble());
        data_.fuselage.w = units::length::meter_t(nodeFuseW.text().toDouble());
        data_.fuselage.l_n = units::length::meter_t(nodeNoseL.text().toDouble());
        data_.fuselage.wetted_area = units::area::square_meter_t(nodeWettedArea.text().toDouble());
        data_.fuselage.press_vol = units::volume::cubic_meter_t(nodePressVol.text().toDouble());
        data_.fuselage.landing_gear = nodeFuselageLG .text().toInt();
        data_.fuselage.cargo_ramp = nodeCargoRamp  .text().toInt();
        data_.fuselage.wetted_area_override = nodeWettedAreaOverride.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::ReadDataWing(QDomElement* parentNode)
{
    QDomElement nodeWingArea = parentNode->firstChildElement("area");
    QDomElement nodeWingAreaExp = parentNode->firstChildElement("area_exp");
    QDomElement nodeWingSpan = parentNode->firstChildElement("span");
    QDomElement nodeWingSweep = parentNode->firstChildElement("sweep");
    QDomElement nodeWingCTip = parentNode->firstChildElement("c_tip");
    QDomElement nodeWingCRoot = parentNode->firstChildElement("c_root");
    QDomElement nodeWingAR = parentNode->firstChildElement("ar");
    QDomElement nodeWingTR = parentNode->firstChildElement("tr");
    QDomElement nodeWingTC = parentNode->firstChildElement("tc");
    QDomElement nodeWingFuel = parentNode->firstChildElement("fuel");
    QDomElement nodeCtrlArea = parentNode->firstChildElement("ctrl_area");
    QDomElement nodeWingDelta = parentNode->firstChildElement("delta");
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
        data_.wing.area = units::area::square_meter_t(nodeWingArea.text().toDouble());
        data_.wing.area_exp = units::area::square_meter_t(nodeWingAreaExp.text().toDouble());
        data_.wing.span = units::length::meter_t(nodeWingSpan.text().toDouble());
        data_.wing.sweep = units::angle::degree_t(nodeWingSweep.text().toDouble());
        data_.wing.c_tip = units::length::meter_t(nodeWingCTip.text().toDouble());
        data_.wing.c_root = units::length::meter_t(nodeWingCRoot.text().toDouble());
        data_.wing.ar = nodeWingAR.text().toDouble();
        data_.wing.tr = nodeWingTR.text().toDouble();
        data_.wing.tc = nodeWingTC.text().toDouble();
        data_.wing.fuel = units::mass::kilogram_t(nodeWingFuel.text().toDouble());
        data_.wing.ctrl_area = units::area::square_meter_t(nodeCtrlArea.text().toDouble());
        data_.wing.delta = nodeWingDelta.text().toInt();
        data_.wing.var_sweep = nodeWingVarSweep .text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::ReadDataHorTail(QDomElement* parentNode)
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
        data_.hor_tail.area = area::square_meter_t(nodeHorTailArea.text().toDouble());
        data_.hor_tail.span = length::meter_t(nodeHorTailSpan.text().toDouble());
        data_.hor_tail.sweep = angle::degree_t(nodeHorTailSweep.text().toDouble());
        data_.hor_tail.c_tip = length::meter_t(nodeHorTailCTip.text().toDouble());
        data_.hor_tail.c_root = length::meter_t(nodeHorTailCRoot.text().toDouble());
        data_.hor_tail.tc = nodeHorTailTC.text().toDouble();
        data_.hor_tail.elev_area = area::square_meter_t(nodeElevArea.text().toDouble());
        data_.hor_tail.w_f = length::meter_t(nodeHorTailWF.text().toDouble());
        data_.hor_tail.arm = length::meter_t(nodeHorTailArm.text().toDouble());
        data_.hor_tail.ar = nodeHorTailAR.text().toDouble();
        data_.hor_tail.tr = nodeHorTailTR.text().toDouble();
        data_.hor_tail.moving = nodeHorTailMoving.text().toInt();
        data_.hor_tail.rolling = nodeHorTailRolling.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::ReadDataVerTail(QDomElement* parentNode)
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
        data_.ver_tail.area = area::square_meter_t(nodeVerTailArea.text().toDouble());
        data_.ver_tail.height = length::meter_t(nodeVerTailHeight.text().toDouble());
        data_.ver_tail.sweep = angle::degree_t(nodeVerTailSweep.text().toDouble());
        data_.ver_tail.c_tip = length::meter_t(nodeVerTailCTip.text().toDouble());
        data_.ver_tail.c_root = length::meter_t(nodeVerTailCRoot.text().toDouble());
        data_.ver_tail.tc = nodeVerTailTC.text().toDouble();
        data_.ver_tail.arm = length::meter_t(nodeVerTailArm.text().toDouble());
        data_.ver_tail.rudd_area = area::square_meter_t(nodeRuddArea.text().toDouble());
        data_.ver_tail.ar = nodeVerTailAR.text().toDouble();
        data_.ver_tail.tr = nodeVerTailTR.text().toDouble();
        data_.ver_tail.t_tail = nodeTailT.text().toInt();
        data_.ver_tail.rotor = nodeVerTailRotor.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::ReadDataLandingGear(QDomElement* parentNode)
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
        data_.landing_gear.main_l = length::meter_t(nodeMainGearL.text().toDouble());
        data_.landing_gear.nose_l = length::meter_t(nodeNoseGearL.text().toDouble());
        data_.landing_gear.main_wheels = nodeMainGearWheels.text().toInt();
        data_.landing_gear.main_struts = nodeMainGearStruts.text().toInt();
        data_.landing_gear.nose_wheels = nodeNoseGearWheels.text().toInt();
        data_.landing_gear.fixed = nodeGearFixed.text().toInt();
        data_.landing_gear.cross = nodeGearCross.text().toInt();
        data_.landing_gear.tripod = nodeGearTripod.text().toInt();
        data_.landing_gear.main_kneel = nodeMainGearKneel.text().toInt();
        data_.landing_gear.nose_kneel = nodeNoseGearKneel.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::ReadDataEngine(QDomElement* parentNode)
{
    QDomElement nodeEngineMass = parentNode->firstChildElement("mass");

    if ( !nodeEngineMass.isNull() )
    {
        data_.engine.mass = mass::kilogram_t(nodeEngineMass.text().toDouble());

        return true;
    }

    return false;
}

bool Aircraft::ReadDataRotors(QDomElement* parentNode)
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
        data_.rotors.main_r = length::meter_t(nodeMainRotorR.text().toDouble());
        data_.rotors.main_cb = length::meter_t(nodeMainRotorCB.text().toDouble());
        data_.rotors.main_rpm = angular_velocity::rpm_t(nodeMainRotorRPM.text().toDouble());
        data_.rotors.main_gear_ratio = nodeMainRotorGR.text().toDouble();
        data_.rotors.tail_r = length::meter_t(nodeTailRotorR.text().toDouble());
        data_.rotors.mcp = power::horsepower_t(nodePowerLimit.text().toDouble());
        data_.rotors.main_tip_vel = velocity::meters_per_second_t(nodeMainRotorTipVel.text().toDouble());
        data_.rotors.main_blades = nodeMainRotorBlades.text().toInt();

        return true;
    }

    return false;
}

bool Aircraft::ReadDataModel3D(QDomElement* parentNode)
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
        data_.model3d.file = nodeModelFile.text();
        data_.model3d.offset_x = length::meter_t(nodeOffsetX.text().toDouble());
        data_.model3d.offset_y = length::meter_t(nodeOffsetY.text().toDouble());
        data_.model3d.offset_z = length::meter_t(nodeOffsetZ.text().toDouble());
        data_.model3d.rotation_x = angle::degree_t(nodeRotationX.text().toDouble());
        data_.model3d.rotation_y = angle::degree_t(nodeRotationY.text().toDouble());
        data_.model3d.rotation_z = angle::degree_t(nodeRotationZ.text().toDouble());
        data_.model3d.scale = nodeScale.text().toDouble();

        return true;
    }

    return false;
}

bool Aircraft::ReadComponents(QDomElement* componentsNode)
{
    QDomElement nodeComponent = componentsNode->firstChildElement();

    while ( !nodeComponent.isNull() )
    {
        Component* temp = nullptr;

        if ( nodeComponent.tagName() == AllElse::xmlTagName )
        {
            temp = new AllElse(&data_);
        }
        else if ( nodeComponent.tagName() == Engine::xmlTagName )
        {
            temp = new Engine(&data_);
        }
        else if ( nodeComponent.tagName() == Fuselage::xmlTagName )
        {
            temp = new Fuselage(&data_);
        }
        else if ( nodeComponent.tagName() == GearMain::xmlTagName )
        {
            temp = new GearMain(&data_);
        }
        else if ( nodeComponent.tagName() == GearNose::xmlTagName )
        {
            temp = new GearNose(&data_);
        }
        else if ( nodeComponent.tagName() == RotorDrive::xmlTagName )
        {
            temp = new RotorDrive(&data_);
        }
        else if ( nodeComponent.tagName() == RotorHub::xmlTagName )
        {
            temp = new RotorHub(&data_);
        }
        else if ( nodeComponent.tagName() == RotorMain::xmlTagName )
        {
            temp = new RotorMain(&data_);
        }
        else if ( nodeComponent.tagName() == RotorTail::xmlTagName )
        {
            temp = new RotorTail(&data_);
        }
        else if ( nodeComponent.tagName() == TailHor::xmlTagName )
        {
            temp = new TailHor(&data_);
        }
        else if ( nodeComponent.tagName() == TailVer::xmlTagName )
        {
            temp = new TailVer(&data_);
        }
        else if ( nodeComponent.tagName() == Wing::xmlTagName )
        {
            temp = new Wing(&data_);
        }

        if ( temp )
        {
            temp->Read(&nodeComponent);
            components_.push_back(temp);
        }

        nodeComponent = nodeComponent.nextSiblingElement();
    }

    return true;
}

void Aircraft::SaveDataGeneral(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "m_empty", data_.general.m_empty());
    XmlUtils::SaveTextNode(doc, parentNode, "mtow", data_.general.mtow());
    XmlUtils::SaveTextNode(doc, parentNode, "m_max_land", data_.general.m_maxLand());
    XmlUtils::SaveTextNode(doc, parentNode, "max_fuel", data_.general.m_maxFuel());
    XmlUtils::SaveTextNode(doc, parentNode, "nz_max", data_.general.nz_max);
    XmlUtils::SaveTextNode(doc, parentNode, "nz_max_land", data_.general.nz_maxLand);
    XmlUtils::SaveTextNode(doc, parentNode, "stall_v", data_.general.v_stall());
    XmlUtils::SaveTextNode(doc, parentNode, "h_cruise", data_.general.h_cruise());
    XmlUtils::SaveTextNode(doc, parentNode, "v_cruise", data_.general.v_cruise());
    XmlUtils::SaveTextNode(doc, parentNode, "mach_max", data_.general.mach_max);
    XmlUtils::SaveTextNode(doc, parentNode, "navy_ac", data_.general.navy_ac);
}

void Aircraft::SaveDataFuselage(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "cargo_door", QString::number(data_.fuselage.cargo_door));
    XmlUtils::SaveTextNode(doc, parentNode, "lenght", data_.fuselage.l());
    XmlUtils::SaveTextNode(doc, parentNode, "height", data_.fuselage.h());
    XmlUtils::SaveTextNode(doc, parentNode, "width", data_.fuselage.w());
    XmlUtils::SaveTextNode(doc, parentNode, "nose_length", data_.fuselage.l_n());
    XmlUtils::SaveTextNode(doc, parentNode, "wetted_area", data_.fuselage.wetted_area());
    XmlUtils::SaveTextNode(doc, parentNode, "press_vol", data_.fuselage.press_vol());
    XmlUtils::SaveTextNode(doc, parentNode, "landing_gear", data_.fuselage.landing_gear);
    XmlUtils::SaveTextNode(doc, parentNode, "cargo_ramp", data_.fuselage.cargo_ramp);
    XmlUtils::SaveTextNode(doc, parentNode, "wetted_area_override", data_.fuselage.wetted_area_override);
}

void Aircraft::SaveDataWing(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "area", data_.wing.area());
    XmlUtils::SaveTextNode(doc, parentNode, "area_exp", data_.wing.area_exp());
    XmlUtils::SaveTextNode(doc, parentNode, "span", data_.wing.span());
    XmlUtils::SaveTextNode(doc, parentNode, "sweep", data_.wing.sweep());
    XmlUtils::SaveTextNode(doc, parentNode, "c_tip", data_.wing.c_tip());
    XmlUtils::SaveTextNode(doc, parentNode, "c_root", data_.wing.c_root());
    XmlUtils::SaveTextNode(doc, parentNode, "ar", data_.wing.ar);
    XmlUtils::SaveTextNode(doc, parentNode, "tr", data_.wing.tr);
    XmlUtils::SaveTextNode(doc, parentNode, "tc", data_.wing.tc);
    XmlUtils::SaveTextNode(doc, parentNode, "fuel", data_.wing.fuel());
    XmlUtils::SaveTextNode(doc, parentNode, "ctrl_area", data_.wing.ctrl_area());
    XmlUtils::SaveTextNode(doc, parentNode, "delta", data_.wing.delta);
    XmlUtils::SaveTextNode(doc, parentNode, "var_sweep", data_.wing.var_sweep);
}

void Aircraft::SaveDataHorTail(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "area", data_.hor_tail.area());
    XmlUtils::SaveTextNode(doc, parentNode, "span", data_.hor_tail.span());
    XmlUtils::SaveTextNode(doc, parentNode, "sweep", data_.hor_tail.sweep());
    XmlUtils::SaveTextNode(doc, parentNode, "c_tip", data_.hor_tail.c_tip());
    XmlUtils::SaveTextNode(doc, parentNode, "c_root", data_.hor_tail.c_root());
    XmlUtils::SaveTextNode(doc, parentNode, "tc", data_.hor_tail.tc);
    XmlUtils::SaveTextNode(doc, parentNode, "elev_area", data_.hor_tail.elev_area());
    XmlUtils::SaveTextNode(doc, parentNode, "w_f", data_.hor_tail.w_f());
    XmlUtils::SaveTextNode(doc, parentNode, "arm", data_.hor_tail.arm());
    XmlUtils::SaveTextNode(doc, parentNode, "ar", data_.hor_tail.ar);
    XmlUtils::SaveTextNode(doc, parentNode, "tr", data_.hor_tail.tr);
    XmlUtils::SaveTextNode(doc, parentNode, "moving", data_.hor_tail.moving);
    XmlUtils::SaveTextNode(doc, parentNode, "rolling", data_.hor_tail.rolling);
}

void Aircraft::SaveDataVerTail(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "area", data_.ver_tail.area());
    XmlUtils::SaveTextNode(doc, parentNode, "height", data_.ver_tail.height());
    XmlUtils::SaveTextNode(doc, parentNode, "sweep", data_.ver_tail.sweep());
    XmlUtils::SaveTextNode(doc, parentNode, "c_tip", data_.ver_tail.c_tip());
    XmlUtils::SaveTextNode(doc, parentNode, "c_root", data_.ver_tail.c_root());
    XmlUtils::SaveTextNode(doc, parentNode, "tc", data_.ver_tail.tc);
    XmlUtils::SaveTextNode(doc, parentNode, "arm", data_.ver_tail.arm());
    XmlUtils::SaveTextNode(doc, parentNode, "rudd_area", data_.ver_tail.rudd_area());
    XmlUtils::SaveTextNode(doc, parentNode, "ar", data_.ver_tail.ar);
    XmlUtils::SaveTextNode(doc, parentNode, "tr", data_.ver_tail.tr);
    XmlUtils::SaveTextNode(doc, parentNode, "t_tail", data_.ver_tail.t_tail);
    XmlUtils::SaveTextNode(doc, parentNode, "rotor", data_.ver_tail.rotor);
}

void Aircraft::SaveDataLandingGear(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "main_gear_l", data_.landing_gear.main_l());
    XmlUtils::SaveTextNode(doc, parentNode, "nose_gear_l", data_.landing_gear.nose_l());
    XmlUtils::SaveTextNode(doc, parentNode, "main_gear_wheels", static_cast<int>(data_.landing_gear.main_wheels));
    XmlUtils::SaveTextNode(doc, parentNode, "main_gear_struts", static_cast<int>(data_.landing_gear.main_struts));
    XmlUtils::SaveTextNode(doc, parentNode, "nose_gear_wheels", static_cast<int>(data_.landing_gear.nose_wheels));
    XmlUtils::SaveTextNode(doc, parentNode, "fixed", data_.landing_gear.fixed);
    XmlUtils::SaveTextNode(doc, parentNode, "cross", data_.landing_gear.cross);
    XmlUtils::SaveTextNode(doc, parentNode, "tripod", data_.landing_gear.tripod);
    XmlUtils::SaveTextNode(doc, parentNode, "main_gear_kneel", data_.landing_gear.main_kneel);
    XmlUtils::SaveTextNode(doc, parentNode, "nose_gear_kneel", data_.landing_gear.nose_kneel);
}

void Aircraft::SaveDataEngine(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "mass", data_.engine.mass());
}

void Aircraft::SaveDataRotors(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "main_rotor_radius", data_.rotors.main_r());
    XmlUtils::SaveTextNode(doc, parentNode, "main_rotor_blade_chord", data_.rotors.main_cb());
    XmlUtils::SaveTextNode(doc, parentNode, "main_rotor_rpm", data_.rotors.main_rpm());
    XmlUtils::SaveTextNode(doc, parentNode, "main_rotor_gear_ratio", data_.rotors.main_gear_ratio);
    XmlUtils::SaveTextNode(doc, parentNode, "tail_rotor_radius", data_.rotors.tail_r());
    XmlUtils::SaveTextNode(doc, parentNode, "mcp", data_.rotors.mcp());
    XmlUtils::SaveTextNode(doc, parentNode, "main_rotor_tip_vel", data_.rotors.main_tip_vel());
    XmlUtils::SaveTextNode(doc, parentNode, "main_rotor_blades", static_cast<int>(data_.rotors.main_blades));
}

void Aircraft::SaveDataModel3D(QDomDocument* doc, QDomElement* parentNode)
{
    XmlUtils::SaveTextNode(doc, parentNode, "model_file", data_.model3d.file);
    XmlUtils::SaveTextNode(doc, parentNode, "offset_x", data_.model3d.offset_x());
    XmlUtils::SaveTextNode(doc, parentNode, "offset_y", data_.model3d.offset_y());
    XmlUtils::SaveTextNode(doc, parentNode, "offset_z", data_.model3d.offset_z());
    XmlUtils::SaveTextNode(doc, parentNode, "rotation_x", data_.model3d.rotation_x());
    XmlUtils::SaveTextNode(doc, parentNode, "rotation_y", data_.model3d.rotation_y());
    XmlUtils::SaveTextNode(doc, parentNode, "rotation_z", data_.model3d.rotation_z());
    XmlUtils::SaveTextNode(doc, parentNode, "scale", data_.model3d.scale);
}

std::string Aircraft::ToStringMetric() const
{
    units::mass::kilogram_t me = totalEmptyMass_;

    units::length::meter_t cg_x = centerOfMass_.x();
    units::length::meter_t cg_y = centerOfMass_.y();
    units::length::meter_t cg_z = centerOfMass_.z();

    units::moment_of_inertia::kilogram_square_meter_t i_xx = inertiaMatrix_.ixx();
    units::moment_of_inertia::kilogram_square_meter_t i_xy = inertiaMatrix_.ixy();
    units::moment_of_inertia::kilogram_square_meter_t i_xz = inertiaMatrix_.ixz();

    units::moment_of_inertia::kilogram_square_meter_t i_yx = inertiaMatrix_.iyx();
    units::moment_of_inertia::kilogram_square_meter_t i_yy = inertiaMatrix_.iyy();
    units::moment_of_inertia::kilogram_square_meter_t i_yz = inertiaMatrix_.iyz();

    units::moment_of_inertia::kilogram_square_meter_t i_zx = inertiaMatrix_.izx();
    units::moment_of_inertia::kilogram_square_meter_t i_zy = inertiaMatrix_.izy();
    units::moment_of_inertia::kilogram_square_meter_t i_zz = inertiaMatrix_.izz();

    return AircraftToString(me,
                            cg_x, cg_y, cg_z,
                            i_xx, i_xy, i_xz,
                            i_yx, i_yy, i_yz,
                            i_zx, i_zy, i_zz);
}

std::string Aircraft::ToStringImperial() const
{
    units::mass::pound_t me = totalEmptyMass_;

    units::length::inch_t cg_x = centerOfMass_.x();
    units::length::inch_t cg_y = centerOfMass_.y();
    units::length::inch_t cg_z = centerOfMass_.z();

    units::moment_of_inertia::slug_square_feet_t i_xx = inertiaMatrix_.ixx();
    units::moment_of_inertia::slug_square_feet_t i_xy = inertiaMatrix_.ixy();
    units::moment_of_inertia::slug_square_feet_t i_xz = inertiaMatrix_.ixz();

    units::moment_of_inertia::slug_square_feet_t i_yx = inertiaMatrix_.iyx();
    units::moment_of_inertia::slug_square_feet_t i_yy = inertiaMatrix_.iyy();
    units::moment_of_inertia::slug_square_feet_t i_yz = inertiaMatrix_.iyz();

    units::moment_of_inertia::slug_square_feet_t i_zx = inertiaMatrix_.izx();
    units::moment_of_inertia::slug_square_feet_t i_zy = inertiaMatrix_.izy();
    units::moment_of_inertia::slug_square_feet_t i_zz = inertiaMatrix_.izz();

    return AircraftToString(me,
                            cg_x, cg_y, cg_z,
                            i_xx, i_xy, i_xz,
                            i_yx, i_yy, i_yz,
                            i_zx, i_zy, i_zz);
}
