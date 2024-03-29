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

#include <AircraftFile.h>

#include <fstream>

#include <QFileInfo>
#include <QTextStream>

AircraftFile::AircraftFile()
{
    newEmpty();
}

AircraftFile::~AircraftFile() {}

void AircraftFile::newEmpty()
{
    _fileName = "";
    _aircraft.reset();
}

bool AircraftFile::exportAs(const QString& fileName)
{
    std::fstream fs(fileName.toStdString(), std::ios_base::out);

    if ( fs.is_open() )
    {
        fs << _aircraft.toString();

        fs.flush();
        fs.close();

        return true;
    }

    return false;
}

bool AircraftFile::readFile(const QString& fileName)
{
    _fileName = "";
    bool status = false;

    newEmpty();

    QFile devFile(fileName);
    if ( devFile.open(QFile::ReadOnly | QFile::Text) )
    {
        QDomDocument doc;
        doc.setContent(&devFile, false);

        QDomElement rootNode = doc.documentElement();
        if ( rootNode.tagName() == "mc_mass" )
        {
            QDomElement nodeAircraft = rootNode.firstChildElement("aircraft");

            if ( !nodeAircraft.isNull() )
            {
                if ( _aircraft.read(&nodeAircraft) )
                {
                    _fileName = fileName;
                    status = true;
                }
            }
        }

        devFile.close();
    }

    return status;
}

bool AircraftFile::saveFile(const QString& fileName)
{
    _fileName = "";
    QString fileTemp = fileName;

    if ( QFileInfo(fileTemp).suffix() != QString("mcmass") )
    {
        fileTemp += ".mcmass";
    }

    QFile devFile(fileTemp);
    if ( devFile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text) )
    {
        QTextStream out;
        out.setDevice(&devFile);
        out.setCodec("UTF-8");
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

        QDomDocument doc("mc_mass");
        doc.setContent(&devFile, false);

        QDomElement rootNode = doc.createElement("mc_mass");
        doc.appendChild(rootNode);

        QDomElement nodeAircraft = doc.createElement("aircraft");
        rootNode.appendChild(nodeAircraft);

        _aircraft.save(&doc, &nodeAircraft);

        out << doc.toString();

        devFile.close();

        _fileName = fileName;
        return true;
    }

    return false;
}
