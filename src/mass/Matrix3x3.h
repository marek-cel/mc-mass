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
#ifndef MATRIX3X3_H
#define MATRIX3X3_H

////////////////////////////////////////////////////////////////////////////////

#include <mass/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

/** */
class Matrix3x3
{
public:

    static const int _rows;
    static const int _cols;
    static const int _size;

    /** @brief Constructor. */
    Matrix3x3();

    /** @brief Copy constructor. */
    Matrix3x3( const Matrix3x3 &mtrx );

    /** @brief Constructor. */
    Matrix3x3( double xx, double xy, double xz,
               double yx, double yy, double yz,
               double zx, double zy, double zz );

    inline double xx() const { return _xx; }
    inline double xy() const { return _xy; }
    inline double xz() const { return _xz; }
    inline double yx() const { return _yx; }
    inline double yy() const { return _yy; }
    inline double yz() const { return _yz; }
    inline double zx() const { return _zx; }
    inline double zy() const { return _zy; }
    inline double zz() const { return _zz; }

    inline double& xx() { return _xx; }
    inline double& xy() { return _xy; }
    inline double& xz() { return _xz; }
    inline double& yx() { return _yx; }
    inline double& yy() { return _yy; }
    inline double& yz() { return _yz; }
    inline double& zx() { return _zx; }
    inline double& zy() { return _zy; }
    inline double& zz() { return _zz; }

    void set( double xx, double xy, double xz,
              double yx, double yy, double yz,
              double zx, double zy, double zz );

    /** @brief @brief Items accessor. */
    inline double operator() ( unsigned int row, unsigned int col ) const
    {
        return _items[ row * _cols + col ];
    }

    /** @brief @brief Items accessor. */
    inline double& operator() ( unsigned int row, unsigned int col )
    {
        return _items[ row * _cols + col ];
    }

    /** @brief Assignment operator. */
    const Matrix3x3& operator= ( const Matrix3x3 &mtrx );

    /** @brief Addition operator. */
    Matrix3x3 operator+ ( const Matrix3x3 &mtrx ) const;

    /** @brief Subtraction operator. */
    Matrix3x3 operator- ( const Matrix3x3 &mtrx ) const;

    /** @brief Multiplication operator (by scalar). */
    Matrix3x3 operator* ( double value ) const;

    /** @brief Multiplication operator (by matrix). */
    Matrix3x3 operator* ( const Matrix3x3 &mtrx ) const;

    /** @brief Multiplication operator (by vector). */
    Vector3 operator* ( const Vector3 &vect ) const;

    /** @brief Division operator (by scalar). */
    Matrix3x3 operator/ ( double value ) const;

    /** @brief Unary addition operator. */
    Matrix3x3& operator+= ( const Matrix3x3 &mtrx );

    /** @brief Unary subtraction operator. */
    Matrix3x3& operator-= ( const Matrix3x3 &mtrx );

    /** @brief Unary multiplication operator (by scalar). */
    Matrix3x3& operator*= ( double value );

    /** @brief Unary division operator (by scalar). */
    Matrix3x3& operator/= ( double value );

private:

    double _items[ 9 ];     ///< matrix items

    double &_xx;            ///< xx element
    double &_xy;            ///< xy element
    double &_xz;            ///< xz element

    double &_yx;            ///< yx element
    double &_yy;            ///< yy element
    double &_yz;            ///< yz element

    double &_zx;            ///< zx element
    double &_zy;            ///< zy element
    double &_zz;            ///< zz element
};

////////////////////////////////////////////////////////////////////////////////

/** @brief Multiplication operator (by scalar). */
inline Matrix3x3 operator* ( double value, const Matrix3x3 &mtrx )
{
    return ( mtrx * value );
}

////////////////////////////////////////////////////////////////////////////////

#endif // MATRIX3X3_H
