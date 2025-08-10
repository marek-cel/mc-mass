/****************************************************************************//*
 *  Copyright (C) 2025 Marek M. Cel
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

#include <Document.h>

#include <utils/StringUtils.h>
#include <utils/DocUtils.h>
#include <utils/XmlDoc.h>

#include <Log.h>

Result Document::readFile(const std::filesystem::path& path)
{
    std::string extension = path.extension().string();
    if ( misc::compareStrings(extension, ".xml") )
    {
        return Result::Failure;
    }

    XmlDoc doc(path);
    if ( !doc.isOpen() )
    {
        Log::error("Failed to open file: %s", path.string().c_str());
        return Result::Failure;
    }

    if ( Result::Failure == readDocument(doc) )
    {
        Log::error("Failed to read file: %s", path.string().c_str());
        return Result::Failure;
    }

    _path = path;
    _name = path.stem().string();

    return Result::Success;
}

Result Document::saveFile(const std::filesystem::path& path)
{
    std::filesystem::path path_temp = path;
    std::string extension = path_temp.extension().string();
    if ( misc::compareStrings(extension, ".xml") )
    {
        path_temp += ".xml";
    }

    XmlDoc doc;
    if ( Result::Failure == saveDocument(doc) )
    {
        Log::error("Failed to save file: %s", path_temp.string().c_str());
        return Result::Failure;
    }

    if ( Result::Failure == doc.saveFile(path_temp) )
    {
        Log::error("Failed to save file: %s", path_temp.string().c_str());
        return Result::Failure;
    }

    _path = path_temp;
    _name = path_temp.stem().string();

    return Result::Success;
}

Result Document::readDocument(XmlDoc& doc)
{
    XmlNode root_node = doc.getRootNode();
    if ( !root_node.isValid() )
    {
        Log::error("Failed to get root node: %s", doc.getPath().string().c_str());
        return Result::Failure;
    }
    if ( 0 != misc::compareStrings(root_node.getName(), "mcmass") )
    {
        Log::error("Wrong file format: %s", doc.getPath().string().c_str());
        return Result::Failure;
    }

    Result result = Result::Success;
    if ( result == Result::Success ) result = readVehicleData(root_node);
    return result;
}

Result Document::readVehicleData(XmlNode& node)
{
    GET_NODE(node, vehicle_data, "vehicle_data");

    Result result = Result::Success;

    if ( result == Result::Success ) result = readVehicleDataGeneral(vehicle_data);
    if ( result == Result::Success ) result = readVehicleDataFuselage(vehicle_data);
    if ( result == Result::Success ) result = readVehicleDataWing(vehicle_data);
    if ( result == Result::Success ) result = readVehicleDataHorTail(vehicle_data);
    if ( result == Result::Success ) result = readVehicleDataVerTail(vehicle_data);
    if ( result == Result::Success ) result = readVehicleDataLandingGear(vehicle_data);
    if ( result == Result::Success ) result = readVehicleDataEngines(vehicle_data);
    if ( result == Result::Success ) result = readVehicleDataRotors(vehicle_data);

    return result;
}

Result Document::readVehicleDataGeneral(XmlNode& node)
{
    GET_NODE(node, general, "general");

    GET_TEXT(general, vehicle_type, "vehicle_type");
    GET_TEXT(general, empty_mass, "empty_mass");
    GET_TEXT(general, max_takeoff_mass, "max_takeoff_mass");
    GET_TEXT(general, max_landing_mass, "max_landing_mass");
    GET_TEXT(general, max_internal_fuel, "max_internal_fuel");
    GET_TEXT(general, design_gross_weight, "design_gross_weight");
    GET_TEXT(general, max_load_factor, "max_load_factor");
    GET_TEXT(general, max_landing_load_factor, "max_landing_load_factor");
    GET_TEXT(general, stall_speed, "stall_speed");
    GET_TEXT(general, cruise_speed, "cruise_speed");
    GET_TEXT(general, cruise_alt, "cruise_alt");
    GET_TEXT(general, max_mach, "max_mach");
    GET_TEXT(general, carrier_capable, "carrier_capable");

    Vehicle::Data data = _vehicle->getData();
    data.type = static_cast<Vehicle::Type>(misc::toInt(vehicle_type.getText()));
    data.general.empty_mass = units::mass::kilogram_t(misc::toDouble(empty_mass.getText()));
    data.general.max_takeoff_mass = units::mass::kilogram_t(misc::toDouble(max_takeoff_mass.getText()));
    data.general.max_landing_mass = units::mass::kilogram_t(misc::toDouble(max_landing_mass.getText()));
    data.general.max_internal_fuel = units::mass::kilogram_t(misc::toDouble(max_internal_fuel.getText()));
    data.general.design_gross_weight = units::mass::kilogram_t(misc::toDouble(design_gross_weight.getText()));
    data.general.max_load_factor = misc::toDouble(max_load_factor.getText());
    data.general.max_landing_load_factor = misc::toDouble(max_landing_load_factor.getText());
    data.general.stall_speed = units::velocity::meters_per_second_t(misc::toDouble(stall_speed.getText()));
    data.general.cruise_speed = units::velocity::meters_per_second_t(misc::toDouble(cruise_speed.getText()));
    data.general.cruise_alt = units::length::meter_t(misc::toDouble(cruise_alt.getText()));
    data.general.max_mach = misc::toDouble(max_mach.getText());
    data.general.carrier_capable = misc::toBool(carrier_capable.getText(), false);

    _vehicle->setData(data);

    return Result::Success;
}

Result Document::readVehicleDataFuselage(XmlNode& node)
{
    GET_NODE(node, fuselage, "fuselage");

    GET_TEXT(fuselage, cargo_door, "cargo_door");
    GET_TEXT(fuselage, length, "length");
    GET_TEXT(fuselage, height, "height");
    GET_TEXT(fuselage, width, "width");
    GET_TEXT(fuselage, nose_length, "nose_length");
    GET_TEXT(fuselage, wetted_area, "wetted_area");
    GET_TEXT(fuselage, press_volume, "press_volume");
    GET_TEXT(fuselage, fuselage_mount_landing_gear, "fuselage_mount_landing_gear");
    GET_TEXT(fuselage, cargo_ramp, "cargo_ramp");
    GET_TEXT(fuselage, wetted_area_override, "wetted_area_override");

    Vehicle::Data data = _vehicle->getData();
    data.fuselage.cargo_door = static_cast<Vehicle::CargoDoor>(misc::toInt(cargo_door.getText()));
    data.fuselage.length = units::length::meter_t(misc::toDouble(length.getText()));
    data.fuselage.height = units::length::meter_t(misc::toDouble(height.getText()));
    data.fuselage.width = units::length::meter_t(misc::toDouble(width.getText()));
    data.fuselage.nose_length = units::length::meter_t(misc::toDouble(nose_length.getText()));
    data.fuselage.wetted_area = units::area::square_meter_t(misc::toDouble(wetted_area.getText()));
    data.fuselage.press_volume = units::volume::cubic_meter_t(misc::toDouble(press_volume.getText()));
    data.fuselage.fuselage_mount_landing_gear = misc::toBool(fuselage_mount_landing_gear.getText(), false);
    data.fuselage.cargo_ramp = misc::toBool(cargo_ramp.getText(), false);
    data.fuselage.wetted_area_override = misc::toBool(wetted_area_override.getText(), false);

    _vehicle->setData(data);

    return Result::Success;
}

Result Document::readVehicleDataWing(XmlNode& node)
{
    GET_NODE(node, wing, "wing");

    GET_TEXT(wing, area, "area");
    GET_TEXT(wing, exposed_area, "exposed_area");
    GET_TEXT(wing, span, "span");
    GET_TEXT(wing, sweep, "sweep");
    GET_TEXT(wing, root_chord, "root_chord");
    GET_TEXT(wing, tip_chord, "tip_chord");
    GET_TEXT(wing, aspect_ratio, "aspect_ratio");
    GET_TEXT(wing, taper_ratio, "taper_ratio");
    GET_TEXT(wing, thickness_to_chord, "thickness_to_chord");
    GET_TEXT(wing, fuel_mass, "fuel_mass");
    GET_TEXT(wing, control_area, "control_area");
    GET_TEXT(wing, delta_wing, "delta_wing");
    GET_TEXT(wing, var_sweep, "var_sweep");

    Vehicle::Data data = _vehicle->getData();
    data.wing.area = units::area::square_meter_t(misc::toDouble(area.getText()));
    data.wing.exposed_area = units::area::square_meter_t(misc::toDouble(exposed_area.getText()));
    data.wing.span = units::length::meter_t(misc::toDouble(span.getText()));
    data.wing.sweep = units::angle::degree_t(misc::toDouble(sweep.getText()));
    data.wing.root_chord = units::length::meter_t(misc::toDouble(root_chord.getText()));
    data.wing.tip_chord = units::length::meter_t(misc::toDouble(tip_chord.getText()));
    data.wing.aspect_ratio = misc::toDouble(aspect_ratio.getText());
    data.wing.taper_ratio = misc::toDouble(taper_ratio.getText());
    data.wing.thickness_to_chord = misc::toDouble(thickness_to_chord.getText());
    data.wing.fuel_mass = units::mass::kilogram_t(misc::toDouble(fuel_mass.getText()));
    data.wing.control_area = units::area::square_meter_t(misc::toDouble(control_area.getText()));
    data.wing.delta_wing = misc::toBool(delta_wing.getText(), false);
    data.wing.var_sweep = misc::toBool(var_sweep.getText(), false);

    _vehicle->setData(data);

    return Result::Success;
}

Result Document::readVehicleDataHorTail(XmlNode& node)
{
    GET_NODE(node, hor_tail, "hor_tail");

    GET_TEXT(hor_tail, area, "area");
    GET_TEXT(hor_tail, span, "span");
    GET_TEXT(hor_tail, sweep, "sweep");
    GET_TEXT(hor_tail, root_chord, "root_chord");
    GET_TEXT(hor_tail, tip_chord, "tip_chord");
    GET_TEXT(hor_tail, thickness_to_chord, "thickness_to_chord");
    GET_TEXT(hor_tail, elev_area, "elev_area");
    GET_TEXT(hor_tail, fuselage_width, "fuselage_width");
    GET_TEXT(hor_tail, arm, "arm");
    GET_TEXT(hor_tail, aspect_ratio, "aspect_ratio");
    GET_TEXT(hor_tail, taper_ratio, "taper_ratio");
    GET_TEXT(hor_tail, all_moving, "all_moving");
    GET_TEXT(hor_tail, rolling_tail, "rolling_tail");

    Vehicle::Data data = _vehicle->getData();
    data.hor_tail.area = units::area::square_meter_t(misc::toDouble(area.getText()));
    data.hor_tail.span = units::length::meter_t(misc::toDouble(span.getText()));
    data.hor_tail.sweep = units::angle::degree_t(misc::toDouble(sweep.getText()));
    data.hor_tail.root_chord = units::length::meter_t(misc::toDouble(root_chord.getText()));
    data.hor_tail.tip_chord = units::length::meter_t(misc::toDouble(tip_chord.getText()));
    data.hor_tail.thickness_to_chord = misc::toDouble(thickness_to_chord.getText());
    data.hor_tail.elev_area = units::area::square_meter_t(misc::toDouble(elev_area.getText()));
    data.hor_tail.fuselage_width = units::length::meter_t(misc::toDouble(fuselage_width.getText()));
    data.hor_tail.arm = units::length::meter_t(misc::toDouble(arm.getText()));
    data.hor_tail.aspect_ratio = misc::toDouble(aspect_ratio.getText());
    data.hor_tail.taper_ratio = misc::toDouble(taper_ratio.getText());
    data.hor_tail.all_moving = misc::toBool(all_moving.getText(), false);
    data.hor_tail.rolling_tail = misc::toBool(rolling_tail.getText(), false);

    _vehicle->setData(data);

    return Result::Success;
}

Result Document::readVehicleDataVerTail(XmlNode& node)
{
    GET_NODE(node, ver_tail, "ver_tail");

    GET_TEXT(ver_tail, area, "area");
    GET_TEXT(ver_tail, height, "height");
    GET_TEXT(ver_tail, sweep, "sweep");
    GET_TEXT(ver_tail, root_chord, "root_chord");
    GET_TEXT(ver_tail, tip_chord, "tip_chord");
    GET_TEXT(ver_tail, thickness_to_chord, "thickness_to_chord");
    GET_TEXT(ver_tail, rudd_area, "rudd_area");
    GET_TEXT(ver_tail, arm, "arm");
    GET_TEXT(ver_tail, aspect_ratio, "aspect_ratio");
    GET_TEXT(ver_tail, taper_ratio, "taper_ratio");
    GET_TEXT(ver_tail, t_tail, "t_tail");
    GET_TEXT(ver_tail, tail_mounted_rotor, "tail_mounted_rotor");

    Vehicle::Data data = _vehicle->getData();
    data.ver_tail.area = units::area::square_meter_t(misc::toDouble(area.getText()));
    data.ver_tail.height = units::length::meter_t(misc::toDouble(height.getText()));
    data.ver_tail.sweep = units::angle::degree_t(misc::toDouble(sweep.getText()));
    data.ver_tail.root_chord = units::length::meter_t(misc::toDouble(root_chord.getText()));
    data.ver_tail.tip_chord = units::length::meter_t(misc::toDouble(tip_chord.getText()));
    data.ver_tail.thickness_to_chord = misc::toDouble(thickness_to_chord.getText());
    data.ver_tail.rudd_area = units::area::square_meter_t(misc::toDouble(rudd_area.getText()));
    data.ver_tail.arm = units::length::meter_t(misc::toDouble(arm.getText()));
    data.ver_tail.aspect_ratio = misc::toDouble(aspect_ratio.getText());
    data.ver_tail.taper_ratio = misc::toDouble(taper_ratio.getText());
    data.ver_tail.t_tail = misc::toBool(t_tail.getText(), false);
    data.ver_tail.tail_mounted_rotor = misc::toBool(tail_mounted_rotor.getText(), false);

    _vehicle->setData(data);

    return Result::Success;
}

Result Document::readVehicleDataLandingGear(XmlNode& node)
{
    GET_NODE(node, landing_gear, "landing_gear");

    GET_TEXT(landing_gear, main_gear_length, "main_gear_length");
    GET_TEXT(landing_gear, nose_gear_length, "nose_gear_length");
    GET_TEXT(landing_gear, main_gear_wheels, "main_gear_wheels");
    GET_TEXT(landing_gear, main_gear_struts, "main_gear_struts");
    GET_TEXT(landing_gear, nose_gear_wheels, "nose_gear_wheels");
    GET_TEXT(landing_gear, fixed, "fixed");
    GET_TEXT(landing_gear, cross_beam, "cross_beam");
    GET_TEXT(landing_gear, tripod, "tripod");
    GET_TEXT(landing_gear, main_gear_kneeling, "main_gear_kneeling");
    GET_TEXT(landing_gear, nose_gear_kneeling, "nose_gear_kneeling");

    Vehicle::Data data = _vehicle->getData();
    data.landing_gear.main_gear_length = units::length::meter_t(misc::toDouble(main_gear_length.getText()));
    data.landing_gear.nose_gear_length = units::length::meter_t(misc::toDouble(nose_gear_length.getText()));
    data.landing_gear.main_gear_wheels = misc::toInt(main_gear_wheels.getText());
    data.landing_gear.main_gear_struts = misc::toInt(main_gear_struts.getText());
    data.landing_gear.nose_gear_wheels = misc::toInt(nose_gear_wheels.getText());
    data.landing_gear.fixed = misc::toBool(fixed.getText(), false);
    data.landing_gear.cross_beam = misc::toBool(cross_beam.getText(), false);
    data.landing_gear.tripod = misc::toBool(tripod.getText(), false);
    data.landing_gear.main_gear_kneeling = misc::toBool(main_gear_kneeling.getText(), false);
    data.landing_gear.nose_gear_kneeling = misc::toBool(nose_gear_kneeling.getText(), false);

    _vehicle->setData(data);

    return Result::Success;
}

Result Document::readVehicleDataEngines(XmlNode& node)
{
    GET_NODE(node, engines, "engines");

    GET_TEXT(engines, number_of_engines, "number_of_engines");
    GET_TEXT(engines, mass, "mass");
    // GET_TEXT(engines, thrust, "thrust");
    // GET_TEXT(engines, diameter, "diameter");
    // GET_TEXT(engines, takeoff_power, "takeoff_power");
    // GET_TEXT(engines, propeller, "propeller");
    // GET_TEXT(engines, thrust_reverser, "thrust_reverser");

    Vehicle::Data data = _vehicle->getData();
    data.engines.number_of_engines = misc::toInt(number_of_engines.getText());
    data.engines.mass = units::mass::kilogram_t(misc::toDouble(mass.getText()));

    _vehicle->setData(data);

    return Result::Success;
}

Result Document::readVehicleDataRotors(XmlNode& node)
{
    GET_NODE(node, rotors, "rotors");

    GET_TEXT(rotors, main_rotor_radius, "main_rotor_radius");
    GET_TEXT(rotors, main_rotor_blade_chord, "main_rotor_blade_chord");
    GET_TEXT(rotors, main_rotor_rpm, "main_rotor_rpm");
    GET_TEXT(rotors, main_rotor_gear_ratio, "main_rotor_gear_ratio");
    GET_TEXT(rotors, tail_rotor_radius, "tail_rotor_radius");
    GET_TEXT(rotors, mcp, "mcp");
    GET_TEXT(rotors, main_rotor_tip_vel, "main_rotor_tip_vel");
    GET_TEXT(rotors, main_rotor_blades, "main_rotor_blades");

    Vehicle::Data data = _vehicle->getData();
    data.rotors.main_rotor_radius = units::length::meter_t(misc::toDouble(main_rotor_radius.getText()));
    data.rotors.main_rotor_blade_chord = units::length::meter_t(misc::toDouble(main_rotor_blade_chord.getText()));
    data.rotors.main_rotor_rpm = units::angular_velocity::revolutions_per_minute_t(misc::toDouble(main_rotor_rpm.getText()));
    data.rotors.main_rotor_gear_ratio = misc::toDouble(main_rotor_gear_ratio.getText());
    data.rotors.tail_rotor_radius = units::length::meter_t(misc::toDouble(tail_rotor_radius.getText()));
    data.rotors.mcp = units::power::horsepower_t(misc::toDouble(mcp.getText()));
    data.rotors.main_rotor_tip_vel = units::velocity::meters_per_second_t(misc::toDouble(main_rotor_tip_vel.getText()));
    data.rotors.main_rotor_blades = misc::toInt(main_rotor_blades.getText());

    _vehicle->setData(data);

    return Result::Success;
}

Result Document::saveDocument(XmlDoc& doc)
{
    XmlNode root_node = doc.createRootNode("mcmass");
    if ( !root_node.isValid() )
    {
        return Result::Failure;
    }

    Result result = Result::Success;
    if ( result == Result::Success ) result = saveVehicleData(root_node);
    return result;
}

Result Document::saveVehicleData(XmlNode& node)
{
    ADD_NODE(node, vehicle_data, "vehicle_data");

    Result result = Result::Success;

    if ( result == Result::Success ) result = saveVehicleDataGeneral(vehicle_data);
    if ( result == Result::Success ) result = saveVehicleDataFuselage(vehicle_data);
    if ( result == Result::Success ) result = saveVehicleDataWing(vehicle_data);
    if ( result == Result::Success ) result = saveVehicleDataHorTail(vehicle_data);
    if ( result == Result::Success ) result = saveVehicleDataVerTail(vehicle_data);
    if ( result == Result::Success ) result = saveVehicleDataLandingGear(vehicle_data);
    if ( result == Result::Success ) result = saveVehicleDataEngines(vehicle_data);
    if ( result == Result::Success ) result = saveVehicleDataRotors(vehicle_data);

    return result;
}

Result Document::saveVehicleDataGeneral(XmlNode& node)
{
    ADD_NODE(node, general, "general");

    ADD_NODE(general, vehicle_type, "vehicle_type");
    ADD_NODE(general, empty_mass, "empty_mass");
    ADD_NODE(general, max_takeoff_mass, "max_takeoff_mass");
    ADD_NODE(general, max_landing_mass, "max_landing_mass");
    ADD_NODE(general, max_internal_fuel, "max_internal_fuel");
    ADD_NODE(general, design_gross_weight, "design_gross_weight");
    ADD_NODE(general, max_load_factor, "max_load_factor");
    ADD_NODE(general, max_landing_load_factor, "max_landing_load_factor");
    ADD_NODE(general, stall_speed, "stall_speed");
    ADD_NODE(general, cruise_speed, "cruise_speed");
    ADD_NODE(general, cruise_alt, "cruise_alt");
    ADD_NODE(general, max_mach, "max_mach");
    ADD_NODE(general, carrier_capable, "carrier_capable");

    Vehicle::Data data = _vehicle->getData();
    ADD_TEXT(vehicle_type, misc::toString(static_cast<int>(data.type)));
    ADD_TEXT(empty_mass, misc::toString(data.general.empty_mass.value()));
    ADD_TEXT(max_takeoff_mass, misc::toString(data.general.max_takeoff_mass.value()));
    ADD_TEXT(max_landing_mass, misc::toString(data.general.max_landing_mass.value()));
    ADD_TEXT(max_internal_fuel, misc::toString(data.general.max_internal_fuel.value()));
    ADD_TEXT(design_gross_weight, misc::toString(data.general.design_gross_weight.value()));
    ADD_TEXT(max_load_factor, misc::toString(data.general.max_load_factor));
    ADD_TEXT(max_landing_load_factor, misc::toString(data.general.max_landing_load_factor));
    ADD_TEXT(stall_speed, misc::toString(data.general.stall_speed.value()));
    ADD_TEXT(cruise_speed, misc::toString(data.general.cruise_speed.value()));
    ADD_TEXT(cruise_alt, misc::toString(data.general.cruise_alt.value()));
    ADD_TEXT(max_mach, misc::toString(data.general.max_mach));
    ADD_TEXT(carrier_capable, data.general.carrier_capable ? "1" : "0");

    return Result::Success;
}

Result Document::saveVehicleDataFuselage(XmlNode& node)
{
    ADD_NODE(node, fuselage, "fuselage");

    ADD_NODE(fuselage, cargo_door, "cargo_door");
    ADD_NODE(fuselage, length, "length");
    ADD_NODE(fuselage, height, "height");
    ADD_NODE(fuselage, width, "width");
    ADD_NODE(fuselage, nose_length, "nose_length");
    ADD_NODE(fuselage, wetted_area, "wetted_area");
    ADD_NODE(fuselage, press_volume, "press_volume");
    ADD_NODE(fuselage, fuselage_mount_landing_gear, "fuselage_mount_landing_gear");
    ADD_NODE(fuselage, cargo_ramp, "cargo_ramp");
    ADD_NODE(fuselage, wetted_area_override, "wetted_area_override");

    Vehicle::Data data = _vehicle->getData();
    ADD_TEXT(cargo_door, misc::toString(static_cast<int>(data.fuselage.cargo_door)));
    ADD_TEXT(length, misc::toString(data.fuselage.length.value()));
    ADD_TEXT(height, misc::toString(data.fuselage.height.value()));
    ADD_TEXT(width, misc::toString(data.fuselage.width.value()));
    ADD_TEXT(nose_length, misc::toString(data.fuselage.nose_length.value()));
    ADD_TEXT(wetted_area, misc::toString(data.fuselage.wetted_area.value()));
    ADD_TEXT(press_volume, misc::toString(data.fuselage.press_volume.value()));
    ADD_TEXT(fuselage_mount_landing_gear, data.fuselage.fuselage_mount_landing_gear ? "1" : "0");
    ADD_TEXT(cargo_ramp, data.fuselage.cargo_ramp ? "1" : "0");
    ADD_TEXT(wetted_area_override, data.fuselage.wetted_area_override ? "1" : "0");

    return Result::Success;
}

Result Document::saveVehicleDataWing(XmlNode& node)
{
    ADD_NODE(node, wing, "wing");

    ADD_NODE(wing, area, "area");
    ADD_NODE(wing, exposed_area, "exposed_area");
    ADD_NODE(wing, span, "span");
    ADD_NODE(wing, sweep, "sweep");
    ADD_NODE(wing, root_chord, "root_chord");
    ADD_NODE(wing, tip_chord, "tip_chord");
    ADD_NODE(wing, aspect_ratio, "aspect_ratio");
    ADD_NODE(wing, taper_ratio, "taper_ratio");
    ADD_NODE(wing, thickness_to_chord, "thickness_to_chord");
    ADD_NODE(wing, fuel_mass, "fuel_mass");
    ADD_NODE(wing, control_area, "control_area");
    ADD_NODE(wing, delta_wing, "delta_wing");
    ADD_NODE(wing, var_sweep, "var_sweep");

    Vehicle::Data data = _vehicle->getData();
    ADD_TEXT(area, misc::toString(data.wing.area.value()));
    ADD_TEXT(exposed_area, misc::toString(data.wing.exposed_area.value()));
    ADD_TEXT(span, misc::toString(data.wing.span.value()));
    ADD_TEXT(sweep, misc::toString(data.wing.sweep.value()));
    ADD_TEXT(root_chord, misc::toString(data.wing.root_chord.value()));
    ADD_TEXT(tip_chord, misc::toString(data.wing.tip_chord.value()));
    ADD_TEXT(aspect_ratio, misc::toString(data.wing.aspect_ratio));
    ADD_TEXT(taper_ratio, misc::toString(data.wing.taper_ratio));
    ADD_TEXT(thickness_to_chord, misc::toString(data.wing.thickness_to_chord));
    ADD_TEXT(fuel_mass, misc::toString(data.wing.fuel_mass.value()));
    ADD_TEXT(control_area, misc::toString(data.wing.control_area.value()));
    ADD_TEXT(delta_wing, data.wing.delta_wing ? "1" : "0");
    ADD_TEXT(var_sweep, data.wing.var_sweep ? "1" : "0");

    return Result::Success;
}

Result Document::saveVehicleDataHorTail(XmlNode& node)
{
    ADD_NODE(node, hor_tail, "hor_tail");

    ADD_NODE(hor_tail, area, "area");
    ADD_NODE(hor_tail, span, "span");
    ADD_NODE(hor_tail, sweep, "sweep");
    ADD_NODE(hor_tail, root_chord, "root_chord");
    ADD_NODE(hor_tail, tip_chord, "tip_chord");
    ADD_NODE(hor_tail, thickness_to_chord, "thickness_to_chord");
    ADD_NODE(hor_tail, elev_area, "elev_area");
    ADD_NODE(hor_tail, fuselage_width, "fuselage_width");
    ADD_NODE(hor_tail, arm, "arm");
    ADD_NODE(hor_tail, aspect_ratio, "aspect_ratio");
    ADD_NODE(hor_tail, taper_ratio, "taper_ratio");
    ADD_NODE(hor_tail, all_moving, "all_moving");
    ADD_NODE(hor_tail, rolling_tail, "rolling_tail");

    Vehicle::Data data = _vehicle->getData();
    ADD_TEXT(area, misc::toString(data.hor_tail.area.value()));
    ADD_TEXT(span, misc::toString(data.hor_tail.span.value()));
    ADD_TEXT(sweep, misc::toString(data.hor_tail.sweep.value()));
    ADD_TEXT(root_chord, misc::toString(data.hor_tail.root_chord.value()));
    ADD_TEXT(tip_chord, misc::toString(data.hor_tail.tip_chord.value()));
    ADD_TEXT(thickness_to_chord, misc::toString(data.hor_tail.thickness_to_chord));
    ADD_TEXT(elev_area, misc::toString(data.hor_tail.elev_area.value()));
    ADD_TEXT(fuselage_width, misc::toString(data.hor_tail.fuselage_width.value()));
    ADD_TEXT(arm, misc::toString(data.hor_tail.arm.value()));
    ADD_TEXT(aspect_ratio, misc::toString(data.hor_tail.aspect_ratio));
    ADD_TEXT(taper_ratio, misc::toString(data.hor_tail.taper_ratio));
    ADD_TEXT(all_moving, data.hor_tail.all_moving ? "1" : "0");
    ADD_TEXT(rolling_tail, data.hor_tail.rolling_tail ? "1" : "0");

    return Result::Success;
}

Result Document::saveVehicleDataVerTail(XmlNode& node)
{
    ADD_NODE(node, ver_tail, "ver_tail");

    ADD_NODE(ver_tail, area, "area");
    ADD_NODE(ver_tail, height, "height");
    ADD_NODE(ver_tail, sweep, "sweep");
    ADD_NODE(ver_tail, root_chord, "root_chord");
    ADD_NODE(ver_tail, tip_chord, "tip_chord");
    ADD_NODE(ver_tail, thickness_to_chord, "thickness_to_chord");
    ADD_NODE(ver_tail, rudd_area, "rudd_area");
    ADD_NODE(ver_tail, arm, "arm");
    ADD_NODE(ver_tail, aspect_ratio, "aspect_ratio");
    ADD_NODE(ver_tail, taper_ratio, "taper_ratio");
    ADD_NODE(ver_tail, t_tail, "t_tail");
    ADD_NODE(ver_tail, tail_mounted_rotor, "tail_mounted_rotor");

    Vehicle::Data data = _vehicle->getData();
    ADD_TEXT(area, misc::toString(data.ver_tail.area.value()));
    ADD_TEXT(height, misc::toString(data.ver_tail.height.value()));
    ADD_TEXT(sweep, misc::toString(data.ver_tail.sweep.value()));
    ADD_TEXT(root_chord, misc::toString(data.ver_tail.root_chord.value()));
    ADD_TEXT(tip_chord, misc::toString(data.ver_tail.tip_chord.value()));
    ADD_TEXT(thickness_to_chord, misc::toString(data.ver_tail.thickness_to_chord));
    ADD_TEXT(rudd_area, misc::toString(data.ver_tail.rudd_area.value()));
    ADD_TEXT(arm, misc::toString(data.ver_tail.arm.value()));
    ADD_TEXT(aspect_ratio, misc::toString(data.ver_tail.aspect_ratio));
    ADD_TEXT(taper_ratio, misc::toString(data.ver_tail.taper_ratio));
    ADD_TEXT(t_tail, data.ver_tail.t_tail ? "1" : "0");
    ADD_TEXT(tail_mounted_rotor, data.ver_tail.tail_mounted_rotor ? "1" : "0");

    return Result::Success;
}

Result Document::saveVehicleDataLandingGear(XmlNode& node)
{
    ADD_NODE(node, landing_gear, "landing_gear");

    ADD_NODE(landing_gear, main_gear_length, "main_gear_length");
    ADD_NODE(landing_gear, nose_gear_length, "nose_gear_length");
    ADD_NODE(landing_gear, main_gear_wheels, "main_gear_wheels");
    ADD_NODE(landing_gear, main_gear_struts, "main_gear_struts");
    ADD_NODE(landing_gear, nose_gear_wheels, "nose_gear_wheels");
    ADD_NODE(landing_gear, fixed, "fixed");
    ADD_NODE(landing_gear, cross_beam, "cross_beam");
    ADD_NODE(landing_gear, tripod, "tripod");
    ADD_NODE(landing_gear, main_gear_kneeling, "main_gear_kneeling");
    ADD_NODE(landing_gear, nose_gear_kneeling, "nose_gear_kneeling");

    Vehicle::Data data = _vehicle->getData();
    ADD_TEXT(main_gear_length, misc::toString(data.landing_gear.main_gear_length.value()));
    ADD_TEXT(nose_gear_length, misc::toString(data.landing_gear.nose_gear_length.value()));
    ADD_TEXT(main_gear_wheels, misc::toString(data.landing_gear.main_gear_wheels));
    ADD_TEXT(main_gear_struts, misc::toString(data.landing_gear.main_gear_struts));
    ADD_TEXT(nose_gear_wheels, misc::toString(data.landing_gear.nose_gear_wheels));
    ADD_TEXT(fixed, data.landing_gear.fixed ? "1" : "0");
    ADD_TEXT(cross_beam, data.landing_gear.cross_beam ? "1" : "0");
    ADD_TEXT(tripod, data.landing_gear.tripod ? "1" : "0");
    ADD_TEXT(main_gear_kneeling, data.landing_gear.main_gear_kneeling ? "1" : "0");
    ADD_TEXT(nose_gear_kneeling, data.landing_gear.nose_gear_kneeling ? "1" : "0");

    return Result::Success;
}

Result Document::saveVehicleDataEngines(XmlNode& node)
{
    ADD_NODE(node, engines, "engines");

    ADD_NODE(engines, number_of_engines, "number_of_engines");
    ADD_NODE(engines, mass, "mass");
    // ADD_NODE(engines, thrust, "thrust");
    // ADD_NODE(engines, diameter, "diameter");
    // ADD_NODE(engines, takeoff_power, "takeoff_power");
    // ADD_NODE(engines, propeller, "propeller");
    // ADD_NODE(engines, thrust_reverser, "thrust_reverser");

    Vehicle::Data data = _vehicle->getData();
    ADD_TEXT(number_of_engines, misc::toString(data.engines.number_of_engines));
    ADD_TEXT(mass, misc::toString(data.engines.mass.value()));
    // ADD_TEXT(thrust, misc::toString(data.engines.thrust.value()));
    // ADD_TEXT(diameter, misc::toString(data.engines.diameter.value()));
    // ADD_TEXT(takeoff_power, misc::toString(data.engines.takeoff_power.value()));
    // ADD_TEXT(propeller, data.engines.propeller ? "1" : "0");
    // ADD_TEXT(thrust_reverser, data.engines.thrust_reverser ? "1" : "0");

    return Result::Success;
}

Result Document::saveVehicleDataRotors(XmlNode& node)
{
    ADD_NODE(node, rotors, "rotors");

    ADD_NODE(rotors, main_rotor_radius, "main_rotor_radius");
    ADD_NODE(rotors, main_rotor_blade_chord, "main_rotor_blade_chord");
    ADD_NODE(rotors, main_rotor_rpm, "main_rotor_rpm");
    ADD_NODE(rotors, main_rotor_gear_ratio, "main_rotor_gear_ratio");
    ADD_NODE(rotors, tail_rotor_radius, "tail_rotor_radius");
    ADD_NODE(rotors, mcp, "mcp");
    ADD_NODE(rotors, main_rotor_tip_vel, "main_rotor_tip_vel");
    ADD_NODE(rotors, main_rotor_blades, "main_rotor_blades");

    Vehicle::Data data = _vehicle->getData();
    ADD_TEXT(main_rotor_radius, misc::toString(data.rotors.main_rotor_radius.value()));
    ADD_TEXT(main_rotor_blade_chord, misc::toString(data.rotors.main_rotor_blade_chord.value()));
    ADD_TEXT(main_rotor_rpm, misc::toString(data.rotors.main_rotor_rpm.value()));
    ADD_TEXT(main_rotor_gear_ratio, misc::toString(data.rotors.main_rotor_gear_ratio));
    ADD_TEXT(tail_rotor_radius, misc::toString(data.rotors.tail_rotor_radius.value()));
    ADD_TEXT(mcp, misc::toString(data.rotors.mcp.value()));
    ADD_TEXT(main_rotor_tip_vel, misc::toString(data.rotors.main_rotor_tip_vel.value()));
    ADD_TEXT(main_rotor_blades, misc::toString(data.rotors.main_rotor_blades));

    return Result::Success;
}
