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

#include <mass/RotorDrive.h>

#include <mass/Units.h>

////////////////////////////////////////////////////////////////////////////////

const char RotorDrive::xml_tag[] = "rotor_drive";

////////////////////////////////////////////////////////////////////////////////

double RotorDrive::computeMass( Type type,
                                double m_rotor_rpm,
                                double m_rotor_gr,
                                double rotor_mcp )
{
    // NASA TP-2015-218751, p.236
    if ( type == Helicopter )
    {
        double n_rotor = 1.0; // number of rotors

        double chi = 1.0; // ?? technology factor

        double engine_rpm = m_rotor_gr * m_rotor_rpm;

        double m_lb = chi * 95.7634 * pow( n_rotor, 0.38553 ) * pow( rotor_mcp, 0.78137 )
                * pow( engine_rpm, 0.09899 ) / pow( m_rotor_rpm, 0.80686 );

        return Units::lb2kg( m_lb );
    }

    return 0.0;
}

////////////////////////////////////////////////////////////////////////////////

RotorDrive::RotorDrive( const Aircraft *ac ) :
    Component( ac )
{
    setName( "Rotor Drive" );
}

////////////////////////////////////////////////////////////////////////////////

RotorDrive::~RotorDrive() {}

////////////////////////////////////////////////////////////////////////////////

void RotorDrive::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( RotorDrive::xml_tag );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double RotorDrive::getComputedMass() const
{
    return computeMass( _ac->getType(),
                        _ac->getMainRotorRPM(),
                        _ac->getMainRotorGear(),
                        _ac->getPowerLimit() );
}
