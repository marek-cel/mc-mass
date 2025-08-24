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

#include <cgi/ManipulatorOrtho.h>

#include <iostream>

namespace cgi {

ManipulatorOrtho::ManipulatorOrtho()
    : osgGA::StandardManipulator()
{}


void ManipulatorOrtho::setTransformation(const osg::Vec3d& eye, const osg::Quat& rotation)
{
    // TODO
}


void ManipulatorOrtho::setTransformation(const osg::Vec3d& eye, const osg::Vec3d& center, const osg::Vec3d& up)
{
    // TODO
}


void ManipulatorOrtho::getTransformation(osg::Vec3d& eye, osg::Quat& rotation) const
{
    // TODO
}


void ManipulatorOrtho::getTransformation(osg::Vec3d& eye, osg::Vec3d& center, osg::Vec3d& up) const
{
    // TODO
}


void ManipulatorOrtho::setByMatrix(const osg::Matrixd& matrix)
{
    // TODO
}


void ManipulatorOrtho::setByInverseMatrix(const osg::Matrixd& matrix)
{
    // TODO
}


osg::Matrixd ManipulatorOrtho::getMatrix() const
{
    // TODO
    return osg::Matrixd::identity();
}


osg::Matrixd ManipulatorOrtho::getInverseMatrix() const
{
    // TODO
    return osg::Matrixd::identity();
}


void ManipulatorOrtho::updateCamera(osg::Camera& camera)
{
    osgGA::StandardManipulator::updateCamera(camera);

    double w2h = (double)(camera.getGraphicsContext()->getTraits()->width)
               / (double)(camera.getGraphicsContext()->getTraits()->height);

    double x_min = -_scale * _fov_y * w2h / 2.0;
    double x_max =  _scale * _fov_y * w2h / 2.0;
    double y_min = -_scale * _fov_y / 2.0;
    double y_max =  _scale * _fov_y / 2.0;

    if ( x_min != _x_min || x_max != _x_max || y_min != _y_min || y_max != _y_max )
    {
        _x_min = x_min;
        _x_max = x_max;
        _y_min = y_min;
        _y_max = y_max;

        camera.setProjectionMatrixAsOrtho(_x_min, _x_max, _y_min, _y_max, _z_near, _z_far);
    }
}


void ManipulatorOrtho::setFovY(double fov_y)
{
    if ( fov_y > 0.0 )
    {
        _fov_y = fov_y;
    }
}


void ManipulatorOrtho::setScale(double scale)
{
    _scale = scale;

    if ( _scale > _scale_max ) _scale = _scale_max;
    if ( _scale < _scale_min ) _scale = _scale_min;
}


void ManipulatorOrtho::setScaleMin(double min)
{
    if ( min >= 0.0 && min < _scale_max )
    {
        _scale_min = min;
    }
}


void ManipulatorOrtho::setScaleMax(double max)
{
    if ( max >= 0.0 && max > _scale_min )
    {
        _scale_max = max;
    }
}


void ManipulatorOrtho::setZNear(double z_near)
{
    if ( z_near > 0.0 && z_near < _z_far )
    {
        _z_near = z_near;
    }
}


void ManipulatorOrtho::setZFar(double z_far)
{
    if ( z_far > 0.0 && z_far > _z_near )
    {
        _z_far = z_far;
    }
}


bool ManipulatorOrtho::handleMouseWheel(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
    osgGA::GUIEventAdapter::ScrollingMotion sm = ea.getScrollingMotion();

    switch ( sm )
    {
    case osgGA::GUIEventAdapter::SCROLL_UP:
        zoomModel( -_wheelZoomFactor );
        us.requestRedraw();
        return true;

    case osgGA::GUIEventAdapter::SCROLL_DOWN:
        zoomModel(  _wheelZoomFactor );
        us.requestRedraw();
        return true;
   }

   return false;
}


bool ManipulatorOrtho::performMovementMiddleMouseButton(const double eventTimeDelta, const double dx, const double dy)
{
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    // TODO
    return false;
}


bool ManipulatorOrtho::performMovementRightMouseButton(const double eventTimeDelta, const double dx, const double dy)
{
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    // TODO
    return false;
}


void ManipulatorOrtho::zoomModel(const float dy)
{
    setScale(_scale * (1.0 + dy));
}


// void ManipulatorOrtho::panModel(const float dx, const float dy, const float dz)
// {
//     double ortho_pan_scale = 0.0005 * _scale;
//     osgGA::TrackballManipulator::panModel(ortho_pan_scale * dx,
//                                           ortho_pan_scale * dy,
//                                           ortho_pan_scale * dz);
// }

} // namespace cgi
