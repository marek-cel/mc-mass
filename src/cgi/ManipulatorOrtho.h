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
#ifndef MC_MASS_CGI_MANIPULATORORTHO_H_
#define MC_MASS_CGI_MANIPULATORORTHO_H_

#include <osgGA/StandardManipulator>

namespace cgi
{


class ManipulatorOrtho : public osgGA::StandardManipulator
{
public:

    ManipulatorOrtho();

    void setTransformation(const osg::Vec3d& eye, const osg::Quat& rotation) override;
    void setTransformation(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up) override;
    void getTransformation(osg::Vec3d& eye, osg::Quat& rotation) const override;
    void getTransformation(osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up) const override;

    void setByMatrix(const osg::Matrixd& matrix) override;
    void setByInverseMatrix(const osg::Matrixd& matrix) override;
    osg::Matrixd getMatrix() const override;
    osg::Matrixd getInverseMatrix() const override;

    void updateCamera(osg::Camera& camera) override;

    void setFovY(double fov_y);

    void setScale(double scale);
    void setScaleMin(double min);
    void setScaleMax(double max);

    void setZNear(double z_near);
    void setZFar(double z_far);

    inline void setWheelZoomFactor(double wheelZoomFactor)
    {
        _wheelZoomFactor = wheelZoomFactor;
    }

protected:

    double _fov_y = 1.0;

    double _x_min = -_fov_y / 2.0;
    double _x_max =  _fov_y / 2.0;
    double _y_min = -_fov_y / 2.0;
    double _y_max =  _fov_y / 2.0;

    double _scale = 1.0;
    double _scale_min = 0.1;
    double _scale_max = 100.0;

    double _z_near = 0.001;
    double _z_far = 1000.0;

    double _wheelZoomFactor = -0.1;

    bool handleMouseWheel(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us) override;

    void zoomModel(const float dy);
};


} // end of cgi namespace

#endif // MC_MASS_CGI_MANIPULATORORTHO_H_
