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
#ifndef MC_MASS_AIRCRAFTFILE_H_
#define MC_MASS_AIRCRAFTFILE_H_

#include <vector>

#include <QDomDocument>
#include <QDomElement>

#include <defs.h>

#include <Aircraft.h>
#include <mass/Component.h>

/**
 * @brief The Aircraft file class.
 */
class AircraftFile
{
public:

    AircraftFile();
    virtual ~AircraftFile();

    void newEmpty();
    bool exportAs(const QString& fileName);
    bool readFile(const QString& fileName);
    bool saveFile(const QString& fileName);

    inline QString getFile() const { return _fileName; }

    inline       Aircraft* getAircraft()       { return &_aircraft; }
    inline const Aircraft* getAircraft() const { return &_aircraft; }

    inline       AircraftData* getAircraftData()       { return _aircraft.getData(); }
    inline const AircraftData* getAircraftData() const { return _aircraft.getData(); }

private:

    Aircraft _aircraft;
    QString _fileName;
};

#endif // MC_MASS_AIRCRAFTFILE_H_
