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

#include <mass/RotorHub.h>

#include <mass/RotorMain.h>

constexpr char RotorHub::xmlTagName[];

units::mass::kilogram_t RotorHub::GetEstimatedMass(const AircraftData& data)
{
    // NASA TP-2015-218751, p.228
    if ( data.type == AircraftData::Helicopter )
    {
        double n_rotor = 1.0; // number of rotors
        length::foot_t r = data.rotors.main_r;
        velocity::feet_per_second_t v_tip = data.rotors.main_tip_vel;
        double mu_h = 1.0; // ?? flap natural frequency
        double chi_h = 1.0; // ?? technology factor
        mass::pound_t w_b = RotorMain::GetEstimatedMass(data);

        mass::pound_t m = chi_h * 0.003722_lb * n_rotor
                * pow(static_cast<double>(data.rotors.main_blades), 0.2807)
                * pow(r(), 1.5377)
                * pow(v_tip(), 0.429)
                * pow(mu_h, 2.1414)
                * pow(w_b() / n_rotor, 0.5505);

        return m;
    }

    return 0.0_kg;
}

RotorHub::RotorHub(const AircraftData* data)
    : Component(data)
{
    SetName("Main Rotor Hub");
}
