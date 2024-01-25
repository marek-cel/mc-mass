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
#ifndef MC_MASS_GUI_RECENTFILEACTION_H_
#define MC_MASS_GUI_RECENTFILEACTION_H_

#include <QAction>

class RecentFileAction : public QAction
{
    Q_OBJECT

public:

    RecentFileAction(QString text, QObject* parent, int id = 0);

    inline void incrementId() { id_++; }

    inline void set_id(int id) { id_ = id; }

private:

    int id_ = 0;

signals:

    void triggered(int id);

private slots:

    void trigger();
};

#endif // MC_MASS_GUI_RECENTFILEACTION_H_
