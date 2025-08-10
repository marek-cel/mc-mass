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

#include <mass/Component.h>

#include <AircraftFile.h>

#include <utils/Cuboid.h>
#include <utils/XmlUtils.h>

units::mass::kilogram_t Component::GetDesignGrossWeight(const AircraftData& data)
{
    // Rayner2018: Aircraft Design, p.565,p.570
    if ( data.type == AircraftData::FighterAttack )
    {
        return data.general.mtow - 0.5 * data.general.m_maxFuel;
    }

    return data.general.mtow;
}

Component::Component(const AircraftData* data)
    : _data(data)
{
    _name = "";
}

void Component::Read(QDomElement* parentNode)
{
    _name = parentNode->attributeNode("name").value().toStdString();

    QDomElement nodeMass = parentNode->firstChildElement("mass");

    QDomElement nodeX = parentNode->firstChildElement("pos_x");
    QDomElement nodeY = parentNode->firstChildElement("pos_y");
    QDomElement nodeZ = parentNode->firstChildElement("pos_z");

    QDomElement nodeL = parentNode->firstChildElement("length");
    QDomElement nodeW = parentNode->firstChildElement("width");
    QDomElement nodeH = parentNode->firstChildElement("height");

    if ( !nodeMass.isNull() ) _m = units::mass::kilogram_t(nodeMass.text().toDouble());

    if ( !nodeX.isNull() ) _r.x() = units::length::meter_t(nodeX.text().toDouble());
    if ( !nodeY.isNull() ) _r.y() = units::length::meter_t(nodeY.text().toDouble());
    if ( !nodeZ.isNull() ) _r.z() = units::length::meter_t(nodeZ.text().toDouble());

    if ( !nodeL.isNull() ) _l = units::length::meter_t(nodeL.text().toDouble());
    if ( !nodeW.isNull() ) _w = units::length::meter_t(nodeW.text().toDouble());
    if ( !nodeH.isNull() ) _h = units::length::meter_t(nodeH.text().toDouble());
}

void Component::Save(QDomDocument* doc, QDomElement* parentNode)
{
    QDomElement node = doc->createElement(GetXmlTagName());
    parentNode->appendChild(node);
    SaveParameters(doc, &node);
}

InertiaMatrix Component::GetInertia() const
{
    return Cuboid::getInertiaMatrix(_m, _l, _w, _h);
}

void Component::SetName(const char* name)
{
    _name = name;
}

void Component::SetPosition(const PositionVector& r)
{
    _r = r;
}

void Component::SetMass(units::mass::kilogram_t m)
{
    _m = m;
}

void Component::SetLength(units::length::meter_t l)
{
    _l = l;
}

void Component::SetWidth(units::length::meter_t w)
{
    _w = w;
}

void Component::SetHeight(units::length::meter_t h)
{
    _h = h;
}

void Component::SaveParameters(QDomDocument* doc, QDomElement* node)
{
    QDomAttr nodeName = doc->createAttribute("name");
    nodeName.setValue(GetName());
    node->setAttributeNode(nodeName);

    XmlUtils::saveTextNode(doc, node, "mass", _m());

    XmlUtils::saveTextNode(doc, node, "pos_x", _r.x()());
    XmlUtils::saveTextNode(doc, node, "pos_y", _r.y()());
    XmlUtils::saveTextNode(doc, node, "pos_z", _r.z()());

    XmlUtils::saveTextNode(doc, node, "length" , _l());
    XmlUtils::saveTextNode(doc, node, "width"  , _w());
    XmlUtils::saveTextNode(doc, node, "height" , _h());
}
