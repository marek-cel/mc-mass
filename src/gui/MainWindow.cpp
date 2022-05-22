/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
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

#include <gui/MainWindow.h>
#include <ui_MainWindow.h>

#include <cmath>

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

#include <gui/DialogEdit.h>

#include <components/AllElse.h>
#include <components/Engine.h>
#include <components/Fuselage.h>
#include <components/GearMain.h>
#include <components/GearNose.h>
#include <components/RotorDrive.h>
#include <components/RotorHub.h>
#include <components/RotorMain.h>
#include <components/RotorTail.h>
#include <components/TailHor.h>
#include <components/TailVer.h>
#include <components/Wing.h>

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow ),

    _saved ( true )
{
    _ui->setupUi( this );

    _ui->textResults->setFontFamily( "Monospace" );

    _scSave   = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_triggered())   );
    _scExport = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_E), this, SLOT(on_actionExport_triggered()) );

    setAircraftType( AircraftData::FighterAttack );
    updateGUI();

    settingsRead();

    _saved = true;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    settingsSave();

    DELPTR( _scSave   );
    DELPTR( _scExport );

    DELPTR( _ui );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::closeEvent( QCloseEvent *event )
{
    askIfSave();

    /////////////////////////////////
    QMainWindow::closeEvent( event );
    /////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::askIfSave()
{
    if ( !_saved )
    {
        QString title = windowTitle();
        QString text = tr( "File have unsaved changes." );

        QMessageBox::StandardButton result = QMessageBox::question( this, title, text,
                                                                    QMessageBox::Save | QMessageBox::Discard,
                                                                    QMessageBox::Save );

        if ( result == QMessageBox::Save )
        {
            saveFile();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::newFile()
{
    askIfSave();

    _currentFile = "";

    _dataFile.newEmpty();

    updateGUI();
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::openFile()
{
    askIfSave();

    QString caption = "Open...";
    QString dir = ( _currentFile.length() > 0 ) ? QFileInfo( _currentFile ).absolutePath() : "";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "XML (*.xml)";

    QString file = QFileDialog::getOpenFileName( this, caption, dir, filter, &selectedFilter );

    if ( file.length() > 0 )
    {
        _currentFile = file;

        updateRecentFiles( _currentFile );
        readFile( _currentFile );
    }

    updateGUI();
    _saved = true;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::saveFile()
{
    if ( _currentFile.length() > 0 )
    {
        saveFile( _currentFile );
    }
    else
    {
        saveFileAs();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::saveFileAs()
{
    QString caption = "Save as...";
    QString dir = ( _currentFile.length() > 0 ) ? QFileInfo( _currentFile ).absolutePath() : ".";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "XML (*.xml)";

    QString newFile = QFileDialog::getSaveFileName( this, caption, dir, filter, &selectedFilter );

    if ( newFile.length() > 0 )
    {
        _currentFile = newFile;
        saveFile( _currentFile );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::exportFileAs()
{
    QString fileName = "";

    QString caption = "Export as...";
    QString dir = ( fileName.length() > 0 ) ? QFileInfo( fileName ).absolutePath() : ".";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "Text File (*.txt)";

    fileName = QFileDialog::getSaveFileName( this, caption, dir, filter, &selectedFilter );

    if ( fileName.length() > 0 )
    {
        exportAs( fileName );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::readFile( QString fileName )
{
    if ( QFileInfo( fileName ).suffix() == QString( "xml" ) )
    {
        if ( !_dataFile.readFile( fileName.toStdString().c_str() ) )
        {
            QMessageBox::warning( this, tr( APP_TITLE ),
                                 tr( "Cannot read file %1." ).arg( fileName ) );
        }
    }

    updateGUI();
    _saved = true;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::saveFile( QString fileName )
{
    if ( _dataFile.saveFile( fileName.toStdString().c_str() ) )
    {
        _saved = true;
    }
    else
    {
        QMessageBox::warning( this, tr( APP_TITLE ),
                             tr( "Cannot save file %1." ).arg(fileName) );
    }

    updateGUI();
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::exportAs( QString fileName )
{
    if ( !_dataFile.exportAs( fileName.toStdString().c_str() ) )
    {
        QMessageBox::warning( this, tr( APP_TITLE ),
                             tr( "Cannot export file %1." ).arg(fileName) );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsRead()
{
    QSettings settings( ORG_NAME, APP_NAME );
    
    settings.beginGroup( "main_window" );

    restoreState( settings.value( "state" ).toByteArray() );
    restoreGeometry( settings.value( "geometry" ).toByteArray() );

    settingsRead_RecentFiles( settings );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsRead_RecentFiles( QSettings &settings )
{
    _recentFilesList = settings.value( "recent_files" ).toStringList();

    updateRecentFiles();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsSave()
{
    QSettings settings( ORG_NAME, APP_NAME );
    
    settings.beginGroup( "main_window" );

    settings.setValue( "state", saveState() );
    settings.setValue( "geometry", saveGeometry() );

    settingsSave_RecentFiles( settings );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsSave_RecentFiles( QSettings &settings )
{
    settings.setValue( "recent_files", _recentFilesList );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::addComponent()
{
    Component *component = 0;

    if ( _ui->comboBoxComponents->currentIndex() == 0 )
    {
        component = new Fuselage( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 1 )
    {
        component = new Wing( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 2 )
    {
        component = new TailHor( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 3 )
    {
        component = new TailVer( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 4 )
    {
        component = new GearMain( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 5 )
    {
        component = new GearNose( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 6 )
    {
        component = new Engine( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 7 )
    {
        component = new RotorDrive( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 8 )
    {
        component = new RotorHub( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 9 )
    {
        component = new RotorMain( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 10 )
    {
        component = new RotorTail( _dataFile.getAircraftData() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 11 )
    {
        component = new AllElse( _dataFile.getAircraftData() );
    }

    if ( component )
    {
        _dataFile.getAircraft()->addComponent( component );
        _saved = false;
    }

    updateGUI();
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::editComponent()
{
    int index = _ui->listComponents->currentRow();

    Component *component = _dataFile.getAircraft()->getComponent( index );

    if ( component )
    {
        DialogEdit::edit( this, component );

        _dataFile.getAircraft()->update();

        _saved = false;

        updateGUI();
        updateTitleBar();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::setAircraftType( AircraftData::Type type )
{
    // data - general
    _ui->labelMassEmpty   ->setEnabled( false );
    _ui->labelMTOW        ->setEnabled( false );
    _ui->labelMassMaxLand ->setEnabled( false );
    _ui->labelMaxNz       ->setEnabled( false );
    _ui->labelMaxNzLand   ->setEnabled( false );
    _ui->labelStallV      ->setEnabled( false );
    _ui->labelCruiseH     ->setEnabled( false );
    _ui->labelCruiseV     ->setEnabled( false );
    _ui->labelMachMax     ->setEnabled( false );

    _ui->spinBoxMassEmpty   ->setEnabled( false );
    _ui->spinBoxMTOW        ->setEnabled( false );
    _ui->spinBoxMassMaxLand ->setEnabled( false );
    _ui->spinBoxMaxNz       ->setEnabled( false );
    _ui->spinBoxMaxNzLand   ->setEnabled( false );
    _ui->spinBoxStallV      ->setEnabled( false );
    _ui->spinBoxCruiseH     ->setEnabled( false );
    _ui->spinBoxCruiseV     ->setEnabled( false );
    _ui->spinBoxMachMax     ->setEnabled( false );

    _ui->checkBoxNavyAircraft->setEnabled( false );

    // data - fuselage
    _ui->comboBoxCargoDoor->setEnabled( false );

    _ui->labelFuseLength ->setEnabled( false );
    _ui->labelFuseHeight ->setEnabled( false );
    _ui->labelFuseWidth  ->setEnabled( false );
    _ui->labelNoseLength ->setEnabled( false );

    _ui->spinBoxFuseLength ->setEnabled( false );
    _ui->spinBoxFuseHeight ->setEnabled( false );
    _ui->spinBoxFuseWidth  ->setEnabled( false );
    _ui->spinBoxNoseLength ->setEnabled( false );

    _ui->spinBoxWettedAreaEstimated ->setEnabled( false );
    _ui->spinBoxWettedAreaReal      ->setEnabled( false );
    _ui->spinBoxPressVol   ->setEnabled( false );

    _ui->labelCargoDoor->setEnabled( false );

    _ui->labelWettedAreaEstimated ->setEnabled( false );
    _ui->labelWettedAreaReal      ->setEnabled( false );
    _ui->labelPressVol   ->setEnabled( false );

    _ui->checkBoxFuselageLG->setEnabled( false );
    _ui->checkBoxCargoRamp->setEnabled( false );
    _ui->checkBoxWettedAreaOverride->setEnabled( false );

    // data - wing
    _ui->labelWingArea    ->setEnabled( false );
    _ui->labelWingAreaExp ->setEnabled( false );
    _ui->labelWingSpan    ->setEnabled( false );
    _ui->labelWingSweep   ->setEnabled( false );
    _ui->labelWingCRoot   ->setEnabled( false );
    _ui->labelWingCTip    ->setEnabled( false );
    _ui->labelWingTC      ->setEnabled( false );
    _ui->labelWingFuel    ->setEnabled( false );
    _ui->labelCtrlArea    ->setEnabled( false );
    _ui->labelWingAR      ->setEnabled( false );
    _ui->labelWingTR      ->setEnabled( false );

    _ui->spinBoxWingArea    ->setEnabled( false );
    _ui->spinBoxWingAreaExp ->setEnabled( false );
    _ui->spinBoxWingSpan    ->setEnabled( false );
    _ui->spinBoxWingSweep   ->setEnabled( false );
    _ui->spinBoxWingCRoot   ->setEnabled( false );
    _ui->spinBoxWingCTip    ->setEnabled( false );
    _ui->spinBoxWingTC      ->setEnabled( false );
    _ui->spinBoxWingFuel    ->setEnabled( false );
    _ui->spinBoxCtrlArea    ->setEnabled( false );
    _ui->spinBoxWingAR      ->setEnabled( false );
    _ui->spinBoxWingTR      ->setEnabled( false );

    _ui->checkBoxWingDelta    ->setEnabled( false );
    _ui->checkBoxWingVarSweep ->setEnabled( false );

    // data - horizontal tail
    _ui->labelHorTailArea  ->setEnabled( false );
    _ui->labelHorTailSpan  ->setEnabled( false );
    _ui->labelHorTailSweep ->setEnabled( false );
    _ui->labelHorTailCRoot ->setEnabled( false );
    _ui->labelHorTailCTip  ->setEnabled( false );
    _ui->labelHorTailTC    ->setEnabled( false );
    _ui->labelElevArea     ->setEnabled( false );
    _ui->labelHorTailWF    ->setEnabled( false );
    _ui->labelHorTailArm   ->setEnabled( false );
    _ui->labelHorTailAR    ->setEnabled( false );
    _ui->labelHorTailTR    ->setEnabled( false );

    _ui->spinBoxHorTailArea  ->setEnabled( false );
    _ui->spinBoxHorTailSpan  ->setEnabled( false );
    _ui->spinBoxHorTailSweep ->setEnabled( false );
    _ui->spinBoxHorTailCRoot ->setEnabled( false );
    _ui->spinBoxHorTailCTip  ->setEnabled( false );
    _ui->spinBoxHorTailTC    ->setEnabled( false );
    _ui->spinBoxElevArea     ->setEnabled( false );
    _ui->spinBoxHorTailWF    ->setEnabled( false );
    _ui->spinBoxHorTailArm   ->setEnabled( false );
    _ui->spinBoxHorTailAR    ->setEnabled( false );
    _ui->spinBoxHorTailTR    ->setEnabled( false );

    _ui->checkBoxHorTailMoving  ->setEnabled( false );
    _ui->checkBoxHorTailRolling ->setEnabled( false );

    // data - vertical tail
    _ui->labelVerTailArea   ->setEnabled( false );
    _ui->labelVerTailHeight ->setEnabled( false );
    _ui->labelVerTailSweep  ->setEnabled( false );
    _ui->labelVerTailCRoot  ->setEnabled( false );
    _ui->labelVerTailCTip   ->setEnabled( false );
    _ui->labelVerTailTC     ->setEnabled( false );
    _ui->labelVerTailArm    ->setEnabled( false );
    _ui->labelRuddArea      ->setEnabled( false );
    _ui->labelVerTailAR     ->setEnabled( false );
    _ui->labelVerTailTR     ->setEnabled( false );

    _ui->spinBoxVerTailArea   ->setEnabled( false );
    _ui->spinBoxVerTailHeight ->setEnabled( false );
    _ui->spinBoxVerTailSweep  ->setEnabled( false );
    _ui->spinBoxVerTailCRoot  ->setEnabled( false );
    _ui->spinBoxVerTailCTip   ->setEnabled( false );
    _ui->spinBoxVerTailTC     ->setEnabled( false );
    _ui->spinBoxVerTailArm    ->setEnabled( false );
    _ui->spinBoxRuddArea      ->setEnabled( false );
    _ui->spinBoxVerTailAR     ->setEnabled( false );
    _ui->spinBoxVerTailTR     ->setEnabled( false );

    _ui->checkBoxTailT        ->setEnabled( false );
    _ui->checkBoxVerTailRotor ->setEnabled( false );

    // data - landing gear
    _ui->labelMainGearLength ->setEnabled( false );
    _ui->labelNoseGearLength ->setEnabled( false );

    _ui->labelMainGearWheels ->setEnabled( false );
    _ui->labelMainGearStruts ->setEnabled( false );
    _ui->labelNoseGearWheels ->setEnabled( false );

    _ui->spinBoxMainGearLength ->setEnabled( false );
    _ui->spinBoxNoseGearLength ->setEnabled( false );

    _ui->spinBoxMainGearWheels ->setEnabled( false );
    _ui->spinBoxMainGearStruts ->setEnabled( false );
    _ui->spinBoxNoseGearWheels ->setEnabled( false );

    _ui->checkBoxGearFixed  ->setEnabled( false );
    _ui->checkBoxGearCross  ->setEnabled( false );
    _ui->checkBoxGearTripod ->setEnabled( false );

    _ui->checkBoxGearMainKneel ->setEnabled( false );
    _ui->checkBoxGearNoseKneel ->setEnabled( false );

    // data - rotors
    _ui->labelMainRotorDiameter  ->setEnabled( false );
    _ui->labelMainRotorChord     ->setEnabled( false );
    _ui->labelMainRotorRPM       ->setEnabled( false );
    _ui->labelTailRotorDiameter  ->setEnabled( false );
    _ui->labelMainRotorGear      ->setEnabled( false );
    _ui->labelPowerLimit         ->setEnabled( false );
    _ui->labelMainRotorTipVel    ->setEnabled( false );
    _ui->labelMainRotorBlades    ->setEnabled( false );

    _ui->spinBoxMainRotorDiameter  ->setEnabled( false );
    _ui->spinBoxMainRotorChord     ->setEnabled( false );
    _ui->spinBoxMainRotorRPM       ->setEnabled( false );
    _ui->spinBoxTailRotorDiameter  ->setEnabled( false );
    _ui->spinBoxMainRotorGear      ->setEnabled( false );
    _ui->spinBoxPowerLimit         ->setEnabled( false );
    _ui->spinBoxMainRotorTipVel    ->setEnabled( false );
    _ui->spinBoxMainRotorBlades    ->setEnabled( false );

    if ( type == AircraftData::Helicopter )
    {
        // data - general
        _ui->labelMassEmpty   ->setEnabled( true );
        _ui->labelMTOW        ->setEnabled( true );
        _ui->labelMaxNz       ->setEnabled( true );
        _ui->labelMaxNzLand   ->setEnabled( true );

        _ui->spinBoxMassEmpty   ->setEnabled( true );
        _ui->spinBoxMTOW        ->setEnabled( true );
        _ui->spinBoxMaxNz       ->setEnabled( true );
        _ui->spinBoxMaxNzLand   ->setEnabled( true );

        // data - fuselage
        _ui->labelFuseLength ->setEnabled( true );
        _ui->labelFuseHeight ->setEnabled( true );
        _ui->labelFuseWidth  ->setEnabled( true );
        _ui->labelNoseLength ->setEnabled( true );

        _ui->spinBoxFuseLength ->setEnabled( true );
        _ui->spinBoxFuseHeight ->setEnabled( true );
        _ui->spinBoxFuseWidth  ->setEnabled( true );
        _ui->spinBoxNoseLength ->setEnabled( true );

        _ui->labelWettedAreaEstimated ->setEnabled( true );

        _ui->spinBoxWettedAreaEstimated ->setEnabled( true );

        _ui->checkBoxCargoRamp->setEnabled( true );
        _ui->checkBoxWettedAreaOverride->setEnabled( true );

        // data - horizontal tail
        _ui->labelHorTailArea ->setEnabled( true );
        _ui->labelHorTailSpan ->setEnabled( true );
        _ui->labelHorTailAR   ->setEnabled( true );

        _ui->spinBoxHorTailArea ->setEnabled( true );
        _ui->spinBoxHorTailSpan ->setEnabled( true );
        _ui->spinBoxHorTailAR   ->setEnabled( true );

        // data - vertical tail
        _ui->labelVerTailArea   ->setEnabled( true );
        _ui->labelVerTailHeight ->setEnabled( true );
        _ui->labelVerTailAR     ->setEnabled( true );

        _ui->spinBoxVerTailArea   ->setEnabled( true );
        _ui->spinBoxVerTailHeight ->setEnabled( true );
        _ui->spinBoxVerTailAR     ->setEnabled( true );

        _ui->checkBoxVerTailRotor ->setEnabled( true );

        // data - rotors
        _ui->labelMainRotorDiameter  ->setEnabled( true );
        _ui->labelMainRotorChord     ->setEnabled( true );
        _ui->labelMainRotorRPM       ->setEnabled( true );
        _ui->labelTailRotorDiameter  ->setEnabled( true );
        _ui->labelMainRotorGear      ->setEnabled( true );
        _ui->labelPowerLimit         ->setEnabled( true );
        _ui->labelMainRotorTipVel    ->setEnabled( true );
        _ui->labelMainRotorBlades    ->setEnabled( true );

        _ui->spinBoxMainRotorDiameter  ->setEnabled( true );
        _ui->spinBoxMainRotorChord     ->setEnabled( true );
        _ui->spinBoxMainRotorRPM       ->setEnabled( true );
        _ui->spinBoxTailRotorDiameter  ->setEnabled( true );
        _ui->spinBoxMainRotorGear      ->setEnabled( true );
        _ui->spinBoxPowerLimit         ->setEnabled( true );
        _ui->spinBoxMainRotorTipVel    ->setEnabled( true );
        _ui->spinBoxMainRotorBlades    ->setEnabled( true );
    }
    else
    {
        // data - general
        _ui->labelMassEmpty   ->setEnabled( true );
        _ui->labelMTOW        ->setEnabled( true );
        _ui->labelMassMaxLand ->setEnabled( true );
        _ui->labelMaxNz       ->setEnabled( true );
        _ui->labelMaxNzLand   ->setEnabled( true );

        _ui->spinBoxMassEmpty   ->setEnabled( true );
        _ui->spinBoxMTOW        ->setEnabled( true );
        _ui->spinBoxMassMaxLand ->setEnabled( true );
        _ui->spinBoxMaxNz       ->setEnabled( true );
        _ui->spinBoxMaxNzLand   ->setEnabled( true );

        // data - fuselage
        _ui->labelFuseLength ->setEnabled( true );
        _ui->labelFuseHeight ->setEnabled( true );
        _ui->labelFuseWidth  ->setEnabled( true );
        _ui->labelNoseLength ->setEnabled( true );

        _ui->spinBoxFuseLength ->setEnabled( true );
        _ui->spinBoxFuseHeight ->setEnabled( true );
        _ui->spinBoxFuseWidth  ->setEnabled( true );
        _ui->spinBoxNoseLength ->setEnabled( true );

        _ui->labelWettedAreaEstimated ->setEnabled( true );

        _ui->spinBoxWettedAreaEstimated ->setEnabled( true );

        _ui->checkBoxWettedAreaOverride->setEnabled( true );

        // data - wing
        _ui->labelWingArea    ->setEnabled( true );
        _ui->labelWingAreaExp ->setEnabled( true );
        _ui->labelWingSpan    ->setEnabled( true );
        _ui->labelWingSweep   ->setEnabled( true );
        _ui->labelWingCRoot   ->setEnabled( true );
        _ui->labelWingCTip    ->setEnabled( true );
        _ui->labelWingTC      ->setEnabled( true );
        _ui->labelWingAR      ->setEnabled( true );
        _ui->labelWingTR      ->setEnabled( true );

        _ui->spinBoxWingArea    ->setEnabled( true );
        _ui->spinBoxWingAreaExp ->setEnabled( true );
        _ui->spinBoxWingSpan    ->setEnabled( true );
        _ui->spinBoxWingSweep   ->setEnabled( true );
        _ui->spinBoxWingCRoot   ->setEnabled( true );
        _ui->spinBoxWingCTip    ->setEnabled( true );
        _ui->spinBoxWingTC      ->setEnabled( true );
        _ui->spinBoxWingAR      ->setEnabled( true );
        _ui->spinBoxWingTR      ->setEnabled( true );

        // data - horizontal tail
        _ui->labelHorTailArea ->setEnabled( true );
        _ui->labelHorTailAR   ->setEnabled( true );
        _ui->labelHorTailTR   ->setEnabled( true );

        _ui->spinBoxHorTailArea ->setEnabled( true );
        _ui->spinBoxHorTailAR   ->setEnabled( true );
        _ui->spinBoxHorTailTR   ->setEnabled( true );

        // data - vertical tail
        _ui->labelVerTailArea   ->setEnabled( true );
        _ui->labelVerTailHeight ->setEnabled( true );
        _ui->labelVerTailSweep  ->setEnabled( true );
        _ui->labelVerTailAR     ->setEnabled( true );
        _ui->labelVerTailTR     ->setEnabled( true );

        _ui->spinBoxVerTailArea   ->setEnabled( true );
        _ui->spinBoxVerTailHeight ->setEnabled( true );
        _ui->spinBoxVerTailSweep  ->setEnabled( true );
        _ui->spinBoxVerTailAR     ->setEnabled( true );
        _ui->spinBoxVerTailTR     ->setEnabled( true );

        _ui->checkBoxTailT->setEnabled( true );

        // data - landing gear
        _ui->labelMainGearLength ->setEnabled( true );
        _ui->labelNoseGearLength ->setEnabled( true );

        _ui->spinBoxMainGearLength ->setEnabled( true );
        _ui->spinBoxNoseGearLength ->setEnabled( true );

        _ui->checkBoxGearFixed  ->setEnabled( true );

        if ( type == AircraftData::FighterAttack )
        {
            // data - general
            _ui->labelMachMax->setEnabled( true );

            _ui->spinBoxMachMax->setEnabled( true );

            _ui->checkBoxNavyAircraft->setEnabled( true );

            // data - wing
            _ui->labelCtrlArea  ->setEnabled( true );

            _ui->spinBoxCtrlArea  ->setEnabled( true );

            _ui->checkBoxWingDelta    ->setEnabled( true );
            _ui->checkBoxWingVarSweep ->setEnabled( true );

            // data - horizontal tail
            _ui->labelHorTailSpan  ->setEnabled( true );
            _ui->labelHorTailWF    ->setEnabled( true );

            _ui->spinBoxHorTailSpan  ->setEnabled( true );
            _ui->spinBoxHorTailWF    ->setEnabled( true );

            _ui->checkBoxHorTailRolling ->setEnabled( true );

            // data - vertical tail
            _ui->labelVerTailArm    ->setEnabled( true );
            _ui->labelVerTailCRoot  ->setEnabled( true );
            _ui->labelVerTailCTip   ->setEnabled( true );
            _ui->labelRuddArea      ->setEnabled( true );

            _ui->spinBoxVerTailArm    ->setEnabled( true );
            _ui->spinBoxVerTailCRoot  ->setEnabled( true );
            _ui->spinBoxVerTailCTip   ->setEnabled( true );
            _ui->spinBoxRuddArea      ->setEnabled( true );

            // data - landing gear
            _ui->labelNoseGearWheels ->setEnabled( true );

            _ui->spinBoxNoseGearWheels ->setEnabled( true );

            _ui->checkBoxGearCross  ->setEnabled( true );
            _ui->checkBoxGearTripod ->setEnabled( true );
        }
        else if ( type == AircraftData::CargoTransport )
        {
            // data - general
            _ui->labelStallV->setEnabled( true );

            _ui->spinBoxStallV->setEnabled( true );

            // data - fuselage
            _ui->labelCargoDoor->setEnabled( true );

            _ui->comboBoxCargoDoor->setEnabled( true );

            _ui->checkBoxFuselageLG->setEnabled( true );

            // data - wing
            _ui->labelCtrlArea  ->setEnabled( true );

            _ui->spinBoxCtrlArea  ->setEnabled( true );

            // data - horizontal tail
            _ui->labelHorTailSpan  ->setEnabled( true );
            _ui->labelHorTailSweep ->setEnabled( true );
            _ui->labelHorTailArm   ->setEnabled( true );
            _ui->labelElevArea     ->setEnabled( true );
            _ui->labelHorTailWF    ->setEnabled( true );

            _ui->spinBoxHorTailSpan  ->setEnabled( true );
            _ui->spinBoxHorTailSweep ->setEnabled( true );
            _ui->spinBoxHorTailArm   ->setEnabled( true );
            _ui->spinBoxElevArea     ->setEnabled( true );
            _ui->spinBoxHorTailWF    ->setEnabled( true );

            _ui->checkBoxHorTailMoving  ->setEnabled( true );

            // data - vertical tail
            _ui->labelVerTailArm    ->setEnabled( true );
            _ui->labelVerTailTC     ->setEnabled( true );

            _ui->spinBoxVerTailArm    ->setEnabled( true );
            _ui->spinBoxVerTailTC     ->setEnabled( true );

            // data - landing gear
            _ui->labelMainGearWheels ->setEnabled( true );
            _ui->labelMainGearStruts ->setEnabled( true );
            _ui->labelNoseGearWheels ->setEnabled( true );

            _ui->spinBoxMainGearWheels ->setEnabled( true );
            _ui->spinBoxMainGearStruts ->setEnabled( true );
            _ui->spinBoxNoseGearWheels ->setEnabled( true );

            _ui->checkBoxGearMainKneel ->setEnabled( true );
            _ui->checkBoxGearNoseKneel ->setEnabled( true );
        }
        else if ( type == AircraftData::GeneralAviation )
        {
            // data - general
            _ui->labelCruiseH->setEnabled( true );
            _ui->labelCruiseV->setEnabled( true );

            _ui->spinBoxCruiseH->setEnabled( true );
            _ui->spinBoxCruiseV->setEnabled( true );

            // data - fuselage
            _ui->labelPressVol->setEnabled( true );

            _ui->spinBoxPressVol->setEnabled( true );

            // data - wing
            _ui->spinBoxWingFuel->setEnabled( true );

            _ui->labelWingFuel->setEnabled( true );

            // data - horizontal tail
            _ui->labelHorTailSweep ->setEnabled( true );
            _ui->labelHorTailArm   ->setEnabled( true );
            _ui->labelHorTailCRoot ->setEnabled( true );
            _ui->labelHorTailCTip  ->setEnabled( true );
            _ui->labelHorTailTC    ->setEnabled( true );

            _ui->spinBoxHorTailSweep ->setEnabled( true );
            _ui->spinBoxHorTailArm   ->setEnabled( true );
            _ui->spinBoxHorTailCRoot ->setEnabled( true );
            _ui->spinBoxHorTailCTip  ->setEnabled( true );
            _ui->spinBoxHorTailTC    ->setEnabled( true );

            // data - vertical tail
            _ui->spinBoxVerTailCRoot ->setEnabled( true );
            _ui->spinBoxVerTailCTip  ->setEnabled( true );
            _ui->spinBoxVerTailTC    ->setEnabled( true );

            _ui->labelVerTailCRoot ->setEnabled( true );
            _ui->labelVerTailCTip  ->setEnabled( true );
            _ui->labelVerTailTC    ->setEnabled( true );

            // data - landing gear
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateGUI()
{
    ///////////////////////////////////////////////////////
    const AircraftData *data = _dataFile.getAircraftData();
    ///////////////////////////////////////////////////////

    // DATA

    // data - general
    _ui->comboBoxAircraftType->setCurrentIndex( data->type );

    _ui->spinBoxMassEmpty   ->setValue( data->general.m_empty   );
    _ui->spinBoxMTOW        ->setValue( data->general.mtow      );
    _ui->spinBoxMassMaxLand ->setValue( data->general.m_maxLand );

    _ui->spinBoxMaxNz     ->setValue( data->general.nz_max     );
    _ui->spinBoxMaxNzLand ->setValue( data->general.nz_maxLand );

    _ui->spinBoxStallV  ->setValue( data->general.v_stall  );
    _ui->spinBoxCruiseH ->setValue( data->general.h_cruise );
    _ui->spinBoxCruiseV ->setValue( data->general.v_cruise );
    _ui->spinBoxMachMax ->setValue( data->general.mach_max );

    _ui->checkBoxNavyAircraft->setChecked( data->general.navy_ac );

    // data - fuselage
    _ui->comboBoxCargoDoor->setCurrentIndex( data->fuselage.cargo_door );

    _ui->spinBoxFuseLength ->setValue( data->fuselage.l );
    _ui->spinBoxFuseHeight ->setValue( data->fuselage.h );
    _ui->spinBoxFuseWidth  ->setValue( data->fuselage.w );

    _ui->spinBoxNoseLength ->setValue( data->fuselage.l_n );

    _ui->spinBoxPressVol   ->setValue( data->fuselage.press_vol   );
    _ui->spinBoxWettedAreaReal ->setValue( data->fuselage.wetted_area );

    _ui->checkBoxFuselageLG ->setChecked( data->fuselage.landing_gear );
    _ui->checkBoxCargoRamp  ->setChecked( data->fuselage.cargo_ramp   );
    _ui->checkBoxWettedAreaOverride->setChecked( data->fuselage.wetted_area_override );

    // data - wing
    _ui->spinBoxWingArea    ->setValue( data->wing.area      );
    _ui->spinBoxWingAreaExp ->setValue( data->wing.area_exp  );
    _ui->spinBoxWingSpan    ->setValue( data->wing.span      );
    _ui->spinBoxWingSweep   ->setValue( data->wing.sweep     );
    _ui->spinBoxWingCRoot   ->setValue( data->wing.c_root    );
    _ui->spinBoxWingCTip    ->setValue( data->wing.c_tip     );
    _ui->spinBoxWingTC      ->setValue( data->wing.t_c       );
    _ui->spinBoxWingFuel    ->setValue( data->wing.fuel      );
    _ui->spinBoxCtrlArea    ->setValue( data->wing.ctrl_area );
    _ui->spinBoxWingAR      ->setValue( data->wing.ar        );
    _ui->spinBoxWingTR      ->setValue( data->wing.tr        );

    _ui->checkBoxWingDelta    ->setChecked( data->wing.delta     );
    _ui->checkBoxWingVarSweep ->setChecked( data->wing.var_sweep );

    // data - horizontal tail
    _ui->spinBoxHorTailArea  ->setValue( data->hor_tail.area      );
    _ui->spinBoxHorTailSpan  ->setValue( data->hor_tail.span      );
    _ui->spinBoxHorTailSweep ->setValue( data->hor_tail.sweep     );
    _ui->spinBoxHorTailCRoot ->setValue( data->hor_tail.c_root    );
    _ui->spinBoxHorTailCTip  ->setValue( data->hor_tail.c_tip     );
    _ui->spinBoxHorTailTC    ->setValue( data->hor_tail.t_c       );
    _ui->spinBoxElevArea     ->setValue( data->hor_tail.elev_area );
    _ui->spinBoxHorTailWF    ->setValue( data->hor_tail.w_f       );
    _ui->spinBoxHorTailArm   ->setValue( data->hor_tail.arm       );
    _ui->spinBoxHorTailAR    ->setValue( data->hor_tail.ar        );
    _ui->spinBoxHorTailTR    ->setValue( data->hor_tail.tr        );

    _ui->checkBoxHorTailMoving  ->setChecked( data->hor_tail.moving  );
    _ui->checkBoxHorTailRolling ->setChecked( data->hor_tail.rolling );

    // data - vertical tail
    _ui->spinBoxVerTailArea   ->setValue( data->ver_tail.area      );
    _ui->spinBoxVerTailHeight ->setValue( data->ver_tail.height    );
    _ui->spinBoxVerTailSweep  ->setValue( data->ver_tail.sweep     );
    _ui->spinBoxVerTailCRoot  ->setValue( data->ver_tail.c_root    );
    _ui->spinBoxVerTailCTip   ->setValue( data->ver_tail.c_tip     );
    _ui->spinBoxVerTailTC     ->setValue( data->ver_tail.t_c       );
    _ui->spinBoxVerTailArm    ->setValue( data->ver_tail.arm       );
    _ui->spinBoxRuddArea      ->setValue( data->ver_tail.rudd_area );
    _ui->spinBoxVerTailAR     ->setValue( data->ver_tail.ar        );
    _ui->spinBoxVerTailTR     ->setValue( data->ver_tail.tr        );

    _ui->checkBoxTailT        ->setChecked( data->ver_tail.t_tail );
    _ui->checkBoxVerTailRotor ->setChecked( data->ver_tail.rotor  );

    // data - landing gear
    _ui->spinBoxMainGearLength ->setValue( data->landing_gear.main_l );
    _ui->spinBoxNoseGearLength ->setValue( data->landing_gear.nose_l );

    _ui->spinBoxMainGearWheels ->setValue( data->landing_gear.main_wheels );
    _ui->spinBoxMainGearStruts ->setValue( data->landing_gear.main_struts );
    _ui->spinBoxNoseGearWheels ->setValue( data->landing_gear.nose_wheels );

    _ui->checkBoxGearFixed  ->setChecked( data->landing_gear.fixed  );
    _ui->checkBoxGearCross  ->setChecked( data->landing_gear.cross  );
    _ui->checkBoxGearTripod ->setChecked( data->landing_gear.tripod );

    _ui->checkBoxGearMainKneel ->setChecked( data->landing_gear.main_kneel );
    _ui->checkBoxGearNoseKneel ->setChecked( data->landing_gear.nose_kneel );

    // data - engine
    _ui->spinBoxEngineMass ->setValue( data->engine.mass );

    // data - rotors
    _ui->spinBoxMainRotorDiameter  ->setValue( data->rotors.main_r    * 2.0 );
    _ui->spinBoxMainRotorChord     ->setValue( data->rotors.main_cb         );
    _ui->spinBoxMainRotorRPM       ->setValue( data->rotors.main_rpm        );
    _ui->spinBoxTailRotorDiameter  ->setValue( data->rotors.tail_r    * 2.0 );
    _ui->spinBoxMainRotorGear      ->setValue( data->rotors.main_gear_ratio );
    _ui->spinBoxPowerLimit         ->setValue( data->rotors.mcp             );
    _ui->spinBoxMainRotorTipVel    ->setValue( data->rotors.main_tip_vel    );
    _ui->spinBoxMainRotorBlades    ->setValue( data->rotors.main_blades     );

    // COMPONENTS

    _ui->listComponents->clear();

    /////////////////////////////////////////////
    const Aircraft *ac = _dataFile.getAircraft();
    /////////////////////////////////////////////

    Aircraft::Components components = ac->getComponents();
    Aircraft::Components::iterator it = components.begin();

    while ( it != components.end() )
    {
        QString name = (*it)->getName();
        _ui->listComponents->addItem( new QListWidgetItem( name, _ui->listComponents ) );

        ++it;
    }

    // RESULTS

    _ui->spinBox_M->setValue( ac->getMassTotal() );

    Vector3 centerOfMass = ac->getCenterOfMass();

    _ui->spinBox_CG_X->setValue( centerOfMass.x() );
    _ui->spinBox_CG_Y->setValue( centerOfMass.y() );
    _ui->spinBox_CG_Z->setValue( centerOfMass.z() );

    Matrix3x3 inertiaMatrix = ac->getInertiaMatrix();

    _ui->spinBox_I_XX->setValue( inertiaMatrix.xx() );
    _ui->spinBox_I_YY->setValue( inertiaMatrix.yy() );
    _ui->spinBox_I_ZZ->setValue( inertiaMatrix.zz() );

    _ui->spinBox_I_XY->setValue( inertiaMatrix.xy() );
    _ui->spinBox_I_XZ->setValue( inertiaMatrix.xz() );
    _ui->spinBox_I_YZ->setValue( inertiaMatrix.yz() );

    _ui->textResults->setText( ac->toString().c_str() );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateTitleBar()
{
    QString title = tr( APP_TITLE );

    if ( _currentFile.length() > 0 )
    {
        title += " - " + QFileInfo( _currentFile ).fileName();
    }

    if ( !_saved ) title += " (*)";

    setWindowTitle( title );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateWettedArea()
{
    double l_fuse = _ui->spinBoxFuseLength ->value();
    double w_fuse = _ui->spinBoxFuseWidth  ->value();
    double h_fuse = _ui->spinBoxFuseHeight ->value();
    double l_nose = _ui->spinBoxNoseLength ->value();

    double a_top  = w_fuse * ( l_fuse - l_nose ) + 0.5 * w_fuse * l_nose;
    double a_side = h_fuse * ( l_fuse - l_nose ) + 0.5 * h_fuse * l_nose;

    // Raymer: Aircraft Design, p.205, eq. 7.13
    double s_wet = 3.4 * ( ( a_top + a_side ) / 2.0 );

    _ui->spinBoxWettedAreaEstimated->setValue( s_wet );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateWingAR()
{
    const AircraftData *data = _dataFile.getAircraftData();

    if ( data->wing.area > 0.0 )
    {
        double ar = pow( data->wing.span, 2.0 ) / data->wing.area;
        _ui->spinBoxWingAR->setValue( ar );
    }
    else
    {
        _ui->spinBoxWingAR->setValue( 0.0 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateWingTR()
{
    const AircraftData *data = _dataFile.getAircraftData();

    if ( data->wing.c_root > 0.0 )
    {
        double tr = data->wing.c_tip / data->wing.c_root;
        _ui->spinBoxWingTR->setValue( tr );
    }
    else
    {
        _ui->spinBoxWingTR->setValue( 0.0 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateHorTailAR()
{
    const AircraftData *data = _dataFile.getAircraftData();

    if ( data->hor_tail.area > 0.0 )
    {
        double ar = pow( data->hor_tail.span, 2.0 ) / data->hor_tail.area;
        _ui->spinBoxHorTailAR->setValue( ar );
    }
    else
    {
        _ui->spinBoxHorTailAR->setValue( 0.0 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateHorTailTR()
{
    const AircraftData *data = _dataFile.getAircraftData();

    if ( data->hor_tail.c_root > 0.0 )
    {
        double tr = data->hor_tail.c_tip / data->hor_tail.c_root;
        _ui->spinBoxHorTailTR->setValue( tr );
    }
    else
    {
        _ui->spinBoxHorTailTR->setValue( 0.0 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateVerTailAR()
{
    const AircraftData *data = _dataFile.getAircraftData();

    if ( data->ver_tail.area > 0.0 )
    {
        double ar = pow( data->ver_tail.height, 2.0 ) / data->ver_tail.area;
        _ui->spinBoxVerTailAR->setValue( ar );
    }
    else
    {
        _ui->spinBoxVerTailAR->setValue( 0.0 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateVerTailTR()
{
    const AircraftData *data = _dataFile.getAircraftData();

    if ( data->ver_tail.c_root > 0.0 )
    {
        double tr = data->ver_tail.c_tip / data->ver_tail.c_root;
        _ui->spinBoxVerTailTR->setValue( tr );
    }
    else
    {
        _ui->spinBoxVerTailTR->setValue( 0.0 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateRotorTipVel()
{
    double omg = 2.0 * M_PI * _ui->spinBoxMainRotorRPM->value() / 60.0;
    double rad = 0.5 * _ui->spinBoxMainRotorDiameter->value();

    double vel = omg * rad;

    _ui->spinBoxMainRotorTipVel->setValue( vel );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateRecentFiles( QString file )
{
    for ( unsigned int i = 0; i < _recentFilesActions.size(); i++ )
    {
        disconnect( _recentFilesActions.at( i ), SIGNAL(triggered(int)), this, SLOT(recentFile_triggered(int)) );
    }

    _recentFilesActions.clear();

    if ( file.length() > 0 )
    {
        QStringList temp;

        temp.push_back( file );

        for ( int i = 0; i < _recentFilesList.size() && i < 4; i++ )
        {
            temp.push_back( _recentFilesList.at( i ) );
        }

        _recentFilesList = temp;
    }

    _ui->menuRecentFiles->clear();

    for ( int i = 0; i < _recentFilesList.size(); i++ )
    {
        _recentFilesActions.push_back( new RecentFileAction( i, _recentFilesList.at( i ), _ui->menuRecentFiles ) );
        connect( _recentFilesActions.at( i ), SIGNAL(triggered(int)), this, SLOT(recentFile_triggered(int)) );
        _ui->menuRecentFiles->addAction( _recentFilesActions.at( i ) );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionNew_triggered()
{
    newFile();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionOpen_triggered()
{
    openFile();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionSave_triggered()
{
    saveFile();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionSaveAs_triggered()
{
    saveFileAs();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionExport_triggered()
{
    exportFileAs();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionExit_triggered()
{
    close();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionClearRecent_triggered()
{
    _recentFilesList.clear();

    updateRecentFiles();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::recentFile_triggered( int id )
{
    _currentFile = _recentFilesList.at( id );

    readFile( _currentFile );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionAbout_triggered()
{
    QFile aboutHtmlFile( ":/gui/html/about.html" );

    QString aboutWinTitle;
    QString aboutInfoText;

    aboutWinTitle = tr( "About" );

    if ( aboutHtmlFile.open( QIODevice::ReadOnly ) )
    {
        aboutInfoText = aboutHtmlFile.readAll();
        aboutHtmlFile.close();
    }

    QMessageBox::about( this, aboutWinTitle, aboutInfoText );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_listComponents_currentRowChanged( int currentRow )
{
    Aircraft::Components components = _dataFile.getAircraft()->getComponents();

    if ( currentRow >=0 && currentRow < (int)components.size() )
    {
        _ui->pushButtonDel  ->setEnabled( true );
        _ui->pushButtonEdit ->setEnabled( true );
    }
    else
    {
        _ui->pushButtonDel  ->setEnabled( false );
        _ui->pushButtonEdit ->setEnabled( false );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_listComponents_doubleClicked( const QModelIndex & )
{
    editComponent();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonAdd_clicked()
{
    addComponent();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonDel_clicked()
{
    Aircraft::Components components = _dataFile.getAircraft()->getComponents();
    int currentRow = _ui->listComponents->currentRow();

    if ( currentRow >=0 && currentRow < (int)components.size() )
    {
        _dataFile.getAircraft()->delComponent( currentRow );
        _saved = false;
    }

    updateGUI();
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonEdit_clicked()
{
    editComponent();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_comboBoxAircraftType_currentIndexChanged( int index )
{
    AircraftData::Type type = AircraftData::FighterAttack;

    switch ( index )
    {
        case AircraftData::FighterAttack   : type = AircraftData::FighterAttack   ; break;
        case AircraftData::CargoTransport  : type = AircraftData::CargoTransport  ; break;
        case AircraftData::GeneralAviation : type = AircraftData::GeneralAviation ; break;
        case AircraftData::Helicopter      : type = AircraftData::Helicopter      ; break;
    }

    setAircraftType( type );

    _dataFile.getAircraftData()->type = type;

    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMassEmpty_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->general.m_empty = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMTOW_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->general.mtow =  arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMassMaxLand_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->general.m_maxLand = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMaxNz_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->general.nz_max = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMaxNzLand_valueChanged(double arg1)
{
    _dataFile.getAircraftData()->general.nz_maxLand = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxStallV_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->general.v_stall = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxCruiseV_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->general.v_cruise = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxCruiseH_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->general.h_cruise = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMachMax_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->general.mach_max = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxNavyAircraft_toggled( bool checked )
{
    _dataFile.getAircraftData()->general.navy_ac = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_comboBoxCargoDoor_currentIndexChanged( int index )
{
    AircraftData::Fuselage::CargoDoor door = AircraftData::Fuselage::NoCargoDoor;

    switch ( index )
    {
        case AircraftData::Fuselage::NoCargoDoor       : door = AircraftData::Fuselage::NoCargoDoor       ; break;
        case AircraftData::Fuselage::OneSideCargoDoor  : door = AircraftData::Fuselage::OneSideCargoDoor  ; break;
        case AircraftData::Fuselage::TwoSideCargoDoor  : door = AircraftData::Fuselage::TwoSideCargoDoor  ; break;
        case AircraftData::Fuselage::AftClamshellDoor  : door = AircraftData::Fuselage::AftClamshellDoor  ; break;
        case AircraftData::Fuselage::TwoSideAndAftDoor : door = AircraftData::Fuselage::TwoSideAndAftDoor ; break;
    }

    _dataFile.getAircraftData()->fuselage.cargo_door = door;

    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxFuseLength_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->fuselage.l = arg1;
    _saved = false;
    updateTitleBar();
    updateWettedArea();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxFuseHeight_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->fuselage.h = arg1;
    _saved = false;
    updateTitleBar();
    updateWettedArea();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxFuseWidth_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->fuselage.w = arg1;
    _saved = false;
    updateTitleBar();
    updateWettedArea();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxNoseLength_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->fuselage.l_n = arg1;
    _saved = false;
    updateTitleBar();
    updateWettedArea();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxPressVol_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->fuselage.press_vol = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWettedAreaEstimated_valueChanged( double arg1 )
{
    if ( !_dataFile.getAircraftData()->fuselage.wetted_area_override )
    {
        _ui->spinBoxWettedAreaReal->setValue( arg1 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWettedAreaReal_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->fuselage.wetted_area = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxFuselageLG_toggled( bool checked )
{
    _dataFile.getAircraftData()->fuselage.landing_gear = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxCargoRamp_toggled( bool checked )
{
    _dataFile.getAircraftData()->fuselage.cargo_ramp = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxWettedAreaOverride_toggled( bool checked )
{
    _dataFile.getAircraftData()->fuselage.wetted_area_override = checked;
    _saved = false;
    updateTitleBar();

    _ui->labelWettedAreaReal->setEnabled( checked );
    _ui->spinBoxWettedAreaReal->setEnabled( checked );

    if ( !checked )
    {
        _ui->spinBoxWettedAreaReal->setValue( _ui->spinBoxWettedAreaEstimated->value() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingArea_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.area = arg1;
    _saved = false;
    updateTitleBar();
    updateWingAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingAreaExp_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.area_exp = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingSpan_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.span = arg1;
    _saved = false;
    updateTitleBar();
    updateWingAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingSweep_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.sweep = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingCRoot_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.c_root = arg1;
    _saved = false;
    updateTitleBar();
    updateWingTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingCTip_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.c_tip = arg1;
    _saved = false;
    updateTitleBar();
    updateWingTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingTC_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.t_c = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingFuel_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.fuel = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxCtrlArea_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.ctrl_area = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingAR_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.ar = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingTR_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->wing.tr = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxWingDelta_toggled( bool checked )
{
    _dataFile.getAircraftData()->wing.delta = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxWingVarSweep_toggled( bool checked )
{
    _dataFile.getAircraftData()->wing.var_sweep = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailArea_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.area = arg1;
    _saved = false;
    updateTitleBar();
    updateHorTailAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailSpan_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.span = arg1;
    _saved = false;
    updateTitleBar();
    updateHorTailAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailSweep_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.sweep = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailCRoot_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.c_root = arg1;
    _saved = false;
    updateTitleBar();
    updateHorTailTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailCTip_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.c_tip = arg1;
    _saved = false;
    updateTitleBar();
    updateHorTailTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailTC_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.t_c = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxElevArea_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.elev_area = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailWF_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.w_f = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailArm_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.arm = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailAR_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.ar = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailTR_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->hor_tail.tr = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxHorTailMoving_toggled( bool checked )
{
    _dataFile.getAircraftData()->hor_tail.moving = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxHorTailRolling_toggled( bool checked )
{
    _dataFile.getAircraftData()->hor_tail.rolling = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailArea_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.area = arg1;
    _saved = false;
    updateTitleBar();
    updateVerTailAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailHeight_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.height = arg1;
    _saved = false;
    updateTitleBar();
    updateVerTailAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailSweep_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.sweep = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailCRoot_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.c_root = arg1;
    _saved = false;
    updateTitleBar();
    updateVerTailTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailCTip_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.c_tip = arg1;
    _saved = false;
    updateTitleBar();
    updateVerTailTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailTC_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.t_c = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailArm_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.arm = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxRuddArea_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.rudd_area = arg1;
    _saved = false;
    updateTitleBar();
}

void MainWindow::on_spinBoxVerTailAR_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.ar = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailTR_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->ver_tail.tr = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxTailT_toggled( bool checked )
{
    _dataFile.getAircraftData()->ver_tail.t_tail = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxVerTailRotor_toggled( bool checked )
{
    _dataFile.getAircraftData()->ver_tail.rotor = checked;
    _saved = false;
    updateTitleBar();
}


////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainGearLength_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->landing_gear.main_l = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxNoseGearLength_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->landing_gear.nose_l = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainGearWheels_valueChanged( int arg1 )
{
    _dataFile.getAircraftData()->landing_gear.main_wheels = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainGearStruts_valueChanged( int arg1 )
{
    _dataFile.getAircraftData()->landing_gear.main_struts = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxNoseGearWheels_valueChanged( int arg1 )
{
    _dataFile.getAircraftData()->landing_gear.nose_wheels = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearFixed_toggled( bool checked )
{
    _dataFile.getAircraftData()->landing_gear.fixed = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearCross_toggled( bool checked )
{
    _dataFile.getAircraftData()->landing_gear.cross = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearTripod_toggled( bool checked )
{
    _dataFile.getAircraftData()->landing_gear.tripod = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearMainKneel_toggled( bool checked )
{
    _dataFile.getAircraftData()->landing_gear.main_kneel = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearNoseKneel_toggled( bool checked )
{
    _dataFile.getAircraftData()->landing_gear.nose_kneel = checked;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxEngineMass_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->engine.mass = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorDiameter_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->rotors.main_r = 0.5 * arg1;
    _saved = false;
    updateTitleBar();
    updateRotorTipVel();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorChord_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->rotors.main_cb = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorRPM_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->rotors.main_rpm = arg1;
    _saved = false;
    updateTitleBar();
    updateRotorTipVel();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxTailRotorDiameter_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->rotors.tail_r = 0.5 * arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorGear_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->rotors.main_gear_ratio = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxPowerLimit_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->rotors.mcp = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorTipVel_valueChanged( double arg1 )
{
    _dataFile.getAircraftData()->rotors.main_tip_vel = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorBlades_valueChanged( int arg1 )
{
    _dataFile.getAircraftData()->rotors.main_blades = arg1;
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
