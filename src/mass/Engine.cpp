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

#include <mass/Engine.h>

constexpr char Engine::xmlTagName[];

units::mass::kilogram_t Engine::GetEstimatedMass(const AircraftData& data)
{
    mass::pound_t w_en = data.engine.mass;

    mass::pound_t m1 = 0.0_lb;
    {
        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = 1.3 * w_en;
        }

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = 1.3 * w_en;
        }

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = 1.4 * w_en;
        }

        // engineering judgement (same as for GeneralAviation)
        if ( data.type == AircraftData::Helicopter )
        {
            m1 = 1.4 * w_en;
        }
    }

    return m1;
}

Engine::Engine(const AircraftData* data)
    : Component(data)
{
    SetName("Engine");
}
