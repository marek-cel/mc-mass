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
#ifndef ROTORDRIVE_H
#define ROTORDRIVE_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Component.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The RotorDrive class.
 *
 * @see Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.236
 */
class RotorDrive : public Component
{
public:

    static const char xml_tag[];

    /**
     * @brief Computes rotor drive system mass.
     * @param type aircraft type
     * @param m_rotor_rpm [rpm] main rotor nominal rotation speed
     * @param m_rotor_gr [-] main rotor gear ratio
     * @param rotor_mcp [hp] drive system power limit (MCP)
     * @return rotor drive system mass expressed in kg
     */
    static double computeMass( Type type,
                               double m_rotor_rpm,
                               double m_rotor_gr,
                               double rotor_mcp );

    RotorDrive( const Aircraft *ac );

    virtual ~RotorDrive();

    virtual void save( QDomDocument *doc, QDomElement *parentNode );

    virtual double getComputedMass() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif // ROTORDRIVE_H
