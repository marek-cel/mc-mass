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

#include <mass/TailHor.h>

#include <utils/Atmosphere.h>

constexpr char TailHor::xmlTagName[];

units::mass::kilogram_t TailHor::GetEstimatedMass(const AircraftData& data)
{
    area::square_foot_t s_ht = data.hor_tail.area;

    // Rayner2018: Aircraft Design, p.568, table 15.2
    mass::pound_t m1 = 0.0_lb;
    {
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = 4.0_lb * s_ht();
        }

        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = 5.5_lb * s_ht();
        }

        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = 2.0_lb * s_ht();
        }
    }

    mass::pound_t m2 = 0.0_lb;
    {
        mass::pound_t w_dg = GetDesignGrossWeight(data);
        double n_z = 1.5 * data.general.nz_max;
        length::foot_t f_w = data.hor_tail.w_f;
        length::foot_t b_h = data.hor_tail.span;
        angle::radian_t sweep = data.hor_tail.sweep;

        // Rayner2018: Aircraft Design, p.572, eq.15.2
        if ( data.type == AircraftData::FighterAttack )
        {
            m2 = 3.316_lb
                    * pow(1 + f_w / b_h, -2.0)
                    * pow(w_dg() * n_z / 1000.0, 0.26)
                    * pow(s_ht(), 0.806);
        }

        // Rayner2018: Aircraft Design, p.574, eq.15.26
        if ( data.type == AircraftData::CargoTransport )
        {
            double k_uht = data.hor_tail.moving ? 1.143 : 1.0;
            length::foot_t l_t = data.hor_tail.arm;
            length::foot_t k_y = 0.3 * l_t; // K_y ~= 0.3 L_t p.577
            area::square_foot_t s_e = data.hor_tail.elev_area;

            m2 = 0.0379_lb * k_uht
                    * pow(1.0 + f_w / b_h, -0.25)
                    * pow(w_dg(), 0.639)
                    * pow(n_z, 0.1)
                    * pow(s_ht(), 0.75)
                    * pow(l_t(), -1.0)
                    * pow(k_y(), 0.704)
                    * pow(cos(sweep()), -1.0)
                    * pow(data.hor_tail.ar, 0.166)
                    * pow(1.0 + s_e / s_ht, 0.1);
        }

        // Rayner2018: Aircraft Design, p.576, eq.15.47
        if ( data.type == AircraftData::GeneralAviation )
        {
            velocity::meters_per_second_t v = data.general.v_cruise;
            density::kilograms_per_cubic_meter_t rho = Atmosphere::GetDensity(data.general.h_cruise);
            pressure::pounds_per_square_foot_t q = 0.5 * rho * v*v;
            double lambda_h = data.hor_tail.tr;

            m2 = 0.016_lb
                    * pow(n_z * w_dg(), 0.414)
                    * pow(q(), 0.168)
                    * pow(s_ht(), 0.896)
                    * pow(100.0 * data.hor_tail.tc / cos(sweep()), -0.12)
                    * pow(data.hor_tail.ar / pow(cos(sweep()), 2.0), 0.043)
                    * pow(lambda_h, -0.02);
        }

        // NASA TP-2015-218751, p.230
        if ( data.type == AircraftData::Helicopter )
        {
            double chi_ht = 1.0; // ?? technology factor

            m2 = chi_ht * 0.7176_lb
                    * pow(s_ht(), 1.1881)
                    * pow(data.hor_tail.ar, 0.3173);
            m1 = m2;
        }
    }

    return (m1 + m2) / 2.0;
}

TailHor::TailHor(const AircraftData* data)
    : Component(data)
{
    SetName("Horizontal Tail");
}
