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

#include <mass/GearMain.h>

#include <mcutils/misc/Units.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

constexpr char GearMain::xmlTagName[];

////////////////////////////////////////////////////////////////////////////////

double GearMain::estimateMass( const AircraftData &data )
{
    double w_dg = Units::kg2lb( data.general.mtow    );
    double w_0  = Units::kg2lb( data.general.m_empty );

    double m1 = 0.0;
    {
        double reduce = data.landing_gear.fixed ? ( 0.014 * w_0 ) : 0.0;

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::FighterAttack )
        {
            double coeff = data.general.navy_ac ? 0.045 : 0.033;
            m1 = 0.85 * Units::lb2kg( coeff * w_dg - reduce );
        }

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::CargoTransport )
        {
            m1 = 0.85 * Units::lb2kg( 0.043 * w_dg - reduce );
        }

        // Rayner: Aircraft Design, p.568, table 15.2
        if ( data.type == AircraftData::GeneralAviation )
        {
            m1 = 0.85 * Units::lb2kg( 0.057 * w_dg - reduce );
        }

        // NASA TP-2015-218751, p.233
        if ( data.type == AircraftData::Helicopter )
        {
            m1 = Units::lb2kg( 0.0325 * w_dg );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_l = Units::kg2lb( data.general.m_maxLand );
        double n_l = 1.5 * data.general.nz_maxLand;

        double l_m_in = Units::m2in( data.landing_gear.main_l );

        // Rayner: Aircraft Design, p.572, eq.15.5
        if ( data.type == AircraftData::FighterAttack )
        {
            double k_cb  = data.landing_gear.cross  ? 2.25  : 1.0;
            double k_tpg = data.landing_gear.tripod ? 0.826 : 1.0;

            m2_lb = k_cb * k_tpg * pow( w_l * n_l, 0.25 ) * pow( l_m_in, 0.973 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.29
        if ( data.type == AircraftData::CargoTransport )
        {
            double k_mp = data.landing_gear.main_kneel ? 1.126 : 1.0;

            m2_lb = 0.0106 * k_mp * pow( w_l, 0.888 ) * pow( n_l, 0.25 ) * pow( l_m_in, 0.4 )
                    * pow( static_cast<double>(data.landing_gear.main_wheels), 0.321 )
                    * pow( static_cast<double>(data.landing_gear.main_struts), -0.5 )
                    * pow( data.general.v_stall, 0.1 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.50
        if ( data.type == AircraftData::GeneralAviation )
        {
            m2_lb = 0.095 * pow( n_l * w_l, 0.768 ) * pow( l_m_in / 12.0, 0.409 );
        }

        // NASA TP-2015-218751, p.233
        if ( data.type == AircraftData::Helicopter )
        {
            m2_lb = 0.4013 * pow( w_dg, 0.6662 ) * pow ( n_l, 0.536 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    //std::cout << "GearMain:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

GearMain::GearMain( const AircraftData *data ) :
    Component( data )
{
    set_name("Main Landing Gear");
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
