/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
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

#include <components/Component.h>

#include <mcutils/physics/ParallelAxis.h>

#include <DataFile.h>

#include <utils/Cuboid.h>
#include <utils/XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

Component::Component(const AircraftData* data)
    : _data(data)
{
    name_ = "";
}

////////////////////////////////////////////////////////////////////////////////

void Component::read(QDomElement* parentNode)
{
    name_ = parentNode->attributeNode( "name" ).value().toStdString();

    QDomElement nodeMass = parentNode->firstChildElement( "mass" );

    QDomElement nodeX = parentNode->firstChildElement( "pos_x" );
    QDomElement nodeY = parentNode->firstChildElement( "pos_y" );
    QDomElement nodeZ = parentNode->firstChildElement( "pos_z" );

    QDomElement nodeL = parentNode->firstChildElement( "length" );
    QDomElement nodeW = parentNode->firstChildElement( "width"  );
    QDomElement nodeH = parentNode->firstChildElement( "height" );

    if ( !nodeMass.isNull() ) mass_ = mass::kilogram_t(nodeMass.text().toDouble());

    if ( !nodeX.isNull() ) _r.x() = nodeX.text().toDouble();
    if ( !nodeY.isNull() ) _r.y() = nodeY.text().toDouble();
    if ( !nodeZ.isNull() ) _r.z() = nodeZ.text().toDouble();

    if ( !nodeL.isNull() ) _l = nodeL.text().toDouble();
    if ( !nodeW.isNull() ) _w = nodeW.text().toDouble();
    if ( !nodeH.isNull() ) _h = nodeH.text().toDouble();
}

////////////////////////////////////////////////////////////////////////////////

void Component::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( getXmlTagName() );
    parentNode->appendChild( node );
    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

Matrix3x3 Component::getInertia() const
{
    double m = mass_();
    return ParallelAxisInertia(m, Cuboid::getInertia(m, _l, _w, _h), _r);
}

////////////////////////////////////////////////////////////////////////////////

void Component::set_name(const char* name)
{
    name_ = name;
}

////////////////////////////////////////////////////////////////////////////////

void Component::setPosition( const Vector3 &r )
{
    _r = r;
}

////////////////////////////////////////////////////////////////////////////////

void Component::set_mass(mass::kilogram_t mass)
{
    mass_ = mass;
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
    QDomAttr nodeName = doc->createAttribute("name");
    nodeName.setValue(name());
    node->setAttributeNode(nodeName);

    XmlUtils::saveTextNode(doc, node, "mass", mass_());

    XmlUtils::saveTextNode(doc, node, "pos_x", _r.x());
    XmlUtils::saveTextNode(doc, node, "pos_y", _r.y());
    XmlUtils::saveTextNode(doc, node, "pos_z", _r.z());

    XmlUtils::saveTextNode(doc, node, "length" , _l);
    XmlUtils::saveTextNode(doc, node, "width"  , _w);
    XmlUtils::saveTextNode(doc, node, "height" , _h);
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
