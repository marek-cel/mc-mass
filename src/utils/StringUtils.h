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
#ifndef MC_MASS_UTILS_STRINGUTILS_H_
#define MC_MASS_UTILS_STRINGUTILS_H_

#include <limits>
#include <sstream>
#include <string>
#include <vector>

/**
 * \brief Compares strings.
 * \param str_1 1st string to compare
 * \param str_2 2nd string to compare
 * \param case_sensitive specifies if comparison is case sensitive
 * \return integer result of the comparison (returns 0 if strings are equal)
 */
int compareStrings(const std::string& str_1, const std::string& str_2,
                            bool case_sensitive = false);

/**
 * \brief Returns string first line;
 * \param str string to be processed
 * \return string first line
 */
std::string getFirstLine(const std::string& str);

/**
 * \brief Splits string with the given delimeter.
 * \param str string to be splitted
 * \param sep string separator
 * \return vector of strings
 */
std::vector<std::string> splitString(const std::string& str, const std::string& sep);

/**
 * \brief Returns string with leading white spaces removed.
 * \param str string to be processed
 * \return string with leading white spaces removed
 */
std::string stripLeadingSpaces(const std::string& str);

/**
 * \brief Returns string with trailing white spaces removed.
 * \param str string to be processed
 * \return string with trailing white spaces removed
 */
std::string stripTrailingSpaces(const std::string& str);

/**
 * \brief Returns string with both leading and trailing white spaces removed.
 * \param str string to be processed
 * \return string with leading and trailing white spaces removed
 */
std::string stripSpaces(const std::string& str);

/**
 * \brief Converts string into variable.
 * \param str string to be processed
 * \param def default value
 * \return result value
 */
bool toBool(const std::string& str, bool def = std::numeric_limits<bool>::quiet_NaN());

/**
 * \brief Converts string into variable.
 * \param str string to be processed
 * \param def default value
 * \return result value
 */
int toInt(const std::string& str, int def = std::numeric_limits<int>::quiet_NaN());

/**
 * \brief Converts string into variable.
 * \param str string to be processed
 * \param def default value
 * \return result value
 */
double toDouble(const std::string& str, double def = std::numeric_limits<double>::quiet_NaN());

/**
 * \brief Converts variable into string.
 * \param val value to be processed
 * \return result string
 */
template <typename T>
inline std::string toString(T val)
{
    std::stringstream ss;
    ss.imbue(std::locale("C"));
    ss << val;
    return ss.str();
}

/**
 * \brief Converts string to lower case.
 * \param str string to be processed
 * \return result string
 */
std::string toLower(const std::string& str);

/**
 * \brief Converts string to upper case.
 * \param str string to be processed
 * \return result string
 */
std::string toUpper(const std::string& str);

#endif // MC_MASS_UTILS_STRINGUTILS_H_
