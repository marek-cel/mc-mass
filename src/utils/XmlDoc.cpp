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

#include <utils/XmlDoc.h>

#include <cstring>
#include <iostream>

XmlDoc::XmlDoc()
{
    _doc = xmlNewDoc(reinterpret_cast<const xmlChar*>("1.0"));
}

XmlDoc::XmlDoc(const char* path)
{
    openFile(path);
}

XmlDoc::XmlDoc(const std::string& path)
    : XmlDoc(path.c_str())
{}

XmlDoc::XmlDoc(const std::filesystem::path& path)
    : XmlDoc(path.string().c_str())
{}

XmlDoc::~XmlDoc()
{
    closeFile();
}

XmlNode XmlDoc::createRootNode(const char* name)
{
    XmlNode root_node;

    if ( _doc != nullptr && _root == nullptr )
    {
        xmlNodePtr root = xmlNewNode(nullptr, reinterpret_cast<const xmlChar*>(name));
        if (root != nullptr)
        {
            _root = new XmlNode(root, _path);
            xmlDocSetRootElement(_doc, root);
            return XmlNode(*_root);
        }
    }

    return root_node;
}

void XmlDoc::openFile(const char* path)
{
    closeFile();

    if ( std::strlen(path) > 0 )
    {
        _doc = xmlParseFile(path);

        if ( _doc == nullptr )
        {
            xmlFreeDoc(_doc);
            return;
        }

        xmlNodePtr root = xmlDocGetRootElement(_doc);

        if ( root == nullptr )
        {
            xmlFreeDoc(_doc);
            return;
        }

        _path->assign(path);
        _root = new XmlNode(root, _path);
        _open = true;
    }
}

void XmlDoc::closeFile()
{
    _path->clear();
    _open = false;

    if ( _root ) delete _root;
    if ( _doc  ) xmlFreeDoc(_doc);

    _root = nullptr;
    _doc  = nullptr;
}

Result XmlDoc::saveFile(const char* path)
{
    _path->clear();
    _open = false;

    if ( _doc == nullptr )
    {
        return Result::Failure;
    }

    if ( _root == nullptr )
    {
        return Result::Failure;
    }

    if ( xmlSaveFormatFileEnc(path, _doc, "UTF-8", 1) )
    {
        _path->assign(path);
        _open = true;
        return Result::Success;
    }

    return Result::Failure;
}

