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
#ifndef MC_MASS_UTILS_XMLNODE_H_
#define MC_MASS_UTILS_XMLNODE_H_

#include <filesystem>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <libxml/tree.h>

#include <Result.h>

/**
 * \brief XML node class.
 */
class XmlNode
{
public:

    typedef std::map<std::string, std::string> Attributes;

    // LCOV_EXCL_START
    XmlNode() = default;
    XmlNode(const XmlNode& node) = default;
    XmlNode(XmlNode&& node) = default;
    ~XmlNode() = default;
    XmlNode& operator=(const XmlNode& node) = default;
    XmlNode& operator=(XmlNode&& node) = default;
    // LCOV_EXCL_STOP

    /**
     * \param node XML node pointer
     * \param path XML file path pointer
     */
    XmlNode(xmlNodePtr node, std::weak_ptr<std::filesystem::path> path);

    XmlNode addChildElement(const char* name);
    XmlNode addChildElement(const std::string& name)
    {
        return addChildElement(name.c_str());
    }

    /**
     * \brief Adds text node to the element.
     * Adds text node to the element. The text node is added as a child of the
     * element.
     * \param text text
     * \return XML text node
     */
    XmlNode addText(const char* text);
    XmlNode addText(const std::string& text)
    {
        return addText(text.c_str());
    }

    /**
     * \brief Adds attribute to the element.
     * Adds attribute to the element. The attribute is added as a child of the
     * element.
     * \param name name of attribute
     * \param val value of attribute
     * \return result of the operation
     */
    Result addAttribute(const char* name, const char* val);
    Result addAttribute(const std::string& name, const std::string& val)
    {
        return addAttribute(name.c_str(), val.c_str());
    }

    /**
     * \brief Returns the value of the attribute.
     * Returns the value of the attribute or an empty string if the attribute
     * has not been specified.
     * \param name name of attribute
     * \return value of the attribute or an empty string if the attribute has not been specified
     */
    std::string getAttribute(const char* name) const;
    std::string getAttribute(const std::string& name) const
    {
        return getAttribute(name.c_str());
    }

    Result setAttribute(const char* name, const char* val);
    Result setAttribute(const std::string& name, const std::string& val)
    {
        return setAttribute(name.c_str(), val.c_str());
    }

    /**
     * \brief Returns element attributes list.
     * Returns element attributes list or empty list if the node is not
     * an element or element does not has any attributes.
     */
    Attributes getAttributes() const;

    /**
     * Returns first child node.
     */
    XmlNode getFirstChild() const;

    /**
     * Returns first child element node of the given name.
     * \param name element name
     * \return node's first child
     */
    XmlNode getFirstChildElement(const char* name = "") const;
    XmlNode getFirstChildElement(const std::string& name) const
    {
        return getFirstChildElement(name.c_str());
    }

    /**
     * \return file path
     */
    std::filesystem::path getPath() const;

    /**
     * \return node file path and line number
     */
    std::string getPathAndLine() const;

    /**
     * \return node line number
     */
    inline int getLine() const
    {
        if ( isValid() )
        {
            return static_cast<int>(_node->line);
        }

        return std::numeric_limits<int>::quiet_NaN();
    }

    /**
     * \return node name
     */
    std::string getName() const
    {
        if ( isValid() )
        {
            return std::string(reinterpret_cast<const char*>(_node->name));
        }

        return std::string();
    }

    /**
     * \return node's next sibling
     */
    XmlNode getNextSibling() const;

    /**
     * \param name element name
     * \return node's next sibling of a given name
     */
    XmlNode getNextSiblingElement(const char* name = "") const;

    /**
     * \return text if node is a text node, otherwise an empty string
     */
    std::string getText() const;

    /**
     * \param name attribute name
     * \param value attribute value
     * \return result of the operation
     */
    Result setText(const char* text);
    Result setText(const std::string& text)
    {
        return setText(text.c_str());
    }

    /**
     * \param name attribute name
     * \return true if an node has attributes of a given name, false otherwise
     */
    bool hasAttribute(const char* name) const;
    bool hasAttribute(const std::string& name) const
    {
        return hasAttribute(name.c_str());
    }

    /**
     * \return true if an node has attributes, false otherwise
     */
    inline bool hasAttributes() const
    {
        if ( isValid() )
        {
            return ( _node->properties != nullptr );
        }

        return false;
    }

    /**
     * \return true if an node has children, false otherwise
     */
    inline bool hasChildren() const
    {
        if ( isValid() )
        {
            return ( _node->children != nullptr );
        }

        return false;
    }

    /**
     * \return true if an node is an attribute, false otherwise
     */
    inline bool isAttribute() const
    {
        if ( isValid() )
        {
            return ( _node->type == XML_ATTRIBUTE_NODE );
        }

        return false;
    }

    /**
     * \return true if an node is a comment, false otherwise
     */
    inline bool isComment() const
    {
        if ( isValid() )
        {
            return ( _node->type == XML_COMMENT_NODE );
        }

        return false;
    }

    /**
     * \return true if an node is an element, false otherwise
     */
    inline bool isElement() const
    {
        if ( isValid() )
        {
            return ( _node->type == XML_ELEMENT_NODE );
        }

        return false;
    }

    /**
     * \return true if an node is a text, false otherwise
     */
    inline bool isText() const
    {
        if ( isValid() )
        {
            return _node->type == XML_TEXT_NODE;
        }

        return false;
    }

    /**
     * \return true if an node is valid, false otherwise
     */
    inline bool isValid() const
    {
        return _node ? true : false;
    }

private:

    std::weak_ptr<std::filesystem::path> _path; ///< XML file path pointer
    xmlNodePtr _node = nullptr;                 ///< XML node pointer
};

#endif // MC_MASS_UTILS_XMLNODE_H_
