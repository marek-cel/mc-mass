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

#include <mass/Component.h>

#include <Document.h>
#include <Xml.h>

#include <mass/Cuboid.h>
#include <mass/Steiner.h>

////////////////////////////////////////////////////////////////////////////////

Component::Component( const Aircraft *ac ) :
    _ac ( ac ),
    _m ( 0.0 ),
    _l ( 0.0 ),
    _w ( 0.0 ),
    _h ( 0.0 )
{
    _name = "";
}

////////////////////////////////////////////////////////////////////////////////

Component::~Component() {}

////////////////////////////////////////////////////////////////////////////////

void Component::read( QDomElement *parentNode )
{
    _name = parentNode->attributeNode( "name" ).value().toStdString();

    QDomElement nodeMass = parentNode->firstChildElement( "mass" );

    QDomElement nodeX = parentNode->firstChildElement( "pos_x" );
    QDomElement nodeY = parentNode->firstChildElement( "pos_y" );
    QDomElement nodeZ = parentNode->firstChildElement( "pos_z" );

    QDomElement nodeL = parentNode->firstChildElement( "length" );
    QDomElement nodeW = parentNode->firstChildElement( "width"  );
    QDomElement nodeH = parentNode->firstChildElement( "height" );

    if ( !nodeMass.isNull() ) _m = nodeMass.text().toDouble();

    if ( !nodeX.isNull() ) _r.x() = nodeX.text().toDouble();
    if ( !nodeY.isNull() ) _r.y() = nodeY.text().toDouble();
    if ( !nodeZ.isNull() ) _r.z() = nodeZ.text().toDouble();

    if ( !nodeL.isNull() ) _l = nodeL.text().toDouble();
    if ( !nodeW.isNull() ) _w = nodeW.text().toDouble();
    if ( !nodeH.isNull() ) _h = nodeH.text().toDouble();
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Component::getInertia() const
{
    return Steiner::getInertia( _m, Cuboid::getInertia( _m, _l, _w, _h ), _r );
}

////////////////////////////////////////////////////////////////////////////////

void Component::setName( const char *name )
{
    _name = name;
}

////////////////////////////////////////////////////////////////////////////////

void Component::setPosition( const Vector3 &r )
{
    _r = r;
}

////////////////////////////////////////////////////////////////////////////////

void Component::setMass( double m )
{
    _m = m;
}

////////////////////////////////////////////////////////////////////////////////

void Component::setLength( double l )
{
    _l = l;
}

////////////////////////////////////////////////////////////////////////////////

void Component::setWidth( double w )
{
    _w = w;
}

////////////////////////////////////////////////////////////////////////////////

void Component::setHeight( double h )
{
    _h = h;
}

////////////////////////////////////////////////////////////////////////////////

void Component::saveParameters( QDomDocument *doc, QDomElement *node )
{
    QDomAttr nodeName = doc->createAttribute( "name" );
    nodeName.setValue( getName() );
    node->setAttributeNode( nodeName );

    Xml::saveTextNode( doc, node, "mass", _m );

    Xml::saveTextNode( doc, node, "pos_x", _r.x() );
    Xml::saveTextNode( doc, node, "pos_y", _r.y() );
    Xml::saveTextNode( doc, node, "pos_z", _r.z() );

    Xml::saveTextNode( doc, node, "length" , _l );
    Xml::saveTextNode( doc, node, "width"  , _w );
    Xml::saveTextNode( doc, node, "height" , _h );
}
