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

#include <DataFile.h>

#include <fstream>

#include <QFileInfo>
#include <QTextStream>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

DataFile::DataFile()
{
    newEmpty();
}

////////////////////////////////////////////////////////////////////////////////

DataFile::~DataFile() {}

////////////////////////////////////////////////////////////////////////////////

void DataFile::newEmpty()
{
    _aircraft.reset();
}

////////////////////////////////////////////////////////////////////////////////

bool DataFile::exportAs( const char *fileName )
{
    std::fstream fs( fileName, std::ios_base::out );

    if ( fs.is_open() )
    {
        fs << _aircraft.toString();

        fs.flush();
        fs.close();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool DataFile::readFile( const char *fileName )
{
    bool status = false;

    newEmpty();

    QFile devFile( fileName );

    if ( devFile.open( QFile::ReadOnly | QFile::Text ) )
    {
        QDomDocument doc;

        doc.setContent( &devFile, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "mscsim_mass" )
        {
            QDomElement nodeAircraft = rootNode.firstChildElement( "aircraft" );

            if ( !nodeAircraft.isNull() )
            {
                if ( _aircraft.read( &nodeAircraft ) )
                {
                    status = true;
                }
            }
        }

        devFile.close();
    }

    return status;
}

////////////////////////////////////////////////////////////////////////////////

bool DataFile::saveFile( const char *fileName )
{
    QString fileTemp = fileName;

    if ( QFileInfo( fileTemp ).suffix() != QString( "xml" ) )
    {
        fileTemp += ".xml";
    }

    QFile devFile( fileTemp );

    if ( devFile.open( QFile::WriteOnly | QFile::Truncate | QFile::Text ) )
    {
        QTextStream out;
        out.setDevice( &devFile );
        out.setCodec("UTF-8");
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

        QDomDocument doc( "mscsim_mass" );

        doc.setContent( &devFile, false );

        QDomElement rootNode = doc.createElement( "mscsim_mass" );
        doc.appendChild( rootNode );

        QDomElement nodeAircraft = doc.createElement( "aircraft" );
        rootNode.appendChild( nodeAircraft );

        _aircraft.save( &doc, &nodeAircraft );

        out << doc.toString();

        devFile.close();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
