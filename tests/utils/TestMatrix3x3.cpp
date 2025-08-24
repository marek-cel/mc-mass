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

#include <utils/Matrix3x3.h>

class TestMatrix3x3 : public ::testing::Test
{
protected:
    constexpr static int size = 3;
    TestMatrix3x3() {}
    virtual ~TestMatrix3x3() {}
    void SetUp() override {}
    void TearDown() override {}
};


TEST_F(TestMatrix3x3, CanGetIdentityMatrix)
{
    Matrix3x3 m = Matrix3x3::getIdentityMatrix();

    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1), 0.0);
    EXPECT_DOUBLE_EQ(m(0,2), 0.0);

    EXPECT_DOUBLE_EQ(m(1,0), 0.0);
    EXPECT_DOUBLE_EQ(m(1,1), 1.0);
    EXPECT_DOUBLE_EQ(m(1,2), 0.0);

    EXPECT_DOUBLE_EQ(m(2,0), 0.0);
    EXPECT_DOUBLE_EQ(m(2,1), 0.0);
    EXPECT_DOUBLE_EQ(m(2,2), 1.0);
}


TEST_F(TestMatrix3x3, CanConstruct)
{
    Matrix3x3* m = nullptr;
    EXPECT_NO_THROW(m = new Matrix3x3());
    delete m;
}


TEST_F(TestMatrix3x3, CanDestruct)
{
    Matrix3x3* m = new Matrix3x3();
    EXPECT_NO_THROW(delete m);
}


TEST_F(TestMatrix3x3, CanInstantiate)
{
    Matrix3x3 m;
    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m(r,c), 0.0) << "Error at row " << r << " and col " << c;
        }
    }
}


TEST_F(TestMatrix3x3, CanInstantiateAndCopy)
{
    constexpr int size = 3;

    Matrix3x3 m0(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m1(m0);

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
        }
    }
}


TEST_F(TestMatrix3x3, CanInstantiateAndSetData)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    EXPECT_DOUBLE_EQ(m1(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m1(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m1(0,2), 3.0);
    EXPECT_DOUBLE_EQ(m1(1,0), 4.0);
    EXPECT_DOUBLE_EQ(m1(1,1), 5.0);
    EXPECT_DOUBLE_EQ(m1(1,2), 6.0);
    EXPECT_DOUBLE_EQ(m1(2,0), 7.0);
    EXPECT_DOUBLE_EQ(m1(2,1), 8.0);
    EXPECT_DOUBLE_EQ(m1(2,2), 9.0);
}


TEST_F(TestMatrix3x3, CanAccessXX)
{
    Matrix3x3 m0;

    m0.xx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}


TEST_F(TestMatrix3x3, CanAccessXY)
{
    Matrix3x3 m0;

    m0.xy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}


TEST_F(TestMatrix3x3, CanAccessXZ)
{
    Matrix3x3 m0;

    m0.xz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}


TEST_F(TestMatrix3x3, CanAccessYX)
{
    Matrix3x3 m0;

    m0.yx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}


TEST_F(TestMatrix3x3, CanAccessYY)
{
    Matrix3x3 m0;

    m0.yy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}


TEST_F(TestMatrix3x3, CanAccessYZ)
{
    Matrix3x3 m0;

    m0.yz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}


TEST_F(TestMatrix3x3, CanAccessZX)
{
    Matrix3x3 m0;

    m0.zx() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}


TEST_F(TestMatrix3x3, CanAccessZY)
{
    Matrix3x3 m0;

    m0.zy() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 0.0);
}


TEST_F(TestMatrix3x3, CanAccessZZ)
{
    Matrix3x3 m0;

    m0.zz() = 1.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 0.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 1.0);
}


TEST_F(TestMatrix3x3, CanSetData)
{
    Matrix3x3 m0;

    m0.set(
        11.0, 12.0, 13.0,
        21.0, 22.0, 23.0,
        31.0, 32.0, 33.0
    );

    EXPECT_DOUBLE_EQ(m0.xx(), 11.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 12.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 13.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 21.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 22.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 23.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 31.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 32.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 33.0);
}


TEST_F(TestMatrix3x3, CanGetTransposed)
{
    Matrix3x3 m0(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m1(m0);
    Matrix3x3 mt = m1.getTransposed();

    for ( int r = 0; r < size; ++r )
    {
        for ( int c = 0; c < size; ++c )
        {
            EXPECT_DOUBLE_EQ(m0(r,c), m1(r,c)) << "Error at row " << r << " and col " << c;
            EXPECT_DOUBLE_EQ(mt(r,c), m0(c,r)) << "Error at row " << r << " and col " << c;
        }
    }
}


TEST_F(TestMatrix3x3, CanAdd)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m2(
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0
    );

    Matrix3x3 m0 = m1 + m2;

    EXPECT_DOUBLE_EQ(m0.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m0.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m0.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m0.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m0.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m0.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m0.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m0.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 10.0);
}


TEST_F(TestMatrix3x3, CanNegate)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m0 = -m1;

    EXPECT_DOUBLE_EQ(m0.xx(), -1.0);
    EXPECT_DOUBLE_EQ(m0.xy(), -2.0);
    EXPECT_DOUBLE_EQ(m0.xz(), -3.0);
    EXPECT_DOUBLE_EQ(m0.yx(), -4.0);
    EXPECT_DOUBLE_EQ(m0.yy(), -5.0);
    EXPECT_DOUBLE_EQ(m0.yz(), -6.0);
    EXPECT_DOUBLE_EQ(m0.zx(), -7.0);
    EXPECT_DOUBLE_EQ(m0.zy(), -8.0);
    EXPECT_DOUBLE_EQ(m0.zz(), -9.0);
}


TEST_F(TestMatrix3x3, CanSubstract)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m2(
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0
    );

    Matrix3x3 m0 = m1 - m2;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m0.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 8.0);
}


TEST_F(TestMatrix3x3, CanMultiplyByNumber)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m0 = m1 * 0.5;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m0.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m0.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m0.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 4.5);
}


TEST_F(TestMatrix3x3, CanMultiplyByMatrix)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m2(
        1.1, 2.2, 3.3,
        4.4, 5.5, 6.6,
        7.7, 8.8, 9.9
    );

    Matrix3x3 m0 = m1 * m2;

    EXPECT_NEAR(m0.xx(),  33.0, 1.0e-9);
    EXPECT_NEAR(m0.xy(),  39.6, 1.0e-9);
    EXPECT_NEAR(m0.xz(),  46.2, 1.0e-9);
    EXPECT_NEAR(m0.yx(),  72.6, 1.0e-9);
    EXPECT_NEAR(m0.yy(),  89.1, 1.0e-9);
    EXPECT_NEAR(m0.yz(), 105.6, 1.0e-9);
    EXPECT_NEAR(m0.zx(), 112.2, 1.0e-9);
    EXPECT_NEAR(m0.zy(), 138.6, 1.0e-9);
    EXPECT_NEAR(m0.zz(), 165.0, 1.0e-9);
}


TEST_F(TestMatrix3x3, CanMultiplyByVector)
{
    Matrix3x3 m1(
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    );

    Matrix3x3 m2(
        -1.0,  0.0,  0.0,
         0.0, -1.0,  0.0,
         0.0,  0.0, -1.0
    );

    Matrix3x3 m3(
        0.0, 1.0, 0.0,
        1.0, 0.0, 0.0,
        0.0, 0.0, 1.0
    );

    Matrix3x3 m4(
        1.0,  0.0,  0.0,
        0.0,  0.0, -1.0,
        0.0, -1.0,  0.0
    );

    Vector3 v(1.0, 2.0, 3.0);

    Vector3 v1 = m1 * v;
    EXPECT_NEAR(v1.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v1.y(),  2.0, 1.0e-9);
    EXPECT_NEAR(v1.z(),  3.0, 1.0e-9);

    Vector3 v2 = m2 * v;
    EXPECT_NEAR(v2.x(), -1.0, 1.0e-9);
    EXPECT_NEAR(v2.y(), -2.0, 1.0e-9);
    EXPECT_NEAR(v2.z(), -3.0, 1.0e-9);

    Vector3 v3 = m3 * v;
    EXPECT_NEAR(v3.x(),  2.0, 1.0e-9);
    EXPECT_NEAR(v3.y(),  1.0, 1.0e-9);
    EXPECT_NEAR(v3.z(),  3.0, 1.0e-9);

    Vector3 v4 = m4 * v;
    EXPECT_NEAR(v4.x(),  1.0, 1.0e-9);
    EXPECT_NEAR(v4.y(), -3.0, 1.0e-9);
    EXPECT_NEAR(v4.z(), -2.0, 1.0e-9);
}


TEST_F(TestMatrix3x3, CanDivideByNumber)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );
    Matrix3x3 m0 = m1 / 2.0;

    EXPECT_DOUBLE_EQ(m0.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m0.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m0.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m0.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m0.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m0.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m0.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m0.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m0.zz(), 4.5);
}


TEST_F(TestMatrix3x3, CanUnaryAdd)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m2(
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0
    );

    m1 += m2;

    EXPECT_DOUBLE_EQ(m1.xx(),  2.0);
    EXPECT_DOUBLE_EQ(m1.xy(),  3.0);
    EXPECT_DOUBLE_EQ(m1.xz(),  4.0);
    EXPECT_DOUBLE_EQ(m1.yx(),  5.0);
    EXPECT_DOUBLE_EQ(m1.yy(),  6.0);
    EXPECT_DOUBLE_EQ(m1.yz(),  7.0);
    EXPECT_DOUBLE_EQ(m1.zx(),  8.0);
    EXPECT_DOUBLE_EQ(m1.zy(),  9.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 10.0);
}


TEST_F(TestMatrix3x3, CanUnarySubstract)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    Matrix3x3 m2(
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0
    );

    m1 -= m2;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.0);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yx(), 3.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.yz(), 5.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 6.0);
    EXPECT_DOUBLE_EQ(m1.zy(), 7.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 8.0);
}


TEST_F(TestMatrix3x3, CanUnaryMultiplyByNumber)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    m1 *= 0.5;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m1.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m1.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m1.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 4.5);
}


TEST_F(TestMatrix3x3, CanUnaryDivideByNumber)
{
    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    m1 /= 2.0;

    EXPECT_DOUBLE_EQ(m1.xx(), 0.5);
    EXPECT_DOUBLE_EQ(m1.xy(), 1.0);
    EXPECT_DOUBLE_EQ(m1.xz(), 1.5);
    EXPECT_DOUBLE_EQ(m1.yx(), 2.0);
    EXPECT_DOUBLE_EQ(m1.yy(), 2.5);
    EXPECT_DOUBLE_EQ(m1.yz(), 3.0);
    EXPECT_DOUBLE_EQ(m1.zx(), 3.5);
    EXPECT_DOUBLE_EQ(m1.zy(), 4.0);
    EXPECT_DOUBLE_EQ(m1.zz(), 4.5);
}


TEST_F(TestMatrix3x3, CanMultiplyNumberByMatrix)
{
    constexpr double val = 2.0;

    Matrix3x3 m1(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );
    Matrix3x3 mr;
    mr = val * m1;

    EXPECT_DOUBLE_EQ(mr.xx(),  2.0);
    EXPECT_DOUBLE_EQ(mr.xy(),  4.0);
    EXPECT_DOUBLE_EQ(mr.xz(),  6.0);
    EXPECT_DOUBLE_EQ(mr.yx(),  8.0);
    EXPECT_DOUBLE_EQ(mr.yy(), 10.0);
    EXPECT_DOUBLE_EQ(mr.yz(), 12.0);
    EXPECT_DOUBLE_EQ(mr.zx(), 14.0);
    EXPECT_DOUBLE_EQ(mr.zy(), 16.0);
    EXPECT_DOUBLE_EQ(mr.zz(), 18.0);
}