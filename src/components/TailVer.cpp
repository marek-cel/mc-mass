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

#include <components/TailVer.h>

#include <mcutil/misc/Units.h>

#include <utils/Atmosphere.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

double TailVer::computeMass( Type type,
                             double v_tail_area,
                             double m_maxto,
                             double nz_max,
                             double v_tail_sweep,
                             double v_tail_arm,
                             double v_tail_ar,
                             double v_tail_tr,
                             double v_tail_tc,
                             double rudd_area,
                             bool t_tail,
                             bool h_tail_roll,
                             double mach_max,
                             double v_cruise,
                             double h_cruise,
                             bool v_tail_rotor )
{
    double s_vt = Units::sqm2sqft( v_tail_area );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        if ( type == FighterAttack )
        {
            m1 = Units::lb2kg( 5.3 * s_vt );
        }

        if ( type == CargoTransport )
        {
            m1 = Units::lb2kg( 5.5 * s_vt );
        }

        if ( type == GeneralAviation )
        {
            m1 = Units::lb2kg( 2.0 * s_vt );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_dg  = Units::kg2lb( m_maxto );
        double n_z   = 1.5 * nz_max;

        double l_t_ft = Units::m2ft( v_tail_arm );

        double ht_hv = t_tail ? 1.0 : 0.0;

        double sweep_rad = Units::deg2rad( v_tail_sweep );

        // Rayner: Aircraft Design, p.572, eq.15.3
        if ( type == FighterAttack )
        {
            double s_r = Units::sqm2sqft( rudd_area );

            double k_rht = h_tail_roll ? 1.047 : 1.0;

            m2_lb = 0.452 * k_rht * pow( 1.0 + ht_hv, 0.5 ) * pow( w_dg * n_z, 0.488 )
                    * pow( s_vt, 0.718 ) * pow( mach_max, 0.341 ) * pow( l_t_ft, -1.0 )
                    * pow( 1.0 + s_r / s_vt, 0.348 ) * pow( v_tail_ar, 0.223 )
                    * pow( 1.0 + v_tail_tr, 0.25 ) * pow( cos( sweep_rad ), -0.323 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.27
        if ( type == CargoTransport )
        {
            double k_z = l_t_ft;

            m2_lb = 0.0026 * pow( 1.0 + ht_hv, 0.225 ) * pow( w_dg, 0.556 )
                    * pow( n_z, 0.536 ) * pow( l_t_ft, -0.5 ) * pow( s_vt, 0.5 )
                    * pow( k_z, 0.875 ) * pow( cos( sweep_rad ), -1.0 )
                    * pow( v_tail_ar, 0.35 ) * pow( v_tail_tc, -0.5 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.48
        if ( type == GeneralAviation )
        {
            double v_mps = Units::kts2mps( v_cruise );
            double h_m   = Units::ft2m( h_cruise );
            double rho = Atmosphere::getDensity( h_m );
            double q = 0.5 * rho * pow( v_mps, 2.0 );
            double q_psf = Units::pa2psf( q );

            double lambda_vt = v_tail_tr;

            if ( lambda_vt < 0.2 ) lambda_vt = 0.2;

            m2_lb = 0.073 * ( 1.0 + 0.2 * ht_hv ) * pow( n_z * w_dg, 0.376 )
                    * pow( q_psf, 0.122 ) * pow( s_vt, 0.873 )
                    * pow( 100.0 * v_tail_tc / cos( sweep_rad ), -0.49 )
                    * pow( v_tail_ar / pow( cos( sweep_rad ), 2.0 ), 0.357 )
                    * pow( lambda_vt, 0.039 );
        }

        // NASA TP-2015-218751, p.230
        if ( type == Helicopter )
        {
            double f_tr = v_tail_rotor ? 1.6311 : 1.0;

            double chi_vt = 1.0; // ?? technology factor

            m2_lb = chi_vt * 1.046 * f_tr * pow( s_vt, 0.9441 ) * pow( v_tail_ar, 0.5332 );

            m1 = Units::lb2kg( m2_lb );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    std::cout << "TailVer:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

TailVer::TailVer( const AircraftData *data ) :
    Component( data )
{
    setName( "Vertical Tail" );
}

////////////////////////////////////////////////////////////////////////////////

void TailVer::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( xmlTagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double TailVer::getComputedMass() const
{
    return computeMass( _ac->getType(),           // Type type,
                        _ac->getVerTailArea(),    // double v_tail_area,
                        _ac->getM_maxTO(),        // double m_maxto,
                        _ac->getNzMax(),          // double nz_max,
                        _ac->getVerTailSweep(),   // double v_tail_sweep,
                        _ac->getVerTailArm(),     // double v_tail_arm,
                        _ac->getVerTailAR(),      // double v_tail_ar,
                        _ac->getVerTailTR(),      // double v_tail_tr,
                        _ac->getVerTailTC(),      // double v_tail_tc,
                        _ac->getRuddArea(),       // double rudd_area,
                        _ac->getTailT(),          // bool t_tail,
                        _ac->getHorTailRolling(), // bool h_tail_roll,
                        _ac->getMachMax(),        // double mach_max,
                        _ac->getCruiseV(),        // double v_cruise,
                        _ac->getCruiseH(),        // double h_cruise
                        _ac->getVerTailRotor() );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
