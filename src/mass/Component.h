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
#ifndef COMPONENT_H
#define COMPONENT_H

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <QDomDocument>
#include <QDomElement>

#include <defs.h>
#include <Types.h>

#include <mass/Aircraft.h>
#include <mass/Matrix3x3.h>
#include <mass/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The Component class.
 */
class Component
{
public:

    /**
     * @brief Constructor.
     * @param aircraft
     */
    Component( const Aircraft *ac );

    /** @brief Destructor. */
    virtual ~Component();

    virtual void read( QDomElement *parentNode );

    virtual void save( QDomDocument *doc, QDomElement *parentNode ) = 0;

    virtual double getComputedMass() const = 0;

    inline const Aircraft* getAircraft() const { return _ac; }

    inline const char* getName() const { return _name.c_str(); }

    inline Vector3 getPosition() const { return _r; }

    inline double getMass   () const { return _m; }
    inline double getLength () const { return _l; }
    inline double getWidth  () const { return _w; }
    inline double getHeight () const { return _h; }

    Matrix3x3 getInertia() const;

    void setName( const char *name );

    void setPosition( const Vector3 &r );

    void setMass   ( double m );
    void setLength ( double l );
    void setWidth  ( double w );
    void setHeight ( double h );

protected:

    const Aircraft *_ac;    ///< aircraft

    std::string _name;      ///< component name

    Vector3 _r;             ///< [m] position

    double _m;              ///< [kg] mass

    double _l;              ///< [m] length
    double _w;              ///< [m] width
    double _h;              ///< [m] height

    virtual void saveParameters( QDomDocument *doc, QDomElement *node );
};

////////////////////////////////////////////////////////////////////////////////

#endif // COMPONENT_H
