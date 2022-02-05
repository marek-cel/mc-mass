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

#include <components/RotorTail.h>

#include <mcutil/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char RotorTail::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double RotorTail::estimateMass( const AircraftData &data )
{
    // NASA TP-2015-218751, p.230
    if ( data.type == AircraftData::Helicopter )
    {
        double chi_tr = 1.0; // ?? technology factor

        double r_mr_ft = Units::m2ft( data.rotors.main_r );
        double r_tr_ft = Units::m2ft( data.rotors.tail_r );

        double v_tip_fps = Units::mps2fps( data.rotors.main_tip_vel );

        double m_lb = chi_tr * 1.3778 * pow( r_tr_ft, 0.0897 )
                * pow( data.rotors.mcp * r_mr_ft / v_tip_fps, 0.8951 );

        return Units::lb2kg( m_lb );
    }

    return 0.0;
}

////////////////////////////////////////////////////////////////////////////////

RotorTail::RotorTail( const AircraftData *data ) :
    Component( data )
{
    setName( "Tail Rotor" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
