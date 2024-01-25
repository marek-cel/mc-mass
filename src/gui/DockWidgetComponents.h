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
#ifndef MC_MASS_GUI_DOCKWIDGETCOMPONENTS_H_
#define MC_MASS_GUI_DOCKWIDGETCOMPONENTS_H_

#include <QDockWidget>

#include <AircraftFile.h>

namespace Ui {
class DockWidgetComponents;
}

class DockWidgetComponents : public QDockWidget
{
    Q_OBJECT

public:

    explicit DockWidgetComponents(AircraftFile* aircraftFile, QWidget *parent = nullptr);
    ~DockWidgetComponents();

    void updateGUI();

    int getCurrentComponentIndex() const { return currentComponentIndex_; }

signals:

    void aircraftChanged();

    void currentComponentChanged();

private:

    Ui::DockWidgetComponents* ui_;
    AircraftFile* aircraftFile_ = nullptr;
    Aircraft* aircraft_ = nullptr;

    int currentComponentIndex_ = -1;

    void addComponent();
    void editComponent();

private slots:

    void on_listComponents_currentRowChanged(int currentRow);
    void on_listComponents_doubleClicked(const QModelIndex &);

    void on_pushButtonAdd_clicked();
    void on_pushButtonDel_clicked();
    void on_pushButtonEdit_clicked();
};

#endif // MC_MASS_GUI_DOCKWIDGETCOMPONENTS_H_
