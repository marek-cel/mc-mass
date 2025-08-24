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

#include <utils/Vector3.h>


class TestVector3 : public ::testing::Test
{
protected:
    TestVector3() {}
    virtual ~TestVector3() {}
    void SetUp() override {}
    void TearDown() override {}
};


TEST_F(TestVector3, CanCreateI)
{
    Vector3 v1 = Vector3::i();

    EXPECT_DOUBLE_EQ(v1.x(), 1.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
}

TEST_F(TestVector3, CanCreateJ)
{
    Vector3 v1 = Vector3::j();

    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 1.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
}

TEST_F(TestVector3, CanCreateK)
{
    Vector3 v1 = Vector3::k();

    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 1.0);
}

TEST_F(TestVector3, CanCreateEx)
{
    Vector3 v1 = Vector3::ex();

    EXPECT_DOUBLE_EQ(v1.x(), 1.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
}

TEST_F(TestVector3, CanCreateEy)
{
    Vector3 v1 = Vector3::ey();

    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 1.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
}

TEST_F(TestVector3, CanCreateEz)
{
    Vector3 v1 = Vector3::ez();

    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 1.0);
}

TEST_F(TestVector3, CanInstantiate)
{
    Vector3 v1;

    EXPECT_DOUBLE_EQ(v1.x(), 0.0);
    EXPECT_DOUBLE_EQ(v1.y(), 0.0);
    EXPECT_DOUBLE_EQ(v1.z(), 0.0);
}

TEST_F(TestVector3, CanInstantiateAndSetData)
{
    Vector3 v1(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(v1.x(), 1.0);
    EXPECT_DOUBLE_EQ(v1.y(), 2.0);
    EXPECT_DOUBLE_EQ(v1.z(), 3.0);
}

TEST_F(TestVector3, CanGetLengthXY)
{
    Vector3 v1(1.0, 2.0, 3.0);
    // 1^2 + 2^2 = 1 + 4 = 5
    EXPECT_DOUBLE_EQ(v1.getLengthXY(), sqrt(5.0));

    Vector3 v2(2.0, 3.0, 4.0);
    // 2^2 + 3^2 = 4 + 9 = 13
    EXPECT_DOUBLE_EQ(v2.getLengthXY(), sqrt(13.0));
}

TEST_F(TestVector3, CanGetLengthXZ)
{
    Vector3 v1(1.0, 2.0, 3.0);
    // 1^2 + 3^2 = 1 + 9 = 10
    EXPECT_DOUBLE_EQ(v1.getLengthXZ(), sqrt(10.0));

    Vector3 v2(2.0, 3.0, 4.0);
    // 2^2 + 4^2 = 4 + 16 = 20
    EXPECT_DOUBLE_EQ(v2.getLengthXZ(), sqrt(20.0));
}

TEST_F(TestVector3, CanGetLengthYZ)
{
    Vector3 v1(1.0, 2.0, 3.0);
    // 2^2 + 3^2 = 4 + 9 = 13
    EXPECT_DOUBLE_EQ(v1.getLengthYZ(), sqrt(13.0));

    Vector3 v2(2.0, 3.0, 4.0);
    // 3^2 + 4^2 = 9 + 16 = 25
    EXPECT_DOUBLE_EQ(v2.getLengthYZ(), sqrt(25.0));
}

TEST_F(TestVector3, CanGetNormalized)
{
    // expected values calculated with GNU Octave
    // tests/utils/octave/test_vector3.m

    Vector3 v1(1.0, 2.0, 3.0);
    Vector3 v1_n = v1.getNormalized();

    EXPECT_NEAR(v1_n.x(), 0.267261, 1.0e-5);
    EXPECT_NEAR(v1_n.y(), 0.534522, 1.0e-5);
    EXPECT_NEAR(v1_n.z(), 0.801784, 1.0e-5);

    EXPECT_DOUBLE_EQ(v1_n.getLength(), 1.0);
}

TEST_F(TestVector3, CanSetData)
{
    Vector3 v;

    v.set(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST_F(TestVector3, CanAccessElementsViaFunctionsXYZ)
{
    Vector3 v;

    v.x() = 1.0;
    v.y() = 2.0;
    v.z() = 3.0;

    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST_F(TestVector3, CanAdd)
{
    Vector3 v1(1.0, 2.0, 3.0);
    Vector3 v2(4.0, 5.0, 6.0);

    Vector3 v12 = v1 + v2;

    EXPECT_DOUBLE_EQ(v12.x(), 5.0);
    EXPECT_DOUBLE_EQ(v12.y(), 7.0);
    EXPECT_DOUBLE_EQ(v12.z(), 9.0);
}

TEST_F(TestVector3, CanNegate)
{
    Vector3 v1(1.0, 2.0, 3.0);

    Vector3 v1_n = -v1;

    EXPECT_DOUBLE_EQ(v1_n.x(), -1.0);
    EXPECT_DOUBLE_EQ(v1_n.y(), -2.0);
    EXPECT_DOUBLE_EQ(v1_n.z(), -3.0);
}

TEST_F(TestVector3, CanSubtract)
{
    Vector3 v1(4.0, 5.0, 6.0);
    Vector3 v2(3.0, 2.0, 1.0);

    Vector3 v12 = v1 - v2;

    EXPECT_DOUBLE_EQ(v12.x(), 1.0);
    EXPECT_DOUBLE_EQ(v12.y(), 3.0);
    EXPECT_DOUBLE_EQ(v12.z(), 5.0);
}

TEST_F(TestVector3, CanMultiplyByScalar)
{
    Vector3 v1(1.0, 2.0, 3.0);

    Vector3 v1_2 = v1 * 2.0;

    EXPECT_DOUBLE_EQ(v1_2.x(), 2.0);
    EXPECT_DOUBLE_EQ(v1_2.y(), 4.0);
    EXPECT_DOUBLE_EQ(v1_2.z(), 6.0);
}

TEST_F(TestVector3, CanCalculateVectorDotProduct)
{
    Vector3 v1(1.0, 0.0, 0.0);
    Vector3 v2(0.0, 1.0, 0.0);
    Vector3 v3(0.0, 0.0, 1.0);
    Vector3 v4(1.0, 2.0, 3.0);

    double s41 = v4 * v1;
    double s42 = v4 * v2;
    double s43 = v4 * v3;
    double s44 = v4 * v4;

    // expected values calculated with wxMaxima
    // tests/utils/octave/test_vector3_dot_product.m
    EXPECT_DOUBLE_EQ(s41,  1.0);
    EXPECT_DOUBLE_EQ(s42,  2.0);
    EXPECT_DOUBLE_EQ(s43,  3.0);
    EXPECT_DOUBLE_EQ(s44, 14.0);
}

TEST_F(TestVector3, CanDivideByScalar)
{
    Vector3 v1(1.0, 2.0, 3.0);

    Vector3 v1_2 = v1 / 2.0;

    EXPECT_DOUBLE_EQ(v1_2.x(), 0.5);
    EXPECT_DOUBLE_EQ(v1_2.y(), 1.0);
    EXPECT_DOUBLE_EQ(v1_2.z(), 1.5);
}

TEST_F(TestVector3, CanCalculateVectorCrossProduct)
{
    Vector3 v1(1.0, 0.0, 0.0);
    Vector3 v2(0.0, 1.0, 0.0);
    Vector3 v3(0.0, 0.0, 1.0);
    Vector3 v4(1.0, 2.0, 3.0);

    Vector3 v41 = v4 % v1;
    Vector3 v42 = v4 % v2;
    Vector3 v43 = v4 % v3;

    // expected values calculated with wxMaxima
    // tests/utils/octave/test_vector3_cross_product.m
    EXPECT_DOUBLE_EQ(v41.x(),  0.0);
    EXPECT_DOUBLE_EQ(v41.y(),  3.0);
    EXPECT_DOUBLE_EQ(v41.z(), -2.0);

    EXPECT_DOUBLE_EQ(v42.x(), -3.0);
    EXPECT_DOUBLE_EQ(v42.y(),  0.0);
    EXPECT_DOUBLE_EQ(v42.z(),  1.0);

    EXPECT_DOUBLE_EQ(v43.x(),  2.0);
    EXPECT_DOUBLE_EQ(v43.y(), -1.0);
    EXPECT_DOUBLE_EQ(v43.z(),  0.0);
}

TEST_F(TestVector3, CanUnaryAdd)
{
    Vector3 v0(1.0, 2.0, 3.0);
    Vector3 v1(2.0, 3.0, 4.0);

    v0 += v1;

    EXPECT_DOUBLE_EQ(v0.x(), 3.0);
    EXPECT_DOUBLE_EQ(v0.y(), 5.0);
    EXPECT_DOUBLE_EQ(v0.z(), 7.0);
}

TEST_F(TestVector3, CanUnarySubtract)
{
    Vector3 v0(3.0, 5.0, 7.0);
    Vector3 v1(2.0, 3.0, 4.0);

    v0 -= v1;

    EXPECT_DOUBLE_EQ(v0.x(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z(), 3.0);
}

TEST_F(TestVector3, CanUnaryMultiplyByScalar)
{
    Vector3 v0(2.0, 4.0, 6.0);

    v0 *= 0.5;

    EXPECT_DOUBLE_EQ(v0.x(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z(), 3.0);
}

TEST_F(TestVector3, CanUnaryDivideByScalar)
{
    Vector3 v0(2.0, 4.0, 6.0);

    v0 /= 2.0;

    EXPECT_DOUBLE_EQ(v0.x(), 1.0);
    EXPECT_DOUBLE_EQ(v0.y(), 2.0);
    EXPECT_DOUBLE_EQ(v0.z(), 3.0);
}

TEST_F(TestVector3, CanMultiplyByScalarByVector)
{
    Vector3 v1(1.0, 2.0, 3.0);

    Vector3 v1_2 = 2.0 * v1;

    EXPECT_DOUBLE_EQ(v1_2.x(), 2.0);
    EXPECT_DOUBLE_EQ(v1_2.y(), 4.0);
    EXPECT_DOUBLE_EQ(v1_2.z(), 6.0);
}