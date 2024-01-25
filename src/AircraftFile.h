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

    /**
     * @brief Constructor.
     */
    AircraftFile();

    /**
     * @brief Destructor.
     */
    virtual ~AircraftFile();

    /** */
    void NewEmpty();

    /** */
    bool ExportAs(const QString& fileName);

    /** */
    bool ReadFile(const QString& fileName);

    /** */
    bool SaveFile(const QString& fileName);

    inline QString GetFile() const { return fileName_; }

    inline       Aircraft* GetAircraft()       { return &aircraft_; }
    inline const Aircraft* GetAircraft() const { return &aircraft_; }

    inline       AircraftData* GetAircraftData()       { return aircraft_.GetData(); }
    inline const AircraftData* GetAircraftData() const { return aircraft_.GetData(); }

private:

    Aircraft aircraft_;     ///<

    QString fileName_;
};

#endif // MC_MASS_AIRCRAFTFILE_H_
