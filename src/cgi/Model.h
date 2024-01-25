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
#ifndef MC_MASS_CGI_MODEL_H_
#define MC_MASS_CGI_MODEL_H_

#include <cgi/Component.h>

#include <osg/PositionAttitudeTransform>

namespace cgi
{

/** */
class Model : public Component
{
public:

    /** */
    Model(std::shared_ptr<Data> data);

    /** */
    virtual ~Model();

    virtual void Update() override;

private:

    osg::ref_ptr<osg::PositionAttitudeTransform> pat_;
    osg::ref_ptr<osg::Group> model_;

    QString model_file_;
    QString project_dir_;

    void UpdateModel(const QString& model_file, const QString& project_dir);
    void UpdateTransformations(double offset_x, double offset_y, double offset_z,
                               double rotation_x, double rotation_y, double rotation_z,
                               double scale);
};

} // namespace cgi

#endif // MC_MASS_CGI_MODEL_H_
