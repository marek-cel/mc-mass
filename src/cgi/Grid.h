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
#ifndef MC_MASS_CGI_GRID_H_
#define MC_MASS_CGI_GRID_H_

#include <osg/Switch>

#include <cgi/Component.h>

/** */
class Grid : public Component
{
public:

    static constexpr int kSize = 10;
    static constexpr int kStep = 1;

    Grid(std::shared_ptr<Data> data);

    void update() override;

private:

    osg::ref_ptr<osg::Switch> _switch;
    bool _grid_visible = true;

    void createGrid();
    void createGridAuxLines();
    void createGridMainLines();
};

#endif // MC_MASS_CGI_GRID_H_
