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
 ******************************************************************************/

#include <utils/Atmosphere.h>

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

// US Standard Atmosphere 1976, Table 3, p.3
const double Atmosphere::_m_i[] = {
    28.0134,
    31.9988,
    39.948,
    44.00995,
    20.183,
    4.0026,
    83.8,
    131.3,
    16.04303,
    2.01594
};

// US Standard Atmosphere 1976, Table 3, p.3
const double Atmosphere::_f_i[] = {
    0.78084,
    0.209476,
    0.00934,
    0.000314,
    0.00001818,
    0.00000524,
    0.00000114,
    0.000000087,
    0.000002,
    0.0000005
};

// US Standard Atmosphere 1976, Table 4, p.3
const double Atmosphere::_h_b[] = {
    11000.0,
    20000.0,
    32000.0,
    47000.0,
    51000.0,
    71000.0,
    84852.0
};

// US Standard Atmosphere 1976, Table I, p.50-73
const double Atmosphere::_p_b[] = {
    101325.0,
     22632.0,
      5474.8,
       868.01,
       110.9,
        66.938,
         3.9564
};

// US Standard Atmosphere 1976, Table I, p.50-73
const double Atmosphere::_t_b[] = {
    288.15,
    216.65,
    216.65,
    228.65,
    270.65,
    270.65,
    214.65
};

// US Standard Atmosphere 1976, Table 4, p.3
const double Atmosphere::_l_b[] = {
    -6.5e-3,
    0.0,
    1.0e-3,
    2.8e-3,
    0.0,
    -2.8e-3,
    -2.0e-3
};

// [kg/kmol] mean molecular weight, US Standard Atmosphere 1976, p.9
const double Atmosphere::_m =
        ( Atmosphere::_m_i[ Atmosphere::N2  ] * Atmosphere::_f_i[ Atmosphere::N2  ]
        + Atmosphere::_m_i[ Atmosphere::O2  ] * Atmosphere::_f_i[ Atmosphere::O2  ]
        + Atmosphere::_m_i[ Atmosphere::Ar  ] * Atmosphere::_f_i[ Atmosphere::Ar  ]
        + Atmosphere::_m_i[ Atmosphere::CO2 ] * Atmosphere::_f_i[ Atmosphere::CO2 ]
        + Atmosphere::_m_i[ Atmosphere::Ne  ] * Atmosphere::_f_i[ Atmosphere::Ne  ]
        + Atmosphere::_m_i[ Atmosphere::He  ] * Atmosphere::_f_i[ Atmosphere::He  ]
        + Atmosphere::_m_i[ Atmosphere::Kr  ] * Atmosphere::_f_i[ Atmosphere::Kr  ]
        + Atmosphere::_m_i[ Atmosphere::Xe  ] * Atmosphere::_f_i[ Atmosphere::Xe  ]
        + Atmosphere::_m_i[ Atmosphere::CH4 ] * Atmosphere::_f_i[ Atmosphere::CH4 ]
        + Atmosphere::_m_i[ Atmosphere::H2  ] * Atmosphere::_f_i[ Atmosphere::H2  ] )
        /
        ( Atmosphere::_f_i[ Atmosphere::N2  ]
        + Atmosphere::_f_i[ Atmosphere::O2  ]
        + Atmosphere::_f_i[ Atmosphere::Ar  ]
        + Atmosphere::_f_i[ Atmosphere::CO2 ]
        + Atmosphere::_f_i[ Atmosphere::Ne  ]
        + Atmosphere::_f_i[ Atmosphere::He  ]
        + Atmosphere::_f_i[ Atmosphere::Kr  ]
        + Atmosphere::_f_i[ Atmosphere::Xe  ]
        + Atmosphere::_f_i[ Atmosphere::CH4 ]
        + Atmosphere::_f_i[ Atmosphere::H2  ] );

const double Atmosphere::_r     = 8.31432e3;    // US Standard Atmosphere 1976, Table 2, p.2
const double Atmosphere::_s     = 110.0;        // US Standard Atmosphere 1976, Table 2, p.2
const double Atmosphere::_beta  = 1.458e-6;     // US Standard Atmosphere 1976, Table 2, p.2
const double Atmosphere::_gamma = 1.4;          // US Standard Atmosphere 1976, Table 2, p.2

const double Atmosphere::_std_sl_p = 101325.0;  // US Standard Atmosphere 1976, Table 2, p.2
const double Atmosphere::_std_sl_t = 288.15;    // US Standard Atmosphere 1976, Table 2, p.2
const double Atmosphere::_std_sl_rho = 1.225;

const double Atmosphere::_g = 9.80665;

////////////////////////////////////////////////////////////////////////////////

double Atmosphere::getDensity( double altitude )
{
    Atmosphere atmosphere;
    atmosphere.update( altitude );
    return atmosphere.getDensity();
}

////////////////////////////////////////////////////////////////////////////////

Atmosphere::Atmosphere()
{
    update( 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

Atmosphere::~Atmosphere() {}

////////////////////////////////////////////////////////////////////////////////

void Atmosphere::update( double altitude )
{
    double h_b = _h_b[ 5 ];
    double p_b = _p_b[ 6 ];
    double t_b = _t_b[ 6 ];
    double l_b = 0.0;

    if ( altitude < _h_b[ 0 ] )
    {
        h_b = 0.0;
        p_b = _p_b[ 0 ];
        t_b = _std_sl_t;
        l_b = -( _std_sl_t - _t_b[ 1 ] ) / _h_b[ 0 ];
    }
    else
    {
        for ( int i = 1; i < 7; i++ )
        {
            if ( altitude < _h_b[ i ] )
            {
                h_b = _h_b[ i - 1 ];
                p_b = _p_b[ i ];
                t_b = _t_b[ i ];
                l_b = _l_b[ i ];

                break;
            }
        }
    }

    double delta_h = altitude - h_b;

    // [K] temperature, US Standard Atmosphere 1976, p.10
    _temperature = t_b + l_b * delta_h;

    // [Pa] pressure, US Standard Atmosphere 1976, p.12
    if ( fabs( l_b ) < 1.0e-6 )
    {
        _pressure = p_b * exp( -( _g * _m * delta_h ) / ( _r * t_b ) );
    }
    else
    {
        _pressure = p_b * pow( t_b / _temperature, ( _g * _m ) / ( _r * l_b ) );

        if ( altitude < _h_b[ 0 ] )
        {
            _pressure = ( _pressure / _std_sl_p ) * _std_sl_p;
        }
    }

    // [kg/m^3] density, US Standard Atmosphere 1976, p.15
    _density = ( _pressure * _m ) / ( _r * _temperature );

    // [m/s] speed of sound, US Standard Atmosphere 1976, p.18
    _speedOfSound = sqrt( ( _gamma * _r * _temperature ) / _m );

    // [Pa*s] dynamic viscosity, US Standard Atmosphere 1976, p.19
    _dynViscosity = _beta * pow( _temperature, 3.0 / 2.0 ) / ( _temperature + _s );

    // [m^2/s] kinematic viscosity, US Standard Atmosphere 1976, p.19
    _kinViscosity = _dynViscosity / _density;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
