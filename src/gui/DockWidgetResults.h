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
#ifndef MC_MASS_GUI_DOCKWIDGETRESULTS_H_
#define MC_MASS_GUI_DOCKWIDGETRESULTS_H_

#include <QDockWidget>
#include <QSettings>

#include <AircraftFile.h>

namespace Ui {
class DockWidgetResults;
}

class DockWidgetResults : public QDockWidget
{
    Q_OBJECT

public:

    explicit DockWidgetResults(AircraftFile* aircraftFile, QWidget *parent = nullptr);
    ~DockWidgetResults();

    void updateGUI();

private:

    Ui::DockWidgetResults* ui_;
    AircraftFile* aircraftFile_ = nullptr;
    Aircraft* aircraft_ = nullptr;

    void setEmptyMass();
    void setCenterOfMass();
    void setInertia();

    void settingsRead();
    void settingsRead_UnitsCombos(QSettings &settings);

    void settingsSave();
    void settingsSave_UnitsCombos(QSettings &settings);

private slots:

    void on_comboBox_Mass_currentIndexChanged(int index);
    void on_comboBox_CG_currentIndexChanged(int index);
    void on_comboBox_Inertia_currentIndexChanged(int index);
};

#endif // MC_MASS_GUI_DOCKWIDGETRESULTS_H_
