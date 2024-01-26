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

#include <mass/Wing.h>

#include <mcutils/misc/Units.h>

#include <utils/Atmosphere.h>

constexpr char Wing::xmlTagName[];

units::mass::kilogram_t Wing::GetEstimatedMass(const AircraftData& data)
{
    area::square_foot_t s_w = data.wing.area_exp;

    // Rayner2018: Aircraft Design, p.568, table 15.2
    mass::pound_t m1 = 0.0_lb;
    {
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = 9.0_lb * s_w();
        }

        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = 10.0_lb * s_w();
        }

        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = 2.5_lb * s_w();
        }
    }

    mass::pound_t m2 = 0.0_lb;
    {
        mass::pound_t w_dg = GetDesignGrossWeight(data);
        double n_z = 1.5 * data.general.nz_max;
        area::square_foot_t s_csw = data.wing.ctrl_area;
        angle::radian_t sweep = data.wing.sweep;
        double tc_root = data.wing.tc;
        double lambda = data.wing.tr;

        // Rayner2018: Aircraft Design, p.572, eq.15.1
        if ( data.type == AircraftData::FighterAttack )
        {
            double k_vs  = data.wing.var_sweep ? 1.19  : 1.0; // p.577
            double k_dw  = data.wing.delta     ? 0.768 : 1.0; // p.577

            // difference between Rayner1992 and Rayner2018
            // Rayner1992 : (t/c)_root^-0.4
            // Rayner2018 : (t/c)_root
            m2 = 0.0103_lb * k_dw * k_vs
                    * pow(w_dg() * n_z, 0.5)
                    * pow(s_w(), 0.622)
                    * pow(data.wing.ar, 0.785)
                    * pow(tc_root, -0.4)
                    * pow(1.0 + lambda, 0.05)
                    * pow(cos(sweep()), -1.0)
                    * pow(s_csw(), 0.04);
        }

        // Rayner2018: Aircraft Design, p.574, eq.15.25
        if ( data.type == AircraftData::CargoTransport )
        {
            m2 = 0.0051_lb
                    * pow(w_dg() * n_z, 0.557)
                    * pow(s_w(), 0.649)
                    * pow(data.wing.ar, 0.5)
                    * pow(tc_root, -0.4)
                    * pow(1.0 + lambda, 0.1)
                    * pow(cos(sweep()), -1.0)
                    * pow(s_csw(), 0.1);
        }

        // Rayner2018: Aircraft Design, p.575, eq.15.46
        if ( data.type == AircraftData::GeneralAviation )
        {
            mass::pound_t w_fw = data.wing.fuel;
            velocity::meters_per_second_t v = data.general.v_cruise;
            density::kilograms_per_cubic_meter_t rho = Atmosphere::GetDensity(data.general.h_cruise);
            pressure::pounds_per_square_foot_t q = 0.5 * rho * v*v;

            m2 = 0.036_lb
                    * pow(s_w(), 0.758)
                    * pow(w_fw(), 0.0035)
                    * pow(data.wing.ar / pow(cos(sweep()), 2.0), 0.6)
                    * pow(q(), 0.006)
                    * pow(lambda, 0.04)
                    * pow(100.0 * tc_root / cos(sweep()), -0.3)
                    * pow(n_z * w_dg(), 0.49);
        }
    }

    return (m1 + m2) / 2.0;
}

Wing::Wing(const AircraftData* data)
    : Component(data)
{
    SetName("Wing");
}
