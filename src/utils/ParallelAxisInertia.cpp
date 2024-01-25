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

#include <utils/ParallelAxisInertia.h>

InertiaMatrix GetParallelAxisInertia(units::mass::kilogram_t m,
                                     const InertiaMatrix& i,
                                     const PositionVector& r)
{
    InertiaMatrix a;

    a.ixx() = m * (  r.y()*r.y() + r.z()*r.z() );
    a.ixy() = m * ( -r.x()*r.y() );
    a.ixz() = m * ( -r.x()*r.z() );

    a.iyx() = m * ( -r.y()*r.x() );
    a.iyy() = m * (  r.x()*r.x() + r.z()*r.z() );
    a.iyz() = m * ( -r.y()*r.z() );

    a.izx() = m * ( -r.z()*r.x() );
    a.izy() = m * ( -r.z()*r.y() );
    a.izz() = m * (  r.x()*r.x() + r.y()*r.y() );

    return (i + a);
}
