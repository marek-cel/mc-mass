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
        double m_maxTO;             ///< [kg] maximum take-off mass
        double m_maxLand;           ///< [kg] maximum landing mass
        double nz_max;              ///< [-] Nz max
        double nz_maxLand;          ///< [-] Nz max (landing)
        double stall_v;             ///< [kts] stall speed
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
        enum CargoDoors
        {
            NoCargoDoors = 0,       ///< no cargo doors
            OneSideCargoDoors,      ///< one side cargo doors
            TwoSideCargoDoors,      ///< two side cargo doors
            AftClamshellDoors,      ///< aft clamshell doors
            TwoSideAndAftDoors      ///< two side and aft clamshell doors
        };

        CargoDoors cargo_door;      ///< cargo doors type

        double l;                   ///< [m] fuselage length
        double h;                   ///< [m] fuselage height
        double w;                   ///< [m] fuselage width

        double nl;                  ///< [m] nose length

        double wetted_area;         ///< [m^2] fuselage wetted area
        double press_vol;           ///< [m^3] volume of pressurized section

        bool mounted_lg;            ///< specifies if main landing gear is fuselage mounted
        bool cargo_ramp;            ///< specifies if helicopter has a cargo ramp
    };

    /**
     * @brief The Wing struct
     */
    struct Wing
    {
        double area;                ///< [m^2] wing area
        double exp;                 ///< [m^2] wing exposed area
        double span;                ///< [m] wing span
        double sweep;               ///< [deg] wing sweep at 25% chord
        double c_t;                 ///< [m] wing tip chord
        double c_r;                 ///< [m] wing root chord
        double ar;                  ///< [-] wing aspect ratio
        double tr;                  ///< [-] wing taper ratio
        double tc;                  ///< [-] wing thickness ratio
        double fuel;                ///< [kg] wing fuel capacity
        double ctrl_area;           ///< [m^2] wing mounted control surface area

        bool delta;                 ///< specifies if delta wing
        bool var;                   ///< specifies if wing has variable sweep
    };

    /**
     * @brief The HorizontalTail struct
     */
    struct HorizontalTail
    {
        double area;                ///< [m^2] horizontal tail area
        double span;                ///< [m] horizontal tail span
        double sweep;               ///< [deg] horizontal tail sweep at 25% MAC
        double c_t;                 ///< [m] horizontal tail tip chord
        double c_r;                 ///< [m] horizontal tail root chord
        double tc;                  ///< [-] horizontal tail thickness ratio
        double elev_area;           ///< [m^2] elevator area
        double fw;                  ///< [m] fuselage width at horizontal tail intersection
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
        double c_t;                 ///< [m] vertical tail tip chord
        double c_r;                 ///< [m] vertical tail root chord
        double tc;                  ///< [-] vertical tail thickness ratio
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
        double engine;              ///< [kg] engine mass
    };

    /**
     * @brief The Rotors struct
     */
    struct Rotors
    {
        double m_rotor_r;           ///< [m]   main rotor radius
        double m_blades_c;          ///< [m]   main rotor blades chord
        double m_rotor_rpm;         ///< [rpm] main rotor rotation speed
        double m_rotor_gear;        ///< [-]   main rotor gearing ratio
        double t_rotor_r;           ///< [m]   tail rotor radius
        double rotor_mcp;           ///< [hp]  drive system power limit (MCP)
        double m_rotor_tv;          ///< [m/s] main rotor blade tip velocity

        int m_rotor_nb;             ///< number of main rotor blades
    };

    Type           type;            ///< aircraft type
    General        general;         ///< general aircraft data
    Fuselage       fuselage;        ///< fuselage data
    Wing           wing;            ///< wing data
    HorizontalTail hTail;           ///< horizontal tail data
    VerticalTail   vTail;           ///< vertical tail data
    LandingGear    lGear;           ///< lannding gear data
    Engine         engine;          ///< engine data
    Rotors         rotors;          ///< helicopter rotors data

};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // AIRCRAFTDATA_H_
