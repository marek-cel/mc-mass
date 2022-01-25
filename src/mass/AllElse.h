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
#ifndef ALLELSE_H
#define ALLELSE_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The AllElse class.
 *
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407
 * @see Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579
 */
class AllElse : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes all-else empty mass.
     * @param type aircraft type
     * @param m_maxto [kg] maximum take-off weight
     * @return all-else empty mass expressed in kg
     */
    static double computeMass( Type type,
                               double m_maxto );

    AllElse( const Aircraft *ac );

    virtual ~AllElse();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // ALLELSE_H
