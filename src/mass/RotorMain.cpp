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

#include <mass/RotorMain.h>

#include <mass/Units.h>

////////////////////////////////////////////////////////////////////////////////

const char RotorMain::xml_tag[] = "rotor_main";

////////////////////////////////////////////////////////////////////////////////

double RotorMain::computeMass( Type type,
                               double m_rotor_r,
                               double m_rotor_c,
                               double m_rotor_tv,
                               int m_rotor_nb )
{
    // NASA TP-2015-218751, p.228
    if ( type == Helicopter )
    {
        double n_rotor = 1.0; // number of rotors

        double r_ft = Units::m2ft( m_rotor_r );
        double c_ft = Units::m2ft( m_rotor_c );

        double v_tip_fps = Units::mps2fps( m_rotor_tv );

        double mu_b = 1.0; // ?? flap natural frequency

        double chi_b = 1.0; // ?? technology factor

        double m_lb = chi_b * 0.02606 * n_rotor * pow( (double)m_rotor_nb, 0.6592 )
                * pow( r_ft, 1.3371 ) * pow( c_ft, 0.9959 )
                * pow( v_tip_fps, 0.6682 ) * pow( mu_b, 2.5279 );

        return Units::lb2kg( m_lb );
    }

    return 0.0;
}

////////////////////////////////////////////////////////////////////////////////

RotorMain::RotorMain( const Aircraft *ac ) :
    Component( ac )
{
    setName( "Main Rotor" );
}

////////////////////////////////////////////////////////////////////////////////

RotorMain::~RotorMain() {}

////////////////////////////////////////////////////////////////////////////////

void RotorMain::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( RotorMain::xml_tag );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double RotorMain::getComputedMass() const
{
    return computeMass( _ac->getType(),
                        _ac->getMainRotorRad(),      //double m_rotor_r,
                        _ac->getMainRotorChord(),    //double m_rotor_c,
                        _ac->getMainRotorTipVel(),   //double m_rotor_tv,
                        _ac->getMainRotorBlades() ); //int m_rotor_nb )
}
