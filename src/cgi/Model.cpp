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

#include <QDir>

namespace cgi
{

Model::Model(std::shared_ptr<Data> data)
    : Component(data)
{
    pat_ = new osg::PositionAttitudeTransform();
    root_->addChild(pat_.get());

    model_ = new osg::Group();
    pat_->addChild(model_.get());
}

Model::~Model() {}

void Model::Update()
{
    if ( !data_.expired() )
    {
        std::shared_ptr<Data> data = data_.lock();

        UpdateModel(data->modelFile, data->projectDir);
        UpdateTransformations(data->offset_x, data->offset_y, data->offset_z,
                              data->rotation_x, data->rotation_y, data->rotation_z,
                              data->scale);
    }
}

void Model::UpdateModel(const QString& model_file, const QString& project_dir)
{
    if ( model_file_ != model_file || project_dir_ != project_dir )
    {
        model_file_ = model_file;
        project_dir_ = project_dir;

        QDir dir(project_dir);
        QString file_path = dir.absoluteFilePath(model_file_);

        model_->removeChildren(0, model_->getNumChildren());

        //std::cout << "file_path.toStdString() " << file_path.toStdString() << std::endl;

        osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(file_path.toStdString());
        if ( model.valid() )
        {
            model_->addChild(model);
        }
    }
}

void Model::UpdateTransformations(double offset_x, double offset_y, double offset_z,
                                  double rotation_x, double rotation_y, double rotation_z,
                                  double scale)
{
    osg::Vec3 r(offset_x, offset_y, offset_z);
    osg::Quat q(rotation_x, osg::X_AXIS,
                rotation_y, osg::Y_AXIS,
                rotation_z, osg::Z_AXIS);
    osg::Vec3 s(scale, scale, scale);

    pat_->setPosition(r);
    pat_->setAttitude(q);
    pat_->setScale(s);
}

} // namespace cgi
