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
    , ui_(new Ui::DockWidgetResults)
    , aircraftFile_(aircraftFile)
{
    ui_->setupUi(this);

    aircraft_ = aircraftFile_->GetAircraft();
    settingsRead();
}

DockWidgetResults::~DockWidgetResults()
{
    settingsSave();
    if ( ui_ ) { delete ui_; } ui_ = nullptr;
}

void DockWidgetResults::updateGUI()
{
    ui_->textResults->setText(aircraft_->ToString().c_str());

    setEmptyMass();
    setCenterOfMass();
    setInertia();
}

void DockWidgetResults::setEmptyMass()
{
    units::mass::kilogram_t me = aircraft_->GetTotalEmptyMass();
    ui_->spinBox_Mass->setValue(ui_->comboBox_Mass->convert(me()));
}

void DockWidgetResults::setCenterOfMass()
{
    units::length::meter_t cg_x = aircraft_->GetCenterOfMass().x();
    units::length::meter_t cg_y = aircraft_->GetCenterOfMass().y();
    units::length::meter_t cg_z = aircraft_->GetCenterOfMass().z();

    ui_->spinBox_CG_X->setValue(ui_->comboBox_CG->convert(cg_x()));
    ui_->spinBox_CG_Y->setValue(ui_->comboBox_CG->convert(cg_y()));
    ui_->spinBox_CG_Z->setValue(ui_->comboBox_CG->convert(cg_z()));
}

void DockWidgetResults::setInertia()
{
    units::moment_of_inertia::kilogram_square_meter_t i_xx = aircraft_->GetInertiaMatrix().ixx();
    units::moment_of_inertia::kilogram_square_meter_t i_xy = aircraft_->GetInertiaMatrix().ixy();
    units::moment_of_inertia::kilogram_square_meter_t i_xz = aircraft_->GetInertiaMatrix().ixz();

    units::moment_of_inertia::kilogram_square_meter_t i_yx = aircraft_->GetInertiaMatrix().iyx();
    units::moment_of_inertia::kilogram_square_meter_t i_yy = aircraft_->GetInertiaMatrix().iyy();
    units::moment_of_inertia::kilogram_square_meter_t i_yz = aircraft_->GetInertiaMatrix().iyz();

    units::moment_of_inertia::kilogram_square_meter_t i_zx = aircraft_->GetInertiaMatrix().izx();
    units::moment_of_inertia::kilogram_square_meter_t i_zy = aircraft_->GetInertiaMatrix().izy();
    units::moment_of_inertia::kilogram_square_meter_t i_zz = aircraft_->GetInertiaMatrix().izz();

    ui_->spinBox_I_XX->setValue(ui_->comboBox_Inertia->convert(i_xx()));
    ui_->spinBox_I_XY->setValue(ui_->comboBox_Inertia->convert(i_xy()));
    ui_->spinBox_I_XZ->setValue(ui_->comboBox_Inertia->convert(i_xz()));

    ui_->spinBox_I_YX->setValue(ui_->comboBox_Inertia->convert(i_yx()));
    ui_->spinBox_I_YY->setValue(ui_->comboBox_Inertia->convert(i_yy()));
    ui_->spinBox_I_YZ->setValue(ui_->comboBox_Inertia->convert(i_yz()));

    ui_->spinBox_I_ZX->setValue(ui_->comboBox_Inertia->convert(i_zx()));
    ui_->spinBox_I_ZY->setValue(ui_->comboBox_Inertia->convert(i_zy()));
    ui_->spinBox_I_ZZ->setValue(ui_->comboBox_Inertia->convert(i_zz()));
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

    ui_->comboBox_Mass->setCurrentIndex(settings.value("mass", 0).toInt());
    ui_->comboBox_CG->setCurrentIndex(settings.value("cg", 0).toInt());
    ui_->comboBox_Inertia->setCurrentIndex(settings.value("inertia", 0).toInt());

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

    settings.setValue("mass", ui_->comboBox_Mass->currentIndex());
    settings.setValue("cg", ui_->comboBox_CG->currentIndex());
    settings.setValue("inertia", ui_->comboBox_Inertia->currentIndex());

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

