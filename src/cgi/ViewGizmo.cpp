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

#include <cgi/ViewGizmo.h>

#include <osg/Billboard>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>

#include <cgi/Colors.h>

namespace cgi {

ViewGizmo::ViewGizmo(std::shared_ptr<Data> data)
    : Component(data)
{
    osg::ref_ptr<osg::StateSet> rootStateSet = root_->getOrCreateStateSet();
    rootStateSet->setMode(GL_LIGHT0   , osg::StateAttribute::OFF);
    rootStateSet->setMode(GL_LIGHT1   , osg::StateAttribute::OFF);
    rootStateSet->setMode(GL_LIGHTING , osg::StateAttribute::OFF);

    CreateGizmo();
}

void ViewGizmo::Update()
{
    ////////////////////
    Component::Update();
    ////////////////////

    if ( !data_.expired() )
    {
        std::shared_ptr<Data> data = data_.lock();

        osg::Quat q(data->camera_x,
                    data->camera_y,
                    data->camera_z,
                    data->camera_w);

        double w2h = static_cast<double>(data->win_width)
                   / static_cast<double>(data->win_height);

        double x = -w2h * CGI_HUD_Y_2 + offset_x_;
        double y = -CGI_HUD_Y_2 + offset_y_;

        q = q.inverse();

        pat_->setAttitude(q);
        pat_->setPosition(osg::Vec3d(x, y, 0.0));
    }
}

void ViewGizmo::CreateGizmo()
{
    pat_ = new osg::PositionAttitudeTransform();
    root_->addChild(pat_.get());

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    pat_->addChild(geode.get());

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();  // colors

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(size, 0.0, 0.0));
    c->push_back(osg::Vec4(Colors::red, 1.0));
    c->push_back(osg::Vec4(Colors::red, 1.0));

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(0.0, size, 0.0));
    c->push_back(osg::Vec4(Colors::lime, 1.0));
    c->push_back(osg::Vec4(Colors::lime, 1.0));

    v->push_back(osg::Vec3d(0.0, 0.0, 0.0));
    v->push_back(osg::Vec3d(0.0, 0.0, size));
    c->push_back(osg::Vec4(Colors::blue, 1.0));
    c->push_back(osg::Vec4(Colors::blue, 1.0));

    n->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    geometry->setVertexArray(v.get());
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, v->size()));
    geometry->setNormalArray(n.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geometry->setColorArray(c.get());
    geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    geode->addDrawable(geometry.get());

    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth();
    lineWidth->setWidth(2.0f);

    geode->getOrCreateStateSet()->setAttributeAndModes(lineWidth, osg::StateAttribute::ON);

//    double offset = size + 3.0;
//    CreateGizmoLabel(osg::Vec3d(offset, 0.0, 0.0), Colors::red  , "X", osgText::TextBase::YZ_PLANE);
//    CreateGizmoLabel(osg::Vec3d(0.0, offset, 0.0), Colors::lime , "Y", osgText::TextBase::XZ_PLANE);
//    CreateGizmoLabel(osg::Vec3d(0.0, 0.0, offset), Colors::blue , "Z", osgText::TextBase::XY_PLANE);

//    CreateGizmoLabel();
}

void ViewGizmo::CreateGizmoLabel(osg::Vec3d pos, osg::Vec3d color, const char* str,
                                 osgText::TextBase::AxisAlignment alignment)
{
    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    pat_->addChild(pat.get());

    pat->setPosition(pos);

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    pat->addChild(geode.get());

    osg::ref_ptr<osgText::Text> text = new osgText::Text();
    geode->addDrawable(text);

    text->setColor(osg::Vec4(color, 1.0));
    text->setCharacterSize(5.0f);
    text->setAxisAlignment(alignment);
    text->setPosition(osg::Vec3(0.0, 0.0, 0.0));
    text->setLayout(osgText::Text::LEFT_TO_RIGHT);
    text->setAlignment(osgText::Text::CENTER_CENTER);
    text->setText(str);
}

void ViewGizmo::CreateGizmoLabel()
{
    double offset = size + 3.0;

    osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
    pat_->addChild(pat.get());

    pat->setPosition(osg::Vec3d(offset, 0.0, 0.0));

    osg::ref_ptr<osg::Billboard> billboard = new osg::Billboard();
    pat->addChild(billboard.get());

    billboard->setMode(osg::Billboard::POINT_ROT_EYE);
    //billboard->setMode(osg::Billboard::POINT_ROT_WORLD);
    //billboard->setNormal(osg::Vec3f(0.0f, 0.0f, 1.0f));
    //billboard->setNormal(osg::Vec3f(0.0f, -1.0f, 0.0f));

    osg::ref_ptr<osgText::Text> text = new osgText::Text();
    billboard->addDrawable(text);

    text->setColor(osg::Vec4(Colors::black, 1.0));
    text->setCharacterSize(5.0f);
    //text->setAxisAlignment(osgText::TextBase::REVERSED_XZ_PLANE);
    text->setAxisAlignment(osgText::TextBase::REVERSED_YZ_PLANE);
    text->setPosition(osg::Vec3(0.0, 0.0, 0.0));
    text->setLayout(osgText::Text::LEFT_TO_RIGHT);
    text->setAlignment(osgText::Text::CENTER_CENTER);
    text->setText("X");
}

} // namespace cgi
