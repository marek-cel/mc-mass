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
#ifndef VECTOR3_H
#define VECTOR3_H

////////////////////////////////////////////////////////////////////////////////

/** */
class Vector3
{
public:

    static const int _size;

    /** @brief Constructor. */
    Vector3();

    /** @brief Copy constructor. */
    Vector3( const Vector3 &vect );

    /** @brief Constructor. */
    Vector3( double x, double y, double z );

    inline double  x() const { return _x; }
    inline double  y() const { return _y; }
    inline double  z() const { return _z; }
    inline double& x()       { return _x; }
    inline double& y()       { return _y; }
    inline double& z()       { return _z; }

    /** @brief Sets vector values. */
    void set( double x, double y, double z );

    /** @brief Items accessor. */
    inline double operator() ( unsigned int index ) const
    {
        return _items[ index ];
    }

    /** @brief Items accessor. */
    inline double& operator() ( unsigned int index )
    {
        return _items[ index ];
    }

    /** @brief Assignment operator. */
    const Vector3& operator= ( const Vector3 &vect );

    /** @brief Addition operator. */
    Vector3 operator+ ( const Vector3 &vect ) const;

    /** @brief Negation operator. */
    Vector3 operator- () const;

    /** @brief Subtraction operator. */
    Vector3 operator- ( const Vector3 &vect ) const;

    /** @brief Multiplication operator (by scalar). */
    Vector3 operator* ( double val ) const;

    /** @brief Division operator (by scalar). */
    Vector3 operator/ ( double val ) const;

    /** @brief Dot product operator. */
    double operator* ( const Vector3 &vect ) const;

    /** @brief Cross product operator. */
    Vector3 operator% ( const Vector3 &vect ) const;

    /** @brief Unary addition operator. */
    Vector3& operator+= ( const Vector3 &vect );

    /** @brief Unary subtraction operator. */
    Vector3& operator-= ( const Vector3 &vect );

    /** @brief Unary multiplication operator (by scalar). */
    Vector3& operator*= ( double val );

    /** @brief Unary division operator (by scalar). */
    Vector3& operator/= ( double val );

    /** @brief Unary cross product operator. */
    Vector3& operator%= ( const Vector3 &vect );

private:

    double _items[ 3 ];     ///< vector items

    double &_x;             ///< x element
    double &_y;             ///< y element
    double &_z;             ///< z element
};

////////////////////////////////////////////////////////////////////////////////

/** @brief Multiplication operator (by scalar). */
inline Vector3 operator* ( double val, const Vector3 &vect )
{
    return ( vect * val );
}

////////////////////////////////////////////////////////////////////////////////

#endif // VECTOR3_H
