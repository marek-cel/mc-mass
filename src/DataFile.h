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
 ******************************************************************************/
#ifndef DATAFILE_H_
#define DATAFILE_H_

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <QDomDocument>
#include <QDomElement>

#include <defs.h>

#include <mcutils/math/Matrix3x3.h>
#include <mcutils/math/Vector3.h>

#include <Aircraft.h>
#include <components/Component.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief The Data file class.
 */
class DataFile
{
public:

    /**
     * @brief Constructor.
     */
    DataFile();

    /**
     * @brief Destructor.
     */
    virtual ~DataFile();

    /** */
    void newEmpty();

    /** */
    bool exportAs( const char *fileName );

    /** */
    bool readFile( const char *fileName );

    /** */
    bool saveFile( const char *fileName );

    inline       Aircraft* getAircraft()       { return &_aircraft; }
    inline const Aircraft* getAircraft() const { return &_aircraft; }

    inline       AircraftData* getAircraftData()       { return _aircraft.getData(); }
    inline const AircraftData* getAircraftData() const { return _aircraft.getData(); }

private:

    Aircraft _aircraft;     ///<
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // DATAFILE_H_
