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

#include <mass/Fuselage.h>

#include <utils/Atmosphere.h>

constexpr char Fuselage::xmlTagName[];

units::mass::kilogram_t Fuselage::GetEstimatedMass(const AircraftData& data)
{
    area::square_foot_t s_f = data.fuselage.wetted_area;

    // Rayner2018: Aircraft Design, p.568, table 15.2
    mass::pound_t m1 = 0.0_lb;
    {
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = 4.8_lb * s_f();
        }

        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = 5.0_lb * s_f();
        }

        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = 1.4_lb * s_f();
        }
    }

    mass::pound_t m2 = 0.0_lb;
    {
        mass::pound_t w_dg = GetDesignGrossWeight(data);
        double n_z  = 1.5 * data.general.nz_max;
        length::foot_t l = data.fuselage.l;
        length::foot_t d = data.fuselage.h;
        length::foot_t w = data.fuselage.w;

        // Rayner2018: Aircraft Design, p.572, eq.15.4
        if ( data.type == AircraftData::FighterAttack )
        {
            // p.577
            double k_dwf = data.wing.delta ? 0.774 : 1.0;

            m2 = 0.499_lb * k_dwf
                    * pow(w_dg(), 0.35)
                    * pow(n_z, 0.25)
                    * pow(l(), 0.5)
                    * pow(d(), 0.849)
                    * pow(w(), 0.685);
        }

        // Rayner2018: Aircraft Design, p.574, eq.15.28
        if ( data.type == AircraftData::CargoTransport )
        {
            double k_door = 1.0;

            switch ( data.fuselage.cargo_door )
            {
                case AircraftData::Fuselage::NoCargoDoor       : k_door = 1.0;  break;
                case AircraftData::Fuselage::OneSideCargoDoor  : k_door = 1.06; break;
                case AircraftData::Fuselage::TwoSideCargoDoor  : k_door = 1.12; break;
                case AircraftData::Fuselage::AftClamshellDoor  : k_door = 1.12; break;
                case AircraftData::Fuselage::TwoSideAndAftDoor : k_door = 1.25; break;
            }

            double k_lg = data.fuselage.landing_gear ? 1.12 : 1.0;
            length::foot_t b_w = data.wing.span;
            angle::radian_t sweep = data.wing.sweep;
            double lambda = data.wing.tr;

            // p.577
            double k_ws = 0.75
                    * ((1.0 + 2.0 * lambda)/(1.0 + lambda))
                    * (b_w / l)
                    * tan(sweep());

            m2 = 0.328_lb * k_door * k_lg
                    * pow(w_dg() * n_z, 0.5)
                    * pow(l(), 0.25)
                    * pow(s_f(), 0.302)
                    * pow (1.0 + k_ws, 0.04)
                    * pow(l / d, 0.1);
        }

        // Rayner2018: Aircraft Design, p.576, eq.15.49
        if ( data.type == AircraftData::GeneralAviation )
        {
            length::foot_t l_t = data.hor_tail.arm;
            volume::cubic_foot_t vol_press = data.fuselage.press_vol;
            velocity::meters_per_second_t v = data.general.v_cruise;
            density::kilograms_per_cubic_meter_t rho = Atmosphere::GetDensity(data.general.h_cruise);
            pressure::pounds_per_square_foot_t q = 0.5 * rho * v*v;

            double w_press = 11.9 + pow(vol_press() * 8.0, 0.271); // p.579

            m2 = 0.052_lb
                    * pow(s_f(), 1.086)
                    * pow(n_z * w_dg(), 0.177)
                    * pow(l_t(), -0.051)
                    * pow (l / d, -0.072)
                    * pow(q(), 0.241)
                    + mass::pound_t(w_press);
        }

        // NASA TP-2015-218751, p.232
        if ( data.type == AircraftData::Helicopter )
        {
            mass::pound_t w_mto = data.general.mtow;

            double f_ramp = data.fuselage.cargo_ramp ? 1.3939 : 1.0;

            mass::pound_t w_basic = 5.896_lb * f_ramp
                    * pow(w_mto() / 1000.0, 0.4908)
                    * pow(n_z, 0.1323)
                    * pow(s_f(), 0.2544)
                    * pow(l(), 0.61);

            double chi_basic = 1.0; // ?? technology factor

            m2 = chi_basic * w_basic;

            // same as m2
            m1 = m2;
        }
    }

    return (m1 + m2) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

Fuselage::Fuselage(const AircraftData* data)
    : Component(data)
{
    SetName("Fuselage");
}
