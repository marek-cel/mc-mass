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
#ifndef MC_MASS_UTILS_POSITIONVECTOR_H_
#define MC_MASS_UTILS_POSITIONVECTOR_H_

#include <units.h>

#include <utils/FirstMomentOfMass.h>

using namespace units::literals;

class PositionVector
{
public:

    units::length::meter_t x() const { return x_; }
    units::length::meter_t y() const { return y_; }
    units::length::meter_t z() const { return z_; }

    inline units::length::meter_t& x() { return x_; }
    inline units::length::meter_t& y() { return y_; }
    inline units::length::meter_t& z() { return z_; }

    FirstMomentOfMass operator*(units::mass::kilogram_t m) const;

private:

    units::length::meter_t x_ = 0.0_m;
    units::length::meter_t y_ = 0.0_m;
    units::length::meter_t z_ = 0.0_m;
};

inline FirstMomentOfMass operator*(units::mass::kilogram_t m, const PositionVector& pos)
{
    return (pos * m);
}

#endif // MC_MASS_UTILS_INERTIAMATRIX_H_
