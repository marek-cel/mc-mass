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
#ifndef COMPONENTS_COMPONENT_H_
#define COMPONENTS_COMPONENT_H_

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <QDomDocument>
#include <QDomElement>

#include <mcutil/math/Matrix3x3.h>
#include <mcutil/math/Vector3.h>

#include <defs.h>

#include <AircraftData.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

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
    Component( const AircraftData *data );

    /** @brief Destructor. */
    virtual ~Component() = default;

    /**
     * @brief Returns component estimated mass.
     * @return [kg] component estimated mass
     */
    virtual double getEstimatedMass() const = 0;

    /**
     * @brief Reads component data.
     * @param parentNode XML parent node
     */
    void read( QDomElement *parentNode );

    /**
     * @brief Saves component data.
     * @param doc XML document
     * @param parentNode XML parent node
     */
    void save( QDomDocument *doc, QDomElement *parentNode );

    /**
     * @brief Returns component XML tag name.
     * @return component XML tag name
     */
    virtual const char* getXmlTagName() const = 0;

    inline const char* getName() const { return _name.c_str(); }

    inline Vector3 getPosition() const { return _r; }

    inline double getMass   () const { return _m; }
    inline double getLength () const { return _l; }
    inline double getWidth  () const { return _w; }
    inline double getHeight () const { return _h; }

    /**
     * @brief getInertia
     * @return
     */
    Matrix3x3 getInertia() const;

    /**
     * @brief setName
     * @param name
     */
    void setName( const char *name );

    /**
     * @brief setPosition
     * @param r
     */
    void setPosition( const Vector3 &r );

    void setMass   ( double m );
    void setLength ( double l );
    void setWidth  ( double w );
    void setHeight ( double h );

protected:

    const AircraftData *_data;  ///< aircraft data

    std::string _name;          ///< component name

    Vector3 _r;                 ///< [m] position

    double _m;                  ///< [kg] mass

    double _l;                  ///< [m] length
    double _w;                  ///< [m] width
    double _h;                  ///< [m] height

    virtual void saveParameters( QDomDocument *doc, QDomElement *node );
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // COMPONENTS_COMPONENT_H_
