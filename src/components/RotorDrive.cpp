/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <components/RotorDrive.h>

#include <utils/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char RotorDrive::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double RotorDrive::estimateMass( const AircraftData &data )
{
    // NASA TP-2015-218751, p.236
    if ( data.type == AircraftData::Helicopter )
    {
        double n_rotor = 1.0; // number of rotors

        double chi = 1.0; // ?? technology factor

        double engine_rpm = data.rotors.main_gear_ratio * data.rotors.main_rpm;

        double m_lb = chi * 95.7634 * pow( n_rotor, 0.38553 ) * pow( data.rotors.mcp, 0.78137 )
                * pow( engine_rpm, 0.09899 ) / pow( data.rotors.main_rpm, 0.80686 );

        return Units::lb2kg( m_lb );
    }

    return 0.0;
}

////////////////////////////////////////////////////////////////////////////////

RotorDrive::RotorDrive( const AircraftData *data ) :
    Component( data )
{
    setName( "Rotor Drive" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
