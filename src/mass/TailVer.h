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
#ifndef TAILVER_H
#define TAILVER_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The TailVer class.
 *
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579
 * @see Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.230-231
 */
class TailVer : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes vertical tail mass.
     * @param type aircraft type
     * @param v_tail_area [m^2] vertical tail area
     * @param m_maxto [kg] maximum take-off weight
     * @param nz_max [-] maximum allowed load factor
     * @param v_tail_sweep [deg] vertical tail sweep
     * @param v_tail_arm [m] vertical tail arm
     * @param v_tail_ar [-] vertical tail aspect ratio
     * @param v_tail_tr [-] vertical tail taper ratio
     * @param v_tail_tc [-] thickness ratio at root
     * @param rudd_area [m^2] rudder area
     * @param t_tail specifies if tail is T-type
     * @param h_tail_roll specifies if horizontal tail is rolling
     * @param mach_max Mach number design maximum
     * @param v_cruise [kts] cruise speed
     * @param h_cruise [ft] cruise altitude
     * @param v_tail_rotor specifies if tail rotor is located on the vertical tail
     * @return vertical tail mass expressed in kg
     */
    static double computeMass( Type type,
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
                               bool v_tail_rotor );

    TailVer( const Aircraft *ac );

    virtual ~TailVer();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // TAILVER_H
