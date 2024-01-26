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

    result.ixx_ = ixx_ + matrix.ixx_;
    result.ixy_ = ixy_ + matrix.ixy_;
    result.ixz_ = ixz_ + matrix.ixz_;

    result.iyx_ = iyx_ + matrix.iyx_;
    result.iyy_ = iyy_ + matrix.iyy_;
    result.iyz_ = iyz_ + matrix.iyz_;

    result.izx_ = izx_ + matrix.izx_;
    result.izy_ = izy_ + matrix.izy_;
    result.izz_ = izz_ + matrix.izz_;

    return result;
}

InertiaMatrix& InertiaMatrix::operator+=(const InertiaMatrix& matrix)
{
    ixx_ += matrix.ixx_;
    ixy_ += matrix.ixy_;
    ixz_ += matrix.ixz_;

    iyx_ += matrix.iyx_;
    iyy_ += matrix.iyy_;
    iyz_ += matrix.iyz_;

    izx_ += matrix.izx_;
    izy_ += matrix.izy_;
    izz_ += matrix.izz_;

    return (*this);
}
