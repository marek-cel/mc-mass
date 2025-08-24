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
#ifndef MC_MASS_CGI_VIEWGIZMO_H_
#define MC_MASS_CGI_VIEWGIZMO_H_

#include <osg/PositionAttitudeTransform>
#include <osgText/Text>

#include <cgi/Component.h>

namespace cgi {

class ViewGizmo : public Component
{
public:

    static constexpr int kOffset_x = 15;
    static constexpr int kOffset_y = 15;

    static constexpr double kSize = 10.0;

    ViewGizmo(std::shared_ptr<Data> data);

    void update() override;

private:

    osg::ref_ptr<osg::PositionAttitudeTransform> _pat;

    int _x0 = 0;
    int _y0 = 0;

    void createGizmo();
    void createGizmoLabel();
    void createGizmoLabel(osg::Vec3d pos, osg::Vec3d color, const char* str,
                          osgText::TextBase::AxisAlignment alignment);

};

} // namespace cgi

#endif // MC_MASS_CGI_VIEWGIZMO_H_
