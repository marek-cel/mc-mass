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

#include <cgi/Highlight.h>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>

#include <cgi/Colors.h>

namespace cgi
{

Highlight::Highlight(std::shared_ptr<Data> data)
    : Component(data)
{
    switch_ = new osg::Switch();
    root_->addChild(switch_.get());
}

Highlight::~Highlight() {}

void Highlight::Update()
{
    if ( !data_.expired() )
    {
        std::shared_ptr<Data> data = data_.lock();

        if ( data->highlight )
        {
            switch_->setAllChildrenOn();
            RewriteHighlight(data->highlight_x,
                             data->highlight_y,
                             data->highlight_z,
                             data->highlight_l,
                             data->highlight_w,
                             data->highlight_h);
        }
        else
        {
            switch_->setAllChildrenOff();
        }
    }
}

void Highlight::RewriteHighlight(double x, double y, double z,
                                 double l, double w, double h)
{
    switch_->removeChildren(0, switch_->getNumChildren());

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    switch_->addChild(geode.get());

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();  // normals
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();  // colors
    osg::ref_ptr<osg::Vec3Array> p = new osg::Vec3Array();

    n->push_back(osg::Vec3(0.0, 0.0, 1.0));
    c->push_back(osg::Vec4(Colors::magenta, 1.0));

    p->push_back(osg::Vec3d(x - 0.5 * l, y - 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y - 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y + 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y + 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y - 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y - 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y + 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y + 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y - 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y + 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y - 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y + 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y - 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y + 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y - 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y + 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y - 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y - 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y + 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x - 0.5 * l, y + 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y - 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y - 0.5 * w, z + 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y + 0.5 * w, z - 0.5 * h));
    p->push_back(osg::Vec3d(x + 0.5 * l, y + 0.5 * w, z + 0.5 * h));

    geometry->setVertexArray(p.get());
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, p->size()));

    geometry->setNormalArray(n.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

    geometry->setColorArray( c.get() );
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

    geode->addDrawable(geometry.get());

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth();
    lineWidth->setWidth(2.0);

    stateSet->setAttributeAndModes(lineWidth, osg::StateAttribute::ON);
    stateSet->setMode(GL_LIGHTING   , osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    stateSet->setMode(GL_DEPTH_TEST , osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    stateSet->setRenderBinDetails(99, "DepthSortedBin");
}

} // namespace cgi
