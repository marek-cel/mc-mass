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

    inline const char* GetName() const { return name_.c_str(); }

    inline PositionVector GetPosition() const { return r_; }

    inline units::mass::kilogram_t GetMass() const { return m_; }

    inline units::length::meter_t GetLength () const { return l_; }
    inline units::length::meter_t GetWidth  () const { return w_; }
    inline units::length::meter_t GetHeight () const { return h_; }

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

    const AircraftData *data_;  ///< aircraft data

    std::string name_;          ///< component name

    PositionVector r_;          ///< position

    units::mass::kilogram_t m_ = 0.0_kg;    ///< [kg] mass

    units::length::meter_t l_ = 0.0_m;      ///< length
    units::length::meter_t w_ = 0.0_m;      ///< width
    units::length::meter_t h_ = 0.0_m;      ///< height

    virtual void SaveParameters(QDomDocument* doc, QDomElement* node);
};

#endif // MC_MASS_MASS_COMPONENT_H_
