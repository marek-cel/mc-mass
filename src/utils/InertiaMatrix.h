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

    inline units::moment_of_inertia::kilogram_square_meter_t ixx() const { return _ixx; }
    inline units::moment_of_inertia::kilogram_square_meter_t ixy() const { return _ixy; }
    inline units::moment_of_inertia::kilogram_square_meter_t ixz() const { return _ixz; }
    inline units::moment_of_inertia::kilogram_square_meter_t iyx() const { return _iyx; }
    inline units::moment_of_inertia::kilogram_square_meter_t iyy() const { return _iyy; }
    inline units::moment_of_inertia::kilogram_square_meter_t iyz() const { return _iyz; }
    inline units::moment_of_inertia::kilogram_square_meter_t izx() const { return _izx; }
    inline units::moment_of_inertia::kilogram_square_meter_t izy() const { return _izy; }
    inline units::moment_of_inertia::kilogram_square_meter_t izz() const { return _izz; }

    inline units::moment_of_inertia::kilogram_square_meter_t& ixx() { return _ixx; }
    inline units::moment_of_inertia::kilogram_square_meter_t& ixy() { return _ixy; }
    inline units::moment_of_inertia::kilogram_square_meter_t& ixz() { return _ixz; }
    inline units::moment_of_inertia::kilogram_square_meter_t& iyx() { return _iyx; }
    inline units::moment_of_inertia::kilogram_square_meter_t& iyy() { return _iyy; }
    inline units::moment_of_inertia::kilogram_square_meter_t& iyz() { return _iyz; }
    inline units::moment_of_inertia::kilogram_square_meter_t& izx() { return _izx; }
    inline units::moment_of_inertia::kilogram_square_meter_t& izy() { return _izy; }
    inline units::moment_of_inertia::kilogram_square_meter_t& izz() { return _izz; }

    InertiaMatrix operator+(const InertiaMatrix& matrix) const;
    InertiaMatrix& operator+=(const InertiaMatrix& matrix);

private:

    units::moment_of_inertia::kilogram_square_meter_t _ixx = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t _ixy = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t _ixz = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t _iyx = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t _iyy = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t _iyz = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t _izx = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t _izy = 0.0_kg_m2;
    units::moment_of_inertia::kilogram_square_meter_t _izz = 0.0_kg_m2;
};

#endif // MC_MASS_UTILS_INERTIAMATRIX_H_
