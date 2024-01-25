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

#include <mass/RotorDrive.h>

#include <mcutils/misc/Units.h>

constexpr char RotorDrive::xmlTagName[];

units::mass::kilogram_t RotorDrive::GetEstimatedMass(const AircraftData& data)
{
    // NASA TP-2015-218751, p.236
    if ( data.type == AircraftData::Helicopter )
    {
        double n_rotor = 1.0; // number of rotors
        double chi = 1.0; // ?? technology factor
        angular_velocity::rpm_t rotor_rpm = data.rotors.main_rpm;
        angular_velocity::rpm_t engine_rpm = data.rotors.main_gear_ratio * rotor_rpm;
        power::horsepower_t mcp = data.rotors.mcp;

        mass::pound_t m = chi * 95.7634_lb
                * pow(n_rotor, 0.38553)
                * pow(mcp(), 0.78137)
                * pow(engine_rpm(), 0.09899) / pow(rotor_rpm(), 0.80686);

        return m;
    }

    return 0.0_kg;
}

RotorDrive::RotorDrive(const AircraftData* data)
    : Component(data)
{
    SetName("Rotor Drive");
}
