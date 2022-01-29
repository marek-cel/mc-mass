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

#include <components/Wing.h>

#include <mcutil/misc/Units.h>

#include <utils/Atmosphere.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

double Wing::computeMass( Type type,
                          double wing_exp,
                          double m_maxto,
                          double nz_max,
                          bool wing_delta,
                          double wing_sweep,
                          double wing_tr,
                          double wing_ar,
                          bool wing_var,
                          double area_ctrl,
                          double wing_tc,
                          double wing_fuel,
                          double v_cruise,
                          double h_cruise )
{
    double s_w = Units::sqm2sqft( wing_exp );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( type == FighterAttack )
        {
            m1 = Units::lb2kg( 9.0 * s_w );
        }

        if ( type == CargoTransport )
        {
            m1 = Units::lb2kg( 10.0 * s_w );
        }

        if ( type == GeneralAviation )
        {
            m1 = Units::lb2kg( 2.5 * s_w );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_dg  = Units::kg2lb( m_maxto );
        double n_z   = 1.5 * nz_max;

        double s_csw = Units::kg2lb( area_ctrl );

        double sweep_rad = Units::deg2rad( wing_sweep );

        // Rayner: Aircraft Design, p.572, eq.15.1
        if ( type == FighterAttack )
        {
            double k_vs  = wing_var   ? 1.19  : 1.0;
            double k_dw  = wing_delta ? 0.768 : 1.0;

            m2_lb = 0.0103 * k_dw * k_vs * pow( w_dg * n_z, 0.5 )
                    * pow( s_w, 0.622 ) * pow( wing_ar, 0.785 ) * pow( wing_tc, -0.4 )
                    * pow( 1.0 + wing_tr, 0.05 ) * pow( cos( sweep_rad ), -1.0 )
                    * pow( s_csw, 0.04 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.25
        if ( type == CargoTransport )
        {
            m2_lb = 0.0051 * pow( w_dg * n_z, 0.557 )
                    * pow( s_w, 0.649 ) * pow( wing_ar, 0.5 ) * pow( wing_tc, -0.4 )
                    * pow( 1.0 + wing_tr, 0.1 ) * pow( cos( sweep_rad ), -1.0 )
                    * pow( s_csw, 0.1 );
        }

        // Rayner: Aircraft Design, p.575, eq.15.46
        if ( type == GeneralAviation )
        {
            double w_fw  = Units::kg2lb( wing_fuel );

            double v_mps = Units::kts2mps( v_cruise );
            double h_m   = Units::ft2m( h_cruise );
            double rho = Atmosphere::getDensity( h_m );
            double q = 0.5 * rho * pow( v_mps, 2.0 );
            double q_psf = Units::pa2psf( q );

            m2_lb = 0.036 * pow( s_w, 0.758 ) * pow( w_fw, 0.0035 )
                    * pow( wing_ar / pow( cos( sweep_rad ), 2.0 ), 0.6 )
                    * pow( q_psf, 0.006 ) * pow( wing_tr, 0.04 )
                    * pow( 100 * wing_tc / cos( sweep_rad ), -0.3 )
                    * pow( w_dg * n_z, 0.49 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    std::cout << "Wing:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

Wing::Wing( const AircraftData *data ) :
    Component( data )
{
    setName( "Wing" );
}

////////////////////////////////////////////////////////////////////////////////

void Wing::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( xmlTagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double Wing::getComputedMass() const
{
    return computeMass( _ac->getType(),      // Type type,
                        _ac->getWingExp(),   // double wing_exp,
                        _ac->getM_maxTO(),   // double m_maxto,
                        _ac->getNzMax(),     // double nz_max,
                        _ac->getWingDelta(), // bool wing_delta,
                        _ac->getWingSweep(), // double wing_sweep,
                        _ac->getWingTR(),    // double wing_tr,
                        _ac->getWingAR(),    // double wing_ar,
                        _ac->getWingVar(),   // bool wing_var,
                        _ac->getCtrlArea(),  // double area_ctrl,
                        _ac->getWingTC(),    // double wing_tc,
                        _ac->getWingFuel(),  // double wing_fuel,
                        _ac->getCruiseV(),   // double v_cruise,
                        _ac->getCruiseH() ); // double h_cruise )
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
