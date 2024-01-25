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
#ifndef MC_MASS_AIRCRAFTDATA_H_
#define MC_MASS_AIRCRAFTDATA_H_

#include <units.h>

#include <QString>

#include <utils/units_extra.h>

using namespace units;
using namespace units::literals;

/**
 * @brief The AircraftData struct.
 */
struct AircraftData
{
    /**
     * @brief The aircraft type enum.
     */
    enum Type
    {
        FighterAttack   = 0,                        ///< Fighter/Attack
        CargoTransport  = 1,                        ///< Cargo/Transport/Bombers
        GeneralAviation = 2,                        ///< General Aviation
        Helicopter      = 3                         ///< Helicopter
    };

    /**
     * @brief The General struct
     */
    struct General
    {
        mass::kilogram_t m_empty = 0.0_kg;          ///< empty mass
        mass::kilogram_t mtow = 0.0_kg;             ///< maximum take-off mass
        mass::kilogram_t m_maxLand = 0.0_kg;        ///< maximum landing mass
        double nz_max = 0.0;                        ///< Nz max
        double nz_maxLand = 0.0;                    ///< Nz max (landing)
        velocity::knot_t v_stall = 0.0_kts;         ///< stall speed
        length::foot_t h_cruise = 0.0_ft;           ///< cruise altitude
        velocity::knot_t v_cruise = 0.0_kts;        ///< cruise speed
        double mach_max = 0.0;                      ///< maximum design Mach number
        bool navy_ac = false;                       ///< specifies if aircraft is navy carrier aircraft
    };

    /**
     * @brief The Fuselage struct
     */
    struct Fuselage
    {
        /**
         * @brief The CargoDoor enum
         */
        enum CargoDoor
        {
            NoCargoDoor = 0,                        ///< no cargo door
            OneSideCargoDoor,                       ///< one side cargo door
            TwoSideCargoDoor,                       ///< two side cargo door
            AftClamshellDoor,                       ///< aft clamshell door
            TwoSideAndAftDoor                       ///< two side and aft clamshell door
        };

        CargoDoor cargo_door = NoCargoDoor;         ///< cargo doors type
        length::meter_t l = 0.0_m;                  ///< fuselage length
        length::meter_t h = 0.0_m;                  ///< fuselage height
        length::meter_t w = 0.0_m;                  ///< fuselage width
        length::meter_t l_n = 0.0_m;                ///< nose length
        area::square_meter_t wetted_area = 0.0_sq_m;///< fuselage wetted area
        volume::cubic_meter_t press_vol = 0.0_cu_m; ///< volume of pressurized section
        bool landing_gear = false;                  ///< specifies if main landing gear is fuselage mounted
        bool cargo_ramp = false;                    ///< specifies if helicopter has a cargo ramp
        bool wetted_area_override = false;          ///< specifies if wetted area override is enabled
    };

    /**
     * @brief The Wing struct
     */
    struct Wing
    {
        area::square_meter_t area = 0.0_sq_m;       ///< wing area
        area::square_meter_t area_exp = 0.0_sq_m;   ///< wing exposed area
        length::meter_t span = 0.0_m;               ///< wing span
        angle::degree_t sweep = 0.0_deg;            ///< wing sweep at 25% chord
        length::meter_t c_tip  = 0.0_m;             ///< wing tip chord
        length::meter_t c_root = 0.0_m;             ///< wing root chord
        double ar = 0.0;                            ///< wing aspect ratio
        double tr = 0.0;                            ///< wing taper ratio
        double tc = 0.0;                            ///< wing thickness ratio
        mass::kilogram_t fuel = 0.0_kg;             ///< wing fuel capacity
        area::square_meter_t ctrl_area = 0.0_sq_m;  ///< wing mounted control surface area
        bool delta = false;                         ///< specifies if delta wing
        bool var_sweep = false;                     ///< specifies if wing has variable sweep
    };

    /**
     * @brief The HorizontalTail struct
     */
    struct HorizontalTail
    {
        area::square_meter_t area = 0.0_sq_m;       ///< horizontal tail area
        length::meter_t span = 0.0_m;               ///< horizontal tail span
        angle::degree_t sweep = 0.0_deg;            ///< horizontal tail sweep at 25% MAC
        length::meter_t c_tip  = 0.0_m;             ///< horizontal tail tip chord
        length::meter_t c_root = 0.0_m;             ///< horizontal tail root chord
        double tc = 0.0;                            ///< horizontal tail thickness ratio
        area::square_meter_t elev_area = 0.0_sq_m;  ///< elevator area
        length::meter_t w_f = 0.0_m;                ///< fuselage width at horizontal tail intersection
        length::meter_t arm = 0.0_m;                ///< horizontal tail arm
        double ar = 0.0;                            ///< horizontal tail aspect ratio
        double tr = 0.0;                            ///< horizontal tail taper ratio
        bool moving  = false;                       ///< specifies if horizontal tail is all moving
        bool rolling = false;                       ///< specifies if horizontal tail is rolling
    };

    /**
     * @brief The VerticalTail struct
     */
    struct VerticalTail
    {
        area::square_meter_t area = 0.0_sq_m;       ///< vertical tail area
        length::meter_t height = 0.0_m;             ///< vertical tail height
        angle::degree_t sweep = 0.0_deg;            ///< vertical tail sweep at 25% MAC
        length::meter_t c_tip  = 0.0_m;             ///< vertical tail tip chord
        length::meter_t c_root = 0.0_m;             ///< vertical tail root chord
        double tc = 0.0;                            ///< vertical tail thickness ratio
        length::meter_t arm = 0.0_m;                ///< vertical tail arm
        area::square_meter_t rudd_area = 0.0_sq_m;  ///< rudder area
        double ar = 0.0;                            ///< vertical tail aspect ratio
        double tr = 0.0;                            ///< vertical tail taper ratio
        bool t_tail = false;                        ///< specifies if T-tail
        bool rotor  = false;                        ///< specifies if tail rotor is mounted on the vertical tail
    };

    /**
     * @brief The LandingGear struct
     */
    struct LandingGear
    {
        length::meter_t main_l = 0.0_m;             ///< extended main gear length
        length::meter_t nose_l = 0.0_m;             ///< extended nose gear length
        unsigned int main_wheels = 0;               ///< main gear wheels number
        unsigned int main_struts = 0;               ///< main gear struts number
        unsigned int nose_wheels = 0;               ///< nose gear wheels number
        bool fixed  = false;                        ///< specifies if gear is fixed
        bool cross  = false;                        ///< specifies if gear has a cross-beam (like F-111)
        bool tripod = false;                        ///< specifies if gear is a tripod (like A-7)
        bool main_kneel = false;                    ///< specifies if main gear is kneeling
        bool nose_kneel = false;                    ///< specifies if nose gear is kneeling
    };

    /**
     * @brief The Engine struct
     */
    struct Engine
    {
        mass::kilogram_t mass = 0.0_kg;             ///< engine mass
    };

    /**
     * @brief The Rotors struct
     */
    struct Rotors
    {
        length::meter_t main_r = 0.0_m;             ///< main rotor radius
        length::meter_t main_cb = 0.0_m;            ///< main rotor blades chord
        angular_velocity::rpm_t main_rpm = 0.0_rpm; ///< main rotor rotation speed
        double main_gear_ratio = 0.0;               ///< main rotor gearing ratio
        length::meter_t tail_r = 0.0_m;             ///< tail rotor radius
        power::horsepower_t mcp = 0.0_hp;           ///< drive system power limit (MCP - Maximum Continuous Power)
        velocity::meters_per_second_t main_tip_vel = 0.0_mps;   ///< main rotor blade tip velocity
        unsigned int main_blades = 0;               ///< number of main rotor blades
    };

    /**
     * @brief The 3D Model struct
     */
    struct Model3D
    {
        QString file;                               ///<
        length::meter_t offset_x = 0.0_m;           ///<
        length::meter_t offset_y = 0.0_m;           ///<
        length::meter_t offset_z = 0.0_m;           ///<
        angle::degree_t rotation_x = 0.0_deg;       ///<
        angle::degree_t rotation_y = 0.0_deg;       ///<
        angle::degree_t rotation_z = 0.0_deg;       ///<
        double scale = 1.0;                         ///<
    };

    Type type = FighterAttack;      ///< aircraft type

    General        general;         ///< general aircraft data
    Fuselage       fuselage;        ///< fuselage data
    Wing           wing;            ///< wing data
    HorizontalTail hor_tail;        ///< horizontal tail data
    VerticalTail   ver_tail;        ///< vertical tail data
    LandingGear    landing_gear;    ///< lannding gear data
    Engine         engine;          ///< engine data
    Rotors         rotors;          ///< helicopter rotors data
    Model3D        model3d;         ///< 3D model data

};

#endif // MC_MASS_AIRCRAFTDATA_H_
