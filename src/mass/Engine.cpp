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

#include <mass/Engine.h>

#include <mass/Atmosphere.h>
#include <mass/Units.h>

////////////////////////////////////////////////////////////////////////////////

const char Engine::xml_tag[] = "engine";

////////////////////////////////////////////////////////////////////////////////

double Engine::computeMass( Type type,
                            double m_engine )
{
    double w_en = Units::kg2lb( m_engine );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( type == FighterAttack )
        {
            m1 = Units::lb2kg( 1.3 * w_en );
        }

        if ( type == CargoTransport )
        {
            m1 = Units::lb2kg( 1.3 * w_en );
        }

        if ( type == GeneralAviation )
        {
            m1 = Units::lb2kg( 1.4 * w_en );
        }

        if ( type == Helicopter )
        {
            // same as for CargoTransport
            m1 = Units::lb2kg( 1.3 * w_en );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        //
        if ( type == FighterAttack )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        //
        if ( type == CargoTransport )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        //
        if ( type == GeneralAviation )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        //
        if ( type == Helicopter )
        {
            m2_lb = Units::kg2lb( m1 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    std::cout << "Engine:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

Engine::Engine( const Aircraft *ac ) :
    Component( ac )
{
    setName( "Engine" );
}

////////////////////////////////////////////////////////////////////////////////

Engine::~Engine() {}

////////////////////////////////////////////////////////////////////////////////

void Engine::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( Engine::xml_tag );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double Engine::getComputedMass() const
{
    return computeMass( _ac->getType(),
                        _ac->getEngineMass() );
}
