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
#ifndef COMPONENTS_GEARNOSE_H_
#define COMPONENTS_GEARNOSE_H_

////////////////////////////////////////////////////////////////////////////////

#include <components/Component.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief The GearNose class.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li>Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 1992, p.398-407</li>
 *   <li>Raymer D. P.: Aircraft Design: A Conceptual Approach, AIAA, 2018, p.568-579</li>
 * </ul>
 */
class GearNose : public Component
{
public:

    static constexpr char xmlTagName[] { "gear_nose" };

    GearNose( const AircraftData *data );

    double getStatisticalMass() const override;

    inline const char* getXmlTagName() const override { return xmlTagName; }
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // COMPONENTS_GEARNOSE_H_
