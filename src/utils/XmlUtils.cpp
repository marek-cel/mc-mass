/****************************************************************************//*
 * Copyright (C) 2022 Marek M. Cel
 *
 * This file is part of MC-Mass.
 *
 * MC-Mass is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MC-Mass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <utils/XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

void XmlUtils::saveTextNode( QDomDocument *doc, QDomElement *parent,
                             const char *tag_name, const QString &text )
{
    QDomElement node = doc->createElement( tag_name );
    parent->appendChild( node );

    QDomNode textNode = doc->createTextNode( text );
    node.appendChild( textNode );
}

////////////////////////////////////////////////////////////////////////////////

void XmlUtils::saveTextNode( QDomDocument *doc, QDomElement *parent,
                             const char *tag_name, double value )
{
    saveTextNode( doc, parent, tag_name, QString::number( value, 'f', 6 ) );
}

////////////////////////////////////////////////////////////////////////////////

void XmlUtils::saveTextNode( QDomDocument *doc, QDomElement *parent,
                             const char *tag_name, int value )
{
    saveTextNode( doc, parent, tag_name, QString::number( value ) );
}

////////////////////////////////////////////////////////////////////////////////

void XmlUtils::saveTextNode( QDomDocument *doc, QDomElement *parent,
                             const char *tag_name, bool value )
{
    saveTextNode( doc, parent, tag_name, QString( value ? "1" : "0" ) );
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
