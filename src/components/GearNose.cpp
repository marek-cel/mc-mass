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

constexpr char GearNose::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double GearNose::estimateMass( const AircraftData &data )
{
    double w_dg = Units::kg2lb( data.general.mtow );
    double w_0  = Units::kg2lb( data.general.m_empty );

    double m1 = 0.0;
    {
        double reduce = data.landing_gear.fixed ? ( 0.014 * w_0 ) : 0.0;

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::FighterAttack )
        {
            double coeff = data.general.navy_ac ? 0.045 : 0.033;
            m1 = 0.15 * Units::lb2kg( coeff * w_dg - reduce );
        }

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = 0.15 * Units::lb2kg( 0.043 * w_dg - reduce );
        }

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = 0.15 * Units::lb2kg( 0.057 * w_dg - reduce );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_l = Units::kg2lb( data.general.m_maxLand );
        double n_l = 1.5 * data.general.nz_maxLand;

        double l_n_in = Units::m2in( data.landing_gear.nose_l );

        // Rayner: Aircraft Design, p.572, eq.15.3
        if ( data.type == AircraftData::FighterAttack )
        {
            m2_lb = pow( w_l * n_l, 0.29 ) * pow( l_n_in, 0.5 )
                  * pow( static_cast<double>(data.landing_gear.nose_wheels), 0.525 );
        }

        // Rayner: Aircraft Design, p.575, eq.15.27
        if ( data.type == AircraftData::CargoTransport )
        {
            double k_np = data.landing_gear.nose_kneel ? 1.15 : 1.0;

            m2_lb = 0.032 * k_np * pow( w_l, 0.646 ) * pow( n_l, 0.2 ) * pow( l_n_in, 0.5 )
                    * pow( static_cast<double>(data.landing_gear.nose_wheels), 0.45 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.48
        if ( data.type == AircraftData::GeneralAviation )
        {
            m2_lb = 0.125 * pow( n_l * w_l, 0.566 ) * pow( l_n_in / 12.0, 0.845 )
                    - ( data.landing_gear.fixed ? 0.014 * w_0 : 0.0 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    //std::cout << "GearNose:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

GearNose::GearNose( const AircraftData *data ) :
    Component( data )
{
    setName( "Nose Landing Gear" );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
