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
#ifndef MC_MASS_UTILS_MATRIX3X3_H_
#define MC_MASS_UTILS_MATRIX3X3_H_

#include <cmath>

#include <sstream>
#include <string>

#include <utils/Check.h>
#include <utils/Vector3.h>

class Matrix3x3
{
public:

    static Matrix3x3 getIdentityMatrix()
    {
        return Matrix3x3(
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
        );
    }

    Matrix3x3() = default;
    Matrix3x3(const Matrix3x3&) = default;
    Matrix3x3(Matrix3x3&&) = default;
    Matrix3x3& operator=(const Matrix3x3&) = default;
    Matrix3x3& operator=(Matrix3x3&&) = default;

    Matrix3x3(double xx, double xy, double xz,
              double yx, double yy, double yz,
              double zx, double zy, double zz)
    {
        set(
            xx, xy, xz,
            yx, yy, yz,
            zx, zy, zz
        );
    }

    bool isValid() const
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if ( !::isValid(_m[i][j]) )
                {
                    return false;
                }
            }
        }
        return true;
    }

    void set(double xx, double xy, double xz,
             double yx, double yy, double yz,
             double zx, double zy, double zz)
    {
        _m[0][0] = xx;  _m[0][1] = xy;  _m[0][2] = xz;
        _m[1][0] = yx;  _m[1][1] = yy;  _m[1][2] = yz;
        _m[2][0] = zx;  _m[2][1] = zy;  _m[2][2] = zz;
    }

    inline double xx() const { return _m[0][0]; }
    inline double xy() const { return _m[0][1]; }
    inline double xz() const { return _m[0][2]; }
    inline double yx() const { return _m[1][0]; }
    inline double yy() const { return _m[1][1]; }
    inline double yz() const { return _m[1][2]; }
    inline double zx() const { return _m[2][0]; }
    inline double zy() const { return _m[2][1]; }
    inline double zz() const { return _m[2][2]; }

    inline double& xx() { return _m[0][0]; }
    inline double& xy() { return _m[0][1]; }
    inline double& xz() { return _m[0][2]; }
    inline double& yx() { return _m[1][0]; }
    inline double& yy() { return _m[1][1]; }
    inline double& yz() { return _m[1][2]; }
    inline double& zx() { return _m[2][0]; }
    inline double& zy() { return _m[2][1]; }
    inline double& zz() { return _m[2][2]; }

    void transpose()
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            for (unsigned int j = i + 1; j < 3; ++j)
            {
                std::swap(_m[i][j], _m[j][i]);
            }
        }
    }

    Matrix3x3 getTransposed() const
    {
        Matrix3x3 result = *this;
        result.transpose();
        return result;
    }

    inline double operator()(unsigned int row, unsigned int col) const
    {
        return _m[row][col];
    }

    Matrix3x3 operator+(const Matrix3x3& other) const
    {
        Matrix3x3 result;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                result._m[i][j] = _m[i][j] + other._m[i][j];
            }
        }
        return result;
    }

    Matrix3x3 operator-() const
    {
        Matrix3x3 result;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                result._m[i][j] = -_m[i][j];
            }
        }
        return result;
    }

    Matrix3x3 operator-(const Matrix3x3& other) const
    {
        Matrix3x3 result;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                result._m[i][j] = _m[i][j] - other._m[i][j];
            }
        }
        return result;
    }

    Matrix3x3 operator*(double scalar) const
    {
        Matrix3x3 result;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                result._m[i][j] = _m[i][j] * scalar;
            }
        }
        return result;
    }

    Vector3 operator*(const Vector3& vec) const
    {
        return Vector3(
            _m[0][0] * vec.x() + _m[0][1] * vec.y() + _m[0][2] * vec.z(),
            _m[1][0] * vec.x() + _m[1][1] * vec.y() + _m[1][2] * vec.z(),
            _m[2][0] * vec.x() + _m[2][1] * vec.y() + _m[2][2] * vec.z()
        );
    }

    Matrix3x3 operator*(const Matrix3x3& other) const
    {
        Matrix3x3 result;
        for (unsigned int i = 0; i < 3; ++i)
        {
            for (unsigned int j = 0; j < 3; ++j)
            {
                result._m[i][j] = 0.0;
                for (unsigned int k = 0; k < 3; ++k)
                {
                    result._m[i][j] += _m[i][k] * other._m[k][j];
                }
            }
        }
        return result;
    }

    Matrix3x3 operator/(double scalar) const
    {
        Matrix3x3 result = *this;
        for (unsigned int i = 0; i < 3; ++i)
        {
            for (unsigned int j = 0; j < 3; ++j)
            {
                result._m[i][j] /= scalar;
            }
        }
        return result;
    }

    Matrix3x3& operator+=(const Matrix3x3& other)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            for (unsigned int j = 0; j < 3; ++j)
            {
                _m[i][j] += other._m[i][j];
            }
        }
        return *this;
    }

    Matrix3x3& operator-=(const Matrix3x3& other)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            for (unsigned int j = 0; j < 3; ++j)
            {
                _m[i][j] -= other._m[i][j];
            }
        }
        return *this;
    }

    Matrix3x3& operator*=(double scalar)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            for (unsigned int j = 0; j < 3; ++j)
            {
                _m[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrix3x3& operator/=(double scalar)
    {
        for (unsigned int i = 0; i < 3; ++i)
        {
            for (unsigned int j = 0; j < 3; ++j)
            {
                _m[i][j] /= scalar;
            }
        }
        return *this;
    }

private:

    double _m[3][3] = {
        { 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 }
    };
};


inline Matrix3x3 operator*(double scalar, const Matrix3x3& mat)
{
    return mat * scalar;
}

#endif // MC_MASS_UTILS_MATRIX3X3_H_
