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

#include <gui/DockWidgetResults.h>
#include <ui_DockWidgetResults.h>

DockWidgetResults::DockWidgetResults(AircraftFile* aircraftFile, QWidget *parent)
    : QDockWidget(parent)
    , _ui(new Ui::DockWidgetResults)
    , _aircraftFile(aircraftFile)
{
    _ui->setupUi(this);

    _aircraft = _aircraftFile->GetAircraft();
    settingsRead();
}

DockWidgetResults::~DockWidgetResults()
{
    settingsSave();
    if ( _ui ) { delete _ui; } _ui = nullptr;
}

void DockWidgetResults::updateGUI()
{
    _ui->textResults->setText(_aircraft->ToString().c_str());

    setEmptyMass();
    setCenterOfMass();
    setInertia();
}

void DockWidgetResults::setEmptyMass()
{
    units::mass::kilogram_t me = _aircraft->GetTotalEmptyMass();
    _ui->spinBox_Mass->setValue(_ui->comboBox_Mass->convert(me()));
}

void DockWidgetResults::setCenterOfMass()
{
    units::length::meter_t cg_x = _aircraft->GetCenterOfMass().x();
    units::length::meter_t cg_y = _aircraft->GetCenterOfMass().y();
    units::length::meter_t cg_z = _aircraft->GetCenterOfMass().z();

    _ui->spinBox_CG_X->setValue(_ui->comboBox_CG->convert(cg_x()));
    _ui->spinBox_CG_Y->setValue(_ui->comboBox_CG->convert(cg_y()));
    _ui->spinBox_CG_Z->setValue(_ui->comboBox_CG->convert(cg_z()));
}

void DockWidgetResults::setInertia()
{
    units::moment_of_inertia::kilogram_square_meter_t i_xx = _aircraft->GetInertiaMatrix().ixx();
    units::moment_of_inertia::kilogram_square_meter_t i_xy = _aircraft->GetInertiaMatrix().ixy();
    units::moment_of_inertia::kilogram_square_meter_t i_xz = _aircraft->GetInertiaMatrix().ixz();

    units::moment_of_inertia::kilogram_square_meter_t i_yx = _aircraft->GetInertiaMatrix().iyx();
    units::moment_of_inertia::kilogram_square_meter_t i_yy = _aircraft->GetInertiaMatrix().iyy();
    units::moment_of_inertia::kilogram_square_meter_t i_yz = _aircraft->GetInertiaMatrix().iyz();

    units::moment_of_inertia::kilogram_square_meter_t i_zx = _aircraft->GetInertiaMatrix().izx();
    units::moment_of_inertia::kilogram_square_meter_t i_zy = _aircraft->GetInertiaMatrix().izy();
    units::moment_of_inertia::kilogram_square_meter_t i_zz = _aircraft->GetInertiaMatrix().izz();

    _ui->spinBox_I_XX->setValue(_ui->comboBox_Inertia->convert(i_xx()));
    _ui->spinBox_I_XY->setValue(_ui->comboBox_Inertia->convert(i_xy()));
    _ui->spinBox_I_XZ->setValue(_ui->comboBox_Inertia->convert(i_xz()));

    _ui->spinBox_I_YX->setValue(_ui->comboBox_Inertia->convert(i_yx()));
    _ui->spinBox_I_YY->setValue(_ui->comboBox_Inertia->convert(i_yy()));
    _ui->spinBox_I_YZ->setValue(_ui->comboBox_Inertia->convert(i_yz()));

    _ui->spinBox_I_ZX->setValue(_ui->comboBox_Inertia->convert(i_zx()));
    _ui->spinBox_I_ZY->setValue(_ui->comboBox_Inertia->convert(i_zy()));
    _ui->spinBox_I_ZZ->setValue(_ui->comboBox_Inertia->convert(i_zz()));
}

void DockWidgetResults::settingsRead()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("dock_results");
    settingsRead_UnitsCombos(settings);
    settings.endGroup();
}

void DockWidgetResults::settingsRead_UnitsCombos(QSettings& settings)
{
    settings.beginGroup("units_combos");

    _ui->comboBox_Mass->setCurrentIndex(settings.value("mass", 0).toInt());
    _ui->comboBox_CG->setCurrentIndex(settings.value("cg", 0).toInt());
    _ui->comboBox_Inertia->setCurrentIndex(settings.value("inertia", 0).toInt());

    settings.endGroup();
}

void DockWidgetResults::settingsSave()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("dock_results");
    settingsSave_UnitsCombos(settings);
    settings.endGroup();
}

void DockWidgetResults::settingsSave_UnitsCombos(QSettings& settings)
{
    settings.beginGroup("units_combos");

    settings.setValue("mass", _ui->comboBox_Mass->currentIndex());
    settings.setValue("cg", _ui->comboBox_CG->currentIndex());
    settings.setValue("inertia", _ui->comboBox_Inertia->currentIndex());

    settings.endGroup();
}

void DockWidgetResults::on_comboBox_Mass_currentIndexChanged(int /*index*/)
{
    setEmptyMass();
}

void DockWidgetResults::on_comboBox_CG_currentIndexChanged(int /*index*/)
{
    setCenterOfMass();
}

void DockWidgetResults::on_comboBox_Inertia_currentIndexChanged(int /*index*/)
{
    setInertia();
}

