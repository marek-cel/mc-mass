#include <gtest/gtest.h>

#include <mass/AllElse.h>

#include <ExampleData.h>

////////////////////////////////////////////////////////////////////////////////

class TestAllElse : public ::testing::Test
{
protected:
    TestAllElse() {}
    virtual ~TestAllElse() {}
    void SetUp() override {}
    void TearDown() override {}

    mc::AircraftData _data;
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAllElse, CanConstruct)
{
    mc::AllElse *component = nullptr;
    EXPECT_NO_THROW( component = new mc::AllElse( &_data ) );
    delete component;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAllElse, CanDestruct)
{
    mc::AllElse *component = new mc::AllElse( &_data );
    EXPECT_NO_THROW( delete component );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAllElse, CanInstantiate)
{
    mc::AllElse component( &_data );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestAllElse, CanEstimateMass)
{
    double mass = mc::AllElse::estimateMass( ExampleData::getDataGeneralAviation() );
}
