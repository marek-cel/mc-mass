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
    , _ui(new Ui::DialogEdit)
    , _component(component)
{
    _ui->setupUi(this);

    if ( _component )
    {
        _ui->lineEdit_Name->setText(_component->GetName());

        double m_kg = _component->GetMass()();
        _ui->spinBox_Mass->setValue(_ui->comboBox_Mass->convert(m_kg));

        double x_m = _component->GetPosition().x()();
        double y_m = _component->GetPosition().y()();
        double z_m = _component->GetPosition().z()();
        _ui->spinBox_X->setValue(_ui->comboBox_X->convert(x_m));
        _ui->spinBox_Y->setValue(_ui->comboBox_Y->convert(y_m));
        _ui->spinBox_Z->setValue(_ui->comboBox_Z->convert(z_m));

        double l_m = _component->GetLength()();
        double w_m = _component->GetWidth()();
        double h_m = _component->GetHeight()();
        _ui->spinBox_L->setValue(_ui->comboBox_L->convert(l_m));
        _ui->spinBox_W->setValue(_ui->comboBox_W->convert(w_m));
        _ui->spinBox_H->setValue(_ui->comboBox_H->convert(h_m));

        updateMass();
    }

    settingsRead();
}

DialogEdit::~DialogEdit()
{
    settingsSave();
    if ( _ui ) { delete _ui; } _ui = nullptr;
}

void DialogEdit::updateComponent(Component *component)
{
    if ( component )
    {
        component->SetName(_ui->lineEdit_Name->text().toStdString().c_str());

        double m_kg = _ui->comboBox_Mass->invert(_ui->spinBox_Mass->value());
        component->SetMass(units::mass::kilogram_t(m_kg));

        PositionVector position;

        double x_m = _ui->comboBox_X->invert(_ui->spinBox_X->value());
        double y_m = _ui->comboBox_Y->invert(_ui->spinBox_Y->value());
        double z_m = _ui->comboBox_Z->invert(_ui->spinBox_Z->value());
        position.x() = length::meter_t(x_m);
        position.y() = length::meter_t(y_m);
        position.z() = length::meter_t(z_m);

        component->SetPosition(position);

        double l_m = _ui->comboBox_L->invert(_ui->spinBox_L->value());
        double w_m = _ui->comboBox_W->invert(_ui->spinBox_W->value());
        double h_m = _ui->comboBox_H->invert(_ui->spinBox_H->value());
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

    _ui->comboBox_Mass->setCurrentIndex(settings.value("mass", 0).toInt());
    _ui->comboBox_X->setCurrentIndex(settings.value("x", 0).toInt());
    _ui->comboBox_Y->setCurrentIndex(settings.value("y", 0).toInt());
    _ui->comboBox_Z->setCurrentIndex(settings.value("z", 0).toInt());
    _ui->comboBox_L->setCurrentIndex(settings.value("l", 0).toInt());
    _ui->comboBox_W->setCurrentIndex(settings.value("w", 0).toInt());
    _ui->comboBox_H->setCurrentIndex(settings.value("h", 0).toInt());
    _ui->comboBox_EstimatedMass->setCurrentIndex(settings.value("h", 0).toInt());

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

    settings.setValue("mass", _ui->comboBox_Mass->currentIndex());
    settings.setValue("x", _ui->comboBox_X->currentIndex());
    settings.setValue("y", _ui->comboBox_Y->currentIndex());
    settings.setValue("z", _ui->comboBox_Z->currentIndex());
    settings.setValue("l", _ui->comboBox_L->currentIndex());
    settings.setValue("w", _ui->comboBox_W->currentIndex());
    settings.setValue("h", _ui->comboBox_H->currentIndex());
    settings.setValue("h", _ui->comboBox_EstimatedMass->currentIndex());

    settings.endGroup();
}

void DialogEdit::updateMass()
{
    units::mass::kilogram_t m_kg = _component->GetEstimatedMass();
    _ui->spinBoxEstimatedMass->setValue(m_kg());
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
    ComboUnits::switchUnits(_ui->spinBox_Mass, _ui->comboBox_Mass);
}


void DialogEdit::on_comboBox_X_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_X, _ui->comboBox_X);
}


void DialogEdit::on_comboBox_Y_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_Y, _ui->comboBox_Y);
}


void DialogEdit::on_comboBox_Z_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_Z, _ui->comboBox_Z);
}


void DialogEdit::on_comboBox_L_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_L, _ui->comboBox_L);
}


void DialogEdit::on_comboBox_W_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_W, _ui->comboBox_W);
}


void DialogEdit::on_comboBox_H_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_H, _ui->comboBox_H);
}


void DialogEdit::on_comboBox_EstimatedMass_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxEstimatedMass, _ui->comboBox_EstimatedMass);
}

