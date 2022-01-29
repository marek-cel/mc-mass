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

#include <components/GearMain.h>

#include <mcutil/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

double GearMain::computeMass( Type type,
                              double m_empty,
                              double m_max_to,
                              double m_max_land,
                              double nz_max_land,
                              double m_gear_l,
                              double v_stall,
                              int m_gear_wheels,
                              int m_gear_struts,
                              bool navy_aircraft,
                              bool gear_fixed,
                              bool gear_cross,
                              bool gear_tripod,
                              bool m_gear_kneeling )
{
    double w_dg = Units::kg2lb( m_max_to );
    double w_0  = Units::kg2lb( m_empty  );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        double reduce = gear_fixed ? ( 0.014 * w_0 ) : 0.0;

        if ( type == FighterAttack )
        {
            double coeff = navy_aircraft ? 0.045 : 0.033;
            m1 = 0.85 * Units::lb2kg( coeff * w_dg - reduce );
        }

        if ( type == CargoTransport )
        {
            m1 = 0.85 * Units::lb2kg( 0.043 * w_dg - reduce );
        }

        if ( type == GeneralAviation )
        {
            m1 = 0.85 * Units::lb2kg( 0.057 * w_dg - reduce );
        }

        // NASA TP-2015-218751, p.233
        if ( type == Helicopter )
        {
            m1 = Units::lb2kg( 0.0325 * w_dg );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_l = Units::kg2lb( m_max_land );
        double n_l = 1.5 * nz_max_land;

        double l_m_in = Units::m2in( m_gear_l );

        // Rayner: Aircraft Design, p.572, eq.15.5
        if ( type == FighterAttack )
        {
            double k_cb  = gear_cross  ? 2.25  : 1.0;
            double k_tpg = gear_tripod ? 0.826 : 1.0;

            m2_lb = k_cb * k_tpg * pow( w_l * n_l, 0.25 ) * pow( l_m_in, 0.973 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.29
        if ( type == CargoTransport )
        {
            double k_mp = m_gear_kneeling ? 1.126 : 1.0;

            m2_lb = 0.0106 * k_mp * pow( w_l, 0.888 ) * pow( n_l, 0.25 )
                    * pow( l_m_in, 0.4 ) * pow( (double)m_gear_wheels, 0.321 )
                    * pow( (double)m_gear_struts, -0.5 ) * pow( v_stall, 0.1 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.50
        if ( type == GeneralAviation )
        {
            m2_lb = 0.095 * pow( n_l * w_l, 0.768 ) * pow( l_m_in / 12.0, 0.409 );
        }

        // NASA TP-2015-218751, p.233
        if ( type == Helicopter )
        {
            m2_lb = 0.4013 * pow( w_dg, 0.6662 ) * pow ( n_l, 0.536 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    std::cout << "GearMain:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

GearMain::GearMain( const AircraftData *data ) :
    Component( data )
{
    setName( "Main Landing Gear" );
}

////////////////////////////////////////////////////////////////////////////////

void GearMain::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( xmlTagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double GearMain::getComputedMass() const
{
    return computeMass( _ac->getType(),
                        _ac->getM_empty(),         // double m_empty,
                        _ac->getM_maxTO(),         // double m_max_to,
                        _ac->getM_maxLand(),       // double m_max_land,
                        _ac->getNzMaxLand(),       // double nz_max_land,
                        _ac->getMainGearLength(),  // double m_gear_l,
                        _ac->getStallV(),          // double v_stall,
                        _ac->getMainGearWheels(),  // int m_gear_wheels,
                        _ac->getMainGearStruts(),  // int m_gear_struts,
                        _ac->getNavyAircraft(),    // bool navy_aircraft,
                        _ac->getGearFixed(),       // bool gear_fixed,
                        _ac->getGearCross(),       // bool gear_cross,
                        _ac->getGearTripod(),      // bool gear_tripod,
                        _ac->getGearMainKneel() ); // bool m_gear_kneeling
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
