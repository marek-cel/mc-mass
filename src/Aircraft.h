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
#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <QDomDocument>
#include <QDomElement>

#include <mcutil/math/Matrix3x3.h>
#include <mcutil/math/Vector3.h>

#include <defs.h>
#include <AircraftData.h>

#include <components/Component.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief The Aircraft class.
 */
class Aircraft
{
public:

    typedef std::vector< Component* > Components;

    Aircraft();

    virtual ~Aircraft();

    /**
     * @brief read
     * @param parentNode
     * @return returns true on success and false on failure
     */
    bool read( QDomElement *parentNode );

    /**
     * Saves aircraft data.
     * @param doc
     * @param parentNode
     */
    void save( QDomDocument *doc, QDomElement *parentNode );

    /**
     * @brief Resets aircraft data. Removes all components.
     */
    void reset();

    /**
     * @brief Updates output data (total mass, cg position, inertia).
     */
    void update();

    inline const Components& getComponents() const { return _components; }

    Component* getComponent( int index );
    void addComponent( Component *component );
    void delComponent( int index );

    inline Vector3   getCenterOfMass  () const { return _centerOfMass;  }
    inline Matrix3x3 getInertiaMatrix () const { return _inertiaMatrix; }
    inline double    getMassTotal     () const { return _massTotal;     }

    inline       AircraftData* getData()       { return &_data; }
    inline const AircraftData* getData() const { return &_data; }

    void setData( const AircraftData &data );

    /** */
    std::string toString() const;

private:

    AircraftData _data;         ///< aircraft data

    Components _components;     ///< mass components

    Vector3   _centerOfMass;    ///< [m] center of mass position
    Matrix3x3 _inertiaMatrix;   ///< [kg*m^2] inertia
    double _massTotal;          ///< [kg]


    void deleteAllComponents();

    bool readData( QDomElement *dataNode );

    bool readDataGeneral     ( QDomElement *parentNode );
    bool readDataFuselage    ( QDomElement *parentNode );
    bool readDataWing        ( QDomElement *parentNode );
    bool readDataHorTail     ( QDomElement *parentNode );
    bool readDataVerTail     ( QDomElement *parentNode );
    bool readDataLandingGear ( QDomElement *parentNode );
    bool readDataEngine      ( QDomElement *parentNode );
    bool readDataRotors      ( QDomElement *parentNode );

    bool readComponents( QDomElement *componentsNode );

    void saveDataGeneral     ( QDomDocument *doc, QDomElement *parentNode );
    void saveDataFuselage    ( QDomDocument *doc, QDomElement *parentNode );
    void saveDataWing        ( QDomDocument *doc, QDomElement *parentNode );
    void saveDataHorTail     ( QDomDocument *doc, QDomElement *parentNode );
    void saveDataVerTail     ( QDomDocument *doc, QDomElement *parentNode );
    void saveDataLandingGear ( QDomDocument *doc, QDomElement *parentNode );
    void saveDataEngine      ( QDomDocument *doc, QDomElement *parentNode );
    void saveDataRotors      ( QDomDocument *doc, QDomElement *parentNode );
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // AIRCRAFT_H_
