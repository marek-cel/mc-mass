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

#include <utils/ParallelAxis.h>


class TestParallelAxis : public ::testing::Test
{
protected:

    TestParallelAxis() {}
    virtual ~TestParallelAxis() {}
    void SetUp() override {}
    void TearDown() override {}
};


TEST_F(TestParallelAxis, CanCalculate)
{
    // expected values from https://en.wikipedia.org/wiki/List_of_moments_of_inertia
    // Slender rod along y-axis of length l and mass m about center
    double l = 1.0;
    double m = 1.0;

    Matrix3x3 i(
        m*l*l/12.0 , 0.0 , 0.0,
        0.0        , 0.0 , 0.0,
        0.0        , 0.0 , m*l*l/12.0
    );

    Vector3 r(0.0, l/2.0, 0.0);

    Matrix3x3 i_end = parallelAxisInertia(m, i, r);

    constexpr double tol = 1.0e-9;
    EXPECT_NEAR(i_end.xx(), m*l*l/3.0, tol);
    EXPECT_NEAR(i_end.xy(), 0.0, tol);
    EXPECT_NEAR(i_end.xz(), 0.0, tol);
    EXPECT_NEAR(i_end.yx(), 0.0, tol);
    EXPECT_NEAR(i_end.yy(), 0.0, tol);
    EXPECT_NEAR(i_end.yz(), 0.0, tol);
    EXPECT_NEAR(i_end.zz(), m*l*l/3.0, tol);
}
