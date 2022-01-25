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
#ifndef XML_H
#define XML_H

////////////////////////////////////////////////////////////////////////////////

#include <QDomDocument>
#include <QDomElement>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The Xml class.
 */
class Xml
{
public:

    static void saveTextNode( QDomDocument *doc, QDomElement *parent,
                              const char *tag_name, const QString &text );

    static void saveTextNode( QDomDocument *doc, QDomElement *parent,
                              const char *tag_name, double value );

    static void saveTextNode( QDomDocument *doc, QDomElement *parent,
                              const char *tag_name, int value );

    static void saveTextNode( QDomDocument *doc, QDomElement *parent,
                              const char *tag_name, bool value );
};

////////////////////////////////////////////////////////////////////////////////

#endif // XML_H
