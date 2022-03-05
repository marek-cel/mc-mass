#include <gtest/gtest.h>

#include <utils/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

class TestVector3 : public ::testing::Test
{
protected:
    TestVector3() {}
    virtual ~TestVector3() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanConstruct)
{
    mc::Vector3 *v = nullptr;
    EXPECT_NO_THROW( v = new mc::Vector3() );
    delete v;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanDestruct)
{
    mc::Vector3 *v = new mc::Vector3();
    EXPECT_NO_THROW( delete v );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanInstantiate)
{
    mc::Vector3 v1;

    EXPECT_DOUBLE_EQ( v1.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v1.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v1.z(), 0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanInstantiateAndCopy)
{
    mc::Vector3 v1( 1.0, 2.0, 3.0 );

    mc::Vector3 v2( v1 );

    EXPECT_DOUBLE_EQ( v2.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v2.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v2.z(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanInstantiateAndSetData)
{
    mc::Vector3 v1( 1.0, 2.0, 3.0 );

    EXPECT_DOUBLE_EQ( v1.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v1.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v1.z(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanSetData)
{
    mc::Vector3 v;

    v.set( 1.0, 0.0, 0.0 );
    EXPECT_DOUBLE_EQ( v.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v.z(), 0.0 );

    v.set( 0.0, 1.0, 0.0 );
    EXPECT_DOUBLE_EQ( v.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v.y(), 1.0 );
    EXPECT_DOUBLE_EQ( v.z(), 0.0 );

    v.set( 0.0, 0.0, 1.0 );
    EXPECT_DOUBLE_EQ( v.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v.z(), 1.0 );

    v.set( 1.0, 2.0, 3.0 );
    EXPECT_DOUBLE_EQ( v.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v.z(), 3.0 );
}


////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanAssign)
{
    mc::Vector3 v;

    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );
    mc::Vector3 v4( 1.0, 2.0, 3.0 );

    v = v1;
    EXPECT_DOUBLE_EQ( v.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v.z(), 0.0 );

    v = v2;
    EXPECT_DOUBLE_EQ( v.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v.y(), 1.0 );
    EXPECT_DOUBLE_EQ( v.z(), 0.0 );

    v = v3;
    EXPECT_DOUBLE_EQ( v.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v.z(), 1.0 );

    v = v4;
    EXPECT_DOUBLE_EQ( v.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v.z(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanAdd)
{
    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );
    mc::Vector3 v4( 1.0, 2.0, 3.0 );

    mc::Vector3 v12 = v1 + v2;
    mc::Vector3 v13 = v1 + v3;
    mc::Vector3 v23 = v2 + v3;

    mc::Vector3 v123 = v1 + v2 + v3;

    mc::Vector3 v41 = v4 + v1;
    mc::Vector3 v42 = v4 + v2;
    mc::Vector3 v43 = v4 + v3;

    mc::Vector3 v4123 = v4 + v1 + v2 + v3;

    EXPECT_DOUBLE_EQ( v12.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v12.y(), 1.0 );
    EXPECT_DOUBLE_EQ( v12.z(), 0.0 );

    EXPECT_DOUBLE_EQ( v13.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v13.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v13.z(), 1.0 );

    EXPECT_DOUBLE_EQ( v23.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v23.y(), 1.0 );
    EXPECT_DOUBLE_EQ( v23.z(), 1.0 );

    EXPECT_DOUBLE_EQ( v123.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v123.y(), 1.0 );
    EXPECT_DOUBLE_EQ( v123.z(), 1.0 );

    EXPECT_DOUBLE_EQ( v41.x(), 2.0 );
    EXPECT_DOUBLE_EQ( v41.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v41.z(), 3.0 );

    EXPECT_DOUBLE_EQ( v42.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v42.y(), 3.0 );
    EXPECT_DOUBLE_EQ( v42.z(), 3.0 );

    EXPECT_DOUBLE_EQ( v43.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v43.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v43.z(), 4.0 );

    EXPECT_DOUBLE_EQ( v4123.x(), 2.0 );
    EXPECT_DOUBLE_EQ( v4123.y(), 3.0 );
    EXPECT_DOUBLE_EQ( v4123.z(), 4.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanNegate)
{
    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );
    mc::Vector3 v4( 1.0, 2.0, 3.0 );

    mc::Vector3 v1_n = -v1;
    mc::Vector3 v2_n = -v2;
    mc::Vector3 v3_n = -v3;
    mc::Vector3 v4_n = -v4;

    EXPECT_DOUBLE_EQ( v1_n.x(), -1.0 );
    EXPECT_DOUBLE_EQ( v1_n.y(),  0.0 );
    EXPECT_DOUBLE_EQ( v1_n.z(),  0.0 );

    EXPECT_DOUBLE_EQ( v2_n.x(),  0.0 );
    EXPECT_DOUBLE_EQ( v2_n.y(), -1.0 );
    EXPECT_DOUBLE_EQ( v2_n.z(),  0.0 );

    EXPECT_DOUBLE_EQ( v3_n.x(),  0.0 );
    EXPECT_DOUBLE_EQ( v3_n.y(),  0.0 );
    EXPECT_DOUBLE_EQ( v3_n.z(), -1.0 );

    EXPECT_DOUBLE_EQ( v4_n.x(), -1.0 );
    EXPECT_DOUBLE_EQ( v4_n.y(), -2.0 );
    EXPECT_DOUBLE_EQ( v4_n.z(), -3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanSubstract)
{
    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );
    mc::Vector3 v4( 1.0, 2.0, 3.0 );

    mc::Vector3 v41 = v4 - v1;
    mc::Vector3 v42 = v4 - v2;
    mc::Vector3 v43 = v4 - v3;

    mc::Vector3 v4123 = v4 - v1 - v2 - v3;

    EXPECT_DOUBLE_EQ( v41.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v41.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v41.z(), 3.0 );

    EXPECT_DOUBLE_EQ( v42.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v42.y(), 1.0 );
    EXPECT_DOUBLE_EQ( v42.z(), 3.0 );

    EXPECT_DOUBLE_EQ( v43.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v43.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v43.z(), 2.0 );

    EXPECT_DOUBLE_EQ( v4123.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v4123.y(), 1.0 );
    EXPECT_DOUBLE_EQ( v4123.z(), 2.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanMultiplyByScalar)
{
    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );
    mc::Vector3 v4( 1.0, 2.0, 3.0 );

    mc::Vector3 v1_2 = v1 * 2.0;
    mc::Vector3 v2_2 = v2 * 2.0;
    mc::Vector3 v3_2 = v3 * 2.0;
    mc::Vector3 v4_2 = v4 * 2.0;

    mc::Vector3 v1_3 = v1 * 3.0;
    mc::Vector3 v2_3 = v2 * 3.0;
    mc::Vector3 v3_3 = v3 * 3.0;
    mc::Vector3 v4_3 = v4 * 3.0;

    EXPECT_DOUBLE_EQ( v1_2.x(), 2.0 );
    EXPECT_DOUBLE_EQ( v1_2.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v1_2.z(), 0.0 );

    EXPECT_DOUBLE_EQ( v2_2.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v2_2.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v2_2.z(), 0.0 );

    EXPECT_DOUBLE_EQ( v3_2.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v3_2.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v3_2.z(), 2.0 );

    EXPECT_DOUBLE_EQ( v4_2.x(), 2.0 );
    EXPECT_DOUBLE_EQ( v4_2.y(), 4.0 );
    EXPECT_DOUBLE_EQ( v4_2.z(), 6.0 );

    EXPECT_DOUBLE_EQ( v1_3.x(), 3.0 );
    EXPECT_DOUBLE_EQ( v1_3.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v1_3.z(), 0.0 );

    EXPECT_DOUBLE_EQ( v2_3.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v2_3.y(), 3.0 );
    EXPECT_DOUBLE_EQ( v2_3.z(), 0.0 );

    EXPECT_DOUBLE_EQ( v3_3.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v3_3.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v3_3.z(), 3.0 );

    EXPECT_DOUBLE_EQ( v4_3.x(), 3.0 );
    EXPECT_DOUBLE_EQ( v4_3.y(), 6.0 );
    EXPECT_DOUBLE_EQ( v4_3.z(), 9.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanDivideByScalar)
{
    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );
    mc::Vector3 v4( 1.0, 2.0, 3.0 );

    mc::Vector3 v1_2 = v1 / 2.0;
    mc::Vector3 v2_2 = v2 / 2.0;
    mc::Vector3 v3_2 = v3 / 2.0;
    mc::Vector3 v4_2 = v4 / 2.0;

    mc::Vector3 v1_4 = v1 / 4.0;
    mc::Vector3 v2_4 = v2 / 4.0;
    mc::Vector3 v3_4 = v3 / 4.0;
    mc::Vector3 v4_4 = v4 / 4.0;

    EXPECT_DOUBLE_EQ( v1_2.x(), 0.5 );
    EXPECT_DOUBLE_EQ( v1_2.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v1_2.z(), 0.0 );

    EXPECT_DOUBLE_EQ( v2_2.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v2_2.y(), 0.5 );
    EXPECT_DOUBLE_EQ( v2_2.z(), 0.0 );

    EXPECT_DOUBLE_EQ( v3_2.x(), 0.0 );
    EXPECT_DOUBLE_EQ( v3_2.y(), 0.0 );
    EXPECT_DOUBLE_EQ( v3_2.z(), 0.5 );

    EXPECT_DOUBLE_EQ( v4_2.x(), 0.5 );
    EXPECT_DOUBLE_EQ( v4_2.y(), 1.0 );
    EXPECT_DOUBLE_EQ( v4_2.z(), 1.5 );

    EXPECT_DOUBLE_EQ( v1_4.x(), 0.25 );
    EXPECT_DOUBLE_EQ( v1_4.y(), 0.0  );
    EXPECT_DOUBLE_EQ( v1_4.z(), 0.0  );

    EXPECT_DOUBLE_EQ( v2_4.x(), 0.0  );
    EXPECT_DOUBLE_EQ( v2_4.y(), 0.25 );
    EXPECT_DOUBLE_EQ( v2_4.z(), 0.0  );

    EXPECT_DOUBLE_EQ( v3_4.x(), 0.0  );
    EXPECT_DOUBLE_EQ( v3_4.y(), 0.0  );
    EXPECT_DOUBLE_EQ( v3_4.z(), 0.25 );

    EXPECT_DOUBLE_EQ( v4_4.x(), 0.25 );
    EXPECT_DOUBLE_EQ( v4_4.y(), 0.5  );
    EXPECT_DOUBLE_EQ( v4_4.z(), 0.75 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanCalculateVectorDotProduct)
{
    // expected values calculated with wxMaxima
    // tests/math/wxmx/test_vector3_dot_product.wxmx

    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );
    mc::Vector3 v4( 1.0, 2.0, 3.0 );

    double s41 = v4 * v1;
    double s42 = v4 * v2;
    double s43 = v4 * v3;
    double s44 = v4 * v4;

    EXPECT_DOUBLE_EQ( s41,  1.0 );
    EXPECT_DOUBLE_EQ( s42,  2.0 );
    EXPECT_DOUBLE_EQ( s43,  3.0 );
    EXPECT_DOUBLE_EQ( s44, 14.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanCalculateVectorCrossProduct)
{
    // expected values calculated with wxMaxima
    // tests/math/wxmx/test_vector3_cross_product.wxmx

    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );
    mc::Vector3 v4( 1.0, 2.0, 3.0 );

    mc::Vector3 v41 = v4 % v1;
    mc::Vector3 v42 = v4 % v2;
    mc::Vector3 v43 = v4 % v3;

    mc::Vector3 v14 = v1 % v4;
    mc::Vector3 v24 = v2 % v4;
    mc::Vector3 v34 = v3 % v4;

    EXPECT_DOUBLE_EQ( v41.x(),  0.0 );
    EXPECT_DOUBLE_EQ( v41.y(),  3.0 );
    EXPECT_DOUBLE_EQ( v41.z(), -2.0 );

    EXPECT_DOUBLE_EQ( v42.x(), -3.0 );
    EXPECT_DOUBLE_EQ( v42.y(),  0.0 );
    EXPECT_DOUBLE_EQ( v42.z(),  1.0 );

    EXPECT_DOUBLE_EQ( v43.x(),  2.0 );
    EXPECT_DOUBLE_EQ( v43.y(), -1.0 );
    EXPECT_DOUBLE_EQ( v43.z(),  0.0 );

    EXPECT_DOUBLE_EQ( v14.x(),  0.0 );
    EXPECT_DOUBLE_EQ( v14.y(), -3.0 );
    EXPECT_DOUBLE_EQ( v14.z(),  2.0 );

    EXPECT_DOUBLE_EQ( v24.x(),  3.0 );
    EXPECT_DOUBLE_EQ( v24.y(),  0.0 );
    EXPECT_DOUBLE_EQ( v24.z(), -1.0 );

    EXPECT_DOUBLE_EQ( v34.x(), -2.0 );
    EXPECT_DOUBLE_EQ( v34.y(),  1.0 );
    EXPECT_DOUBLE_EQ( v34.z(),  0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanUnaryAdd)
{
    mc::Vector3 v0( 1.0, 2.0, 3.0 );
    mc::Vector3 v1( 2.0, 3.0, 4.0 );

    v0 += v1;

    EXPECT_DOUBLE_EQ( v0.x(), 3.0 );
    EXPECT_DOUBLE_EQ( v0.y(), 5.0 );
    EXPECT_DOUBLE_EQ( v0.z(), 7.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanUnarySubstract)
{
    mc::Vector3 v0( 3.0, 5.0, 7.0 );
    mc::Vector3 v1( 2.0, 3.0, 4.0 );

    v0 -= v1;

    EXPECT_DOUBLE_EQ( v0.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v0.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v0.z(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanUnaryMultiplyByScalar)
{
    mc::Vector3 v0( 2.0, 4.0, 6.0 );

    v0 *= 0.5;

    EXPECT_DOUBLE_EQ( v0.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v0.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v0.z(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanUnaryDivideByScalar)
{
    mc::Vector3 v0( 2.0, 4.0, 6.0 );

    v0 /= 2.0;

    EXPECT_DOUBLE_EQ( v0.x(), 1.0 );
    EXPECT_DOUBLE_EQ( v0.y(), 2.0 );
    EXPECT_DOUBLE_EQ( v0.z(), 3.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanUnaryVectorCrossProduct)
{
    mc::Vector3 v0( 1.0, 2.0, 3.0 );

    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 v2( 0.0, 1.0, 0.0 );
    mc::Vector3 v3( 0.0, 0.0, 1.0 );

    mc::Vector3 vt;

    vt = v0;
    vt %= v1;

    EXPECT_DOUBLE_EQ( vt.x(),  0.0 );
    EXPECT_DOUBLE_EQ( vt.y(),  3.0 );
    EXPECT_DOUBLE_EQ( vt.z(), -2.0 );

    vt = v0;
    vt %= v2;

    EXPECT_DOUBLE_EQ( vt.x(), -3.0 );
    EXPECT_DOUBLE_EQ( vt.y(),  0.0 );
    EXPECT_DOUBLE_EQ( vt.z(),  1.0 );

    vt = v0;
    vt %= v3;

    EXPECT_DOUBLE_EQ( vt.x(),  2.0 );
    EXPECT_DOUBLE_EQ( vt.y(), -1.0 );
    EXPECT_DOUBLE_EQ( vt.z(),  0.0 );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestVector3, CanMultiplyScalarByVector)
{
    mc::Vector3 v1( 1.0, 0.0, 0.0 );
    mc::Vector3 r = 2.0 * v1;

    EXPECT_DOUBLE_EQ( r.x(), 2.0 );
    EXPECT_DOUBLE_EQ( r.y(), 0.0 );
    EXPECT_DOUBLE_EQ( r.z(), 0.0 );
}
