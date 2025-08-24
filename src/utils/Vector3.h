/****************************************************************************//*
 *  Copyright (C) 2025 Marek M. Cel
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
#ifndef MC_MASS_UTILS_VECTOR3_H_
#define MC_MASS_UTILS_VECTOR3_H_

#include <cmath>

#include <sstream>
#include <string>

#include <utils/Check.h>

class Vector3
{
public:

    inline static const Vector3 i() { return Vector3(1.0, 0.0, 0.0); }
    inline static const Vector3 j() { return Vector3(0.0, 1.0, 0.0); }
    inline static const Vector3 k() { return Vector3(0.0, 0.0, 1.0); }

    inline static const Vector3 ex() { return i(); }
    inline static const Vector3 ey() { return j(); }
    inline static const Vector3 ez() { return k(); }

    Vector3() = default;
    Vector3(const Vector3&) = default;
    Vector3(Vector3&&) = default;
    Vector3& operator=(const Vector3&) = default;
    Vector3& operator=(Vector3&&) = default;

    Vector3(double x, double y, double z)
    {
        set(x, y, z);
    }

    bool isValid() const
    {
        return ::isValid(_x) && ::isValid(_y) && ::isValid(_z);
    }

    inline double getLengthXY() const { return sqrt(_x*_x + _y*_y); }
    inline double getLengthXZ() const { return sqrt(_x*_x + _z*_z); }
    inline double getLengthYZ() const { return sqrt(_y*_y + _z*_z); }

    double getLength2() const
    {
        return _x*_x + _y*_y + _z*_z;
    }

    double getLength() const
    {
        return sqrt(getLength2());
    }

    void normalize()
    {
        double len = getLength();
        if ( len > 0.0 )
        {
            _x /= len;
            _y /= len;
            _z /= len;
        }
    }

    Vector3 getNormalized() const
    {
        Vector3 result = *this;
        result.normalize();
        return result;
    }

    std::string toString() const
    {
        std::stringstream ss;
        ss << _x << "\t" << _y << "\t" << _z;
        return ss.str();
    }

    void set(double x, double y, double z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    void zeroize()
    {
        _x = 0.0;
        _y = 0.0;
        _z = 0.0;
    }

    inline double  x() const { return _x; }
    inline double  y() const { return _y; }
    inline double  z() const { return _z; }
    inline double& x()       { return _x; }
    inline double& y()       { return _y; }
    inline double& z()       { return _z; }

    inline double  p() const { return _x; }
    inline double  q() const { return _y; }
    inline double  r() const { return _z; }
    inline double& p()       { return _x; }
    inline double& q()       { return _y; }
    inline double& r()       { return _z; }

    inline double  u() const { return _x; }
    inline double  v() const { return _y; }
    inline double  w() const { return _z; }
    inline double& u()       { return _x; }
    inline double& v()       { return _y; }
    inline double& w()       { return _z; }

    Vector3 operator+(const Vector3& other) const
    {
        return Vector3(_x + other._x, _y + other._y, _z + other._z);
    }

    Vector3 operator-() const
    {
        return Vector3(-_x, -_y, -_z);
    }

    Vector3 operator-(const Vector3& other) const
    {
        return Vector3(_x - other._x, _y - other._y, _z - other._z);
    }

    Vector3 operator*(double scalar) const
    {
        return Vector3(_x * scalar, _y * scalar, _z * scalar);
    }

    double operator*(const Vector3& other) const
    {
        return _x * other._x + _y * other._y + _z * other._z;
    }

    Vector3 operator/(double scalar) const
    {
        return (*this) * (1.0 / scalar);
    }

    Vector3 operator%(const Vector3& other) const
    {
        return Vector3(
            _y * other._z - _z * other._y,
            _z * other._x - _x * other._z,
            _x * other._y - _y * other._x
        );
    }

    Vector3& operator+=(const Vector3& other)
    {
        _x += other._x;
        _y += other._y;
        _z += other._z;
        return *this;
    }

    Vector3& operator-=(const Vector3& other)
    {
        _x -= other._x;
        _y -= other._y;
        _z -= other._z;
        return *this;
    }

    Vector3& operator*=(double scalar)
    {
        _x *= scalar;
        _y *= scalar;
        _z *= scalar;
        return *this;
    }

    Vector3& operator/=(double scalar)
    {
        return (*this) *= (1.0 / scalar);
    }

private:

    double _x = 0.0;
    double _y = 0.0;
    double _z = 0.0;
};


inline Vector3 operator*(double scalar, const Vector3& vec)
{
    return vec * scalar;
}

#endif // MC_MASS_UTILS_VECTOR3_H_
