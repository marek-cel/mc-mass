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

#include <components/Engine.h>

#include <mcutil/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char Engine::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double Engine::estimateMass( const AircraftData &data )
{
    double w_en = Units::kg2lb( data.engine.mass );

    double m1 = 0.0;
    {
        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = Units::lb2kg( 1.3 * w_en );
        }

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = Units::lb2kg( 1.3 * w_en );
        }

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = Units::lb2kg( 1.4 * w_en );
        }

        // engineering judgement (same as for CargoTransport)
        if ( data.type == AircraftData::Helicopter )
        {
            m1 = Units::lb2kg( 1.3 * w_en );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        //
        if ( data.type == AircraftData::FighterAttack )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        //
        if ( data.type == AircraftData::CargoTransport )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        //
        if ( data.type == AircraftData::GeneralAviation )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        //
        if ( data.type == AircraftData::Helicopter )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    //std::cout << "Engine:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

Engine::Engine( const AircraftData *data ) :
    Component( data )
{
    setName( "Engine" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
