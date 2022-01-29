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

#include <components/GearNose.h>

#include <mcutil/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

double GearNose::computeMass( Type type,
                              double m_empty,
                              double m_maxto,
                              double m_max_land,
                              double nz_max_land,
                              double n_gear_l,
                              int n_gear_wheels,
                              bool navy_aircraft,
                              bool gear_fixed,
                              bool n_gear_kneeling )
{
    double w_dg = Units::kg2lb( m_maxto );
    double w_0  = Units::kg2lb( m_empty );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        double reduce = gear_fixed ? ( 0.014 * w_0 ) : 0.0;

        if ( type == FighterAttack )
        {
            double coeff = navy_aircraft ? 0.045 : 0.033;
            m1 = 0.15 * Units::lb2kg( coeff * w_dg - reduce );
        }

        if ( type == CargoTransport )
        {
            m1 = 0.15 * Units::lb2kg( 0.043 * w_dg - reduce );
        }

        if ( type == GeneralAviation )
        {
            m1 = 0.15 * Units::lb2kg( 0.057 * w_dg - reduce );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_l = Units::kg2lb( m_max_land );
        double n_l = 1.5 * nz_max_land;

        double l_n_in = Units::m2in( n_gear_l );

        // Rayner: Aircraft Design, p.572, eq.15.3
        if ( type == FighterAttack )
        {
            m2_lb = pow( w_l * n_l, 0.29 ) * pow( l_n_in, 0.5 ) * pow( (double)n_gear_wheels, 0.525 );
        }

        // Rayner: Aircraft Design, p.575, eq.15.27
        if ( type == CargoTransport )
        {
            double k_np = n_gear_kneeling ? 1.15 : 1.0;

            m2_lb = 0.032 * k_np * pow( w_l, 0.646 ) * pow( n_l, 0.2 )
                    * pow( l_n_in, 0.5 ) * pow( (double)n_gear_wheels, 0.45 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.48
        if ( type == GeneralAviation )
        {
            m2_lb = 0.125 * pow( n_l * w_l, 0.566 ) * pow( l_n_in / 12.0, 0.845 )
                    - ( gear_fixed ? 0.014 * w_0 : 0.0 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    std::cout << "GearNose:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

GearNose::GearNose( const AircraftData *data ) :
    Component( data )
{
    setName( "Nose Landing Gear" );
}

////////////////////////////////////////////////////////////////////////////////

void GearNose::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( xmlTagName );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double GearNose::getComputedMass() const
{
    return computeMass( _ac->getType(),            // Type type,
                        _ac->getM_empty(),         // double m_empty,
                        _ac->getM_maxTO(),         // double m_maxto,
                        _ac->getM_maxLand(),       // double m_max_land,
                        _ac->getNzMaxLand(),       // double nz_max_land,
                        _ac->getNoseGearLength(),  // double n_gear_l,
                        _ac->getNoseGearWheels(),  // int n_gear_wheels,
                        _ac->getNavyAircraft(),    // bool navy_aircraft,
                        _ac->getGearFixed(),       // bool gear_fixed,
                        _ac->getGearNoseKneel() ); // bool n_gear_kneeling
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
