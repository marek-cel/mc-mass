/****************************************************************************//*
 * Copyright (C) 2022 Marek M. Cel
 *
 * This file is part of MC-Mass.
 *
 * MC-Mass is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MC-Mass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <components/Wing.h>

#include <mcutil/misc/Units.h>

#include <utils/Atmosphere.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char Wing::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double Wing::estimateMass( const AircraftData &data )
{
    double s_w = Units::sqm2sqft( data.wing.area_exp );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = Units::lb2kg( 9.0 * s_w );
        }

        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = Units::lb2kg( 10.0 * s_w );
        }

        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = Units::lb2kg( 2.5 * s_w );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_dg  = Units::kg2lb( data.general.mtow );
        double n_z   = 1.5 * data.general.nz_max;

        double s_csw = Units::kg2lb( data.wing.ctrl_area );

        double sweep_rad = Units::deg2rad( data.wing.sweep );

        // Rayner: Aircraft Design, p.572, eq.15.1
        if ( data.type == AircraftData::FighterAttack )
        {
            double k_vs  = data.wing.var_sweep ? 1.19  : 1.0;
            double k_dw  = data.wing.delta     ? 0.768 : 1.0;

            m2_lb = 0.0103 * k_dw * k_vs * pow( w_dg * n_z, 0.5 )
                    * pow( s_w, 0.622 ) * pow( data.wing.ar, 0.785 ) * pow( data.wing.t_c, -0.4 )
                    * pow( 1.0 + data.wing.tr, 0.05 ) * pow( cos( sweep_rad ), -1.0 )
                    * pow( s_csw, 0.04 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.25
        if ( data.type == AircraftData::CargoTransport )
        {
            m2_lb = 0.0051 * pow( w_dg * n_z, 0.557 )
                    * pow( s_w, 0.649 ) * pow( data.wing.ar, 0.5 ) * pow( data.wing.t_c, -0.4 )
                    * pow( 1.0 + data.wing.tr, 0.1 ) * pow( cos( sweep_rad ), -1.0 )
                    * pow( s_csw, 0.1 );
        }

        // Rayner: Aircraft Design, p.575, eq.15.46
        if ( data.type == AircraftData::GeneralAviation )
        {
            double w_fw  = Units::kg2lb( data.wing.fuel );

            double v_mps = Units::kts2mps( data.general.v_cruise );
            double h_m   = Units::ft2m( data.general.h_cruise );
            double rho = Atmosphere::getDensity( h_m );
            double q = 0.5 * rho * pow( v_mps, 2.0 );
            double q_psf = Units::pa2psf( q );

            m2_lb = 0.036 * pow( s_w, 0.758 ) * pow( w_fw, 0.0035 )
                    * pow( data.wing.ar / pow( cos( sweep_rad ), 2.0 ), 0.6 )
                    * pow( q_psf, 0.006 ) * pow( data.wing.tr, 0.04 )
                    * pow( 100 * data.wing.t_c / cos( sweep_rad ), -0.3 )
                    * pow( w_dg * n_z, 0.49 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    //std::cout << "Wing:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

Wing::Wing( const AircraftData *data ) :
    Component( data )
{
    setName( "Wing" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
