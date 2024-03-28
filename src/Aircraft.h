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
#ifndef MC_MASS_AIRCRAFT_H_
#define MC_MASS_AIRCRAFT_H_

#include <vector>

#include <QDomDocument>
#include <QDomElement>

#include <defs.h>
#include <AircraftData.h>

#include <mass/Component.h>

/**
 * @brief The Aircraft class.
 */
class Aircraft
{
public:

    typedef std::vector<Component*> Components;

    Aircraft();
    virtual ~Aircraft();

    /**
     * @brief read
     * @param parentNode
     * @return returns true on success and false on failure
     */
    bool read(QDomElement* parentNode);

    /**
     * Saves aircraft data.
     * @param doc
     * @param parentNode
     */
    void save(QDomDocument* doc, QDomElement* parentNode);

    /**
     * @brief Resets aircraft data. Removes all components.
     */
    void reset();

    /**
     * @brief Updates output data (total mass, cg position, inertia).
     */
    void update();

    inline const Components& getComponents() const { return _components;}
_
    Component* getComponent(int index);
    void addComponent(Component* component);
    void deleteComponent(int index);

    inline PositionVector getCenterOfMass() const { return _centerOfMass;  }
    inline InertiaMatrix getInertiaMatrix() const { return _inertiaMatrix; }
    inline units::mass::kilogram_t getTotalEmptyMass() const { return _totalEmptyMass; }

    inline       AircraftData* getData()       { return &_data; }
    inline const AircraftData* getData() const { return &_data; }

    void setData(const AircraftData& data);

    std::string toString() const;

private:

    AircraftData _data;             ///< aircraft data

    Components _components;         ///< mass components

    PositionVector _centerOfMass;   ///< [m] center of mass position
    InertiaMatrix _inertiaMatrix;   ///< [kg*m^2] inertia
    units::mass::kilogram_t _totalEmptyMass = 0.0_kg;    ///< total mass

    bool _verbose = false;

    void deleteAllComponents();

    bool readData(QDomElement* dataNode);

    bool readDataGeneral(QDomElement* parentNode);
    bool readDataFuselage(QDomElement* parentNode);
    bool readDataWing(QDomElement* parentNode);
    bool readDataHorTail(QDomElement* parentNode);
    bool readDataVerTail(QDomElement* parentNode);
    bool readDataLandingGear(QDomElement* parentNode);
    bool readDataEngine(QDomElement* parentNode);
    bool readDataRotors(QDomElement* parentNode);
    bool readDataModel3D(QDomElement* parentNode);

    bool readComponents(QDomElement* componentsNode);

    void saveDataGeneral(QDomDocument* doc, QDomElement* parentNode);
    void saveDataFuselage(QDomDocument* doc, QDomElement* parentNode);
    void saveDataWing(QDomDocument* doc, QDomElement* parentNode);
    void saveDataHorTail(QDomDocument* doc, QDomElement* parentNode);
    void saveDataVerTail(QDomDocument* doc, QDomElement* parentNode);
    void saveDataLandingGear(QDomDocument* doc, QDomElement* parentNode);
    void saveDataEngine(QDomDocument* doc, QDomElement* parentNode);
    void saveDataRotors(QDomDocument* doc, QDomElement* parentNode);
    void saveDataModel3D(QDomDocument* doc, QDomElement* parentNode);

    std::string toStringMetric() const;
    std::string toStringImperial() const;
};

#endif // MC_MASS_AIRCRAFT_H_
