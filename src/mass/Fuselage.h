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
#ifndef FUSELAGE_H
#define FUSELAGE_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The Fuselage class.
 *
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579
 * @see Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.231-232
 */
class Fuselage : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes fuselage mass.
     * @param type aircraft type
     * @param l [m] fuselage structural length
     * @param w [m] fuselage structural width
     * @param h [m] fuselage structural height
     * @param wetted_area [m^2] fuselage wetted area
     * @param m_maxto [kg] maximum take-off weight
     * @param nz_max [-] maximum allowed load factor
     * @param wing_delta specifies if aircraft has delta wing
     * @param cargo_door cargo door type
     * @param fuselage_lg fuselage mounted landing gear
     * @param wing_span [m] wing span
     * @param wing_sweep [deg] wing sweep at 25% chord
     * @param wing_tr [-] taper ratio
     * @param h_tail_arm [m] horizontal tail arm
     * @param press_vol [m^3] volume of pressurized section
     * @param v_cruise [kts] cruise speed
     * @param h_cruise [ft] cruise altitude
     * @param cargo_ramp specifies if helicopter has a cargo ramp
     * @return fuselage mass expressed in kg
     */
    static double computeMass( Type type,
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
                               bool cargo_ramp );

    Fuselage( const Aircraft *ac );

    virtual ~Fuselage();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // FUSELAGE_H
