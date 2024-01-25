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
#ifndef MC_MASS_CGI_HIGHLIGHT_H_
#define MC_MASS_CGI_HIGHLIGHT_H_

#include <cgi/Component.h>

#include <osg/Switch>

namespace cgi
{

/** */
class Highlight : public Component
{
public:

    /** */
    Highlight(std::shared_ptr<Data> data);

    /** */
    virtual ~Highlight();

    virtual void Update() override;

private:

    osg::ref_ptr<osg::Switch> switch_;

    void RewriteHighlight(double x, double y, double z,
                          double l, double w, double h);
};

} // namespace cgi

#endif // MC_MASS_CGI_HIGHLIGHT_H_
