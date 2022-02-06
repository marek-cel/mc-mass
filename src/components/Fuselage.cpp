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

#include <components/Fuselage.h>

#include <mcutil/misc/Units.h>

#include <utils/Atmosphere.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char Fuselage::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double Fuselage::estimateMass( const AircraftData &data )
{
    double s_f = Units::sqm2sqft( data.fuselage.wetted_area );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( data.type == AircraftData::FighterAttack )
        {
            m1 = Units::lb2kg( 4.8 * s_f );
        }

        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = Units::lb2kg( 5.0 * s_f );
        }

        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = Units::lb2kg( 1.4 * s_f );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_dg = Units::kg2lb( data.general.mtow );
        double n_z  = 1.5 * data.general.nz_max;
        double l_ft = Units::m2ft( data.fuselage.l );
        double d_ft = Units::m2ft( data.fuselage.h );
        double w_ft = Units::m2ft( data.fuselage.w );

        // Rayner: Aircraft Design, p.572, eq.15.4
        if ( data.type == AircraftData::FighterAttack )
        {
            double k_dwf = data.wing.delta ? 0.774 : 1.0;

            m2_lb = 0.499 * k_dwf * pow( w_dg, 0.35 ) * pow( n_z, 0.25 )
                    * pow( l_ft, 0.5 ) * pow( d_ft, 0.849 ) * pow( w_ft, 0.685 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.28
        if ( data.type == AircraftData::CargoTransport )
        {
            double k_door = 1.0;

            switch ( data.fuselage.cargo_door )
            {
                case AircraftData::Fuselage::NoCargoDoor       : k_door = 1.0;  break;
                case AircraftData::Fuselage::OneSideCargoDoor  : k_door = 1.06; break;
                case AircraftData::Fuselage::TwoSideCargoDoor  : k_door = 1.12; break;
                case AircraftData::Fuselage::AftClamshellDoor  : k_door = 1.12; break;
                case AircraftData::Fuselage::TwoSideAndAftDoor : k_door = 1.25; break;
            }

            double k_lg = data.fuselage.landing_gear ? 1.12 : 1.0;

            double b_w = Units::m2ft( data.wing.span );
            double sweep_rad = Units::deg2rad( data.wing.sweep );

            double k_ws = 0.75
                    * ( (1.0 + 2.0 * data.wing.tr)/(1.0 + data.wing.tr) )
                    * ( b_w * tan( sweep_rad ) / l_ft );

            m2_lb = 0.328 * k_door * k_lg * pow( w_dg * n_z, 0.5 )
                            * pow( l_ft, 0.25 ) * pow( s_f, 0.302 ) * pow ( 1 + k_ws, 0.04 )
                            * pow( l_ft / d_ft, 0.1 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.49
        if ( data.type == AircraftData::GeneralAviation )
        {
            double l_t_ft = Units::m2ft( data.hor_tail.arm );

            double vol_press_cuft = Units::cum2cuft( data.fuselage.press_vol );
            double w_press = 11.9 + pow( vol_press_cuft * 8.0, 0.271 );

            double v_mps = Units::kts2mps( data.general.v_cruise );
            double h_m   = Units::ft2m( data.general.h_cruise );
            double rho = Atmosphere::getDensity( h_m );
            double q = 0.5 * rho * pow( v_mps, 2.0 );
            double q_psf = Units::pa2psf( q );

            m2_lb = 0.052 * pow( s_f, 1.086 ) * pow( n_z * w_dg, 0.177 )
                            * pow( l_t_ft, -0.051 ) * pow ( l_ft / d_ft, -0.072 )
                            * pow( q_psf, 0.241 ) + w_press;
        }

        // NASA TP-2015-218751, p.232
        if ( data.type == AircraftData::Helicopter )
        {
            double f_ramp = data.fuselage.cargo_ramp ? 1.3939 : 1.0;

            double w_basic = 5.896 * f_ramp * pow( w_dg / 1000.0, 0.4908 )
                    * pow( n_z, 0.1323 ) * pow( s_f, 0.2544 ) * pow( l_ft, 0.61 );

            double chi_basic = 1.0; // ?? technology factor

            m2_lb = chi_basic * w_basic;

            // same as m2
            m1 = Units::lb2kg( m2_lb );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    //std::cout << "Fuselage:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

Fuselage::Fuselage( const AircraftData *data ) :
    Component( data )
{
    setName( "Fuselage" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
