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
#ifndef TAILHOR_H
#define TAILHOR_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The TailHor class.
 *
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579
 * @see Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.230-231
 */
class TailHor : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes horizontal tail mass.
     * @param type aircraft type
     * @param h_tail_area [m^2] tail area
     * @param m_maxto [kg] maximum take-off weight
     * @param nz_max [-] maximum allowed load factor
     * @param h_tail_f_w [m] fuselage width at horizontal tail intersection
     * @param h_tail_span [m] horizontal tail span
     * @param h_tail_sweep [deg] tail sweep
     * @param h_tail_moving specifies if is all-moving tail
     * @param h_tail_ar horizontal tail aspect ratio
     * @param h_tail_arm [m] tail length 25%-MAC to tail 25%-MAC
     * @param elev_area [m^2] elevator area
     * @param h_tail_tr [-] horizontal tail taper ratio
     * @param h_tail_tc [-] horizontal tail thickness ratio
     * @param v_cruise [kts] cruise speed
     * @param h_cruise [ft] cruise altitude
     * @return horizontal tail mass expressed in kg
     */
    static double computeMass( Type type,
                               double h_tail_area,
                               double m_maxto,
                               double nz_max,
                               double h_tail_f_w,
                               double h_tail_span,
                               double h_tail_sweep,
                               bool h_tail_moving,
                               double h_tail_ar,
                               double h_tail_arm,
                               double elev_area,
                               double h_tail_tr,
                               double h_tail_tc,
                               double v_cruise,
                               double h_cruise );

    TailHor( const Aircraft *ac );

    virtual ~TailHor();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // TAILHOR_H
