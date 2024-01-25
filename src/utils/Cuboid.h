/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
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
#ifndef MC_MASS_UTILS_CUBOID_H_
#define MC_MASS_UTILS_CUBOID_H_

#include <units.h>

#include <utils/InertiaMatrix.h>

/**
 * @brief The Cuboid class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Awrejcewicz J.: Classical Mechanics: Kinematics and Statics, 2012, p.155</li>
 * </ul>
 */
class Cuboid
{
public:

    /**
     * @brief Returns cuboid matrix of inertia.
     * @param m [kg] mass
     * @param l [m] length (dimension x-component)
     * @param w [m] width  (dimension y-component)
     * @param h [m] height (dimension z-component)
     * @return matrix of inertia [kg*m^2]
     */
    static InertiaMatrix GetInertiaMatrix(units::mass::kilogram_t m,
                                          units::length::meter_t l,
                                          units::length::meter_t w,
                                          units::length::meter_t h );
};

#endif // MC_MASS_UTILS_CUBOID_H_
