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
#ifndef MC_MASS_MASS_COMPONENT_H_
#define MC_MASS_MASS_COMPONENT_H_

#include <string>

#include <units.h>

#include <QDomDocument>
#include <QDomElement>

#include <utils/InertiaMatrix.h>
#include <utils/PositionVector.h>

#include <defs.h>

#include <AircraftData.h>

using namespace units::literals;

/**
 * @brief The Component class.
 */
class Component
{
public:

    static units::mass::kilogram_t GetDesignGrossWeight(const AircraftData& data);

    /**
     * @brief Constructor.
     * @param data aircraft data struct
     */
    Component(const AircraftData* data);

    /** @brief Destructor. */
    virtual ~Component() = default;

    /**
     * @brief Returns component estimated mass.
     * @return component estimated mass
     */
    virtual units::mass::kilogram_t GetEstimatedMass() const = 0;

    /**
     * @brief Reads component data.
     * @param parentNode XML parent node
     */
    void Read(QDomElement* parentNode);

    /**
     * @brief Saves component data.
     * @param doc XML document
     * @param parentNode XML parent node
     */
    void Save(QDomDocument* doc, QDomElement* parentNode);

    /**
     * @brief Returns component XML tag name.
     * @return component XML tag name
     */
    virtual const char* GetXmlTagName() const = 0;

    inline const char* GetName() const { return _name.c_str(); }

    inline PositionVector GetPosition() const { return _r; }

    inline units::mass::kilogram_t GetMass() const { return _m; }

    inline units::length::meter_t GetLength () const { return _l; }
    inline units::length::meter_t GetWidth  () const { return _w; }
    inline units::length::meter_t GetHeight () const { return _h; }

    /**
     * @brief getInertia
     * @return
     */
    virtual InertiaMatrix GetInertia() const;

    /**
     * @brief setName
     * @param name
     */
    void SetName(const char* name);

    /**
     * @brief setPosition
     * @param r
     */
    void SetPosition(const PositionVector& r);

    void SetMass(units::mass::kilogram_t m);
    void SetLength(units::length::meter_t l);
    void SetWidth(units::length::meter_t w);
    void SetHeight(units::length::meter_t h);

protected:

    const AircraftData* _data;  ///< aircraft data

    std::string _name;          ///< component name

    PositionVector _r;          ///< position

    units::mass::kilogram_t _m = 0.0_kg;    ///< [kg] mass

    units::length::meter_t _l = 0.0_m;      ///< length
    units::length::meter_t _w = 0.0_m;      ///< width
    units::length::meter_t _h = 0.0_m;      ///< height

    virtual void SaveParameters(QDomDocument* doc, QDomElement* node);
};

#endif // MC_MASS_MASS_COMPONENT_H_
