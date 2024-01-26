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

#include <mass/GearMain.h>

constexpr char GearMain::xmlTagName[];

units::mass::kilogram_t GearMain::GetEstimatedMass(const AircraftData& data)
{
    constexpr double coef_m = 0.85;
    mass::pound_t w_dg = GetDesignGrossWeight(data);
    mass::pound_t w_mto = data.general.mtow;
    mass::pound_t w_0 = data.general.m_empty;
    mass::pound_t reduction = coef_m * data.landing_gear.fixed ? (0.014 * w_0) : 0.0_lb;

    mass::pound_t m1 = 0.0_lb;
    {
        // Rayner2018: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::FighterAttack )
        {
            double coeff = data.general.navy_ac ? 0.045 : 0.033;
            m1 = coef_m * 1.0_lb * coeff * w_dg() - reduction;
        }

        // Rayner2018: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = coef_m * 0.043_lb * w_dg() - reduction;
        }

        // Rayner2018: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = coef_m * 0.057_lb * w_dg() - reduction;
        }

        // NASA TP-2015-218751, p.233
        if ( data.type == AircraftData::Helicopter )
        {
            m1 = 0.0325 * w_mto;
        }
    }

    mass::pound_t m2 = 0.0_lb;
    {
        mass::pound_t w_l = data.general.m_maxLand;
        double n_l = 1.5 * data.general.nz_maxLand; // p.578
        length::inch_t l_m = data.landing_gear.main_l;

        // Rayner2018: Aircraft Design, p.572, eq.15.5
        if ( data.type == AircraftData::FighterAttack )
        {
            double k_cb  = data.landing_gear.cross  ? 2.25  : 1.0;  // p.577
            double k_tpg = data.landing_gear.tripod ? 0.826 : 1.0;  // p.577

            m2 = 1.0_lb * k_cb * k_tpg
                    * pow(w_l() * n_l, 0.25)
                    * pow(l_m(), 0.973);
        }

        // Rayner2018: Aircraft Design, p.574, eq.15.29
        if ( data.type == AircraftData::CargoTransport )
        {
            velocity::knot_t v_stall = data.general.v_stall;

            double k_mp = data.landing_gear.main_kneel ? 1.126 : 1.0; // p.577

            m2 = 0.0106_lb * k_mp
                    * pow(w_l(), 0.888)
                    * pow(n_l, 0.25)
                    * pow(l_m(), 0.4)
                    * pow(static_cast<double>(data.landing_gear.main_wheels), 0.321)
                    * pow(static_cast<double>(data.landing_gear.main_struts), -0.5)
                    * pow(v_stall(), 0.1);
        }

        // Rayner2018: Aircraft Design, p.576, eq.15.50
        if ( data.type == AircraftData::GeneralAviation )
        {
            m2 = 0.095_lb
                    * pow(n_l * w_l(), 0.768)
                    * pow(l_m() / 12.0, 0.409)
                    - reduction;
        }

        // NASA TP-2015-218751, p.233
        if ( data.type == AircraftData::Helicopter )
        {
            double w_s = 1.0; // [lb/ft^2] wing loading (1.0 for helicopters) p.233

            m2 = 0.4013_lb
                    * pow(w_mto(), 0.6662)
                    * pow(n_l, 0.536)
                    * pow(w_s, 0.1525);
        }
    }

    return (m1 + m2) / 2.0;
}

GearMain::GearMain(const AircraftData* data)
    : Component(data)
{
    SetName("Main Landing Gear");
}
