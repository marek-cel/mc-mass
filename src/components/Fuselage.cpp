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

double Fuselage::computeMass( Type type,
                              double l, double w, double h,
                              double wetted_area,
                              double m_maxto,
                              double nz_max,
                              bool wing_delta,
                              CargoDoor cargo_door,
                              bool fuselage_lg,
                              double wing_span,
                              double wing_sweep,
                              double wing_tr,
                              double h_tail_arm,
                              double press_vol,
                              double v_cruise,
                              double h_cruise,
                              bool cargo_ramp )
{
    double s_f = Units::sqm2sqft( wetted_area );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( type == FighterAttack )
        {
            m1 = Units::lb2kg( 4.8 * s_f );
        }

        if ( type == CargoTransport )
        {
            m1 = Units::lb2kg( 5.0 * s_f );
        }

        if ( type == GeneralAviation )
        {
            m1 = Units::lb2kg( 1.4 * s_f );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_dg = Units::kg2lb( m_maxto );
        double n_z  = 1.5 * nz_max;
        double l_ft = Units::m2ft( l );
        double d_ft = Units::m2ft( h );
        double w_ft = Units::m2ft( w );

        // Rayner: Aircraft Design, p.572, eq.15.4
        if ( type == FighterAttack )
        {
            double k_dwf = wing_delta ? 0.774 : 1.0;

            m2_lb = 0.499 * k_dwf * pow( w_dg, 0.35 ) * pow( n_z, 0.25 )
                    * pow( l_ft, 0.5 ) * pow( d_ft, 0.849 ) * pow( w_ft, 0.685 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.28
        if ( type == CargoTransport )
        {
            double k_door = 1.0;

            switch ( cargo_door )
            {
                case NoCargoDoor       : k_door = 1.0;  break;
                case OneSideCargoDoor  : k_door = 1.06; break;
                case TwoSideCargoDoor  : k_door = 1.12; break;
                case AftClamshellDoor  : k_door = 1.12; break;
                case TwoSideAndAftDoor : k_door = 1.25; break;
            }

            double k_lg = fuselage_lg ? 1.12 : 1.0;

            double b_w = Units::m2ft( wing_span );
            double sweep_rad = Units::deg2rad( wing_sweep );

            double k_ws = 0.75
                    * ( (1.0 + 2.0 * wing_tr)/(1.0 + wing_tr) )
                    * ( b_w * tan( sweep_rad ) / l_ft );

            m2_lb = 0.328 * k_door * k_lg * pow( w_dg * n_z, 0.5 )
                            * pow( l_ft, 0.25 ) * pow( s_f, 0.302 ) * pow ( 1 + k_ws, 0.04 )
                            * pow( l_ft / d_ft, 0.1 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.49
        if ( type == GeneralAviation )
        {
            double l_t_ft = Units::m2ft( h_tail_arm );

            double vol_press_cuft = Units::cum2cuft( press_vol );
            double w_press = 11.9 + pow( vol_press_cuft * 8.0, 0.271 );

            double v_mps = Units::kts2mps( v_cruise );
            double h_m   = Units::ft2m( h_cruise );
            double rho = Atmosphere::getDensity( h_m );
            double q = 0.5 * rho * pow( v_mps, 2.0 );
            double q_psf = Units::pa2psf( q );

            m2_lb = 0.052 * pow( s_f, 1.086 ) * pow( n_z * w_dg, 0.177 )
                            * pow( l_t_ft, -0.051 ) * pow ( l_ft / d_ft, -0.072 )
                            * pow( q_psf, 0.241 ) + w_press;
        }

        // NASA TP-2015-218751, p.232
        if ( type == Helicopter )
        {
            double f_ramp = cargo_ramp ? 1.3939 : 1.0;

            double w_basic = 5.896 * f_ramp * pow( w_dg / 1000.0, 0.4908 )
                    * pow( n_z, 0.1323 ) * pow( s_f, 0.2544 ) * pow( l_ft, 0.61 );

            double chi_basic = 1.0; // ?? technology factor

            m2_lb = chi_basic * w_basic;

            m1 = Units::lb2kg( m2_lb );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    std::cout << "Fuselage:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

Fuselage::Fuselage( const AircraftData *data ) :
    Component( data )
{
    setName( "Fuselage" );
}

////////////////////////////////////////////////////////////////////////////////

void Fuselage::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( xmlTagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double Fuselage::getComputedMass() const
{
    return computeMass( _ac->getType(),       // Type type,
                        _ac->getFuseLength(), // double l,
                        _ac->getFuseWidth(),  // double w,
                        _ac->getFuseHeight(), // double h,
                        _ac->getWettedArea(), // double wetted_area,
                        _ac->getM_maxTO(),    // double m_maxto,
                        _ac->getNzMax(),      // double nz_max,
                        _ac->getWingDelta(),  // bool wing_delta,
                        _ac->getCargoDoor(),  // CargoDoor cargo_door,
                        _ac->getFuselageLG(), // bool fuselage_lg,
                        _ac->getWingSpan(),   // double wing_span,
                        _ac->getWingSweep(),  // double wing_sweep,
                        _ac->getWingTR(),     // double wing_tr,
                        _ac->getHorTailArm(), // double h_tail_arm,
                        _ac->getPressVol(),   // double press_vol,
                        _ac->getCruiseV(),    // double v_cruise,
                        _ac->getCruiseH(),    // double h_cruise
                        _ac->getCargoRamp() );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
