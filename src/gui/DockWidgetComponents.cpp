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

#include <gui/DockWidgetComponents.h>
#include <ui_DockWidgetComponents.h>

#include <gui/DialogEdit.h>

#include <mass/AllElse.h>
#include <mass/Engine.h>
#include <mass/Fuselage.h>
#include <mass/GearMain.h>
#include <mass/GearNose.h>
#include <mass/RotorDrive.h>
#include <mass/RotorHub.h>
#include <mass/RotorMain.h>
#include <mass/RotorTail.h>
#include <mass/TailHor.h>
#include <mass/TailVer.h>
#include <mass/Wing.h>

DockWidgetComponents::DockWidgetComponents(AircraftFile* aircraftFile, QWidget *parent)
    : QDockWidget(parent)
    , _ui(new Ui::DockWidgetComponents)
    , _aircraftFile(aircraftFile)
{
    _ui->setupUi(this);

    _aircraft = _aircraftFile->GetAircraft();
    updateGUI();
}

DockWidgetComponents::~DockWidgetComponents()
{
    if ( _ui ) { delete _ui; } _ui = nullptr;
}

void DockWidgetComponents::updateGUI()
{
    _ui->listComponents->clear();

    Aircraft::Components components = _aircraft->GetComponents();
    for ( auto component : components )
    {
        QString name = component->GetName();
        _ui->listComponents->addItem(new QListWidgetItem(name, _ui->listComponents));
    }

    if ( _previousComponentIndex >= 0 && _previousComponentIndex < _ui->listComponents->count() )
    {
        _ui->listComponents->setCurrentRow(_previousComponentIndex);
        _previousComponentIndex = -1;
    }
}

void DockWidgetComponents::addComponent()
{
    Component* component = nullptr;

    if ( _ui->comboBoxComponents->currentIndex() == 0 )
    {
        component = new Fuselage(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 1 )
    {
        component = new Wing(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 2 )
    {
        component = new TailHor(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 3 )
    {
        component = new TailVer(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 4 )
    {
        component = new GearMain(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 5 )
    {
        component = new GearNose(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 6 )
    {
        component = new Engine(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 7 )
    {
        component = new RotorDrive(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 8 )
    {
        component = new RotorHub(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 9 )
    {
        component = new RotorMain(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 10 )
    {
        component = new RotorTail(_aircraft->GetData());
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 11 )
    {
        component = new AllElse(_aircraft->GetData());
    }

    if ( component )
    {
        _aircraft->AddComponent(component);
        emit(aircraftChanged());
    }
}

void DockWidgetComponents::editComponent()
{
    int index = _ui->listComponents->currentRow();
    Component* component = _aircraft->GetComponent(index);
    if ( component )
    {
        if ( QDialog::Accepted == DialogEdit::edit(this, component) )
        {
            _aircraft->Update();
            _previousComponentIndex = index;
            emit(aircraftChanged());
        }
    }
}

void DockWidgetComponents::on_listComponents_currentRowChanged(int currentRow)
{
    _currentComponentIndex = currentRow;

    Aircraft::Components components = _aircraft->GetComponents();

    if ( currentRow >=0 && currentRow < static_cast<int>(components.size()) )
    {
        _ui->pushButtonDel  ->setEnabled(true);
        _ui->pushButtonEdit ->setEnabled(true);
    }
    else
    {
        _ui->pushButtonDel  ->setEnabled(false);
        _ui->pushButtonEdit ->setEnabled(false);
    }

    emit(currentComponentChanged());
}

void DockWidgetComponents::on_listComponents_doubleClicked(const QModelIndex&)
{
    editComponent();
}

void DockWidgetComponents::on_listComponents_itemSelectionChanged()
{
    QList<QListWidgetItem*> selectdItems = _ui->listComponents->selectedItems();
    if ( selectdItems.count() == 0 )
    {
        _currentComponentIndex = -1;
    }
    else
    {
        _currentComponentIndex = _ui->listComponents->currentRow();
    }

    emit(currentComponentChanged());
}

void DockWidgetComponents::on_pushButtonAdd_clicked()
{
    addComponent();
}

void DockWidgetComponents::on_pushButtonDel_clicked()
{
    Aircraft::Components components = _aircraft->GetComponents();
    int currentRow = _ui->listComponents->currentRow();

    if ( currentRow >=0 && currentRow < static_cast<int>(components.size()) )
    {
        _aircraft->DeleteComponent(currentRow);
    }

    emit(aircraftChanged());
}

void DockWidgetComponents::on_pushButtonEdit_clicked()
{
    editComponent();
}
