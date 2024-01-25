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
#ifndef MC_MASS_CGI_DATA_H_
#define MC_MASS_CGI_DATA_H_

#include <QString>

namespace cgi {

struct Data
{

    double camera_w = 1.0;
    double camera_x = 0.0;
    double camera_y = 0.0;
    double camera_z = 0.0;

    int win_width  = 0;
    int win_height = 0;

    QString projectDir;
    QString modelFile;

    double offset_x = 0.0;
    double offset_y = 0.0;
    double offset_z = 0.0;

    double rotation_x = 0.0;
    double rotation_y = 0.0;
    double rotation_z = 0.0;

    double scale = 1.0;

    bool highlight = false;

    double highlight_x = 0.0;
    double highlight_y = 0.0;
    double highlight_z = 0.0;

    double highlight_l = 0.0;
    double highlight_w = 0.0;
    double highlight_h = 0.0;

    bool grid_visible = true;
};

} // namespace cgi

#endif // MC_MASS_CGI_DATA_H_
