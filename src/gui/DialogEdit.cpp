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

#include <gui/DialogEdit.h>
#include <ui_DialogEdit.h>

int DialogEdit::edit(QWidget* parent, Component* component)
{
    DialogEdit* dialog = new DialogEdit(parent, component);

    int result = dialog->exec();

    if ( result == QDialog::Accepted )
    {
        dialog->updateComponent(component);
    }

    if ( dialog ) { delete dialog; } dialog = nullptr;

    return result;
}

DialogEdit::DialogEdit(QWidget* parent, const Component* component)
    : QDialog(parent)
    , ui_(new Ui::DialogEdit)
    , component_(component)
{
    ui_->setupUi(this);

    if ( component_ )
    {
        ui_->lineEdit_Name->setText(component_->GetName());

        double m_kg = component_->GetMass()();
        ui_->spinBox_Mass->setValue(ui_->comboBox_Mass->convert(m_kg));

        double x_m = component_->GetPosition().x()();
        double y_m = component_->GetPosition().y()();
        double z_m = component_->GetPosition().z()();
        ui_->spinBox_X->setValue(ui_->comboBox_X->convert(x_m));
        ui_->spinBox_Y->setValue(ui_->comboBox_Y->convert(y_m));
        ui_->spinBox_Z->setValue(ui_->comboBox_Z->convert(z_m));

        double l_m = component_->GetLength()();
        double w_m = component_->GetWidth()();
        double h_m = component_->GetHeight()();
        ui_->spinBox_L->setValue(ui_->comboBox_L->convert(l_m));
        ui_->spinBox_W->setValue(ui_->comboBox_W->convert(w_m));
        ui_->spinBox_H->setValue(ui_->comboBox_H->convert(h_m));

        updateMass();
    }

    settingsRead();
}

DialogEdit::~DialogEdit()
{
    settingsSave();
    if ( ui_ ) { delete ui_; } ui_ = nullptr;
}

void DialogEdit::updateComponent(Component *component)
{
    if ( component )
    {
        component->SetName(ui_->lineEdit_Name->text().toStdString().c_str());

        double m_kg = ui_->comboBox_Mass->invert(ui_->spinBox_Mass->value());
        component->SetMass(units::mass::kilogram_t(m_kg));

        PositionVector position;

        double x_m = ui_->comboBox_X->invert(ui_->spinBox_X->value());
        double y_m = ui_->comboBox_Y->invert(ui_->spinBox_Y->value());
        double z_m = ui_->comboBox_Z->invert(ui_->spinBox_Z->value());
        position.x() = length::meter_t(x_m);
        position.y() = length::meter_t(y_m);
        position.z() = length::meter_t(z_m);

        component->SetPosition(position);

        double l_m = ui_->comboBox_L->invert(ui_->spinBox_L->value());
        double w_m = ui_->comboBox_W->invert(ui_->spinBox_W->value());
        double h_m = ui_->comboBox_H->invert(ui_->spinBox_H->value());
        component->SetLength(units::length::meter_t(l_m));
        component->SetWidth(units::length::meter_t(w_m));
        component->SetHeight(units::length::meter_t(h_m));
    }
}

void DialogEdit::settingsRead()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("dialog_edit");
    settingsRead_UnitsCombos(settings);
    settings.endGroup();
}

void DialogEdit::settingsRead_UnitsCombos(QSettings& settings)
{
    settings.beginGroup("units_combos");

    ui_->comboBox_Mass->setCurrentIndex(settings.value("mass", 0).toInt());
    ui_->comboBox_X->setCurrentIndex(settings.value("x", 0).toInt());
    ui_->comboBox_Y->setCurrentIndex(settings.value("y", 0).toInt());
    ui_->comboBox_Z->setCurrentIndex(settings.value("z", 0).toInt());
    ui_->comboBox_L->setCurrentIndex(settings.value("l", 0).toInt());
    ui_->comboBox_W->setCurrentIndex(settings.value("w", 0).toInt());
    ui_->comboBox_H->setCurrentIndex(settings.value("h", 0).toInt());
    ui_->comboBox_EstimatedMass->setCurrentIndex(settings.value("h", 0).toInt());

    settings.endGroup();
}

void DialogEdit::settingsSave()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("dialog_edit");
    settingsSave_UnitsCombos(settings);
    settings.endGroup();
}

void DialogEdit::settingsSave_UnitsCombos(QSettings& settings)
{
    settings.beginGroup("units_combos");

    settings.setValue("mass", ui_->comboBox_Mass->currentIndex());
    settings.setValue("x", ui_->comboBox_X->currentIndex());
    settings.setValue("y", ui_->comboBox_Y->currentIndex());
    settings.setValue("z", ui_->comboBox_Z->currentIndex());
    settings.setValue("l", ui_->comboBox_L->currentIndex());
    settings.setValue("w", ui_->comboBox_W->currentIndex());
    settings.setValue("h", ui_->comboBox_H->currentIndex());
    settings.setValue("h", ui_->comboBox_EstimatedMass->currentIndex());

    settings.endGroup();
}

void DialogEdit::updateMass()
{
    units::mass::kilogram_t m_kg = component_->GetEstimatedMass();
    ui_->spinBoxEstimatedMass->setValue(m_kg());
}

void DialogEdit::on_spinBox_X_valueChanged(double /*arg1*/)
{
    updateMass();
}

void DialogEdit::on_spinBox_Y_valueChanged(double /*arg1*/)
{
    updateMass();
}

void DialogEdit::on_spinBox_Z_valueChanged(double /*arg1*/)
{
    updateMass();
}

void DialogEdit::on_spinBox_L_valueChanged(double /*arg1*/)
{
    updateMass();
}

void DialogEdit::on_spinBox_W_valueChanged(double /*arg1*/)
{
    updateMass();
}

void DialogEdit::on_spinBox_H_valueChanged(double /*arg1*/)
{
    updateMass();
}

void DialogEdit::on_comboBox_Mass_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_Mass, ui_->comboBox_Mass);
}


void DialogEdit::on_comboBox_X_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_X, ui_->comboBox_X);
}


void DialogEdit::on_comboBox_Y_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_Y, ui_->comboBox_Y);
}


void DialogEdit::on_comboBox_Z_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_Z, ui_->comboBox_Z);
}


void DialogEdit::on_comboBox_L_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_L, ui_->comboBox_L);
}


void DialogEdit::on_comboBox_W_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_W, ui_->comboBox_W);
}


void DialogEdit::on_comboBox_H_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_H, ui_->comboBox_H);
}


void DialogEdit::on_comboBox_EstimatedMass_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxEstimatedMass, ui_->comboBox_EstimatedMass);
}

