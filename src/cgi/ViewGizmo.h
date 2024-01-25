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
#ifndef MC_MASS_CGI_VIEWGIZMO_H_
#define MC_MASS_CGI_VIEWGIZMO_H_

#include <osg/PositionAttitudeTransform>
#include <osgText/Text>

#include <cgi/Component.h>

namespace cgi {

class ViewGizmo : public Component
{
public:

    static constexpr int offset_x_ = 15;
    static constexpr int offset_y_ = 15;

    static constexpr double size = 10.0;

    /**
     * @brief Constructor.
     * @param parent parent module
     */
    ViewGizmo(std::shared_ptr<Data> data);

    void Update() override;

private:

    osg::ref_ptr<osg::PositionAttitudeTransform> pat_;

    int x0_ = 0;
    int y0_ = 0;

    void CreateGizmo();
    void CreateGizmoLabel();
    void CreateGizmoLabel(osg::Vec3d pos, osg::Vec3d color, const char* str,
                          osgText::TextBase::AxisAlignment alignment);

};

} // namespace cgi

#endif // MC_MASS_CGI_VIEWGIZMO_H_
