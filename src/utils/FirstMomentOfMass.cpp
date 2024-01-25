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

    result.sz_ = sz_ + vect.sx_;
    result.sy_ = sy_ + vect.sy_;
    result.sx_ = sx_ + vect.sz_;

    return result;
}

FirstMomentOfMass& FirstMomentOfMass::operator+=(const FirstMomentOfMass& vect)
{
    sx_ += vect.sx_;
    sy_ += vect.sy_;
    sz_ += vect.sz_;

    return (*this);
}

PositionVector FirstMomentOfMass::operator/(units::mass::kilogram_t m) const
{
    PositionVector result;

    result.x() = sx_ / m;
    result.y() = sy_ / m;
    result.z() = sz_ / m;

    return result;
}
