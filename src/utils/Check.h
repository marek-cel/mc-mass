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
#ifndef MC_MASS_UTILS_CHECK_H_
#define MC_MASS_UTILS_CHECK_H_

#ifdef _MSC_VER
#   include <float.h>
#endif

#include <cmath>
#include <vector>

/**
 * \brief Checks if given varaible is Infinite.
 * \param val value to test
 * \return function returns TRUE if tested value is Infinite, TRUE otherwise
 */
template <typename T>
inline bool isInf(const T& val)
{
#   ifdef _MSC_VER
    return !_finite(static_cast<double>(val));
#   else
    return std::isinf(static_cast<double>(val));
#   endif
}

/**
 * \brief Checks if given varaible is NaN.
 * \param val value to test
 * \return function returns TRUE if tested value is NaN, TRUE otherwise
 */
template <typename T>
inline bool isNaN(const T& val)
{
    return val != val;
}

/**
 * \brief Checks if given varaible is Infinite or NaN.
 * \param val value to test
 * \return function returns FALSE if tested value is Infinite or NaN, TRUE otherwise
 */
template <typename T>
inline bool isValid(const T& val)
{
    return !( isNaN(val) || isInf(val) );
}

/**
 * \brief Checks if given array is Infinite or NaN.
 * \param array array to test
 * \param size the size of given array
 * \return function returns FALSE if tested array is Infinite or NaN, TRUE otherwise
 */
template <typename T>
inline bool isValid(const T array[], unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (isNaN(array[i]) || isInf(array[i])) return false;
    }

    return true;
}

#endif // MC_MASS_UTILS_CHECK_H_
