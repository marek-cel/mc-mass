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

#include <utils/Cuboid.h>

InertiaMatrix Cuboid::GetInertiaMatrix(units::mass::kilogram_t m,
                                       units::length::meter_t l,
                                       units::length::meter_t w,
                                       units::length::meter_t h)
{
    InertiaMatrix result;

    result.ixx() = m * (w*w + h*h) / 12.0;
    result.ixy() = 0.0_kg_m2;
    result.ixz() = 0.0_kg_m2;

    result.iyx() = 0.0_kg_m2;
    result.iyy() = m * (l*l + h*h) / 12.0;
    result.iyz() = 0.0_kg_m2;

    result.izx() = 0.0_kg_m2;
    result.izy() = 0.0_kg_m2;
    result.izz() = m * (l*l + w*w) / 12.0;

    return result;
}
