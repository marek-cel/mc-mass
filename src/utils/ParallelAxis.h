/****************************************************************************//*
 *  Copyright (C) 2025 Marek M. Cel
 *
 *  This file is part of MC-Mass.
 *
 *  MC-Mass is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MC-Mass is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/
#ifndef MC_MASS_UTILS_PARALLELAXIS_H_
#define MC_MASS_UTILS_PARALLELAXIS_H_

#include <utils/Matrix3x3.h>
#include <utils/Vector3.h>

/**
 * \brief Gets matrix of inertia about parallel axis.
 * \param m [kg] mass
 * \param i [kg*m^2] inertia tensor
 * \param r [m] position
 * \return shifted inertia tensor [kg*m^2]
 *
 * ### Refernces:
 * - Awrejcewicz J.: Classical Mechanics: Kinematics and Statics, 2012, p.163
 * - [Parallel axis theorem - Wikipedia](https://en.wikipedia.org/wiki/Parallel_axis_theorem)
 */
inline Matrix3x3 parallelAxisInertia(double m, const Matrix3x3& i, const Vector3& r)
{
    Matrix3x3 a(
        r.y()*r.y() + r.z()*r.z() , -r.x()*r.y()               , -r.x()*r.z(),
       -r.y()*r.x()               ,  r.x()*r.x() + r.z()*r.z() , -r.y()*r.z(),
       -r.z()*r.x()               , -r.z()*r.y()               ,  r.x()*r.x() + r.y()*r.y()
    );

    return (i + m * a);
}

#endif // MC_MASS_UTILS_PARALLELAXIS_H_
