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

#include <mass/RotorMain.h>

constexpr char RotorMain::xmlTagName[];

units::mass::kilogram_t RotorMain::GetEstimatedMass(const AircraftData& data)
{
    // NASA TP-2015-218751, p.228
    if ( data.type == AircraftData::Helicopter )
    {
        double n_rotor = 1.0; // number of rotors
        length::foot_t r = data.rotors.main_r;
        length::foot_t c = data.rotors.main_cb;
        velocity::feet_per_second_t v_tip = data.rotors.main_tip_vel;
        double mu_b = 1.0; // ?? flap natural frequency
        double chi_b = 1.0; // ?? technology factor

        mass::pound_t m = chi_b * 0.02606_lb * n_rotor
                * pow(static_cast<double>(data.rotors.main_blades), 0.6592)
                * pow(r(), 1.3371)
                * pow(c(), 0.9959)
                * pow(v_tip(), 0.6682)
                * pow(mu_b, 2.5279);

        return m;
    }

    return 0.0_kg;
}

RotorMain::RotorMain(const AircraftData* data)
    : Component(data)
{
    SetName("Main Rotor");
}

InertiaMatrix RotorMain::GetInertia() const
{
    return InertiaMatrix(); // ??
}
