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
#ifndef MC_MASS_CGI_MANAGER_H_
#define MC_MASS_CGI_MANAGER_H_

#include <filesystem>

#include <cgi/ManipulatorOrtho.h>

#include <cgi/CGI.h>
#include <cgi/HUD.h>

namespace cgi {

class Manager
{
public:

    Manager();
    virtual ~Manager();

    void update();

    inline osgGA::CameraManipulator* getCameraManipulator()
    {
        return _manipulator.get();
    }

    inline osg::Group* getNodeCGI() { return _cgi->root().get(); }
    inline osg::Group* getNodeHUD() { return _hud->root().get(); }

    void setCameraManipulatorOrtho();

    void setGridVisibility(bool grid_visible);

    void setWinHeight(int h);
    void setWinWidth(int w);

    void setModelData(
        const std::filesystem::path& model_file,
        double offset_x, double offset_y, double offset_z,
        double rotation_x, double rotation_y, double rotation_z,
        double scale
    );

    void setProjectDir(const std::filesystem::path& project_dir);

    void setHighlightData(
        bool highlight,
        double highlight_x = 0.0,
        double highlight_y = 0.0,
        double highlight_z = 0.0,
        double highlight_l = 0.0,
        double highlight_w = 0.0,
        double highlight_h = 0.0
    );

private:

    std::shared_ptr<Data> _data;

    std::shared_ptr<CGI> _cgi;
    std::shared_ptr<HUD> _hud;

    osg::ref_ptr<osgGA::CameraManipulator> _manipulator;    ///< current manipulator
    osg::ref_ptr<ManipulatorOrtho> _manipulatorOrtho;
};

} // namespace cgi

#endif // MC_MASS_CGI_MANAGER_H_
