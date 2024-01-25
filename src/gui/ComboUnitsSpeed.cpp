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

#include <gui/ComboUnitsSpeed.h>

#include <units.h>

using namespace units::literals;

ComboUnitsSpeed::ComboUnitsSpeed(QWidget* parent)
    : ComboUnits(parent)
{
    coefs_.push_back(1.0);
    names_.push_back(QString(tr("kts")));

    coefs_.push_back(1_kts / 1_kph);
    names_.push_back(QString(tr("km/h")));

    for ( int i = 0; i < names_.size(); i++ )
    {
        addItem(names_[i]);
    }
}
