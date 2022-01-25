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
#ifndef GEARMAIN_H
#define GEARMAIN_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The GearMain class.
 *
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579
 * @see Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.233
 */
class GearMain : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes main landing gear mass.
     * @param type aircraft type
     * @param m_empty [kg] aircraft empty mass
     * @param m_maxto [kg] maximum take-off mass
     * @param m_max_land [kg] maximum landing mass
     * @param nz_max_land [-] maximum allowed landing nz
     * @param m_gear_l [m] extended main gear length
     * @param v_stall [kts] stall speed
     * @param m_gear_wheels number of main gear wheels
     * @param m_gear_struts number of main gear struts
     * @param navy_aircraft
     * @param gear_fixed
     * @param gear_cross
     * @param gear_tripod
     * @param m_gear_kneeling
     * @return main landing gear mass expressed in kg
     */
    static double computeMass( Type type,
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
                               bool m_gear_kneeling );

    GearMain( const Aircraft *ac );

    virtual ~GearMain();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // GEARMAIN_H
