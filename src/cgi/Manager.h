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
#ifndef MC_MASS_CGI_MANAGER_H_
#define MC_MASS_CGI_MANAGER_H_

#include <cgi/ManipulatorOrbit.h>
#include <cgi/ManipulatorTrack.h>

#include <cgi/CGI.h>
#include <cgi/HUD.h>

namespace cgi {

class Model;

/** */
class Manager
{
public:

    /** */
    Manager();

    /** */
    virtual ~Manager();

    /** */
    void Update();

    /** */
    inline osgGA::CameraManipulator* GetCameraManipulator()
    {
        return _manipulator.get();
    }

    /** Returns root node. */
    inline osg::Group* GetNodeCGI() { return cgi_->root().get(); }

    /** Returns root node. */
    inline osg::Group* GetNodeHUD() { return hud_->root().get(); }

    void SetCameraManipulatorOrbit();
    void SetCameraManipulatorTrack();

    void SetGridVisibility(bool grid_visible);

    void SetWinHeight(int h);
    void SetWinWidth(int w);

    void SetModelData(const QString& model_file,
                      double offset_x, double offset_y, double offset_z,
                      double rotation_x, double rotation_y, double rotation_z,
                      double scale);

    void SetProjectDir(const QString& project_dir);

    void SetHighlightData(bool highlight,
                          double highlight_x = 0.0,
                          double highlight_y = 0.0,
                          double highlight_z = 0.0,
                          double highlight_l = 0.0,
                          double highlight_w = 0.0,
                          double highlight_h = 0.0);

private:

    std::shared_ptr<Data> data_;

    std::shared_ptr<CGI> cgi_;
    std::shared_ptr<HUD> hud_;

    osg::ref_ptr<osgGA::CameraManipulator> _manipulator;    ///< current manipulator

    osg::ref_ptr<ManipulatorOrbit> _manipulatorOrbit;
    osg::ref_ptr<ManipulatorTrack> _manipulatorTrack;
};

} // namespace cgi

#endif // MC_MASS_CGI_MANAGER_H_
