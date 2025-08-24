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
#ifndef MC_MASS_GUI_WIDGETCGI_H_
#define MC_MASS_GUI_WIDGETCGI_H_

#include <cgi/Manager.h>
#include <gui/WidgetOSG.h>

/**
 * @brief CGI widget class.
 */
class WidgetCGI : public WidgetOSG
{
    Q_OBJECT

public:

    explicit WidgetCGI(QWidget* parent = nullptr);
    virtual ~WidgetCGI();

    void updateGUI();

    cgi::Manager* getManagerCGI() { return _manager_cgi; }

    void resetView();
    void topView();
    void bottomView();
    void frontView();
    void backView();
    void leftView();
    void rightView();

    void setCameraManipulatorOrtho();

protected:

    void resizeEvent(QResizeEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

private:

    cgi::Manager* _manager_cgi = nullptr;

    osg::ref_ptr<osg::Camera> _camera_cgi;
    osg::ref_ptr<osg::Camera> _camera_hud;

    int _timerId = 0;

    QWidget* addViewWidget();

    void createCameras();
};

#endif // MC_MASS_GUI_WIDGETCGI_H_
