/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
 *
 *  This file is part of MC-Mass.
 *
 *  MC-Mass is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MC-Mass is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <mass/TailVer.h>

#include <mcutils/misc/Units.h>

#include <utils/Atmosphere.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char TailVer::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double TailVer::estimateMass( const AircraftData &data )
{
    double s_vt = Units::sqm2sqft( data.ver_tail.area );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = Units::lb2kg( 5.3 * s_vt );
        }

        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = Units::lb2kg( 5.5 * s_vt );
        }

        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = Units::lb2kg( 2.0 * s_vt );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_dg  = Units::kg2lb( data.general.mtow );
        double n_z   = 1.5 * data.general.nz_max;

        double l_t_ft = Units::m2ft( data.ver_tail.arm );

        double ht_hv = data.ver_tail.t_tail ? 1.0 : 0.0;

        double sweep_rad = Units::deg2rad( data.ver_tail.sweep );

        // Rayner: Aircraft Design, p.572, eq.15.3
        if ( data.type == AircraftData::FighterAttack )
        {
            double s_r = Units::sqm2sqft( data.ver_tail.rudd_area );

            double k_rht = data.hor_tail.rolling ? 1.047 : 1.0;

            m2_lb = 0.452 * k_rht * pow( 1.0 + ht_hv, 0.5 ) * pow( w_dg * n_z, 0.488 )
                    * pow( s_vt, 0.718 ) * pow( data.general.mach_max, 0.341 ) * pow( l_t_ft, -1.0 )
                    * pow( 1.0 + s_r / s_vt, 0.348 ) * pow( data.ver_tail.ar, 0.223 )
                    * pow( 1.0 + data.ver_tail.tr, 0.25 ) * pow( cos( sweep_rad ), -0.323 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.27
        if ( data.type == AircraftData::CargoTransport )
        {
            double k_z = l_t_ft;

            m2_lb = 0.0026 * pow( 1.0 + ht_hv, 0.225 ) * pow( w_dg, 0.556 )
                    * pow( n_z, 0.536 ) * pow( l_t_ft, -0.5 ) * pow( s_vt, 0.5 )
                    * pow( k_z, 0.875 ) * pow( cos( sweep_rad ), -1.0 )
                    * pow( data.ver_tail.ar, 0.35 ) * pow( data.ver_tail.t_c, -0.5 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.48
        if ( data.type == AircraftData::GeneralAviation )
        {
            double v_mps = Units::kts2mps( data.general.v_cruise );
            double h_m   = Units::ft2m( data.general.h_cruise );
            double rho = Atmosphere::getDensity( h_m );
            double q = 0.5 * rho * pow( v_mps, 2.0 );
            double q_psf = Units::pa2psf( q );

            double lambda_vt = data.ver_tail.tr;

            if ( lambda_vt < 0.2 ) lambda_vt = 0.2;

            m2_lb = 0.073 * ( 1.0 + 0.2 * ht_hv ) * pow( n_z * w_dg, 0.376 )
                    * pow( q_psf, 0.122 ) * pow( s_vt, 0.873 )
                    * pow( 100.0 * data.ver_tail.t_c / cos( sweep_rad ), -0.49 )
                    * pow( data.ver_tail.ar / pow( cos( sweep_rad ), 2.0 ), 0.357 )
                    * pow( lambda_vt, 0.039 );
        }

        // NASA TP-2015-218751, p.230
        if ( data.type == AircraftData::Helicopter )
        {
            double f_tr = data.ver_tail.rotor ? 1.6311 : 1.0;

            double chi_vt = 1.0; // ?? technology factor

            m2_lb = chi_vt * 1.046 * f_tr * pow( s_vt, 0.9441 ) * pow( data.ver_tail.ar, 0.5332 );

            m1 = Units::lb2kg( m2_lb ); // same as m2
        }

        m2 = Units::lb2kg( m2_lb );
    }

    //std::cout << "TailVer:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

TailVer::TailVer( const AircraftData *data ) :
    Component( data )
{
    set_name("Vertical Tail");
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
