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
#ifndef WING_H
#define WING_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The Wing class.
 *
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579
 */
class Wing : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes wing mass.
     * @param type aircraft type
     * @param wing_exp [m^2] wing exposed area
     * @param m_maxto [kg] maximum take-off mass
     * @param nz_max [-] maximum allowed load factor
     * @param wing_delta specifies if aircraft has delta wing
     * @param wing_sweep [deg] wing sweep at 25% chord
     * @param wing_tr [-] taper ratio
     * @param wing_ar [-]  aspect ratio
     * @param wing_var specifies if wing has variable sweep
     * @param area_ctrl [m^2] wing mounted control surface area
     * @param wing_tc [-] thickness ratio at root
     * @param wing_fuel [kg] wing fuel capacity
     * @param v_cruise [kts] cruise speed
     * @param h_cruise [ft] cruise altitude
     * @return wing mass expressed in kg
     */
    static double computeMass( Type type,
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
                               double h_cruise );

    Wing( const Aircraft *ac );

    virtual ~Wing();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // WING_H
