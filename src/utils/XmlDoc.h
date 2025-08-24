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
#ifndef MC_MASS_UTILS_XMLDOC_H_
#define MC_MASS_UTILS_XMLDOC_H_

#include <filesystem>
#include <string>

#include <libxml/tree.h>

#include <Result.h>
#include <utils/XmlNode.h>

/**
 * \brief XML Document class.
 */
class XmlDoc
{
public:

    /**
     * \brief Creates an empty XML document.
     */
    XmlDoc();

    /**
     * \brief Opens XML file.
     * \param path XML file path
     */
    XmlDoc(const char* path);

    /**
     * \brief Opens XML file.
     * \param file XML file path
     */
    XmlDoc(const std::string& path);

    /**
     * \brief Opens XML file.
     * \param file XML file path
     */
    XmlDoc(const std::filesystem::path& path);

    /**
     * \brief Destructor.
     */
    ~XmlDoc();

    /**
     * \brief Creates XML document root node.
     * \param name XML document root node name
     * \return XML document root node
     */
    XmlNode createRootNode(const char* name);
    inline XmlNode createRootNode(const std::string& name)
    {
        return createRootNode(name.c_str());
    }

    /**
     * \return file path
     */
    inline std::filesystem::path getPath() const
    {
        return *_path;
    }

    /**
     * Gets XML document root node.
     * \return XML document root node
     */
    inline XmlNode getRootNode()
    {
        return XmlNode(*_root);
    }

    /**
     * Checks if XML document is open.
     * \return returns true if XML document is open
     */
    inline bool isOpen() const
    {
        return _open;
    }

    /**
     * Open file for reading.
     * \param path XML file path
     */
    void openFile(const char* path);
    inline void openFile(const std::string& path)
    {
        openFile(path.c_str());
    }
    inline void openFile(const std::filesystem::path& path)
    {
        openFile(path.string());
    }

    /** Closes file. */
    void closeFile();

    /**
     * \brief Saves XML document to file.
     * \param path XML file path
     * \return result of the operation
     */
    Result saveFile(const char* path);
    inline Result saveFile(const std::string& path)
    {
        return saveFile(path.c_str());
    }
    inline Result saveFile(const std::filesystem::path& path)
    {
        return saveFile(path.string());
    }

private:

    std::shared_ptr<std::filesystem::path> _path = std::make_shared<std::filesystem::path>(); ///< XML file path

    xmlDocPtr _doc = nullptr;   ///< XML document pointer
    bool _open = false;         ///< specifies if document is open
    XmlNode *_root = nullptr;   ///< XML document root node
};

#endif // MC_MASS_UTILS_XMLDOC_H_
