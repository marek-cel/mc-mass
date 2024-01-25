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
    manager_cgi_ = new cgi::Manager();

    QWidget *widget = addViewWidget();

    layout_ = new QGridLayout(this);
    layout_->setContentsMargins(1, 1, 1, 1);
    layout_->addWidget(widget, 0, 0);

    setLayout(layout_);

    shortcut_view_default_ = new QShortcut( QKeySequence(Qt::Key_0), this, SLOT(resetView()) );
    shortcut_view_top_     = new QShortcut( QKeySequence(Qt::Key_7), this, SLOT(topView())   );
    shortcut_view_back_    = new QShortcut( QKeySequence(Qt::Key_3), this, SLOT(backView())   );
    shortcut_view_left_    = new QShortcut( QKeySequence(Qt::Key_1), this, SLOT(leftView())   );
    shortcut_view_bottom_  = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_7), this, SLOT(bottomView()) );
    shortcut_view_front_   = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_3), this, SLOT(frontView()) );
    shortcut_view_right_   = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_1), this, SLOT(rightView()) );

    setCameraManipulatorOrbit();
    resetView();

    timer_id_ = startTimer(1000.0 / 60.0);
}

WidgetCGI::~WidgetCGI()
{
    if ( timer_id_ ) killTimer( timer_id_ );

    if ( manager_cgi_ ) { delete manager_cgi_; } manager_cgi_ = nullptr;
}

void WidgetCGI::resetView()
{
    osg::ref_ptr<osgGA::OrbitManipulator> manipulator =
            dynamic_cast<osgGA::OrbitManipulator*>(manager_cgi_->GetCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2       , osg::X_AXIS,
                              -0.75 * M_PI  , osg::Y_AXIS,
                               M_PI_2 / 3.0 , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::topView()
{
    osg::ref_ptr<osgGA::OrbitManipulator> manipulator =
            dynamic_cast<osgGA::OrbitManipulator*>(manager_cgi_->GetCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI , osg::X_AXIS,
                               0.0  , osg::Y_AXIS,
                              -M_PI , osg::Z_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::bottomView()
{
    osg::ref_ptr<osgGA::OrbitManipulator> manipulator =
            dynamic_cast<osgGA::OrbitManipulator*>(manager_cgi_->GetCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(0.0  , osg::X_AXIS,
                               0.0  , osg::Y_AXIS,
                              -M_PI , osg::Z_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::frontView()
{
    osg::ref_ptr<osgGA::OrbitManipulator> manipulator =
            dynamic_cast<osgGA::OrbitManipulator*>(manager_cgi_->GetCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2 , osg::X_AXIS,
                              -M_PI_2 , osg::Y_AXIS,
                               0.0    , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::backView()
{
    osg::ref_ptr<osgGA::OrbitManipulator> manipulator =
            dynamic_cast<osgGA::OrbitManipulator*>(manager_cgi_->GetCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2 , osg::X_AXIS,
                               M_PI_2 , osg::Y_AXIS,
                               0.0    , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::leftView()
{
    osg::ref_ptr<osgGA::OrbitManipulator> manipulator =
            dynamic_cast<osgGA::OrbitManipulator*>(manager_cgi_->GetCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2 , osg::X_AXIS,
                               M_PI   , osg::Y_AXIS,
                               0.0    , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::rightView()
{
    osg::ref_ptr<osgGA::OrbitManipulator> manipulator =
            dynamic_cast<osgGA::OrbitManipulator*>(manager_cgi_->GetCameraManipulator());

    osg::Matrixd matrix = manipulator->getMatrix();

    osg::Quat quat = osg::Quat(M_PI_2 , osg::X_AXIS,
                               0.0    , osg::Y_AXIS,
                               0.0    , osg::X_AXIS);

    matrix.setRotate(quat);
    manipulator->setByMatrix(matrix);
}

void WidgetCGI::setCameraManipulatorOrbit()
{
    manager_cgi_->SetCameraManipulatorOrbit();
    getOsgViewer()->setCameraManipulator(manager_cgi_->GetCameraManipulator());
}

void WidgetCGI::setCameraManipulatorTrack()
{
    manager_cgi_->SetCameraManipulatorTrack();
    getOsgViewer()->setCameraManipulator(manager_cgi_->GetCameraManipulator());
}

void WidgetCGI::resizeEvent(QResizeEvent* event)
{
    ////////////////////////////
    QWidget::resizeEvent(event);
    ////////////////////////////

    manager_cgi_->SetWinHeight(event->size().height());
    manager_cgi_->SetWinWidth(event->size().width());
}

void WidgetCGI::timerEvent(QTimerEvent* event)
{
    ///////////////////////////
    QWidget::timerEvent(event);
    ///////////////////////////

    update();
    manager_cgi_->Update();
}

QWidget* WidgetCGI::addViewWidget()
{
    createCameras();

    setSceneData(manager_cgi_->GetNodeCGI());
    camera_hud_->addChild(manager_cgi_->GetNodeHUD());

    addEventHandler(new osgViewer::StatsHandler);
    setKeyEventSetsDone(0);
    assignSceneDataToCameras();

    return gwin_->getGLWidget();
}

void WidgetCGI::createCameras()
{
    camera_cgi_ = getOsgViewer()->getCamera();
    camera_hud_ = new osg::Camera();

    camera_cgi_->setGraphicsContext(gwin_);
    camera_hud_->setGraphicsContext(gwin_);

    osg::GraphicsContext* context = camera_cgi_->getGraphicsContext();
    camera_hud_->setGraphicsContext(context);

    const osg::GraphicsContext::Traits* traits = _camera->getGraphicsContext()->getTraits();

    double w2h = static_cast<double>(traits->width)
               / static_cast<double>(traits->height);

    camera_cgi_->setClearColor(osg::Vec4(0.47, 0.71, 1.0, 1.0));
    //camera_cgi_->setClearColor(osg::Vec4(0.216, 0.216, 0.216, 1.0));
    camera_cgi_->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    camera_cgi_->setProjectionMatrixAsPerspective(30.0, w2h, 0.1, 1000000.0);

    camera_hud_->setProjectionMatrixAsOrtho2D(-CGI_HUD_Y_2 * w2h, CGI_HUD_Y_2 * w2h, -CGI_HUD_Y_2, CGI_HUD_Y_2);
    camera_hud_->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera_hud_->setViewMatrix(osg::Matrix::identity());
    camera_hud_->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera_hud_->setRenderOrder(osg::Camera::POST_RENDER);
    camera_hud_->setAllowEventFocus(false);
    camera_hud_->setProjectionResizePolicy(osg::Camera::HORIZONTAL);
    camera_hud_->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));

    getOsgViewer()->addSlave(camera_hud_, false);
}
