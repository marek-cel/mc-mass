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

#include <utils/FirstMomentOfMass.h>

#include <utils/PositionVector.h>

FirstMomentOfMass FirstMomentOfMass::operator+(const FirstMomentOfMass& vect) const
{
    FirstMomentOfMass result;

    result._sx = _sx + vect._sx;
    result._sy = _sy + vect._sy;
    result._sz = _sz + vect._sz;

    return result;
}

FirstMomentOfMass& FirstMomentOfMass::operator+=(const FirstMomentOfMass& vect)
{
    _sx += vect._sx;
    _sy += vect._sy;
    _sz += vect._sz;

    return (*this);
}

PositionVector FirstMomentOfMass::operator/(units::mass::kilogram_t m) const
{
    PositionVector result;

    result.x() = _sx / m;
    result.y() = _sy / m;
    result.z() = _sz / m;

    return result;
}
