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
 ******************************************************************************/

#include <utils/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

const int Vector3::_size = 3;

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3() :
    _x ( _items[ 0 ] ),
    _y ( _items[ 1 ] ),
    _z ( _items[ 2 ] )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( const Vector3 &vect ) :
    _x ( _items[ 0 ] ),
    _y ( _items[ 1 ] ),
    _z ( _items[ 2 ] )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] = vect._items[ i ];
    }
}

////////////////////////////////////////////////////////////////////////////////

Vector3::Vector3( double x, double y, double z ) :
    _x ( _items[ 0 ] ),
    _y ( _items[ 1 ] ),
    _z ( _items[ 2 ] )
{
    set( x, y, z );
}

////////////////////////////////////////////////////////////////////////////////

void Vector3::set( double x, double y, double z )
{
    _x = x;
    _y = y;
    _z = z;
}

////////////////////////////////////////////////////////////////////////////////

const Vector3& Vector3::operator= ( const Vector3 &vect )
{
    _x = vect._x;
    _y = vect._y;
    _z = vect._z;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator+ ( const Vector3 &vect ) const
{
    Vector3 result;

    result._x = _x + vect._x;
    result._y = _y + vect._y;
    result._z = _z + vect._z;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator- () const
{
    Vector3 result;

    result._x = -_x;
    result._y = -_y;
    result._z = -_z;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator- ( const Vector3 &vect ) const
{
    Vector3 result;

    result._x = _x - vect._x;
    result._y = _y - vect._y;
    result._z = _z - vect._z;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator* ( double val ) const
{
    Vector3 result;

    result._x = _x * val;
    result._y = _y * val;
    result._z = _z * val;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator/ ( double val ) const
{
    Vector3 result;

    result._x = _x / val;
    result._y = _y / val;
    result._z = _z / val;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

double Vector3::operator* ( const Vector3 &vect ) const
{
    return ( _x*vect._x + _y*vect._y + _z*vect._z );
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator% ( const Vector3 &vect ) const
{
    Vector3 result;

    result._x = _y * vect._z - _z * vect._y;
    result._y = _z * vect._x - _x * vect._z;
    result._z = _x * vect._y - _y * vect._x;

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator+= ( const Vector3 &vect )
{
    _x += vect._x;
    _y += vect._y;
    _z += vect._z;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator-= ( const Vector3 &vect )
{
    _x -= vect._x;
    _y -= vect._y;
    _z -= vect._z;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator*= ( double val )
{
    _x *= val;
    _y *= val;
    _z *= val;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator/= ( double val )
{
    _x /= val;
    _y /= val;
    _z /= val;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator%= ( const Vector3 &vect )
{
    (*this) = (*this) % vect;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
