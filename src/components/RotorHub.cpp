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

#include <components/RotorHub.h>

#include <mcutil/misc/Units.h>

#include <components/RotorMain.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

double RotorHub::computeMass( Type type,
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

        double v_tip_fps = Units::mps2fps( m_rotor_tv );

        double mu_h = 1.0; // ?? flap natural frequency

        double chi_h = 1.0; // ?? technology factor

        double w_b = RotorMain::computeMass( type,
                                             m_rotor_r,
                                             m_rotor_c,
                                             m_rotor_tv,
                                             m_rotor_nb );

        double m_lb = chi_h * 0.003722 * n_rotor * pow( (double)m_rotor_nb, 0.2807 )
                * pow( r_ft, 1.5377 ) * pow( v_tip_fps, 0.429 ) * pow( mu_h, 2.1414 )
                * pow( w_b / n_rotor, 0.5505 );

        return Units::lb2kg( m_lb );
    }

    return 0.0;
}

////////////////////////////////////////////////////////////////////////////////

RotorHub::RotorHub( const AircraftData *data ) :
    Component( data )
{
    setName( "Main Rotor Hub" );
}

////////////////////////////////////////////////////////////////////////////////

void RotorHub::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( xmlTagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double RotorHub::getComputedMass() const
{
    return computeMass( _ac->getType(),
                        _ac->getMainRotorRad(),      //double m_rotor_r,
                        _ac->getMainRotorChord(),    //double m_rotor_c,
                        _ac->getMainRotorTipVel(),   //double m_rotor_tv,
                        _ac->getMainRotorBlades() ); //int m_rotor_nb )
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
