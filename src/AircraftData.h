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
#ifndef AIRCRAFTDATA_H_
#define AIRCRAFTDATA_H_

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

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
        FighterAttack   = 0,        ///< Fighter/Attack
        CargoTransport  = 1,        ///< Cargo/Transport/Bombers
        GeneralAviation = 2,        ///< General Aviation
        Helicopter      = 3         ///< Helicopter
    };

    /**
     * @brief The General struct
     */
    struct General
    {
        double m_empty;             ///< [kg] empty mass
        double mtow;                ///< [kg] maximum take-off mass
        double m_maxLand;           ///< [kg] maximum landing mass
        double nz_max;              ///< [-] Nz max
        double nz_maxLand;          ///< [-] Nz max (landing)
        double v_stall;             ///< [kts] stall speed
        double h_cruise;            ///< [ft]  cruise altitude
        double v_cruise;            ///< [kts] cruise speed
        double mach_max;            ///< [-] maximum design Mach number

        bool navy_ac;               ///< specifies if aircraft is navy carrier aircraft
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
            NoCargoDoor = 0,        ///< no cargo door
            OneSideCargoDoor,       ///< one side cargo door
            TwoSideCargoDoor,       ///< two side cargo door
            AftClamshellDoor,       ///< aft clamshell door
            TwoSideAndAftDoor       ///< two side and aft clamshell door
        };

        CargoDoor cargo_door;       ///< cargo doors type

        double l;                   ///< [m] fuselage length
        double h;                   ///< [m] fuselage height
        double w;                   ///< [m] fuselage width

        double l_n;                 ///< [m] nose length

        double wetted_area;         ///< [m^2] fuselage wetted area
        double press_vol;           ///< [m^3] volume of pressurized section

        bool landing_gear;          ///< specifies if main landing gear is fuselage mounted
        bool cargo_ramp;            ///< specifies if helicopter has a cargo ramp
    };

    /**
     * @brief The Wing struct
     */
    struct Wing
    {
        double area;                ///< [m^2] wing area
        double area_exp;            ///< [m^2] wing exposed area
        double span;                ///< [m] wing span
        double sweep;               ///< [deg] wing sweep at 25% chord
        double c_tip;               ///< [m] wing tip chord
        double c_root;              ///< [m] wing root chord
        double ar;                  ///< [-] wing aspect ratio
        double tr;                  ///< [-] wing taper ratio
        double t_c;                 ///< [-] wing thickness ratio
        double fuel;                ///< [kg] wing fuel capacity
        double ctrl_area;           ///< [m^2] wing mounted control surface area

        bool delta;                 ///< specifies if delta wing
        bool var_sweep;             ///< specifies if wing has variable sweep
    };

    /**
     * @brief The HorizontalTail struct
     */
    struct HorizontalTail
    {
        double area;                ///< [m^2] horizontal tail area
        double span;                ///< [m] horizontal tail span
        double sweep;               ///< [deg] horizontal tail sweep at 25% MAC
        double c_tip;               ///< [m] horizontal tail tip chord
        double c_root;              ///< [m] horizontal tail root chord
        double t_c;                 ///< [-] horizontal tail thickness ratio
        double elev_area;           ///< [m^2] elevator area
        double w_f;                 ///< [m] fuselage width at horizontal tail intersection
        double arm;                 ///< [m] horizontal tail arm
        double ar;                  ///< [-] horizontal tail aspect ratio
        double tr;                  ///< [-] horizontal tail taper ratio

        bool moving;                ///< specifies if horizontal tail is all moving
        bool rolling;               ///< specifies if horizontal tail is rolling
    };

    /**
     * @brief The VerticalTail struct
     */
    struct VerticalTail
    {
        double area;                ///< [m^2] vertical tail area
        double height;              ///< [m] vertical tail height
        double sweep;               ///< [deg] vertical tail sweep at 25% MAC
        double c_tip;               ///< [m] vertical tail tip chord
        double c_root;              ///< [m] vertical tail root chord
        double t_c;                 ///< [-] vertical tail thickness ratio
        double arm;                 ///< [m] vertical tail arm
        double rudd_area;           ///< [m^2] rudder area
        double ar;                  ///< [-] vertical tail aspect ratio
        double tr;                  ///< [-] vertical tail taper ratio

        bool t_tail;                ///< specifies if T-tail
        bool rotor;                 ///< specifies if tail rotor is mounted on the vertical tail
    };

    /**
     * @brief The LandingGear struct
     */
    struct LandingGear
    {
        double main_l;              ///< [m] extended main gear length
        double nose_l;              ///< [m] extended nose gear length

        int main_wheels;            ///< main gear wheels number
        int main_struts;            ///< main gear struts number
        int nose_wheels;            ///< nose gear wheels number

        bool fixed;                 ///< specifies if gear is fixed
        bool cross;                 ///< specifies if gear has a cross-beam (like F-111)
        bool tripod;                ///< specifies if gear is a tripod (like A-7)

        bool main_kneel;            ///< specifies if main gear is kneeling
        bool nose_kneel;            ///< specifies if nose gear is kneeling
    };

    /**
     * @brief The Engine struct
     */
    struct Engine
    {
        double mass;                ///< [kg] engine mass
    };

    /**
     * @brief The Rotors struct
     */
    struct Rotors
    {
        double main_r;              ///< [m]   main rotor radius
        double main_cb;             ///< [m]   main rotor blades chord
        double main_rpm;            ///< [rpm] main rotor rotation speed
        double main_gear_ratio;     ///< [-]   main rotor gearing ratio
        double tail_r;              ///< [m]   tail rotor radius
        double mcp;                 ///< [hp]  drive system power limit (MCP - Maximum Continuous Power)
        double main_tip_vel;        ///< [m/s] main rotor blade tip velocity

        int main_blades;            ///< number of main rotor blades
    };

    Type           type;            ///< aircraft type
    General        general;         ///< general aircraft data
    Fuselage       fuselage;        ///< fuselage data
    Wing           wing;            ///< wing data
    HorizontalTail hor_tail;        ///< horizontal tail data
    VerticalTail   ver_tail;        ///< vertical tail data
    LandingGear    landing_gear;    ///< lannding gear data
    Engine         engine;          ///< engine data
    Rotors         rotors;          ///< helicopter rotors data

};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // AIRCRAFTDATA_H_
