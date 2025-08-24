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

#include <utils/StringUtils.h>

#include <cstdio>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

#include <utils/Check.h>


int compareStrings(const std::string& str_1, const std::string& str_2,
                   bool case_sensitive)
{
    std::string strTemp_1 = str_1;
    std::string strTemp_2 = str_2;
    if (!case_sensitive)
    {
        strTemp_1 = toLower(str_1);
        strTemp_2 = toLower(str_2);
    }
    return strTemp_1.compare(strTemp_2);
}


std::string getFirstLine(const std::string& str)
{
    std::istringstream iss(str);
    std::string firstLine;
    std::getline(iss, firstLine);
    return firstLine;
}


std::vector<std::string> splitString(const std::string& str, const std::string& sep)
{
    std::vector<std::string> result;

    std::string temp = str;
    size_t pos = 0;
    std::string token;
    while ((pos = temp.find(sep)) != std::string::npos)
    {
        token = temp.substr(0, pos);
        result.push_back(token);
        temp.erase(0, pos + 1);
    }
    result.push_back(temp);
    return result;
}


std::string stripLeadingSpaces(const std::string& str)
{
    std::string::size_type offset = 0;
    for (unsigned int i = 0; i < str.size(); ++i)
    {
        if (!isspace(str.c_str()[i]))
        {
            break;
        }
        offset++;
    }
    return str.substr(offset);
}


std::string stripTrailingSpaces(const std::string& str)
{
    std::string::size_type offset = 0;
    for (unsigned int i = 0; i < str.size(); ++i)
    {
        if (!isspace(str.c_str()[i]))
        {
            offset = static_cast<std::string::size_type>(i);
        }
    }
    return str.substr(0, offset + 1);
}


std::string stripSpaces(const std::string& str)
{
    std::string::size_type offset_l = 0;
    std::string::size_type offset_t = 0;
    bool l_passed = false;
    for (unsigned int i = 0; i < str.size(); ++i)
    {
        if (!isspace(str.c_str()[i]))
        {
            offset_t = i;
            l_passed = true;
        }
        else
        {
            if (!l_passed) offset_l++;
        }
    }
    return str.substr(offset_l, offset_t - offset_l + 1);
}


bool toBool(const std::string& str, bool def)
{
    bool result = def;
    int temp = std::numeric_limits<int>::quiet_NaN();
    std::stringstream ss(str);
    ss >> temp;
    if (isValid(temp))
    {
        result = temp != 0;
    }
    return result;
}


int toInt(const std::string& str, int def)
{
    int result = def;
    int temp = std::numeric_limits<int>::quiet_NaN();
    std::stringstream ss(str);
    ss >> temp;
    if (isValid(temp))
    {
        result = temp;
    }
    return result;
}


double toDouble(const std::string& str, double def)
{
    double result = def;
    double temp = std::numeric_limits<double>::quiet_NaN();
    std::stringstream ss(str);
    ss >> temp;
    if (isValid(temp))
    {
        result = temp;
    }
    return result;
}


std::string toLower(const std::string& str)
{
    std::string result;
    result.clear();
    unsigned int length = static_cast<unsigned int>(str.length());
    for (unsigned int i = 0; i < length; ++i)
    {
        result += static_cast<char>(tolower(str.c_str()[i]));
    }
    return result;
}


std::string toUpper(const std::string& str)
{
    std::string result;
    result.clear();
    unsigned int length = static_cast<unsigned int>(str.length());
    for (unsigned int i = 0; i < length; ++i)
    {
        result += static_cast<char>(toupper(str.c_str()[i]));
    }
    return result;
}
