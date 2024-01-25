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
    bool Read(QDomElement* parentNode);

    /**
     * Saves aircraft data.
     * @param doc
     * @param parentNode
     */
    void Save(QDomDocument* doc, QDomElement* parentNode);

    /**
     * @brief Resets aircraft data. Removes all components.
     */
    void Reset();

    /**
     * @brief Updates output data (total mass, cg position, inertia).
     */
    void Update();

    inline const Components& GetComponents() const { return components_; }

    Component* GetComponent(int index);
    void AddComponent(Component* component);
    void DeleteComponent(int index);

    inline PositionVector GetCenterOfMass() const { return centerOfMass_;  }
    inline InertiaMatrix GetInertiaMatrix() const { return inertiaMatrix_; }
    inline units::mass::kilogram_t GetTotalEmptyMass() const { return totalEmptyMass_; }

    inline       AircraftData* GetData()       { return &data_; }
    inline const AircraftData* GetData() const { return &data_; }

    void SetData(const AircraftData& data);

    /** */
    std::string ToString() const;

private:

    AircraftData data_;             ///< aircraft data

    Components components_;         ///< mass components

    PositionVector centerOfMass_;   ///< [m] center of mass position
    InertiaMatrix inertiaMatrix_;   ///< [kg*m^2] inertia
    units::mass::kilogram_t totalEmptyMass_ = 0.0_kg;    ///< total mass

    void DeleteAllComponents();

    bool ReadData(QDomElement* dataNode);

    bool ReadDataGeneral(QDomElement* parentNode);
    bool ReadDataFuselage(QDomElement* parentNode);
    bool ReadDataWing(QDomElement* parentNode);
    bool ReadDataHorTail(QDomElement* parentNode);
    bool ReadDataVerTail(QDomElement* parentNode);
    bool ReadDataLandingGear(QDomElement* parentNode);
    bool ReadDataEngine(QDomElement* parentNode);
    bool ReadDataRotors(QDomElement* parentNode);
    bool ReadDataModel3D(QDomElement* parentNode);

    bool ReadComponents(QDomElement* componentsNode);

    void SaveDataGeneral(QDomDocument* doc, QDomElement* parentNode);
    void SaveDataFuselage(QDomDocument* doc, QDomElement* parentNode);
    void SaveDataWing(QDomDocument* doc, QDomElement* parentNode);
    void SaveDataHorTail(QDomDocument* doc, QDomElement* parentNode);
    void SaveDataVerTail(QDomDocument* doc, QDomElement* parentNode);
    void SaveDataLandingGear(QDomDocument* doc, QDomElement* parentNode);
    void SaveDataEngine(QDomDocument* doc, QDomElement* parentNode);
    void SaveDataRotors(QDomDocument* doc, QDomElement* parentNode);
    void SaveDataModel3D(QDomDocument* doc, QDomElement* parentNode);

    std::string ToStringMetric() const;
    std::string ToStringImperial() const;
};

#endif // MC_MASS_AIRCRAFT_H_
