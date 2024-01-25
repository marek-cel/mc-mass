/****************************************************************************//*
 *  Copyright (C) 2024 Marek M. Cel
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
#ifndef MC_MASS_UTILS_PARALLELAXISINERTIA_H_
#define MC_MASS_UTILS_PARALLELAXISINERTIA_H_

#include <utils/InertiaMatrix.h>
#include <utils/PositionVector.h>

/**
 * @brief GetParallelAxisInertia
 * @param m mass
 * @param i inertia matrix
 * @param r position
 * @return shifted inertia matrix
 */
InertiaMatrix GetParallelAxisInertia(units::mass::kilogram_t m,
                                     const InertiaMatrix& i,
                                     const PositionVector& r);

#endif // MC_MASS_UTILS_PARALLELAXISINERTIA_H_
