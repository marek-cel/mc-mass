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

#include <gtest/gtest.h>

#include <limits>
#include <vector>

#include <utils/Check.h>


class TestCheck : public ::testing::Test
{
protected:

    TestCheck() {}
    virtual ~TestCheck() {}
    void SetUp() override {}
    void TearDown() override {}
};


TEST_F(TestCheck, CanCheckIfIsInf)
{
    double zero = 0.0;

    EXPECT_FALSE(isInf(0.0));
    EXPECT_FALSE(isInf(DBL_MIN));
    EXPECT_FALSE(isInf(DBL_MAX));
    EXPECT_FALSE(isInf(std::numeric_limits<double>::min()));
    EXPECT_FALSE(isInf(std::numeric_limits<double>::max()));

    EXPECT_TRUE(isInf(std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(isInf(1.0 / zero));
}


TEST_F(TestCheck, CanCheckIfIsNaN)
{
    EXPECT_FALSE(isNaN(0.0));
    EXPECT_FALSE(isNaN(DBL_MIN));
    EXPECT_FALSE(isNaN(DBL_MAX));
    EXPECT_FALSE(isNaN(std::numeric_limits<double>::min()));
    EXPECT_FALSE(isNaN(std::numeric_limits<double>::max()));

    EXPECT_TRUE(isNaN(std::numeric_limits<double>::quiet_NaN()));
}


TEST_F(TestCheck, CanCheckIfIsValid)
{
    double zero = 0.0;

    EXPECT_TRUE(isValid(0.0));
    EXPECT_TRUE(isValid(DBL_MIN));
    EXPECT_TRUE(isValid(DBL_MAX));
    EXPECT_TRUE(isValid(std::numeric_limits<double>::min()));
    EXPECT_TRUE(isValid(std::numeric_limits<double>::max()));

    EXPECT_FALSE(isValid(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(isValid(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(isValid(1.0 / zero));
}


TEST_F(TestCheck, CanCheckIfIsValidArray)
{
    double zero = 0.0;

    double a1[] = { 0.0, 1.0, 2.0 };
    EXPECT_TRUE(isValid(a1, 3));

    double a2[] = { 0.0, 1.0, DBL_MIN };
    EXPECT_TRUE(isValid(a2, 3));

    double a3[] = { 0.0, 1.0, DBL_MAX };
    EXPECT_TRUE(isValid(a3, 3));

    double a4[] = { 0.0, 1.0, std::numeric_limits<double>::min() };
    EXPECT_TRUE(isValid(a4, 3));

    double a5[] = { 0.0, 1.0, std::numeric_limits<double>::max() };
    EXPECT_TRUE(isValid(a5, 3));

    double a6[] = { 0.0, 1.0, std::numeric_limits<double>::quiet_NaN() };
    EXPECT_FALSE(isValid(a6, 3));

    double a7[] = { 0.0, 1.0, std::numeric_limits<double>::infinity() };
    EXPECT_FALSE(isValid(a7, 3));

    double a8[] = { 0.0, 1.0, 1.0 / zero };
    EXPECT_FALSE(isValid(a8, 3));
}
