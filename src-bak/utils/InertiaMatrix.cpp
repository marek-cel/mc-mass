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

#include <utils/InertiaMatrix.h>

InertiaMatrix InertiaMatrix::operator+(const InertiaMatrix& matrix) const
{
    InertiaMatrix result;

    result._ixx = _ixx + matrix._ixx;
    result._ixy = _ixy + matrix._ixy;
    result._ixz = _ixz + matrix._ixz;

    result._iyx = _iyx + matrix._iyx;
    result._iyy = _iyy + matrix._iyy;
    result._iyz = _iyz + matrix._iyz;

    result._izx = _izx + matrix._izx;
    result._izy = _izy + matrix._izy;
    result._izz = _izz + matrix._izz;

    return result;
}

InertiaMatrix& InertiaMatrix::operator+=(const InertiaMatrix& matrix)
{
    _ixx += matrix._ixx;
    _ixy += matrix._ixy;
    _ixz += matrix._ixz;

    _iyx += matrix._iyx;
    _iyy += matrix._iyy;
    _iyz += matrix._iyz;

    _izx += matrix._izx;
    _izy += matrix._izy;
    _izz += matrix._izz;

    return (*this);
}
