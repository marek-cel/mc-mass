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
#ifndef UNITS_H
#define UNITS_H

////////////////////////////////////////////////////////////////////////////////

#include <cmath>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Units conversion class.
 */
class Units
{
public:

    // ANGLE

    /**
     * @brief Converts given angle from degrees to radians.
     * @param ang angle expressed in degrees
     * @return angle expressed in radians
     */
    static inline double deg2rad( double ang = 1.0 )
    {
        return ang * M_PI / 180.0;
    }

    /**
     * @brief Converts given angle from radians to degrees.
     * @param ang angle expressed in radians
     * @return angle expressed in degrees
     */
    static inline double rad2deg( double ang = 1.0 )
    {
        return ang * 180.0 / M_PI;
    }

    // LENGTH

    /**
     * @brief Converts given length from metres to feet.
     * @param len length expressed in metres
     * @return length expressed in feet
     */
    static inline double m2ft( double len = 1.0 )
    {
        return len * 3.2808399;
    }

    /**
     * @brief Converts given length from metres to inches.
     * @param len length expressed in metres
     * @return length expressed in inches
     */
    static inline double m2in( double len = 1.0 )
    {
        return len * 39.3700787;
    }

    /**
     * @brief Converts given length from feet to metres.
     * @param len length expressed in feet
     * @return length expressed in metres
     */
    static inline double ft2m( double len = 1.0 )
    {
        return len * 0.3048;
    }

    // VELOCITY

    /**
     * @brief Converts given velocity from m/s to knots.
     * @param vel velocity expressed in m/s
     * @return velocity expressed in knots
     */
    static inline double mps2kts( double vel = 1.0 )
    {
        return vel * 1.943844491;
    }

    /**
     * @brief Converts given velocity from kntos to m/s.
     * @param vel velocity expressed in knots
     * @return velocity expressed in m/s
     */
    static inline double kts2mps( double vel = 1.0 )
    {
        return vel * 0.5144444444444;
    }

    /**
     * @brief Converts given velocity from m/s to ft/s.
     * @param vel velocity expressed in m/s
     * @return velocity expressed in ft/s
     */
    static inline double mps2fps( double vel = 1.0 )
    {
        return vel * 3.2808399;
    }

    // AREA

    static inline double sqm2sqft( double area = 1.0 )
    {
        return area * 10.7639104;
    }

    static inline double sqft2sqm( double area = 1.0 )
    {
        return area * 0.09290304;
    }

    // VOLUME

    static inline double cum2cuft( double vol = 1.0 )
    {
        return vol * 35.3146667;
    }

    // MASS

    /**
     * @brief Converts given mass from kilograms to pounds.
     * @param mass mass expressed in kilograms
     * @return mass expressed in pounds
     */
    static inline double kg2lb( double mass = 1.0 )
    {
        return mass * 2.20462262;
    }

    /**
     * @brief Converts given mass from pounds to kilograms.
     * @param mass mass expressed in pounds
     * @return mass expressed in kilograms
     */
    static inline double lb2kg( double mass = 1.0 )
    {
        return mass * 0.45359237;
    }

    // PRESSURE

    /**
     * @brief Converts given pressure from pascals to psf.
     * @param press pressure expressed in pascals
     * @return pressure expressed in psf
     */
    static inline double pa2psf( double mass = 1.0 )
    {
        return mass * 0.020885434273039;
    }
};

////////////////////////////////////////////////////////////////////////////////

#endif // UNITS_H
