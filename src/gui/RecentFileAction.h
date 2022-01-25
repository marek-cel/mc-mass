/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 ******************************************************************************/
#ifndef RECENTFILEACTION_H
#define RECENTFILEACTION_H

////////////////////////////////////////////////////////////////////////////////

#include <QAction>

////////////////////////////////////////////////////////////////////////////////

class RecentFileAction : public QAction
{
    Q_OBJECT

public:

    RecentFileAction( int id, QString text, QObject *parent );

private:

    int _id;

signals:

    void triggered( int id );

private slots:

    void trigger();
};

////////////////////////////////////////////////////////////////////////////////

#endif // RECENTFILEACTION_H
