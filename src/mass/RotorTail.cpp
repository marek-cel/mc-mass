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

#include <mass/RotorTail.h>

#include <utils/ParallelAxisInertia.h>

constexpr char RotorTail::xmlTagName[];

units::mass::kilogram_t RotorTail::GetEstimatedMass(const AircraftData& data)
{
    // NASA TP-2015-218751, p.230
    if ( data.type == AircraftData::Helicopter )
    {
        double chi_tr = 1.0; // ?? technology factor
        length::foot_t r_mr = data.rotors.main_r;
        length::foot_t r_tr = data.rotors.tail_r;
        velocity::feet_per_second_t v_tip = data.rotors.main_tip_vel;
        power::horsepower_t mcp = data.rotors.mcp;

        mass::pound_t m = chi_tr * 1.3778_lb
                * pow(r_tr(), 0.0897)
                * pow(mcp() * r_mr() / v_tip(), 0.8951);

        return m;
    }

    return 0.0_kg;
}

RotorTail::RotorTail(const AircraftData* data)
    : Component(data)
{
    SetName("Tail Rotor");
}

InertiaMatrix RotorTail::GetInertia() const
{
    return GetParallelAxisInertia(m_, InertiaMatrix(), r_);
}
