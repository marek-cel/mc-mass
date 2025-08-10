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

#include <gui/WidgetCGI.h>

#include <osgGA/StateSetManipulator>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

WidgetCGI::WidgetCGI(QWidget* parent)
    : WidgetOSG(parent)
{
    _manager_cgi = new cgi::Manager();

    QWidget* widget = addViewWidget();

    _layout = new QGridLayout(this);
    _layout->setContentsMargins(1, 1, 1, 1);
    _layout->addWidget(widget, 0, 0);

    setLayout(_layout);

    setCameraManipulatorOrtho();
    resetView();

    _timerId = startTimer(1000.0 / 60.0);
}

WidgetCGI::~WidgetCGI()
{
    if ( _timerId ) killTimer( _timerId );

    if ( _manager_cgi ) { delete _manager_cgi; } _manager_cgi = nullptr;
}

void WidgetCGI::resetView()
{
    osg::ref_ptr<cgi::ManipulatorOrtho> manipulator =
            dynamic_cast<cgi::ManipulatorOrtho*>(_manager_cgi->getCameraManipulator());
}

void WidgetCGI::topView()
{
    osg::ref_ptr<cgi::ManipulatorOrtho> manipulator =
            dynamic_cast<cgi::ManipulatorOrtho*>(_manager_cgi->getCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI , osg::X_AXIS,
                               0.0  , osg::Y_AXIS,
                              -M_PI , osg::Z_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::bottomView()
{
    osg::ref_ptr<cgi::ManipulatorOrtho> manipulator =
            dynamic_cast<cgi::ManipulatorOrtho*>(_manager_cgi->getCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(0.0  , osg::X_AXIS,
                               0.0  , osg::Y_AXIS,
                              -M_PI , osg::Z_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::frontView()
{
    osg::ref_ptr<cgi::ManipulatorOrtho> manipulator =
            dynamic_cast<cgi::ManipulatorOrtho*>(_manager_cgi->getCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2 , osg::X_AXIS,
                              -M_PI_2 , osg::Y_AXIS,
                               0.0    , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::backView()
{
    osg::ref_ptr<cgi::ManipulatorOrtho> manipulator =
            dynamic_cast<cgi::ManipulatorOrtho*>(_manager_cgi->getCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2 , osg::X_AXIS,
                               M_PI_2 , osg::Y_AXIS,
                               0.0    , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::leftView()
{
    osg::ref_ptr<cgi::ManipulatorOrtho> manipulator =
            dynamic_cast<cgi::ManipulatorOrtho*>(_manager_cgi->getCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2 , osg::X_AXIS,
                               M_PI   , osg::Y_AXIS,
                               0.0    , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::rightView()
{
    osg::ref_ptr<cgi::ManipulatorOrtho> manipulator =
            dynamic_cast<cgi::ManipulatorOrtho*>(_manager_cgi->getCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2 , osg::X_AXIS,
                               0.0    , osg::Y_AXIS,
                               0.0    , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::setCameraManipulatorOrtho()
{
    _manager_cgi->setCameraManipulatorOrtho();
    getOsgViewer()->setCameraManipulator(_manager_cgi->getCameraManipulator());
}

void WidgetCGI::resizeEvent(QResizeEvent* event)
{
    ////////////////////////////
    QWidget::resizeEvent(event);
    ////////////////////////////

    _manager_cgi->setWinHeight(event->size().height());
    _manager_cgi->setWinWidth(event->size().width());
}

void WidgetCGI::timerEvent(QTimerEvent* event)
{
    ///////////////////////////
    QWidget::timerEvent(event);
    ///////////////////////////

    update();
    _manager_cgi->update();
}

QWidget* WidgetCGI::addViewWidget()
{
    createCameras();

    setSceneData(_manager_cgi->getNodeCGI());
    _camera_hud->addChild(_manager_cgi->getNodeHUD());

    addEventHandler(new osgViewer::StatsHandler);
    setKeyEventSetsDone(0);
    assignSceneDataToCameras();

    return _gwin->getGLWidget();
}

void WidgetCGI::createCameras()
{
    _camera_cgi = getOsgViewer()->getCamera();
    _camera_hud = new osg::Camera();

    _camera_cgi->setGraphicsContext(_gwin);
    _camera_hud->setGraphicsContext(_gwin);

    osg::GraphicsContext* context = _camera_cgi->getGraphicsContext();
    _camera_hud->setGraphicsContext(context);

    const osg::GraphicsContext::Traits* traits = _camera->getGraphicsContext()->getTraits();

    double w2h = static_cast<double>(traits->width)
               / static_cast<double>(traits->height);

    _camera_cgi->setClearColor(osg::Vec4(0.47, 0.71, 1.0, 1.0));
    //_camera_cgi->setClearColor(osg::Vec4(0.216, 0.216, 0.216, 1.0));
    _camera_cgi->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    // _camera_cgi->setProjectionMatrixAsPerspective(30.0, w2h, 0.1, 1000000.0);
    _camera_cgi->setProjectionMatrixAsOrtho(-CGI_FOV_Y_2 * w2h, CGI_FOV_Y_2 * w2h, -CGI_FOV_Y_2, CGI_FOV_Y_2, 0.1, 1000000.0);

    _camera_hud->setProjectionMatrixAsOrtho2D(-HUD_FOV_Y_2 * w2h, HUD_FOV_Y_2 * w2h, -HUD_FOV_Y_2, HUD_FOV_Y_2);
    _camera_hud->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    _camera_hud->setViewMatrix(osg::Matrix::identity());
    _camera_hud->setClearMask(GL_DEPTH_BUFFER_BIT);
    _camera_hud->setRenderOrder(osg::Camera::POST_RENDER);
    _camera_hud->setAllowEventFocus(false);
    _camera_hud->setProjectionResizePolicy(osg::Camera::HORIZONTAL);
    _camera_hud->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));

    getOsgViewer()->addSlave(_camera_hud, false);
}
