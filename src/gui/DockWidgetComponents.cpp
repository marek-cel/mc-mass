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
    , ui_(new Ui::DockWidgetComponents)
    , aircraftFile_(aircraftFile)
{
    ui_->setupUi(this);

    aircraft_ = aircraftFile_->GetAircraft();
    updateGUI();
}

DockWidgetComponents::~DockWidgetComponents()
{
    if ( ui_ ) { delete ui_; } ui_ = nullptr;
}

void DockWidgetComponents::updateGUI()
{
    ui_->listComponents->clear();

    Aircraft::Components components = aircraft_->GetComponents();
    for ( auto component : components )
    {
        QString name = component->GetName();
        ui_->listComponents->addItem(new QListWidgetItem(name, ui_->listComponents));
    }
}

void DockWidgetComponents::addComponent()
{
    Component* component = nullptr;

    if ( ui_->comboBoxComponents->currentIndex() == 0 )
    {
        component = new Fuselage(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 1 )
    {
        component = new Wing(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 2 )
    {
        component = new TailHor(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 3 )
    {
        component = new TailVer(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 4 )
    {
        component = new GearMain(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 5 )
    {
        component = new GearNose(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 6 )
    {
        component = new Engine(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 7 )
    {
        component = new RotorDrive(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 8 )
    {
        component = new RotorHub(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 9 )
    {
        component = new RotorMain(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 10 )
    {
        component = new RotorTail(aircraft_->GetData());
    }
    else if ( ui_->comboBoxComponents->currentIndex() == 11 )
    {
        component = new AllElse(aircraft_->GetData());
    }

    if ( component )
    {
        aircraft_->AddComponent(component);
        emit(aircraftChanged());
    }
}

void DockWidgetComponents::editComponent()
{
    int index = ui_->listComponents->currentRow();
    Component* component = aircraft_->GetComponent(index);
    if ( component )
    {
        if ( QDialog::Accepted == DialogEdit::edit(this, component) )
        {
            aircraft_->Update();
            emit(aircraftChanged());
        }
    }
}

void DockWidgetComponents::on_listComponents_currentRowChanged(int currentRow)
{
    currentComponentIndex_ = currentRow;

    Aircraft::Components components = aircraft_->GetComponents();

    if ( currentRow >=0 && currentRow < static_cast<int>(components.size()) )
    {
        ui_->pushButtonDel  ->setEnabled(true);
        ui_->pushButtonEdit ->setEnabled(true);
    }
    else
    {
        ui_->pushButtonDel  ->setEnabled(false);
        ui_->pushButtonEdit ->setEnabled(false);
    }

    emit(currentComponentChanged());
}

void DockWidgetComponents::on_listComponents_doubleClicked(const QModelIndex&)
{
    editComponent();
}

void DockWidgetComponents::on_pushButtonAdd_clicked()
{
    addComponent();
}

void DockWidgetComponents::on_pushButtonDel_clicked()
{
    Aircraft::Components components = aircraft_->GetComponents();
    int currentRow = ui_->listComponents->currentRow();

    if ( currentRow >=0 && currentRow < static_cast<int>(components.size()) )
    {
        aircraft_->DeleteComponent(currentRow);
    }

    emit(aircraftChanged());
}

void DockWidgetComponents::on_pushButtonEdit_clicked()
{
    editComponent();
}
