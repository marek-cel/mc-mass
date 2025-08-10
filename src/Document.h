/****************************************************************************//*
 *  Copyright (C) 2025 Marek M. Cel
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
#ifndef MC_MASS_DOCUMENT_H_
#define MC_MASS_DOCUMENT_H_

#include <filesystem>
#include <memory>
#include <string>

#include <utils/XmlDoc.h>

#include <Result.h>
#include <Vehicle.h>

class Document
{
public:

    Result readFile(const std::filesystem::path& path);
    Result saveFile(const std::filesystem::path& path);

    std::string getName() const { return _name; }

    inline std::filesystem::path getPath() const { return _path; }
    std::weak_ptr<Vehicle> getVehicle() { return _vehicle; }

private:

    std::string _name = "Untitled"; ///< name of the document
    std::filesystem::path _path;    ///< path to the document
    std::shared_ptr<Vehicle> _vehicle = std::make_shared<Vehicle>(); ///< vehicle data

    Result readDocument(XmlDoc& doc);
    Result readVehicleData(XmlNode& node);
    Result readVehicleDataGeneral(XmlNode& node);
    Result readVehicleDataFuselage(XmlNode& node);
    Result readVehicleDataWing(XmlNode& node);
    Result readVehicleDataHorTail(XmlNode& node);
    Result readVehicleDataVerTail(XmlNode& node);
    Result readVehicleDataLandingGear(XmlNode& node);
    Result readVehicleDataEngines(XmlNode& node);
    Result readVehicleDataRotors(XmlNode& node);

    Result saveDocument(XmlDoc& doc);
    Result saveVehicleData(XmlNode& node);
    Result saveVehicleDataGeneral(XmlNode& node);
    Result saveVehicleDataFuselage(XmlNode& node);
    Result saveVehicleDataWing(XmlNode& node);
    Result saveVehicleDataHorTail(XmlNode& node);
    Result saveVehicleDataVerTail(XmlNode& node);
    Result saveVehicleDataLandingGear(XmlNode& node);
    Result saveVehicleDataEngines(XmlNode& node);
    Result saveVehicleDataRotors(XmlNode& node);
};

#endif // MC_MASS_DOCUMENT_H_


