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
#ifndef MC_MASS_MASS_ALLELSE_H_
#define MC_MASS_MASS_ALLELSE_H_

#include <mass/Component.h>

/**
 * @brief The AllElse class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407</li>
 *   <li>Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579</li>
 * </ul>
 */
class AllElse : public Component
{
public:

    static constexpr char xmlTagName[] { "all_else" };      ///< component XML tag name

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
    AllElse(const AircraftData* data);

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
};

#endif // MC_MASS_MASS_ALLELSE_H_