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
#ifndef MC_MASS_MASS_ROTORMAIN_H_
#define MC_MASS_MASS_ROTORMAIN_H_

#include <mass/Component.h>

/**
 * @brief The RotorMain class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.228-229</li>
 * </ul>
 */
class RotorMain : public Component
{
public:

    static constexpr char xmlTagName[] { "rotor_main" };    ///< component XML tag name

    /**
     * @brief Estimates component mass based on the aircraft parameters.
     * @param[in] data aircraft parameters
     * @return [kg] component statistical mass
     */
    static units::mass::kilogram_t GetEstimatedMass(const AircraftData& data);

    /**
     * @brief Constructor.
     * @param data aircraft data struct
     */
    RotorMain( const AircraftData *data );

    /**
     * @brief Returns component estimated mass.
     * @return [kg] component estimated mass
     */
    inline units::mass::kilogram_t GetEstimatedMass() const override
    {
        return GetEstimatedMass(*data_);
    }

    /**
     * @brief Returns component XML tag name.
     * @return component XML tag name
     */
    inline const char* GetXmlTagName() const override { return xmlTagName; }

    InertiaMatrix GetInertia() const override;
};

#endif // MC_MASS_MASS_ROTORMAIN_H_