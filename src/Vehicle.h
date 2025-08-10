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
#ifndef MC_MASS_VEHICLE_H_
#define MC_MASS_VEHICLE_H_

#include <units.h>

using namespace units::literals;

class Vehicle
{
public:

    enum class Type
    {
        FighterAttack   = 0,    ///< Fighter/Attack
        CargoTransport  = 1,    ///< Cargo/Transport/Bombers
        GeneralAviation = 2,    ///< General Aviation
        Helicopter      = 3     ///< Helicopter
    };

    constexpr static int TypeCount = static_cast<int>(Type::Helicopter) + 1;

    enum class CargoDoor
    {
        NoCargoDoor = 0,        ///< no cargo door
        OneSideCargoDoor,       ///< one side cargo door
        TwoSideCargoDoor,       ///< two side cargo door
        AftClamshellDoor,       ///< aft clamshell door
        TwoSideAndAftDoor       ///< two side and aft clamshell door
    };

    constexpr static int CargoDoorCount = static_cast<int>(CargoDoor::TwoSideAndAftDoor) + 1;

    struct Data
    {
        struct General
        {
            units::mass::kilogram_t empty_mass        = 0_kg;           ///< empty mass
            units::mass::kilogram_t max_takeoff_mass  = 0_kg;           ///< maximum takeoff mass
            units::mass::kilogram_t max_landing_mass  = 0_kg;           ///< maximum landing mass
            units::mass::kilogram_t max_internal_fuel = 0_kg;           ///< maximum fuel mass
            units::mass::kilogram_t design_gross_weight = 0_kg;         ///< design gross weight
            double max_load_factor = 0.0;                               ///< maximum load factor
            double max_landing_load_factor = 0.0;                       ///< maximum landing load factor
            units::velocity::meters_per_second_t stall_speed  = 0_mps;  ///< stall speed
            units::velocity::meters_per_second_t cruise_speed = 0_mps;  ///< cruise speed
            units::length::meter_t cruise_alt = 0_m;                    ///< cruise altitude
            double max_mach = 0.0;                                      ///< maximum mach
            bool carrier_capable = false;                               ///< carrier capable
        };

        struct Fuselage
        {
            CargoDoor cargo_door = CargoDoor::NoCargoDoor;              ///< cargo door type
            units::length::meter_t length = 0_m;                        ///< fuselage structural length (excludes radome cowling, tail cap)
            units::length::meter_t height = 0_m;                        ///< fuselage structural height
            units::length::meter_t width = 0_m;                         ///< fuselage structural width
            units::length::meter_t nose_length = 0_m;                   ///< nose length
            units::area::square_meter_t wetted_area = 0_sq_m;           ///< fuselage wetted area
            units::volume::cubic_meter_t press_volume = 0_cu_m;         ///< volume of pressurized section
            bool fuselage_mount_landing_gear = false;                   ///< specifies if main landing gear is fuselage mounted
            bool cargo_ramp = false;                                    ///< specifies if helicopter has a cargo ramp
            bool wetted_area_override = false;                          ///< specifies if fuselage wetted area is overridden
        };

        struct Wing
        {
            units::area::square_meter_t area = 0.0_sq_m;                ///< wing area
            units::area::square_meter_t exposed_area = 0.0_sq_m;        ///< wing exposed area
            units::length::meter_t span = 0.0_m;                        ///< wing span
            units::angle::degree_t sweep = 0.0_deg;                     ///< wing sweep angle at 25% MAC
            units::length::meter_t root_chord = 0.0_m;                  ///< wing root chord
            units::length::meter_t tip_chord = 0.0_m;                   ///< wing tip chord
            double aspect_ratio = 0.0;                                  ///< wing aspect ratio
            double taper_ratio = 0.0;                                   ///< wing taper ratio
            double thickness_to_chord = 0.0;                            ///< wing thickness to chord ratio at root
            units::mass::kilogram_t fuel_mass = 0.0_kg;                 ///< wing fuel capacity
            units::area::square_meter_t control_area = 0.0_sq_m;        ///< wing mounted control surfaces area
            bool delta_wing = false;                                    ///< specifies if wing is a delta wing
            bool var_sweep = false;                                     ///< specifies if wing has variable sweep
        };

        struct HorizontalTail
        {
            units::area::square_meter_t area = 0.0_sq_m;                ///< horizontal tail area
            units::length::meter_t span = 0.0_m;                        ///< horizontal tail span
            units::angle::degree_t sweep = 0.0_deg;                     ///< horizontal tail sweep angle at 25% MAC
            units::length::meter_t root_chord = 0.0_m;                  ///< horizontal tail root chord
            units::length::meter_t tip_chord = 0.0_m;                   ///< horizontal tail tip chord
            double thickness_to_chord = 0.0;                            ///< horizontal tail thickness to chord ratio
            units::area::square_meter_t elev_area = 0.0_sq_m;           ///< horizontal tail elevator area
            units::length::meter_t fuselage_width = 0.0_m;              ///< fuselage width at horizontal tail
            units::length::meter_t arm = 0.0_m;                         ///< horizontal tail arm
            double aspect_ratio = 0.0;                                  ///< horizontal tail aspect ratio
            double taper_ratio = 0.0;                                   ///< horizontal tail taper ratio
            bool all_moving = false;                                    ///< specifies if horizontal tail is all moving
            bool rolling_tail = false;                                  ///< specifies if horizontal tail is a rolling tail
        };

        struct VerticalTail
        {
            units::area::square_meter_t area = 0.0_sq_m;                ///< vertical tail area
            units::length::meter_t height = 0.0_m;                      ///< vertical tail height
            units::angle::degree_t sweep = 0.0_deg;                     ///< vertical tail sweep angle at 25% MAC
            units::length::meter_t root_chord = 0.0_m;                  ///< vertical tail root chord
            units::length::meter_t tip_chord = 0.0_m;                   ///< vertical tail tip chord
            double thickness_to_chord = 0.0;                            ///< vertical tail thickness to chord ratio
            units::area::square_meter_t rudd_area = 0.0_sq_m;           ///< vertical tail rudder area
            units::length::meter_t arm = 0.0_m;                         ///< vertical tail arm
            double aspect_ratio = 0.0;                                  ///< vertical tail aspect ratio
            double taper_ratio = 0.0;                                   ///< vertical tail taper ratio
            bool t_tail = false;                                        ///< specifies if vertical tail is a T-tail
            bool tail_mounted_rotor = false;                            ///< specifies if vertical tail is a tail mounted rotor
        };

        struct LandingGear
        {
            units::length::meter_t main_gear_length = 0.0_m;            ///< extended main landing gear length
            units::length::meter_t nose_gear_length = 0.0_m;            ///< extended nose landing gear length
            int main_gear_wheels = 0;                                   ///< number of main landing gear wheels
            int main_gear_struts = 0;                                   ///< number of main landing gear struts
            int nose_gear_wheels = 0;                                   ///< number of nose landing gear wheels
            bool fixed = false;                                         ///< specifies if landing gear is fixed
            bool cross_beam = false;                                    ///< specifies if landing gear is a cross beam (like F-111)
            bool tripod = false;                                        ///< specifies if landing gear is a tripod (like A-7)
            bool main_gear_kneeling = false;                            ///< specifies if main landing gear is kneeling
            bool nose_gear_kneeling = false;                            ///< specifies if nose landing gear is kneeling
        };

        struct Engines
        {
            int number_of_engines = 0;                                  ///< number of engines
            units::mass::kilogram_t mass = 0.0_kg;                      ///< mass per engine
            units::force::newton_t thrust = 0.0_N;                      ///< thrust per engine
            units::length::meter_t diameter = 0.0_m;                    ///< engine diameter
            units::power::horsepower_t takeoff_power = 0.0_hp;          ///< takeoff power per engine
            bool propeller = false;                                     ///< specifies if engine is a propeller
            bool thrust_reverser = false;                               ///< specifies if engine has thrust reverser
        };

        struct Rotors
        {
            units::length::meter_t main_rotor_radius = 0.0_m;           ///< main rotor radius
            units::length::meter_t main_rotor_blade_chord = 0.0_m;      ///< main rotor blade chord
            units::angular_velocity::revolutions_per_minute_t main_rotor_rpm = 0.0_rpm; ///< main rotor RPM
            double main_rotor_gear_ratio = 0.0;                         ///< main rotor gear ratio
            units::length::meter_t tail_rotor_radius = 0.0_m;           ///< tail rotor radius
            units::power::horsepower_t mcp = 0.0_hp;                    ///< drive system power limit (MCP - Maximum Continuous Power)
            units::velocity::meters_per_second_t main_rotor_tip_vel = 0.0_mps; ///< main rotor tip velocity
            int main_rotor_blades = 0;                                  ///< number of main rotor blades
        };

        General        general;             ///< general data
        Fuselage       fuselage;            ///< fuselage data
        Wing           wing;                ///< wing data
        HorizontalTail hor_tail;            ///< horizontal tail data
        VerticalTail   ver_tail;            ///< vertical tail data
        LandingGear    landing_gear;        ///< landing gear data
        Engines        engines;             ///< engines data
        Rotors         rotors;              ///< rotors data

        Type type = Type::FighterAttack;    ///< vehicle type
    };

    Data getData() const { return _data; }
    void setData(const Data& data) { _data = data; }

private:

    Data _data; ///< vehicle data
};

#endif // MC_MASS_VEHICLE_H_
