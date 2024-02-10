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
    data_ = std::make_shared<Data>();

    cgi_ = std::make_shared<CGI>(data_);
    hud_ = std::make_shared<HUD>(data_);

    Builder::BuildCGI(data_, cgi_);
    Builder::BuildHUD(data_, hud_);

    _manipulatorOrbit = new ManipulatorOrbit();
    _manipulatorTrack = new ManipulatorTrack();

    _manipulator = _manipulatorTrack;
}

Manager::~Manager() {}

void Manager::Update()
{
    osg::Quat q = _manipulator->getMatrix().getRotate();

    data_->camera_w = q.w();
    data_->camera_x = q.x();
    data_->camera_y = q.y();
    data_->camera_z = q.z();

    cgi_->Update();
    hud_->Update();
}

void Manager::SetCameraManipulatorOrbit()
{
    _manipulator = _manipulatorOrbit;
    _manipulatorOrbit->setTrackNode(cgi_->root().get());
}

void Manager::SetCameraManipulatorTrack()
{
    _manipulator = _manipulatorTrack;
    _manipulatorTrack->setNode(cgi_->root().get());
}

void Manager::SetGridVisibility(bool grid_visible)
{
    data_->grid_visible = grid_visible;
}

void Manager::SetWinHeight(int h)
{
    data_->win_height = h;
}

void Manager::SetWinWidth(int w)
{
    data_->win_width = w;
}

void Manager::SetModelData(const QString& model_file,
                           double offset_x, double offset_y, double offset_z,
                           double rotation_x, double rotation_y, double rotation_z,
                           double scale)
{
    data_->modelFile = model_file;

    data_->offset_x = offset_x;
    data_->offset_y = offset_y;
    data_->offset_z = offset_z;

    data_->rotation_x = rotation_x;
    data_->rotation_y = rotation_y;
    data_->rotation_z = rotation_z;

    data_->scale = scale;
}

void Manager::SetProjectDir(const QString& project_dir)
{
    data_->projectDir = project_dir;
}

void Manager::SetHighlightData(bool highlight,
                               double highlight_x,
                               double highlight_y,
                               double highlight_z,
                               double highlight_l,
                               double highlight_w,
                               double highlight_h)
{
    data_->highlight = highlight;

    data_->highlight_x = highlight_x;
    data_->highlight_y = highlight_y;
    data_->highlight_z = highlight_z;

    data_->highlight_l = highlight_l;
    data_->highlight_w = highlight_w;
    data_->highlight_h = highlight_h;
}

} // namespace cgi
