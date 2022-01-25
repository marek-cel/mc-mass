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
#ifndef ROTORTAIL_H
#define ROTORTAIL_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The RotorTail class.
 *
 * @see Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.230
 */
class RotorTail : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes tail rotor mass.
     * @param type aircraft type
     * @param m_rotor_r [m] main rotor radius
     * @param t_rotor_r [m] tail rotor radius
     * @param m_rotor_tv [m/s] main rotor blade tip velocity
     * @param rotor_mcp [hp] drive system power limit (MCP)
     * @return tail rotor mass expressed in kg
     */
    static double computeMass( Type type,
                               double m_rotor_r,
                               double t_rotor_r,
                               double m_rotor_tv,
                               double rotor_mcp );

    RotorTail( const Aircraft *ac );

    virtual ~RotorTail();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // ROTORTAIL_H
