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

#include <mass/TailVer.h>

#include <utils/Atmosphere.h>

constexpr char TailVer::xmlTagName[];

units::mass::kilogram_t TailVer::GetEstimatedMass(const AircraftData& data)
{
    area::square_foot_t s_vt = data.ver_tail.area;

    // Rayner2018: Aircraft Design, p.568, table 15.2
    mass::pound_t m1 = 0.0_lb;
    {
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = 5.3_lb * s_vt();
        }

        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = 5.5_lb * s_vt();
        }

        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = 2.0_lb * s_vt();
        }
    }

    mass::pound_t m2 = 0.0_lb;
    {
        mass::pound_t w_dg = GetDesignGrossWeight(data);
        double n_z = 1.5 * data.general.nz_max;
        length::foot_t l_t = data.ver_tail.arm;
        double ht_hv = data.ver_tail.t_tail ? 1.0 : 0.0;
        angle::radian_t sweep = data.ver_tail.sweep;

        // Rayner2018: Aircraft Design, p.572, eq.15.3
        if ( data.type == AircraftData::FighterAttack )
        {
            area::square_foot_t s_r = data.ver_tail.rudd_area;
            double lambda = data.ver_tail.tr;

            double k_rht = data.hor_tail.rolling ? 1.047 : 1.0; // p.577

            m2 = 0.452_lb * k_rht
                    * pow(1.0 + ht_hv, 0.5)
                    * pow(w_dg() * n_z, 0.488)
                    * pow(s_vt(), 0.718)
                    * pow(data.general.mach_max, 0.341)
                    * pow(l_t(), -1.0)
                    * pow(1.0 + s_r / s_vt, 0.348)
                    * pow(data.ver_tail.ar, 0.223)
                    * pow(1.0 + lambda, 0.25)
                    * pow(cos(sweep()), -0.323);
        }

        // Rayner2018: Aircraft Design, p.574, eq.15.27
        if ( data.type == AircraftData::CargoTransport )
        {
            length::foot_t k_z = l_t; // K_z ~= L_t p.577
            double tc_root = data.ver_tail.tc;

            m2 = 0.0026_lb
                    * pow(1.0 + ht_hv, 0.225)
                    * pow(w_dg(), 0.556)
                    * pow(n_z, 0.536)
                    * pow(l_t(), -0.5)
                    * pow(s_vt(), 0.5)
                    * pow(k_z(), 0.875)
                    * pow(cos(sweep()), -1.0)
                    * pow(data.ver_tail.ar, 0.35)
                    * pow(tc_root, -0.5);
        }

        // Rayner2018: Aircraft Design, p.576, eq.15.48
        if ( data.type == AircraftData::GeneralAviation )
        {
            velocity::meters_per_second_t v = data.general.v_cruise;
            density::kilograms_per_cubic_meter_t rho = Atmosphere::GetDensity(data.general.h_cruise);
            pressure::pounds_per_square_foot_t q = 0.5 * rho * v*v;
            double lambda_vt = data.ver_tail.tr;

            if ( lambda_vt < 0.2 ) lambda_vt = 0.2;

            m2 = 0.073_lb * (1.0 + 0.2 * ht_hv)
                    * pow(n_z * w_dg(), 0.376)
                    * pow(q(), 0.122)
                    * pow(s_vt(), 0.873)
                    * pow(100.0 * data.ver_tail.tc / cos(sweep()), -0.49)
                    * pow(data.ver_tail.ar / pow(cos(sweep()), 2.0), 0.357)
                    * pow(lambda_vt, 0.039);
        }

        // NASA TP-2015-218751, p.230
        if ( data.type == AircraftData::Helicopter )
        {
            double f_tr = data.ver_tail.rotor ? 1.6311 : 1.0;
            double chi_vt = 1.0; // ?? technology factor

            m2 = chi_vt * 1.046_lb * f_tr
                    * pow(s_vt(), 0.9441)
                    * pow(data.ver_tail.ar, 0.5332);
            m1 = m2;
        }
    }

    return (m1 + m2) / 2.0;
}

TailVer::TailVer(const AircraftData* data)
    : Component(data)
{
    SetName("Vertical Tail");
}
