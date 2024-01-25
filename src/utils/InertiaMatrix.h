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
#ifndef MC_MASS_UTILS_INERTIAMATRIX_H_
#define MC_MASS_UTILS_INERTIAMATRIX_H_

#include <utils/units_extra.h>

using namespace units::literals;

class InertiaMatrix
{
public:

    inline units::moment_of_inertia::kilogram_square_meter_t ixx() const { return ixx_; }
    inline units::moment_of_inertia::kilogram_square_meter_t ixy() const { return ixy_; }
    inline units::moment_of_inertia::kilogram_square_meter_t ixz() const { return ixz_; }
    inline units::moment_of_inertia::kilogram_square_meter_t iyx() const { return iyx_; }
    inline units::moment_of_inertia::kilogram_square_meter_t iyy() const { return iyy_; }
    inline units::moment_of_inertia::kilogram_square_meter_t iyz() const { return iyz_; }
    inline units::moment_of_inertia::kilogram_square_meter_t izx() const { return izx_; }
    inline units::moment_of_inertia::kilogram_square_meter_t izy() const { return izy_; }
    inline units::moment_of_inertia::kilogram_square_meter_t izz() const { return izz_; }

    inline units::moment_of_inertia::kilogram_square_meter_t& ixx() { return ixx_; }
    inline units::moment_of_inertia::kilogram_square_meter_t& ixy() { return ixy_; }
    inline units::moment_of_inertia::kilogram_square_meter_t& ixz() { return ixz_; }
    inline units::moment_of_inertia::kilogram_square_meter_t& iyx() { return iyx_; }
    inline units::moment_of_inertia::kilogram_square_meter_t& iyy() { return iyy_; }
    inline units::moment_of_inertia::kilogram_square_meter_t& iyz() { return iyz_; }
    inline units::moment_of_inertia::kilogram_square_meter_t& izx() { return izx_; }
    inline units::moment_of_inertia::kilogram_square_meter_t& izy() { return izy_; }
    inline units::moment_of_inertia::kilogram_square_meter_t& izz() { return izz_; }

    InertiaMatrix operator+(const InertiaMatrix& matrix) const;
    InertiaMatrix& operator+=(const InertiaMatrix& matrix);

private:

    units::moment_of_inertia::kilogram_square_meter_t ixx_ = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t ixy_ = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t ixz_ = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t iyx_ = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t iyy_ = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t iyz_ = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t izx_ = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t izy_ = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t izz_ = 0.0_kg_m2;
};

#endif // MC_MASS_UTILS_INERTIAMATRIX_H_
