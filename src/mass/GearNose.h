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
#ifndef GEARNOSE_H
#define GEARNOSE_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The GearNose class.
 *
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579
 */
class GearNose : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes landing gear mass.
     * @param type aircraft type
     * @param m_empty [kg] aircraft empty mass
     * @param m_maxto [kg] maximum take-off mass
     * @param m_max_land [kg] maximum landing mass
     * @param nz_max_land [-] maximum allowed landing nz
     * @param n_gear_l [m] extended nose gear length
     * @param n_gear_wheels number of nose gear wheels
     * @param navy_aircraft specifies
     * @param gear_fixed
     * @param n_gear_kneeling
     * @return nose landing gear mass expressed in kg
     */
    static double computeMass( Type type,
                               double m_empty,
                               double m_maxto,
                               double m_max_land,
                               double nz_max_land,
                               double n_gear_l,
                               int n_gear_wheels,
                               bool navy_aircraft,
                               bool gear_fixed,
                               bool n_gear_kneeling );

    GearNose( const Aircraft *ac );

    virtual ~GearNose();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // GEARNOSE_H
