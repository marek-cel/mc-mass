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
 *
 ******************************************************************************/

#include <components/AllElse.h>

#include <mcutil/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

double AllElse::estimateMass( const AircraftData *data )
{
    double w_dg = Units::kg2lb( data->general.mtow );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( data->type == AircraftData::FighterAttack )
        {
            m1 = Units::lb2kg( 0.17 * w_dg );
        }

        if ( data->type == AircraftData::CargoTransport )
        {
            m1 = Units::lb2kg( 0.17 * w_dg );
        }

        if ( data->type == AircraftData::GeneralAviation )
        {
            m1 = Units::lb2kg( 0.1  * w_dg );
        }

        // ??
        if ( data->type == AircraftData::Helicopter )
        {
            m1 = Units::lb2kg( 0.25 * w_dg );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        //
        if ( data->type == AircraftData::FighterAttack )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        //
        if ( data->type == AircraftData::CargoTransport )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        //
        if ( data->type == AircraftData::GeneralAviation )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    std::cout << "AllElse:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

AllElse::AllElse( const AircraftData *data ) :
    Component( data )
{
    setName( "All-else Empty" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
