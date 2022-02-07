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

#include <utils/Matrix3x3.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

const int Matrix3x3::_rows = 3;
const int Matrix3x3::_cols = 3;
const int Matrix3x3::_size = Matrix3x3::_rows * Matrix3x3::_cols;

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3() :
    _xx ( _items[ 0 ] ),
    _xy ( _items[ 1 ] ),
    _xz ( _items[ 2 ] ),
    _yx ( _items[ 3 ] ),
    _yy ( _items[ 4 ] ),
    _yz ( _items[ 5 ] ),
    _zx ( _items[ 6 ] ),
    _zy ( _items[ 7 ] ),
    _zz ( _items[ 8 ] )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( const Matrix3x3 &mtrx ) :
    _xx ( _items[ 0 ] ),
    _xy ( _items[ 1 ] ),
    _xz ( _items[ 2 ] ),
    _yx ( _items[ 3 ] ),
    _yy ( _items[ 4 ] ),
    _yz ( _items[ 5 ] ),
    _zx ( _items[ 6 ] ),
    _zy ( _items[ 7 ] ),
    _zz ( _items[ 8 ] )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] = mtrx._items[ i ];
    }
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3::Matrix3x3( double xx, double xy, double xz,
                      double yx, double yy, double yz,
                      double zx, double zy, double zz ) :
    _xx ( _items[ 0 ] ),
    _xy ( _items[ 1 ] ),
    _xz ( _items[ 2 ] ),
    _yx ( _items[ 3 ] ),
    _yy ( _items[ 4 ] ),
    _yz ( _items[ 5 ] ),
    _zx ( _items[ 6 ] ),
    _zy ( _items[ 7 ] ),
    _zz ( _items[ 8 ] )
{
    set( xx, xy, xz,
         yx, yy, yz,
         zx, zy, zz );
}

////////////////////////////////////////////////////////////////////////////////

void Matrix3x3::set( double xx, double xy, double xz,
                     double yx, double yy, double yz,
                     double zx, double zy, double zz )
{
    _xx = xx;
    _xy = xy;
    _xz = xz;

    _yx = yx;
    _yy = yy;
    _yz = yz;

    _zx = zx;
    _zy = zy;
    _zz = zz;
}

////////////////////////////////////////////////////////////////////////////////

const Matrix3x3& Matrix3x3::operator= ( const Matrix3x3 &mtrx )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] = mtrx._items[ i ];
    }

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator+ ( const Matrix3x3 &mtrx ) const
{
    Matrix3x3 result;

    for ( unsigned int i = 0; i < _size; i++ )
    {
        result._items[ i ] = _items[ i ] + mtrx._items[ i ];
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator- ( const Matrix3x3 &mtrx ) const
{
    Matrix3x3 result;

    for ( unsigned int i = 0; i < _size; i++ )
    {
        result._items[ i ] = _items[ i ] - mtrx._items[ i ];
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator* ( double value ) const
{
    Matrix3x3 result;

    for ( unsigned int i = 0; i < _size; i++ )
    {
        result._items[ i ] = _items[ i ] * value;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator* ( const Matrix3x3 &mtrx ) const
{
    Matrix3x3 result;

    for ( unsigned int r = 0; r < _rows; r++ )
    {
        for ( unsigned int c = 0; c < _cols; c++ )
        {
            result(r,c) = 0.0;

            for ( unsigned int i = 0; i < _cols; i++ )
            {
                result(r,c) += ( _items[ r*_cols + i ] * mtrx(i,c) );
            }
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Matrix3x3::operator* ( const Vector3 &vect ) const
{
    Vector3 result;

    for ( unsigned int r = 0; r < _rows; r++ )
    {
        result(r) = 0.0;

        for ( unsigned int c = 0; c < _cols; c++ )
        {
            result(r) += ( _items[ r*_cols + c ] * vect(c) );
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Matrix3x3::operator/ ( double value ) const
{
    Matrix3x3 result;

    for ( unsigned int i = 0; i < _size; i++ )
    {
        result._items[ i ] = _items[ i ] / value;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator+= ( const Matrix3x3 &mtrx )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] += mtrx._items[ i ];
    }

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator-= ( const Matrix3x3 &mtrx )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] -= mtrx._items[ i ];
    }

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator*= ( double value )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] *= value;
    }

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3& Matrix3x3::operator/= ( double value )
{
    for ( unsigned int i = 0; i < _size; i++ )
    {
        _items[ i ] /= value;
    }

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
