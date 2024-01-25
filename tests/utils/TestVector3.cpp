#include <gtest/gtest.h>

#include <units.h>

#include <utils/Vector3.h>

using namespace units;
using namespace units::literals;

class TestVector3 : public ::testing::Test
{
protected:
    TestVector3() {}
    virtual ~TestVector3() {}
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestVector3, CanConstruct)
{
    Vector3<double>* v = nullptr;
    EXPECT_NO_THROW((v = new Vector3<double>()));
    delete v;
}

TEST_F(TestVector3, CanDestruct)
{
    constexpr int size = 3;
    Vector3<double>* v = new Vector3<double>();
    EXPECT_NO_THROW(delete v);
}

TEST_F(TestVector3, CanInstantiate)
{
    Vector3<double> v;

    EXPECT_DOUBLE_EQ(v.x(), 0.0);
    EXPECT_DOUBLE_EQ(v.y(), 0.0);
    EXPECT_DOUBLE_EQ(v.z(), 0.0);
}

TEST_F(TestVector3, CanInstantiateAndSet)
{
    Vector3<double> v(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(v.x(), 1.0);
    EXPECT_DOUBLE_EQ(v.y(), 2.0);
    EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST_F(TestVector3, CanInstantiateUnits)
{
    Vector3<length::meter_t> v;

    EXPECT_DOUBLE_EQ(v.x()(), 0.0);
    EXPECT_DOUBLE_EQ(v.y()(), 0.0);
    EXPECT_DOUBLE_EQ(v.z()(), 0.0);
}

TEST_F(TestVector3, CanInstantiateUnitsAndSet)
{
    Vector3<length::meter_t> v(1.0_ft, 2.0_ft, 3.0_ft);

    EXPECT_DOUBLE_EQ(v.x()(), 0.3048);
    EXPECT_DOUBLE_EQ(v.y()(), 0.3048 * 2.0);
    EXPECT_DOUBLE_EQ(v.z()(), 0.3048 * 3.0);
}

TEST_F(TestVector3, CanGetHalfLength)
{
    Vector3<double> v;

    v.x() = 1.0;
    v.y() = 2.0;
    v.z() = 3.0;

    // 1^2 + 2^2 + 3^2 = 1 + 4 + 9 = 14
    EXPECT_DOUBLE_EQ(v.GetLength2(), 14.0);
}

TEST_F(TestVector3, CanGetLength)
{
    Vector3<double> v;

    v.x() = 1.0;
    v.y() = 2.0;
    v.z() = 3.0;

    // sqrt(1^2 + 2^2 + 3^2) = sqrt(1 + 4 + 9) = sqrt(14) ~= 3.741657
    EXPECT_NEAR(v.GetLength(), 3.741657, 1.0e-5);
}

TEST_F(TestVector3, CanAdd)
{
    Vector3<double> v1(1.0, 2.0, 3.0);
    Vector3<double> v2(4.0, 5.0, 6.0);

    Vector3<double> vr = v1 + v2;

    EXPECT_DOUBLE_EQ(vr.x(), 5.0);
    EXPECT_DOUBLE_EQ(vr.y(), 7.0);
    EXPECT_DOUBLE_EQ(vr.z(), 9.0);
}

TEST_F(TestVector3, CanNegate)
{
    Vector3<double> v1(1.0, 2.0, 3.0);

    Vector3<double> vr = -v1;

    EXPECT_DOUBLE_EQ(vr.x(), -1.0);
    EXPECT_DOUBLE_EQ(vr.y(), -2.0);
    EXPECT_DOUBLE_EQ(vr.z(), -3.0);
}

TEST_F(TestVector3, CanSubtract)
{
    Vector3<double> v1(4.0, 5.0, 6.0);
    Vector3<double> v2(1.0, 2.0, 3.0);

    Vector3<double> vr = v1 - v2;

    EXPECT_DOUBLE_EQ(vr.x(), 3.0);
    EXPECT_DOUBLE_EQ(vr.y(), 3.0);
    EXPECT_DOUBLE_EQ(vr.z(), 3.0);
}

TEST_F(TestVector3, CanMultiplyByScalar)
{
    Vector3<double> v1(1.0, 2.0, 3.0);

    Vector3<double> vr = v1 * 2.0;

    EXPECT_DOUBLE_EQ(vr.x(), 2.0);
    EXPECT_DOUBLE_EQ(vr.y(), 4.0);
    EXPECT_DOUBLE_EQ(vr.z(), 6.0);
}

TEST_F(TestVector3, CanDivideByScalar)
{
    Vector3<double> v1(1.0, 2.0, 3.0);

    Vector3<double> vr = v1 / 2.0;

    EXPECT_DOUBLE_EQ(vr.x(), 0.5);
    EXPECT_DOUBLE_EQ(vr.y(), 1.0);
    EXPECT_DOUBLE_EQ(vr.z(), 1.5);
}

//TEST_F(TestVector3, CanCalculateVectorCrossProduct)
//{
//    Vector3<double> v1(1.0, 0.0, 0.0);
//    Vector3<double> v2(0.0, 1.0, 0.0);
//    Vector3<double> v3(0.0, 0.0, 1.0);
//    Vector3<double> v4(1.0, 2.0, 3.0);

//    Vector3<double> v41 = v4 % v1;
//    Vector3<double> v42 = v4 % v2;
//    Vector3<double> v43 = v4 % v3;

//    EXPECT_DOUBLE_EQ(v41.x(),  0.0);
//    EXPECT_DOUBLE_EQ(v41.y(),  3.0);
//    EXPECT_DOUBLE_EQ(v41.z(), -2.0);

//    EXPECT_DOUBLE_EQ(v42.x(), -3.0);
//    EXPECT_DOUBLE_EQ(v42.y(),  0.0);
//    EXPECT_DOUBLE_EQ(v42.z(),  1.0);

//    EXPECT_DOUBLE_EQ(v43.x(),  2.0);
//    EXPECT_DOUBLE_EQ(v43.y(), -1.0);
//    EXPECT_DOUBLE_EQ(v43.z(),  0.0);
//}

TEST_F(TestVector3, CanCalculateVectorCrossProductDoubleAndUnits)
{
//    Vector3<length::meter_t> v1(1.0_m, 0.0_m, 0.0_m);
//    Vector3<length::meter_t> v2(0.0_m, 1.0_m, 0.0_m);
//    Vector3<length::meter_t> v3(0.0_m, 0.0_m, 1.0_m);
//    Vector3<double> v4(1.0, 2.0, 3.0);

//    Vector3<length::meter_t> v41 = v4 % v1;
//    Vector3<length::meter_t> v42 = v4 % v2;
//    Vector3<length::meter_t> v43 = v4 % v3;

//    EXPECT_DOUBLE_EQ(v41.x()(),  0.0);
//    EXPECT_DOUBLE_EQ(v41.y()(),  3.0);
//    EXPECT_DOUBLE_EQ(v41.z()(), -2.0);

//    EXPECT_DOUBLE_EQ(v42.x()(), -3.0);
//    EXPECT_DOUBLE_EQ(v42.y()(),  0.0);
//    EXPECT_DOUBLE_EQ(v42.z()(),  1.0);

//    EXPECT_DOUBLE_EQ(v43.x()(),  2.0);
//    EXPECT_DOUBLE_EQ(v43.y()(), -1.0);
//    EXPECT_DOUBLE_EQ(v43.z()(),  0.0);
}

TEST_F(TestVector3, CanCalculateVectorCrossProductUnits)
{
//    length::meter_t r = 1.0_m;
//    force::newton_t f = 1.0_N;
//    torque::newton_meter_t m = r * f;

    Vector3<length::meter_t> r1(1.0_m, 0.0_m, 0.0_m);
    Vector3<length::meter_t> r2(0.0_m, 1.0_m, 0.0_m);
    Vector3<length::meter_t> r3(0.0_m, 0.0_m, 1.0_m);
    Vector3<force::newton_t> f(1.0_N, 2.0_N, 3.0_N);

//    r1 % f;
//    std::cout << typeid(r1 % f).name() << std::endl;

    Vector3<units::unit_t<units::compound_unit<typename units::traits::unit_t_traits<length::meter_t>::unit_type, typename units::traits::unit_t_traits<force::newton_t>::unit_type>>>
            m1 = r1 % f;
//    Vector3<torque::newton_meter_t> m1 = r1 % f;
//    Vector3<torque::newton_meter_t> m2 = r2 % f;
//    Vector3<torque::newton_meter_t> m3 = r3 % f;

//    EXPECT_DOUBLE_EQ(m1.x()(),  0.0);
//    EXPECT_DOUBLE_EQ(m1.y()(),  3.0);
//    EXPECT_DOUBLE_EQ(m1.z()(), -2.0);

//    EXPECT_DOUBLE_EQ(m2.x()(), -3.0);
//    EXPECT_DOUBLE_EQ(m2.y()(),  0.0);
//    EXPECT_DOUBLE_EQ(m2.z()(),  1.0);

//    EXPECT_DOUBLE_EQ(m3.x()(),  2.0);
//    EXPECT_DOUBLE_EQ(m3.y()(), -1.0);
//    EXPECT_DOUBLE_EQ(m3.z()(),  0.0);
}

TEST_F(TestVector3, CanUnaryAdd)
{
    Vector3<double> v1(1.0, 2.0, 3.0);
    Vector3<double> v2(4.0, 5.0, 6.0);

    v1 += v2;

    EXPECT_DOUBLE_EQ(v1.x(), 5.0);
    EXPECT_DOUBLE_EQ(v1.y(), 7.0);
    EXPECT_DOUBLE_EQ(v1.z(), 9.0);
}

TEST_F(TestVector3, CanUnarySubtract)
{
    Vector3<double> v1(4.0, 5.0, 6.0);
    Vector3<double> v2(1.0, 2.0, 3.0);

    v1 -= v2;

    EXPECT_DOUBLE_EQ(v1.x(), 3.0);
    EXPECT_DOUBLE_EQ(v1.y(), 3.0);
    EXPECT_DOUBLE_EQ(v1.z(), 3.0);
}

TEST_F(TestVector3, CanUnaryMultiplyByScalar)
{
    Vector3<double> v1(1.0, 2.0, 3.0);

    v1 *= 2.0;

    EXPECT_DOUBLE_EQ(v1.x(), 2.0);
    EXPECT_DOUBLE_EQ(v1.y(), 4.0);
    EXPECT_DOUBLE_EQ(v1.z(), 6.0);
}

TEST_F(TestVector3, CanUnaryDivideByScalar)
{
    Vector3<double> v1(1.0, 2.0, 3.0);

    v1 /= 2.0;

    EXPECT_DOUBLE_EQ(v1.x(), 0.5);
    EXPECT_DOUBLE_EQ(v1.y(), 1.0);
    EXPECT_DOUBLE_EQ(v1.z(), 1.5);
}
