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
#ifndef MC_MASS_GUI_DIALOGEDIT_H_
#define MC_MASS_GUI_DIALOGEDIT_H_

#include <QDialog>
#include <QSettings>

#include <mass/Component.h>

namespace Ui {
    class DialogEdit;
}

class DialogEdit : public QDialog
{
    Q_OBJECT

public:

    static int edit(QWidget* parent, Component* component);

    explicit DialogEdit(QWidget* parent = nullptr, const Component* component = nullptr);

    virtual ~DialogEdit();

    void updateComponent(Component* comp);

private:

    Ui::DialogEdit *ui_;            ///<

    const Component *component_;    ///<

    void settingsRead();
    void settingsRead_UnitsCombos(QSettings &settings);

    void settingsSave();
    void settingsSave_UnitsCombos(QSettings &settings);

    void updateMass();

private slots:

    void on_spinBox_X_valueChanged(double arg1);
    void on_spinBox_Y_valueChanged(double arg1);
    void on_spinBox_Z_valueChanged(double arg1);
    void on_spinBox_L_valueChanged(double arg1);
    void on_spinBox_W_valueChanged(double arg1);
    void on_spinBox_H_valueChanged(double arg1);

    void on_comboBox_Mass_currentIndexChanged(int index);
    void on_comboBox_X_currentIndexChanged(int index);
    void on_comboBox_Y_currentIndexChanged(int index);
    void on_comboBox_Z_currentIndexChanged(int index);
    void on_comboBox_L_currentIndexChanged(int index);
    void on_comboBox_W_currentIndexChanged(int index);
    void on_comboBox_H_currentIndexChanged(int index);
    void on_comboBox_EstimatedMass_currentIndexChanged(int index);
};

#endif // MC_MASS_GUI_DIALOGEDIT_H_
