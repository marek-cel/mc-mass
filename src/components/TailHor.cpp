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

#include <components/TailHor.h>

#include <mcutils/misc/Units.h>

#include <utils/Atmosphere.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char TailHor::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double TailHor::estimateMass( const AircraftData &data )
{
    double s_ht = Units::sqm2sqft( data.hor_tail.area );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = Units::lb2kg( 4.0 * s_ht );
        }

        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = Units::lb2kg( 5.5 * s_ht );
        }

        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = Units::lb2kg( 2.0 * s_ht );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_dg  = Units::kg2lb( data.general.mtow );
        double n_z   = 1.5 * data.general.nz_max;

        double f_w_ft = Units::m2ft( data.hor_tail.w_f );
        double b_h_ft = Units::m2ft( data.hor_tail.span );

        double sweep_rad = Units::deg2rad( data.hor_tail.sweep );

        // Rayner: Aircraft Design, p.572, eq.15.2
        if ( data.type == AircraftData::FighterAttack )
        {
            m2_lb = 3.316 * pow( 1 + f_w_ft / b_h_ft, -2.0 )
                    * pow( w_dg * n_z / 1000.0, 0.26 )
                    * pow( s_ht, 0.806 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.26
        if ( data.type == AircraftData::CargoTransport )
        {
            double k_uht = data.hor_tail.moving ? 1.143 : 1.0;

            double l_t_ft = Units::m2ft( data.hor_tail.arm );
            double k_y = 0.3 * l_t_ft;

            double s_e = Units::sqm2sqft( data.hor_tail.elev_area );

            m2_lb = 0.0379 * k_uht * pow( 1.0 + f_w_ft / b_h_ft, -0.25 )
                    * pow( w_dg, 0.639 ) * pow( n_z, 0.1 ) * pow( s_ht, 0.75 )
                    * pow( l_t_ft, -1.0 ) * pow( k_y, 0.704 )
                    * pow( cos( sweep_rad ), -1.0 ) * pow( data.hor_tail.ar, 0.166 )
                    * pow( 1.0 + s_e / s_ht, 0.1 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.47
        if ( data.type == AircraftData::GeneralAviation )
        {
            double v_mps = Units::kts2mps( data.general.v_cruise );
            double h_m   = Units::ft2m( data.general.h_cruise );
            double rho = Atmosphere::getDensity( h_m );
            double q = 0.5 * rho * pow( v_mps, 2.0 );
            double q_psf = Units::pa2psf( q );

            m2_lb = 0.016 * pow( n_z * w_dg, 0.414 ) * pow( q_psf, 0.006 )
                    * pow( data.hor_tail.tr, 0.04 )
                    * pow( 100.0 * data.hor_tail.t_c / cos( sweep_rad ), -0.3 )
                    * pow( n_z * w_dg, 0.49 );
        }

        // NASA TP-2015-218751, p.230
        if ( data.type == AircraftData::Helicopter )
        {
            double chi_ht = 1.0; // ?? technology factor

            m2_lb = chi_ht * 0.7176 * pow( s_ht, 1.1881 ) * pow( data.hor_tail.ar, 0.3173 );

            m1 = Units::lb2kg( m2_lb ); // same as m2
        }

        m2 = Units::lb2kg( m2_lb );
    }

    //std::cout << "TailHor:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

TailHor::TailHor( const AircraftData *data ) :
    Component( data )
{
    setName( "Horizontal Tail" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
