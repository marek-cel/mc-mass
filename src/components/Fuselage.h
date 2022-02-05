/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 ******************************************************************************/
#ifndef COMPONENTS_FUSELAGE_H_
#define COMPONENTS_FUSELAGE_H_

////////////////////////////////////////////////////////////////////////////////

#include <components/Component.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief The Fuselage class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407</li>
 *   <li>Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579</li>
 *   <li>Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.231-232</li>
 * </ul>
 */
class Fuselage : public Component
{
public:

    static constexpr char xmlTagName[] { "fuselage" };      ///< component XML tag name

    /**
     * @brief Estimates component mass based on the aircraft parameters.
     * @param[in] data aircraft parameters
     * @return [kg] component statistical mass
     */
    static double estimateMass( const AircraftData &data );

    /**
     * @brief Constructor.
     * @param data aircraft data struct
     */
    Fuselage( const AircraftData *data );

    /**
     * @brief Returns component estimated mass.
     * @return [kg] component estimated mass
     */
    inline double getEstimatedMass() const override
    {
        return estimateMass( *_data );
    }

    /**
     * @brief Returns component XML tag name.
     * @return component XML tag name
     */
    inline const char* getXmlTagName() const override { return xmlTagName; }
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // COMPONENTS_FUSELAGE_H_
