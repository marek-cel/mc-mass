/****************************************************************************//*
 * Copyright (C) 2022 Marek M. Cel
 *
 * This file is part of MC-Mass.
 *
 * MC-Mass is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MC-Mass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <gui/RecentFileAction.h>

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

RecentFileAction::RecentFileAction( int id, QString text, QObject *parent ) :
    QAction( text, parent )
{
    _id = id;
    connect( this, SIGNAL(triggered()), this, SLOT(trigger()) );
}

////////////////////////////////////////////////////////////////////////////////

void RecentFileAction::trigger()
{
    emit(triggered(_id));
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
