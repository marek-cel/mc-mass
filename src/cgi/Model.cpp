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

#include <cgi/Model.h>

#include <osgDB/ReadFile>

namespace cgi
{

Model::Model(std::shared_ptr<Data> data)
    : Component(data)
{
    _pat = new osg::PositionAttitudeTransform();
    _root->addChild(_pat.get());

    _model = new osg::Group();
    _pat->addChild(_model.get());
}

Model::~Model() {}

void Model::update()
{
    if ( !_data.expired() )
    {
        std::shared_ptr<Data> data = _data.lock();

        updateModel(data->modelFile, data->projectDir);
        updateTransformations(data->offset_x, data->offset_y, data->offset_z,
                              data->rotation_x, data->rotation_y, data->rotation_z,
                              data->scale);
    }
}

void Model::updateModel(const std::filesystem::path& model_file, const std::filesystem::path& project_dir)
{
    if ( _model_file != model_file || _project_dir != project_dir )
    {
        _model_file = model_file;
        _project_dir = project_dir;

        _model->removeChildren(0, _model->getNumChildren());

        osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(model_file.string());
        if ( model.valid() )
        {
            _model->addChild(model);
        }
    }
}

void Model::updateTransformations(double offset_x, double offset_y, double offset_z,
                                  double rotation_x, double rotation_y, double rotation_z,
                                  double scale)
{
    osg::Vec3 r(offset_x, offset_y, offset_z);
    osg::Quat q(rotation_x, osg::X_AXIS,
                rotation_y, osg::Y_AXIS,
                rotation_z, osg::Z_AXIS);
    osg::Vec3 s(scale, scale, scale);

    _pat->setPosition(r);
    _pat->setAttitude(q);
    _pat->setScale(s);
}

} // namespace cgi
