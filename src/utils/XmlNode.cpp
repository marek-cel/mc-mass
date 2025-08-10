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

#include <utils/XmlNode.h>

#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <iostream>

// #include <mcsim/utils/misc/StringUtils.h>

namespace mc {

XmlNode::XmlNode(xmlNodePtr node, std::weak_ptr<std::filesystem::path> path)
    : _path(path)
    , _node(node)
{}

XmlNode XmlNode::addChildElement(const char* name)
{
    if ( !isElement() )
    {
        return XmlNode();
    }

    xmlNodePtr child = xmlNewChild(_node, nullptr, reinterpret_cast<const xmlChar*>(name), nullptr);
    if (child == nullptr)
    {
        return XmlNode();
    }

    return XmlNode(child, _path);
}

XmlNode XmlNode::addText(const char* text)
{
    if ( !isElement() )
    {
        return XmlNode();
    }

    xmlNodePtr child = xmlNewText(reinterpret_cast<const xmlChar*>(text));
    if (child == nullptr)
    {
        return XmlNode();
    }

    child = xmlAddChild(_node, child);
    return XmlNode(child, _path);
}

Result XmlNode::addAttribute(const char* name, const char* val)
{
    if ( !isElement() )
    {
        return Result::Failure;
    }

    xmlAttrPtr attr = xmlNewProp(_node, reinterpret_cast<const xmlChar*>(name), reinterpret_cast<const xmlChar*>(val));
    if (attr == nullptr)
    {
        return Result::Failure;
    }

    return Result::Success;
}

std::string XmlNode::getAttribute(const char* name) const
{
    if ( hasAttributes() )
    {
        xmlAttrPtr attr = _node->properties;
        while ( attr != 0 )
        {
            if ( 0 == xmlStrcmp(attr->name, reinterpret_cast<const xmlChar*>(name)) )
            {
                if ( attr->children != 0 )
                {
                    xmlChar *value = xmlNodeListGetString(attr->children->doc, attr->children, 1);
                    std::string result = reinterpret_cast<const char*>(value);
                    xmlFree(value);
                    return result;
                }
                else
                {
                    return std::string();
                }
            }

            attr = attr->next;
        }
    }

    return std::string();
}

Result XmlNode::setAttribute(const char* name, const char* val)
{
    if ( !isElement() || !hasAttribute(name) )
    {
        return Result::Failure;
    }

    xmlAttrPtr attr = xmlSetProp(_node, reinterpret_cast<const xmlChar*>(name), reinterpret_cast<const xmlChar*>(val));
    if (attr == nullptr)
    {
        return Result::Failure;
    }

    return Result::Success;
}

XmlNode::Attributes XmlNode::getAttributes() const
{
    Attributes attributes;
    attributes.clear();

    if ( hasAttributes() )
    {
        xmlAttrPtr attr = _node->properties;

        while ( attr != 0 )
        {
            if ( attr->children != 0 )
            {
                xmlChar *value = xmlNodeListGetString(attr->children->doc, attr->children, 1);
                std::string str_name  = reinterpret_cast<const char*>(attr->name);
                std::string str_value = reinterpret_cast<const char*>(value);
                attributes.insert(std::pair<std::string, std::string>(str_name, str_value));
                xmlFree(value);
            }

            attr = attr->next;
        }
    }

    return attributes;
}

XmlNode XmlNode::getFirstChild() const
{
    XmlNode result;
    if ( isValid() )
    {
        if ( _node->children != 0 )
        {
            result._node = _node->children;
            result._path = _path;
        }
    }
    return result;
}

XmlNode XmlNode::getFirstChildElement(const char* name) const
{
    XmlNode result;

    if ( isValid() )
    {
        xmlNodePtr child = _node->children;

        while ( child != 0 )
        {
            if ( child->type == XML_ELEMENT_NODE )
            {
                if ( 0 == xmlStrcmp(child->name, reinterpret_cast<const xmlChar*>(name)) || strlen(name) == 0 )
                {
                    result._node = child;
                    result._path = _path;
                    return result;
                }
            }

            child = child->next;
        }
    }

    return result;
}

std::filesystem::path XmlNode::getPath() const
{
    if ( !_path.expired() )
    {
        return *_path.lock();
    }

    return std::string("");
}

std::string XmlNode::getPathAndLine() const
{
    std::string file = "[Unknown]";
    if ( !_path.expired() )
    {
        file = _path.lock()->string();
    }
    std::string result;
    result += file;
    result += "(";
    result += std::to_string(static_cast<int>(_node->line));
    result += ")";
    return result;
}

XmlNode XmlNode::getNextSibling() const
{
    XmlNode result;
    if ( isValid() )
    {
        if ( _node->next != nullptr )
        {
            result._node = _node->next;
            result._path = _path;
        }
    }
    return result;
}

XmlNode XmlNode::getNextSiblingElement(const char* name) const
{
    XmlNode result;

    if ( isValid() )
    {
        xmlNodePtr next = _node->next;

        while ( next != nullptr )
        {
            if ( next->type == XML_ELEMENT_NODE )
            {
                if ( 0 == xmlStrcmp(next->name, reinterpret_cast<const xmlChar*>(name)) || strlen(name) == 0 )
                {
                    result._node = next;
                    result._path = _path;
                    return result;
                }
            }

            next = next->next;
        }
    }

    return result;
}

std::string XmlNode::getText() const
{
    switch ( _node->type )
    {
    case XML_TEXT_NODE:
        return std::string(reinterpret_cast<const char*>(_node->content));
        break;

    default:
        return std::string();
        break;
    }

    return std::string();
}

Result XmlNode::setText(const char* text)
{
    if ( !isValid() || !isText() )
    {
        return Result::Failure;
    }

    xmlNodeSetContent(_node, reinterpret_cast<const xmlChar*>(text));
    return Result::Success;
}

bool XmlNode::hasAttribute(const char* name) const
{
    if ( hasAttributes() )
    {
        xmlAttrPtr attr = _node->properties;

        while ( attr != 0 )
        {
            if ( 0 == xmlStrcmp(attr->name, reinterpret_cast<const xmlChar*>(name)) )
            {
                return true;
            }

            attr = attr->next;
        }
    }

    return false;
}

} // namespace mc
