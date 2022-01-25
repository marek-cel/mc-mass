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

#include <mass/RotorTail.h>

#include <mass/Units.h>

////////////////////////////////////////////////////////////////////////////////

const char RotorTail::xml_tag[] = "rotor_tail";

////////////////////////////////////////////////////////////////////////////////

double RotorTail::computeMass( Type type,
                               double m_rotor_r,
                               double t_rotor_r,
                               double m_rotor_tv,
                               double rotor_mcp )
{
    // NASA TP-2015-218751, p.230
    if ( type == Helicopter )
    {
        double chi_tr = 1.0; // ?? technology factor

        double r_mr_ft = Units::m2ft( m_rotor_r );
        double r_tr_ft = Units::m2ft( t_rotor_r );

        double v_tip_fps = Units::mps2fps( m_rotor_tv );

        double m_lb = chi_tr * 1.3778 * pow( r_tr_ft, 0.0897 )
                * pow( rotor_mcp * r_mr_ft / v_tip_fps, 0.8951 );

        return Units::lb2kg( m_lb );
    }

    return 0.0;
}

////////////////////////////////////////////////////////////////////////////////

RotorTail::RotorTail( const Aircraft *ac ) :
    Component( ac )
{
    setName( "Tail Rotor" );
}

////////////////////////////////////////////////////////////////////////////////

RotorTail::~RotorTail() {}

////////////////////////////////////////////////////////////////////////////////

void RotorTail::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( RotorTail::xml_tag );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double RotorTail::getComputedMass() const
{
    return computeMass( _ac->getType(),
                        _ac->getMainRotorRad(),    //double m_rotor_r,
                        _ac->getTailRotorRad(),    //double t_rotor_r,
                        _ac->getMainRotorTipVel(), //double m_rotor_tv,
                        _ac->getPowerLimit() );    //double rotor_mcp
}
