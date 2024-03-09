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

#include <mass/GearNose.h>

constexpr char GearNose::xmlTagName[];

units::mass::kilogram_t GearNose::GetEstimatedMass(const AircraftData& data)
{
    constexpr double coef_n = 0.15;
    mass::pound_t w_dg = GetDesignGrossWeight(data);
    mass::pound_t w_0 = data.general.m_empty;
    mass::pound_t reduction = coef_n * ( data.landing_gear.fixed ? (0.014 * w_0) : 0.0_lb );

    mass::pound_t m1 = 0.0_lb;
    {
        // Rayner2018: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::FighterAttack )
        {
            double coeff = data.general.navy_ac ? 0.045 : 0.033;
            m1 = coef_n * 1.0_lb * coeff * w_dg() - reduction;
        }

        // Rayner2018: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = coef_n * 0.043_lb * w_dg() - reduction;
        }

        // Rayner2018: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = coef_n * 0.057_lb * w_dg() - reduction;
        }
    }

    mass::pound_t m2 = 0.0_lb;
    {
        mass::pound_t w_l = data.general.m_maxLand;
        double n_l = 1.5 * data.general.nz_maxLand;
        length::inch_t l_n = data.landing_gear.nose_l;

        // Rayner2018: Aircraft Design, p.572, eq.15.3
        if ( data.type == AircraftData::FighterAttack )
        {
            m2 = 1.0_lb
                    * pow(w_l() * n_l, 0.29)
                    * pow(l_n(), 0.5)
                    * pow(static_cast<double>(data.landing_gear.nose_wheels), 0.525);
        }

        // Rayner2018: Aircraft Design, p.575, eq.15.27
        if ( data.type == AircraftData::CargoTransport )
        {
            double k_np = data.landing_gear.nose_kneel ? 1.15 : 1.0; // p.577

            m2 = 0.032_lb * k_np
                    * pow(w_l(), 0.646)
                    * pow(n_l, 0.2)
                    * pow(l_n(), 0.5)
                    * pow(static_cast<double>(data.landing_gear.nose_wheels), 0.45);
        }

        // Rayner2018: Aircraft Design, p.576, eq.15.48
        if ( data.type == AircraftData::GeneralAviation )
        {
            m2 = 0.125_lb
                    * pow(n_l * w_l(), 0.566)
                    * pow(l_n() / 12.0, 0.845)
                    - reduction;
        }
    }

    return (m1 + m2) / 2.0;
}

GearNose::GearNose(const AircraftData* data)
    : Component(data)
{
    SetName("Nose Landing Gear");
}
