/****************************************************************************//*
 *  Copyright (C) 2024 Marek M. Cel
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
#ifndef MC_MASS_UTILS_FIRSTMOMENTOFMASS_H_
#define MC_MASS_UTILS_FIRSTMOMENTOFMASS_H_

#include <utils/units_extra.h>

using namespace units::literals;

class FirstMomentOfMass
{
public:

    units::first_moment_of_mass::kilogram_meter_t sx() const { return sx_; }
    units::first_moment_of_mass::kilogram_meter_t sy() const { return sy_; }
    units::first_moment_of_mass::kilogram_meter_t sz() const { return sz_; }

    inline units::first_moment_of_mass::kilogram_meter_t& sx() { return sx_; }
    inline units::first_moment_of_mass::kilogram_meter_t& sy() { return sy_; }
    inline units::first_moment_of_mass::kilogram_meter_t& sz() { return sz_; }

    FirstMomentOfMass operator+(const FirstMomentOfMass& vect) const;
    FirstMomentOfMass& operator+=(const FirstMomentOfMass& vect);

    class PositionVector operator/(units::mass::kilogram_t m) const;

private:

    units::first_moment_of_mass::kilogram_meter_t sx_ = 0.0_kg_m;
    units::first_moment_of_mass::kilogram_meter_t sy_ = 0.0_kg_m;
    units::first_moment_of_mass::kilogram_meter_t sz_ = 0.0_kg_m;
};

#endif // MC_MASS_UTILS_FIRSTMOMENTOFMASS_H_
