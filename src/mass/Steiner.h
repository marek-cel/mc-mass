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
#ifndef STEINER_H
#define STEINER_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Matrix3x3.h>
#include <mass/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The Steiner's theorem class.
 */
class Steiner
{
public:

    /**
     * @brief Gets inertia of shifted object.
     * @param m [kg] mass
     * @param i [kg*m^2] inertia tensor
     * @param r [m] position
     * @return shifted inertia tensor [kg*m^2]
     */
    static Matrix3x3 getInertia( double m, const Matrix3x3 &i, const Vector3 &r );

};

////////////////////////////////////////////////////////////////////////////////

#endif // STEINER_H
