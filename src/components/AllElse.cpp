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

#include <components/AllElse.h>

#include <mcutil/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char AllElse::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double AllElse::estimateMass( const AircraftData &data )
{
    double w_dg = Units::kg2lb( data.general.mtow );

    double m = 0.0;

    // Rayner: Aircraft Design, p.568, table 15.2
    if ( data.type == AircraftData::FighterAttack )
    {
        m = Units::lb2kg( 0.17 * w_dg );
    }

    // Rayner: Aircraft Design, p.568, table 15.2
    if ( data.type == AircraftData::CargoTransport )
    {
        m = Units::lb2kg( 0.17 * w_dg );
    }

    // Rayner: Aircraft Design, p.568, table 15.2
    if ( data.type == AircraftData::GeneralAviation )
    {
        m = Units::lb2kg( 0.1  * w_dg );
    }

    // engineering judgement
    if ( data.type == AircraftData::Helicopter )
    {
        m = Units::lb2kg( 0.25 * w_dg );
    }

    return m;
}

////////////////////////////////////////////////////////////////////////////////

AllElse::AllElse( const AircraftData *data ) :
    Component( data )
{
    setName( "All-else Empty" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
