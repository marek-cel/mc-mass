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

#include <iostream>

#include <utils/Atmosphere.h>
#include <utils/Check.h>

#include <CsvFileReader.h>


class TestAtmosphere : public ::testing::Test
{
protected:

    TestAtmosphere() {}
    virtual ~TestAtmosphere() {}

    void SetUp() override {}
    void TearDown() override {}
};


TEST_F(TestAtmosphere, CanInstantiate)
{
    Atmosphere atm;
}


TEST_F(TestAtmosphere, CanCalculate)
{
    std::vector<double> h_ref;
    std::vector<double> t_ref;
    std::vector<double> p_ref;
    std::vector<double> rho_ref;
    std::vector<double> a_ref;
    std::vector<double> mu_ref;

    // expected values from https://www.digitaldutch.com/atmoscalc/table.htm
    ReadCsvDataFromFile("../tests/utils/data/test_env_ussa1976.csv",
                        &h_ref, &t_ref, &p_ref, &rho_ref, &a_ref, &mu_ref);

    EXPECT_GT(h_ref   .size(), 0) << "No reference data.";
    EXPECT_GT(t_ref   .size(), 0) << "No reference data.";
    EXPECT_GT(p_ref   .size(), 0) << "No reference data.";
    EXPECT_GT(rho_ref .size(), 0) << "No reference data.";
    EXPECT_GT(a_ref   .size(), 0) << "No reference data.";
    EXPECT_GT(mu_ref  .size(), 0) << "No reference data.";

    EXPECT_EQ(h_ref.size(), t_ref   .size()) << "Reference data corrupted.";
    EXPECT_EQ(h_ref.size(), p_ref   .size()) << "Reference data corrupted.";
    EXPECT_EQ(h_ref.size(), rho_ref .size()) << "Reference data corrupted.";
    EXPECT_EQ(h_ref.size(), a_ref   .size()) << "Reference data corrupted.";
    EXPECT_EQ(h_ref.size(), mu_ref  .size()) << "Reference data corrupted.";

    Atmosphere atm;

    if ( h_ref.size() == 0 )
    {
        EXPECT_TRUE(false) << "No reference data.";
    }

    for ( unsigned int i = 0; i < h_ref.size(); i++ )
    {
        double h = h_ref.at(i);

        atm.update(h);

        double t   = atm.getTemperature();
        double p   = atm.getPressure();
        double rho = atm.getDensity();
        double a   = atm.getSpeedOfSound();
        double mu  = atm.getDynViscosity();

        double tol_t   = 0.01 * t_ref   .at(i);
        double tol_p   = 0.01 * p_ref   .at(i);
        double tol_rho = 0.01 * rho_ref .at(i);
        double tol_a   = 0.01 * a_ref   .at(i);
        double tol_mu  = 0.1  * mu_ref  .at(i);

        EXPECT_NEAR( t   , t_ref   .at(i), tol_t   ) << "Mismatch at altitude= " << h;
        EXPECT_NEAR( p   , p_ref   .at(i), tol_p   ) << "Mismatch at altitude= " << h;
        EXPECT_NEAR( rho , rho_ref .at(i), tol_rho ) << "Mismatch at altitude= " << h;
        EXPECT_NEAR( a   , a_ref   .at(i), tol_a   ) << "Mismatch at altitude= " << h;
        EXPECT_NEAR( mu  , mu_ref  .at(i), tol_mu  ) << "Mismatch at altitude= " << h;
    }
}


TEST_F(TestAtmosphere, CanCalculateOutOfRange)
{
    Atmosphere atm;
    atm.update(1.0e7);

    double t   = atm.getTemperature();
    double p   = atm.getPressure();
    double rho = atm.getDensity();
    double a   = atm.getSpeedOfSound();
    double mu  = atm.getDynViscosity();

    EXPECT_TRUE(isValid(t));
    EXPECT_TRUE(isValid(p));
    EXPECT_TRUE(isValid(rho));
    EXPECT_TRUE(isValid(a));
    EXPECT_TRUE(isValid(mu));
}
