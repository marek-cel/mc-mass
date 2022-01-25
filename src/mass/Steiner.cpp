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

#include <mass/Steiner.h>

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Steiner::getInertia( double m, const Matrix3x3 &i, const Vector3 &r )
{
    Matrix3x3 a( r.y()*r.y() + r.z()*r.z() , -r.x()*r.y()              , -r.x()*r.z(),
                 -r.y()*r.x()              , r.x()*r.x() + r.z()*r.z() , -r.y()*r.z(),
                 -r.z()*r.x()              , -r.z()*r.y()              , r.x()*r.x() + r.y()*r.y() );

    return ( i + m * a );
}
