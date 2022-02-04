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
#ifndef COMPONENTS_ROTORHUB_H_
#define COMPONENTS_ROTORHUB_H_

////////////////////////////////////////////////////////////////////////////////

#include <components/Component.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief The RotorHub class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Johnson W.: NDARC NASA Design and Analysis of Rotorcraft, NASA TP-2015-218751, 2015, p.228-229</li>
 * </ul>
 */
class RotorHub : public Component
{
public:

    static constexpr char xmlTagName[] { "rotor_hub" };     ///< component XML tag name

    /**
     * @brief Estimates component mass based on the aircraft parameters.
     * @param[in] data aircraft parameters
     * @return [kg] component statistical mass
     */
    static double estimateMass( const AircraftData *data );

    /**
     * @brief Constructor.
     * @param data aircraft data struct
     */
    RotorHub( const AircraftData *data );

    /**
     * @brief Returns component estimated mass.
     * @return [kg] component estimated mass
     */
    inline double getEstimatedMass() const override
    {
        return estimateMass( _data );
    }

    /**
     * @brief Returns component XML tag name.
     * @return component XML tag name
     */
    inline const char* getXmlTagName() const override { return xmlTagName; }
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // COMPONENTS_ROTORHUB_H_
