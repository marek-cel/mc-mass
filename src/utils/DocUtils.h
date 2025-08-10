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
#ifndef MC_MASS_UTILS_DOCUTILS_H_
#define MC_MASS_UTILS_DOCUTILS_H_

#define ADD_NODE(parent, node, name) \
    XmlNode node = parent.addChildElement(name); \
    if ( !node.isValid() ) \
    { \
        Log::error("Failed to create %s node.", name); \
        return Result::Failure; \
    }

#define ADD_TEXT(node, text) \
    { \
        XmlNode text_node = node.addText(text); \
        if ( !text_node.isValid() || !text_node.isText() ) \
        { \
            Log::error("Failed to set %s text.", node.getName()); \
            return Result::Failure; \
        } \
    }

#define GET_NODE(parent, node, name) \
    XmlNode node = parent.getFirstChildElement(name); \
    if ( !node.isValid() ) \
    { \
        Log::error("Failed to get %s node.", name); \
        return Result::Failure; \
    }

#define GET_TEXT(parent, text, name) \
    XmlNode text; \
    { \
        XmlNode node = parent.getFirstChildElement(name); \
        if ( !node.isValid() ) \
        { \
            Log::error("Failed to get %s text.", name); \
            return Result::Failure; \
        } \
        text = node.getFirstChild(); \
        if ( !text.isValid() || !text.isText() ) \
        { \
            Log::error("Failed to get %s text.", name); \
            return Result::Failure; \
        } \
    }

#endif // MC_MASS_UTILS_DOCUTILS_H_
