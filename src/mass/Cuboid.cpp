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

#include <mass/Cuboid.h>

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Cuboid::getInertia( double m, double l, double w, double h )
{
    Matrix3x3 result;

    result.xx() = m * ( w*w + h*h ) / 12.0;
    result.xy() = 0.0;
    result.xz() = 0.0;

    result.yx() = 0.0;
    result.yy() = m * ( l*l + h*h ) / 12.0;
    result.yz() = 0.0;

    result.zx() = 0.0;
    result.zy() = 0.0;
    result.zz() = m * ( l*l + w*w ) / 12.0;

    return result;
}
