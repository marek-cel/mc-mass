#include "ExampleData.h"

////////////////////////////////////////////////////////////////////////////////

mc::AircraftData ExampleData::getDataFighterAttack()
{
    mc::AircraftData data;

    data.type = mc::AircraftData::FighterAttack;

    // general
    data.general.m_empty    = 0.0;
    data.general.mtow       = 0.0;
    data.general.m_maxLand  = 0.0;
    data.general.nz_max     = 0.0;
    data.general.nz_maxLand = 0.0;
    data.general.v_stall    = 0.0;
    data.general.h_cruise   = 0.0;
    data.general.v_cruise   = 0.0;
    data.general.mach_max   = 0.0;

    data.general.navy_ac = false;

    // fuselage
    data.fuselage.cargo_door = mc::AircraftData::Fuselage::NoCargoDoor;

    data.fuselage.l = 0.0;
    data.fuselage.h = 0.0;
    data.fuselage.w = 0.0;

    data.fuselage.l_n = 0.0;

    data.fuselage.wetted_area = 0.0;
    data.fuselage.press_vol   = 0.0;

    data.fuselage.landing_gear = false;
    data.fuselage.cargo_ramp   = false;

    // wing
    data.wing.area      = 0.0;
    data.wing.area_exp  = 0.0;
    data.wing.span      = 0.0;
    data.wing.sweep     = 0.0;
    data.wing.c_tip     = 0.0;
    data.wing.c_root    = 0.0;
    data.wing.ar        = 0.0;
    data.wing.tr        = 0.0;
    data.wing.t_c       = 0.0;
    data.wing.fuel      = 0.0;
    data.wing.ctrl_area = 0.0;

    data.wing.delta     = false;
    data.wing.var_sweep = false;

    // horizontal tail
    data.hor_tail.area      = 0.0;
    data.hor_tail.span      = 0.0;
    data.hor_tail.sweep     = 0.0;
    data.hor_tail.c_tip     = 0.0;
    data.hor_tail.c_root    = 0.0;
    data.hor_tail.t_c       = 0.0;
    data.hor_tail.elev_area = 0.0;
    data.hor_tail.w_f       = 0.0;
    data.hor_tail.arm       = 0.0;
    data.hor_tail.ar        = 0.0;
    data.hor_tail.tr        = 0.0;

    data.hor_tail.moving  = false;
    data.hor_tail.rolling = false;

    // vertical tail
    data.ver_tail.area      = 0.0;
    data.ver_tail.height    = 0.0;
    data.ver_tail.sweep     = 0.0;
    data.ver_tail.c_tip     = 0.0;
    data.ver_tail.c_root    = 0.0;
    data.ver_tail.t_c       = 0.0;
    data.ver_tail.arm       = 0.0;
    data.ver_tail.rudd_area = 0.0;
    data.ver_tail.ar        = 0.0;
    data.ver_tail.tr        = 0.0;

    data.ver_tail.t_tail = false;
    data.ver_tail.rotor  = false;

    // landing gear
    data.landing_gear.main_l = 0.0;
    data.landing_gear.nose_l = 0.0;

    data.landing_gear.main_wheels = 0;
    data.landing_gear.main_struts = 0;
    data.landing_gear.nose_wheels = 0;

    data.landing_gear.fixed  = false;
    data.landing_gear.cross  = false;
    data.landing_gear.tripod = false;

    data.landing_gear.main_kneel = false;
    data.landing_gear.nose_kneel = false;

    // engine
    data.engine.mass = 0.0;

    // rotors
    data.rotors.main_r          = 0.0;
    data.rotors.main_cb         = 0.0;
    data.rotors.main_rpm        = 0.0;
    data.rotors.main_gear_ratio = 0.0;
    data.rotors.tail_r          = 0.0;
    data.rotors.mcp             = 0.0;
    data.rotors.main_tip_vel    = 0.0;

    data.rotors.main_blades = 0;

    return data;
}

////////////////////////////////////////////////////////////////////////////////

mc::AircraftData ExampleData::getDataCargoTransport()
{
    mc::AircraftData data;

    data.type = mc::AircraftData::CargoTransport;

    // general
    data.general.m_empty    = 0.0;
    data.general.mtow       = 0.0;
    data.general.m_maxLand  = 0.0;
    data.general.nz_max     = 0.0;
    data.general.nz_maxLand = 0.0;
    data.general.v_stall    = 0.0;
    data.general.h_cruise   = 0.0;
    data.general.v_cruise   = 0.0;
    data.general.mach_max   = 0.0;

    data.general.navy_ac = false;

    // fuselage
    data.fuselage.cargo_door = mc::AircraftData::Fuselage::NoCargoDoor;

    data.fuselage.l = 0.0;
    data.fuselage.h = 0.0;
    data.fuselage.w = 0.0;

    data.fuselage.l_n = 0.0;

    data.fuselage.wetted_area = 0.0;
    data.fuselage.press_vol   = 0.0;

    data.fuselage.landing_gear = false;
    data.fuselage.cargo_ramp   = false;

    // wing
    data.wing.area      = 0.0;
    data.wing.area_exp  = 0.0;
    data.wing.span      = 0.0;
    data.wing.sweep     = 0.0;
    data.wing.c_tip     = 0.0;
    data.wing.c_root    = 0.0;
    data.wing.ar        = 0.0;
    data.wing.tr        = 0.0;
    data.wing.t_c       = 0.0;
    data.wing.fuel      = 0.0;
    data.wing.ctrl_area = 0.0;

    data.wing.delta     = false;
    data.wing.var_sweep = false;

    // horizontal tail
    data.hor_tail.area      = 0.0;
    data.hor_tail.span      = 0.0;
    data.hor_tail.sweep     = 0.0;
    data.hor_tail.c_tip     = 0.0;
    data.hor_tail.c_root    = 0.0;
    data.hor_tail.t_c       = 0.0;
    data.hor_tail.elev_area = 0.0;
    data.hor_tail.w_f       = 0.0;
    data.hor_tail.arm       = 0.0;
    data.hor_tail.ar        = 0.0;
    data.hor_tail.tr        = 0.0;

    data.hor_tail.moving  = false;
    data.hor_tail.rolling = false;

    // vertical tail
    data.ver_tail.area      = 0.0;
    data.ver_tail.height    = 0.0;
    data.ver_tail.sweep     = 0.0;
    data.ver_tail.c_tip     = 0.0;
    data.ver_tail.c_root    = 0.0;
    data.ver_tail.t_c       = 0.0;
    data.ver_tail.arm       = 0.0;
    data.ver_tail.rudd_area = 0.0;
    data.ver_tail.ar        = 0.0;
    data.ver_tail.tr        = 0.0;

    data.ver_tail.t_tail = false;
    data.ver_tail.rotor  = false;

    // landing gear
    data.landing_gear.main_l = 0.0;
    data.landing_gear.nose_l = 0.0;

    data.landing_gear.main_wheels = 0;
    data.landing_gear.main_struts = 0;
    data.landing_gear.nose_wheels = 0;

    data.landing_gear.fixed  = false;
    data.landing_gear.cross  = false;
    data.landing_gear.tripod = false;

    data.landing_gear.main_kneel = false;
    data.landing_gear.nose_kneel = false;

    // engine
    data.engine.mass = 0.0;

    // rotors
    data.rotors.main_r          = 0.0;
    data.rotors.main_cb         = 0.0;
    data.rotors.main_rpm        = 0.0;
    data.rotors.main_gear_ratio = 0.0;
    data.rotors.tail_r          = 0.0;
    data.rotors.mcp             = 0.0;
    data.rotors.main_tip_vel    = 0.0;

    data.rotors.main_blades = 0;

    return data;
}

////////////////////////////////////////////////////////////////////////////////

mc::AircraftData ExampleData::getDataGeneralAviation()
{
    mc::AircraftData data;

    data.type = mc::AircraftData::GeneralAviation;

    // general
    data.general.m_empty    = 754.0;
    data.general.mtow       = 1157.0;
    data.general.m_maxLand  = 1157.0;
    data.general.nz_max     = 4.4;
    data.general.nz_maxLand = 4.4;
    data.general.v_stall    = 53.0;
    data.general.h_cruise   = 3000.0;
    data.general.v_cruise   = 124.0;
    data.general.mach_max   = 0.0;

    data.general.navy_ac = false;

    // fuselage
    data.fuselage.cargo_door = mc::AircraftData::Fuselage::NoCargoDoor;

    data.fuselage.l = 7.22;
    data.fuselage.h = 1.4;
    data.fuselage.w = 1.1;

    data.fuselage.l_n = 2.0;

    data.fuselage.wetted_area = 26.43;
    data.fuselage.press_vol   = 0.0;

    data.fuselage.landing_gear = true;
    data.fuselage.cargo_ramp   = false;

    // wing
    data.wing.area      = 16.17;
    data.wing.area_exp  = 15.9;
    data.wing.span      = 11.0;
    data.wing.sweep     = 0.0;
    data.wing.c_tip     = 1.13;
    data.wing.c_root    = 1.7;
    data.wing.ar        = 7.483;
    data.wing.tr        = 0.665;
    data.wing.t_c       = 0.12;
    data.wing.fuel      = 165.0;
    data.wing.ctrl_area = 2.75;

    data.wing.delta     = false;
    data.wing.var_sweep = false;

    // horizontal tail
    data.hor_tail.area      = 2.0;
    data.hor_tail.span      = 3.48;
    data.hor_tail.sweep     = 0.0;
    data.hor_tail.c_tip     = 0.82;
    data.hor_tail.c_root    = 1.3;
    data.hor_tail.t_c       = 0.12;
    data.hor_tail.elev_area = 1.35;
    data.hor_tail.w_f       = 0.35;
    data.hor_tail.arm       = 4.79;
    data.hor_tail.ar        = 6.055;
    data.hor_tail.tr        = 0.631;

    data.hor_tail.moving  = false;
    data.hor_tail.rolling = false;

    // vertical tail
    data.ver_tail.area      = 1.04;
    data.ver_tail.height    = 1.77;
    data.ver_tail.sweep     = 33.6;
    data.ver_tail.c_tip     = 0.7;
    data.ver_tail.c_root    = 1.42;
    data.ver_tail.t_c       = 0.09;
    data.ver_tail.arm       = 4.79;
    data.ver_tail.rudd_area = 0.76;
    data.ver_tail.ar        = 3.012;
    data.ver_tail.tr        = 0.493;

    data.ver_tail.t_tail = false;
    data.ver_tail.rotor  = false;

    // landing gear
    data.landing_gear.main_l = 0.7;
    data.landing_gear.nose_l = 0.6;

    data.landing_gear.main_wheels = 2;
    data.landing_gear.main_struts = 2;
    data.landing_gear.nose_wheels = 1;

    data.landing_gear.fixed  = true;
    data.landing_gear.cross  = false;
    data.landing_gear.tripod = false;

    data.landing_gear.main_kneel = false;
    data.landing_gear.nose_kneel = false;

    // engine
    data.engine.mass = 126.0;

    // rotors
    data.rotors.main_r          = 0.0;
    data.rotors.main_cb         = 0.0;
    data.rotors.main_rpm        = 0.0;
    data.rotors.main_gear_ratio = 0.0;
    data.rotors.tail_r          = 0.0;
    data.rotors.mcp             = 0.0;
    data.rotors.main_tip_vel    = 0.0;

    data.rotors.main_blades = 0;

    return data;
}

////////////////////////////////////////////////////////////////////////////////

mc::AircraftData ExampleData::getDataHelicopter()
{
    mc::AircraftData data;

    data.type = mc::AircraftData::Helicopter;

    // general
    data.general.m_empty    = 0.0;
    data.general.mtow       = 0.0;
    data.general.m_maxLand  = 0.0;
    data.general.nz_max     = 0.0;
    data.general.nz_maxLand = 0.0;
    data.general.v_stall    = 0.0;
    data.general.h_cruise   = 0.0;
    data.general.v_cruise   = 0.0;
    data.general.mach_max   = 0.0;

    data.general.navy_ac = false;

    // fuselage
    data.fuselage.cargo_door = mc::AircraftData::Fuselage::NoCargoDoor;

    data.fuselage.l = 0.0;
    data.fuselage.h = 0.0;
    data.fuselage.w = 0.0;

    data.fuselage.l_n = 0.0;

    data.fuselage.wetted_area = 0.0;
    data.fuselage.press_vol   = 0.0;

    data.fuselage.landing_gear = false;
    data.fuselage.cargo_ramp   = false;

    // wing
    data.wing.area      = 0.0;
    data.wing.area_exp  = 0.0;
    data.wing.span      = 0.0;
    data.wing.sweep     = 0.0;
    data.wing.c_tip     = 0.0;
    data.wing.c_root    = 0.0;
    data.wing.ar        = 0.0;
    data.wing.tr        = 0.0;
    data.wing.t_c       = 0.0;
    data.wing.fuel      = 0.0;
    data.wing.ctrl_area = 0.0;

    data.wing.delta     = false;
    data.wing.var_sweep = false;

    // horizontal tail
    data.hor_tail.area      = 0.0;
    data.hor_tail.span      = 0.0;
    data.hor_tail.sweep     = 0.0;
    data.hor_tail.c_tip     = 0.0;
    data.hor_tail.c_root    = 0.0;
    data.hor_tail.t_c       = 0.0;
    data.hor_tail.elev_area = 0.0;
    data.hor_tail.w_f       = 0.0;
    data.hor_tail.arm       = 0.0;
    data.hor_tail.ar        = 0.0;
    data.hor_tail.tr        = 0.0;

    data.hor_tail.moving  = false;
    data.hor_tail.rolling = false;

    // vertical tail
    data.ver_tail.area      = 0.0;
    data.ver_tail.height    = 0.0;
    data.ver_tail.sweep     = 0.0;
    data.ver_tail.c_tip     = 0.0;
    data.ver_tail.c_root    = 0.0;
    data.ver_tail.t_c       = 0.0;
    data.ver_tail.arm       = 0.0;
    data.ver_tail.rudd_area = 0.0;
    data.ver_tail.ar        = 0.0;
    data.ver_tail.tr        = 0.0;

    data.ver_tail.t_tail = false;
    data.ver_tail.rotor  = false;

    // landing gear
    data.landing_gear.main_l = 0.0;
    data.landing_gear.nose_l = 0.0;

    data.landing_gear.main_wheels = 0;
    data.landing_gear.main_struts = 0;
    data.landing_gear.nose_wheels = 0;

    data.landing_gear.fixed  = false;
    data.landing_gear.cross  = false;
    data.landing_gear.tripod = false;

    data.landing_gear.main_kneel = false;
    data.landing_gear.nose_kneel = false;

    // engine
    data.engine.mass = 0.0;

    // rotors
    data.rotors.main_r          = 0.0;
    data.rotors.main_cb         = 0.0;
    data.rotors.main_rpm        = 0.0;
    data.rotors.main_gear_ratio = 0.0;
    data.rotors.tail_r          = 0.0;
    data.rotors.mcp             = 0.0;
    data.rotors.main_tip_vel    = 0.0;

    data.rotors.main_blades = 0;

    return data;
}
