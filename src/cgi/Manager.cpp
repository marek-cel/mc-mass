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

#include <cgi/Manager.h>

#include <cgi/Builder.h>

namespace cgi {

Manager::Manager()
{
    _data = std::make_shared<Data>();

    _cgi = std::make_shared<CGI>(_data);
    _hud = std::make_shared<HUD>(_data);

    Builder::buildCGI(_data, _cgi);
    Builder::buildHUD(_data, _hud);

    _manipulatorOrtho = new ManipulatorOrtho();
    setCameraManipulatorOrtho();
}

Manager::~Manager() {}

void Manager::update()
{
    osg::Quat q = _manipulator->getMatrix().getRotate();

    _data->camera_w = q.w();
    _data->camera_x = q.x();
    _data->camera_y = q.y();
    _data->camera_z = q.z();

    _cgi->update();
    _hud->update();
}

void Manager::setCameraManipulatorOrtho()
{
    _manipulator = _manipulatorOrtho;
    _manipulatorOrtho->setNode(_cgi->root().get());
}

void Manager::setGridVisibility(bool grid_visible)
{
    _data->grid_visible = grid_visible;
}

void Manager::setWinHeight(int h)
{
    _data->win_height = h;
}

void Manager::setWinWidth(int w)
{
    _data->win_width = w;
}

void Manager::setModelData(const std::filesystem::path& model_file,
                           double offset_x, double offset_y, double offset_z,
                           double rotation_x, double rotation_y, double rotation_z,
                           double scale)
{
    _data->modelFile = model_file;

    _data->offset_x = offset_x;
    _data->offset_y = offset_y;
    _data->offset_z = offset_z;

    _data->rotation_x = rotation_x;
    _data->rotation_y = rotation_y;
    _data->rotation_z = rotation_z;

    _data->scale = scale;
}

void Manager::setProjectDir(const std::filesystem::path& project_dir)
{
    _data->projectDir = project_dir;
}

void Manager::setHighlightData(bool highlight,
                               double highlight_x,
                               double highlight_y,
                               double highlight_z,
                               double highlight_l,
                               double highlight_w,
                               double highlight_h)
{
    _data->highlight = highlight;

    _data->highlight_x = highlight_x;
    _data->highlight_y = highlight_y;
    _data->highlight_z = highlight_z;

    _data->highlight_l = highlight_l;
    _data->highlight_w = highlight_w;
    _data->highlight_h = highlight_h;
}

} // namespace cgi
