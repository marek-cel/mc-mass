/****************************************************************************//*
 * Copyright (C) 2021 Marek M. Cel
 *
 * Creative Commons Legal Code
 *
 * CC0 1.0 Universal
 *
 *     CREATIVE COMMONS CORPORATION IS NOT A LAW FIRM AND DOES NOT PROVIDE
 *     LEGAL SERVICES. DISTRIBUTION OF THIS DOCUMENT DOES NOT CREATE AN
 *     ATTORNEY-CLIENT RELATIONSHIP. CREATIVE COMMONS PROVIDES THIS
 *     INFORMATION ON AN "AS-IS" BASIS. CREATIVE COMMONS MAKES NO WARRANTIES
 *     REGARDING THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS
 *     PROVIDED HEREUNDER, AND DISCLAIMS LIABILITY FOR DAMAGES RESULTING FROM
 *     THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS PROVIDED
 *     HEREUNDER.
 *
 * Statement of Purpose
 *
 * The laws of most jurisdictions throughout the world automatically confer
 * exclusive Copyright and Related Rights (defined below) upon the creator
 * and subsequent owner(s) (each and all, an "owner") of an original work of
 * authorship and/or a database (each, a "Work").
 *
 * Certain owners wish to permanently relinquish those rights to a Work for
 * the purpose of contributing to a commons of creative, cultural and
 * scientific works ("Commons") that the public can reliably and without fear
 * of later claims of infringement build upon, modify, incorporate in other
 * works, reuse and redistribute as freely as possible in any form whatsoever
 * and for any purposes, including without limitation commercial purposes.
 * These owners may contribute to the Commons to promote the ideal of a free
 * culture and the further production of creative, cultural and scientific
 * works, or to gain reputation or greater distribution for their Work in
 * part through the use and efforts of others.
 *
 * For these and/or other purposes and motivations, and without any
 * expectation of additional consideration or compensation, the person
 * associating CC0 with a Work (the "Affirmer"), to the extent that he or she
 * is an owner of Copyright and Related Rights in the Work, voluntarily
 * elects to apply CC0 to the Work and publicly distribute the Work under its
 * terms, with knowledge of his or her Copyright and Related Rights in the
 * Work and the meaning and intended legal effect of CC0 on those rights.
 *
 * 1. Copyright and Related Rights. A Work made available under CC0 may be
 * protected by copyright and related or neighboring rights ("Copyright and
 * Related Rights"). Copyright and Related Rights include, but are not
 * limited to, the following:
 *
 *   i. the right to reproduce, adapt, distribute, perform, display,
 *      communicate, and translate a Work;
 *  ii. moral rights retained by the original author(s) and/or performer(s);
 * iii. publicity and privacy rights pertaining to a person's image or
 *      likeness depicted in a Work;
 *  iv. rights protecting against unfair competition in regards to a Work,
 *      subject to the limitations in paragraph 4(a), below;
 *   v. rights protecting the extraction, dissemination, use and reuse of data
 *      in a Work;
 *  vi. database rights (such as those arising under Directive 96/9/EC of the
 *      European Parliament and of the Council of 11 March 1996 on the legal
 *      protection of databases, and under any national implementation
 *      thereof, including any amended or successor version of such
 *      directive); and
 * vii. other similar, equivalent or corresponding rights throughout the
 *      world based on applicable law or treaty, and any national
 *      implementations thereof.
 *
 * 2. Waiver. To the greatest extent permitted by, but not in contravention
 * of, applicable law, Affirmer hereby overtly, fully, permanently,
 * irrevocably and unconditionally waives, abandons, and surrenders all of
 * Affirmer's Copyright and Related Rights and associated claims and causes
 * of action, whether now known or unknown (including existing as well as
 * future claims and causes of action), in the Work (i) in all territories
 * worldwide, (ii) for the maximum duration provided by applicable law or
 * treaty (including future time extensions), (iii) in any current or future
 * medium and for any number of copies, and (iv) for any purpose whatsoever,
 * including without limitation commercial, advertising or promotional
 * purposes (the "Waiver"). Affirmer makes the Waiver for the benefit of each
 * member of the public at large and to the detriment of Affirmer's heirs and
 * successors, fully intending that such Waiver shall not be subject to
 * revocation, rescission, cancellation, termination, or any other legal or
 * equitable action to disrupt the quiet enjoyment of the Work by the public
 * as contemplated by Affirmer's express Statement of Purpose.
 *
 * 3. Public License Fallback. Should any part of the Waiver for any reason
 * be judged legally invalid or ineffective under applicable law, then the
 * Waiver shall be preserved to the maximum extent permitted taking into
 * account Affirmer's express Statement of Purpose. In addition, to the
 * extent the Waiver is so judged Affirmer hereby grants to each affected
 * person a royalty-free, non transferable, non sublicensable, non exclusive,
 * irrevocable and unconditional license to exercise Affirmer's Copyright and
 * Related Rights in the Work (i) in all territories worldwide, (ii) for the
 * maximum duration provided by applicable law or treaty (including future
 * time extensions), (iii) in any current or future medium and for any number
 * of copies, and (iv) for any purpose whatsoever, including without
 * limitation commercial, advertising or promotional purposes (the
 * "License"). The License shall be deemed effective as of the date CC0 was
 * applied by Affirmer to the Work. Should any part of the License for any
 * reason be judged legally invalid or ineffective under applicable law, such
 * partial invalidity or ineffectiveness shall not invalidate the remainder
 * of the License, and in such case Affirmer hereby affirms that he or she
 * will not (i) exercise any of his or her remaining Copyright and Related
 * Rights in the Work or (ii) assert any associated claims and causes of
 * action with respect to the Work, in either case contrary to Affirmer's
 * express Statement of Purpose.
 *
 * 4. Limitations and Disclaimers.
 *
 *  a. No trademark or patent rights held by Affirmer are waived, abandoned,
 *     surrendered, licensed or otherwise affected by this document.
 *  b. Affirmer offers the Work as-is and makes no representations or
 *     warranties of any kind concerning the Work, express, implied,
 *     statutory or otherwise, including without limitation warranties of
 *     title, merchantability, fitness for a particular purpose, non
 *     infringement, or the absence of latent or other defects, accuracy, or
 *     the present or absence of errors, whether or not discoverable, all to
 *     the greatest extent permissible under applicable law.
 *  c. Affirmer disclaims responsibility for clearing rights of other persons
 *     that may apply to the Work or any use thereof, including without
 *     limitation any person's Copyright and Related Rights in the Work.
 *     Further, Affirmer disclaims responsibility for obtaining any necessary
 *     consents, permissions or other rights required for any use of the
 *     Work.
 *  d. Affirmer understands and acknowledges that Creative Commons is not a
 *     party to this document and has no duty or obligation with respect to
 *     this CC0 or use of the Work.
 ******************************************************************************/

#include <gui/MainWindow.h>
#include <ui_MainWindow.h>

#include <cmath>

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

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


////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    _ui ( new Ui::MainWindow ),

    _saved ( true )
{
    _ui->setupUi( this );

    _scSave   = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_triggered())   );
    _scExport = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_E), this, SLOT(on_actionExport_triggered()) );

    setAircraftType( FighterAttack );
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

    _doc.newEmpty();

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
        if ( !_doc.readFile( fileName.toStdString().c_str() ) )
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
    if ( _doc.saveFile( fileName.toStdString().c_str() ) )
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
    if ( !_doc.exportAs( fileName.toStdString().c_str() ) )
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
        component = new Fuselage( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 1 )
    {
        component = new Wing( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 2 )
    {
        component = new TailHor( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 3 )
    {
        component = new TailVer( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 4 )
    {
        component = new GearMain( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 5 )
    {
        component = new GearNose( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 6 )
    {
        component = new Engine( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 7 )
    {
        component = new RotorDrive( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 8 )
    {
        component = new RotorHub( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 9 )
    {
        component = new RotorMain( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 10 )
    {
        component = new RotorTail( _doc.getAircraft() );
    }
    else if ( _ui->comboBoxComponents->currentIndex() == 11 )
    {
        component = new AllElse( _doc.getAircraft() );
    }

    if ( component )
    {
        _doc.getAircraft()->addComponent( component );
        _saved = false;
    }

    updateGUI();
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::editComponent()
{
    int index = _ui->listComponents->currentRow();

    Component *component = _doc.getAircraft()->getComponent( index );

    if ( component )
    {
        DialogEdit::edit( this, component );

        _doc.getAircraft()->update();

        _saved = false;

        updateGUI();
        updateTitleBar();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::setAircraftType( Type type )
{
    // data - general
    _ui->labelMassEmpty   ->setEnabled( false );
    _ui->labelMassMaxTO   ->setEnabled( false );
    _ui->labelMassMaxLand ->setEnabled( false );
    _ui->labelMaxNz       ->setEnabled( false );
    _ui->labelMaxNzLand   ->setEnabled( false );
    _ui->labelStallV      ->setEnabled( false );
    _ui->labelCruiseH     ->setEnabled( false );
    _ui->labelCruiseV     ->setEnabled( false );
    _ui->labelMachMax     ->setEnabled( false );

    _ui->spinBoxMassEmpty   ->setEnabled( false );
    _ui->spinBoxMassMaxTO   ->setEnabled( false );
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

    _ui->spinBoxWettedArea ->setEnabled( false );
    _ui->spinBoxPressVol   ->setEnabled( false );

    _ui->labelCargoDoor->setEnabled( false );

    _ui->labelWettedArea ->setEnabled( false );
    _ui->labelPressVol   ->setEnabled( false );

    _ui->checkBoxFuselageLG->setEnabled( false );
    _ui->checkBoxCargoRamp->setEnabled( false );

    // data - wing
    _ui->labelWingArea  ->setEnabled( false );
    _ui->labelWingExp   ->setEnabled( false );
    _ui->labelWingSpan  ->setEnabled( false );
    _ui->labelWingSweep ->setEnabled( false );
    _ui->labelWingCR    ->setEnabled( false );
    _ui->labelWingCT    ->setEnabled( false );
    _ui->labelWingTC    ->setEnabled( false );
    _ui->labelWingFuel  ->setEnabled( false );
    _ui->labelCtrlArea  ->setEnabled( false );
    _ui->labelWingAR    ->setEnabled( false );
    _ui->labelWingTR    ->setEnabled( false );

    _ui->spinBoxWingArea  ->setEnabled( false );
    _ui->spinBoxWingExp   ->setEnabled( false );
    _ui->spinBoxWingSpan  ->setEnabled( false );
    _ui->spinBoxWingSweep ->setEnabled( false );
    _ui->spinBoxWingCR    ->setEnabled( false );
    _ui->spinBoxWingCT    ->setEnabled( false );
    _ui->spinBoxWingTC    ->setEnabled( false );
    _ui->spinBoxWingFuel  ->setEnabled( false );
    _ui->spinBoxCtrlArea  ->setEnabled( false );
    _ui->spinBoxWingAR    ->setEnabled( false );
    _ui->spinBoxWingTR    ->setEnabled( false );

    _ui->checkBoxWingDelta ->setEnabled( false );
    _ui->checkBoxWingVar   ->setEnabled( false );

    // data - horizontal tail
    _ui->labelHorTailArea  ->setEnabled( false );
    _ui->labelHorTailSpan  ->setEnabled( false );
    _ui->labelHorTailSweep ->setEnabled( false );
    _ui->labelHorTailCR    ->setEnabled( false );
    _ui->labelHorTailCT    ->setEnabled( false );
    _ui->labelHorTailTC    ->setEnabled( false );
    _ui->labelElevArea     ->setEnabled( false );
    _ui->labelHorTailFW    ->setEnabled( false );
    _ui->labelHorTailArm   ->setEnabled( false );
    _ui->labelHorTailAR    ->setEnabled( false );
    _ui->labelHorTailTR    ->setEnabled( false );

    _ui->spinBoxHorTailArea  ->setEnabled( false );
    _ui->spinBoxHorTailSpan  ->setEnabled( false );
    _ui->spinBoxHorTailSweep ->setEnabled( false );
    _ui->spinBoxHorTailCR    ->setEnabled( false );
    _ui->spinBoxHorTailCT    ->setEnabled( false );
    _ui->spinBoxHorTailTC    ->setEnabled( false );
    _ui->spinBoxElevArea     ->setEnabled( false );
    _ui->spinBoxHorTailFW    ->setEnabled( false );
    _ui->spinBoxHorTailArm   ->setEnabled( false );
    _ui->spinBoxHorTailAR    ->setEnabled( false );
    _ui->spinBoxHorTailTR    ->setEnabled( false );

    _ui->checkBoxHorTailMoving  ->setEnabled( false );
    _ui->checkBoxHorTailRolling ->setEnabled( false );

    // data - vertical tail
    _ui->labelVerTailArea   ->setEnabled( false );
    _ui->labelVerTailHeight ->setEnabled( false );
    _ui->labelVerTailSweep  ->setEnabled( false );
    _ui->labelVerTailCR     ->setEnabled( false );
    _ui->labelVerTailCT     ->setEnabled( false );
    _ui->labelVerTailTC     ->setEnabled( false );
    _ui->labelVerTailArm    ->setEnabled( false );
    _ui->labelRuddArea      ->setEnabled( false );
    _ui->labelVerTailAR     ->setEnabled( false );
    _ui->labelVerTailTR     ->setEnabled( false );

    _ui->spinBoxVerTailArea   ->setEnabled( false );
    _ui->spinBoxVerTailHeight ->setEnabled( false );
    _ui->spinBoxVerTailSweep  ->setEnabled( false );
    _ui->spinBoxVerTailCR     ->setEnabled( false );
    _ui->spinBoxVerTailCT     ->setEnabled( false );
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

    if ( type == Helicopter )
    {
        // data - general
        _ui->labelMassEmpty   ->setEnabled( true );
        _ui->labelMassMaxTO   ->setEnabled( true );
        _ui->labelMaxNz       ->setEnabled( true );
        _ui->labelMaxNzLand   ->setEnabled( true );

        _ui->spinBoxMassEmpty   ->setEnabled( true );
        _ui->spinBoxMassMaxTO   ->setEnabled( true );
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

        _ui->labelWettedArea ->setEnabled( true );

        _ui->spinBoxWettedArea ->setEnabled( true );

        _ui->checkBoxCargoRamp->setEnabled( true );

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
        _ui->labelMassMaxTO   ->setEnabled( true );
        _ui->labelMassMaxLand ->setEnabled( true );
        _ui->labelMaxNz       ->setEnabled( true );
        _ui->labelMaxNzLand   ->setEnabled( true );

        _ui->spinBoxMassEmpty   ->setEnabled( true );
        _ui->spinBoxMassMaxTO   ->setEnabled( true );
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

        _ui->labelWettedArea ->setEnabled( true );

        _ui->spinBoxWettedArea ->setEnabled( true );

        // data - wing
        _ui->labelWingArea  ->setEnabled( true );
        _ui->labelWingExp   ->setEnabled( true );
        _ui->labelWingSpan  ->setEnabled( true );
        _ui->labelWingSweep ->setEnabled( true );
        _ui->labelWingCR    ->setEnabled( true );
        _ui->labelWingCT    ->setEnabled( true );
        _ui->labelWingTC    ->setEnabled( true );
        _ui->labelWingAR    ->setEnabled( true );
        _ui->labelWingTR    ->setEnabled( true );

        _ui->spinBoxWingArea  ->setEnabled( true );
        _ui->spinBoxWingExp   ->setEnabled( true );
        _ui->spinBoxWingSpan  ->setEnabled( true );
        _ui->spinBoxWingSweep ->setEnabled( true );
        _ui->spinBoxWingCR    ->setEnabled( true );
        _ui->spinBoxWingCT    ->setEnabled( true );
        _ui->spinBoxWingTC    ->setEnabled( true );
        _ui->spinBoxWingAR    ->setEnabled( true );
        _ui->spinBoxWingTR    ->setEnabled( true );

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

        if      ( type == FighterAttack )
        {
            // data - general
            _ui->labelMachMax->setEnabled( true );

            _ui->spinBoxMachMax->setEnabled( true );

            _ui->checkBoxNavyAircraft->setEnabled( true );

            // data - wing
            _ui->labelCtrlArea  ->setEnabled( true );

            _ui->spinBoxCtrlArea  ->setEnabled( true );

            _ui->checkBoxWingDelta ->setEnabled( true );
            _ui->checkBoxWingVar   ->setEnabled( true );

            // data - horizontal tail
            _ui->labelHorTailSpan  ->setEnabled( true );
            _ui->labelHorTailFW    ->setEnabled( true );

            _ui->spinBoxHorTailSpan  ->setEnabled( true );
            _ui->spinBoxHorTailFW    ->setEnabled( true );

            _ui->checkBoxHorTailRolling ->setEnabled( true );

            // data - vertical tail
            _ui->labelVerTailArm    ->setEnabled( true );
            _ui->labelVerTailCR     ->setEnabled( true );
            _ui->labelVerTailCT     ->setEnabled( true );
            _ui->labelRuddArea      ->setEnabled( true );

            _ui->spinBoxVerTailArm    ->setEnabled( true );
            _ui->spinBoxVerTailCR     ->setEnabled( true );
            _ui->spinBoxVerTailCT     ->setEnabled( true );
            _ui->spinBoxRuddArea      ->setEnabled( true );

            // data - landing gear
            _ui->labelNoseGearWheels ->setEnabled( true );

            _ui->spinBoxNoseGearWheels ->setEnabled( true );

            _ui->checkBoxGearCross  ->setEnabled( true );
            _ui->checkBoxGearTripod ->setEnabled( true );
        }
        else if ( type == CargoTransport )
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
            _ui->labelHorTailFW    ->setEnabled( true );

            _ui->spinBoxHorTailSpan  ->setEnabled( true );
            _ui->spinBoxHorTailSweep ->setEnabled( true );
            _ui->spinBoxHorTailArm   ->setEnabled( true );
            _ui->spinBoxElevArea     ->setEnabled( true );
            _ui->spinBoxHorTailFW    ->setEnabled( true );

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
        else if ( type == GeneralAviation )
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
            _ui->labelHorTailCR    ->setEnabled( true );
            _ui->labelHorTailCT    ->setEnabled( true );
            _ui->labelHorTailTC    ->setEnabled( true );

            _ui->spinBoxHorTailSweep ->setEnabled( true );
            _ui->spinBoxHorTailArm   ->setEnabled( true );
            _ui->spinBoxHorTailCR    ->setEnabled( true );
            _ui->spinBoxHorTailCT    ->setEnabled( true );
            _ui->spinBoxHorTailTC    ->setEnabled( true );

            // data - vertical tail
            _ui->spinBoxVerTailCR     ->setEnabled( true );
            _ui->spinBoxVerTailCT     ->setEnabled( true );
            _ui->spinBoxVerTailTC     ->setEnabled( true );

            _ui->labelVerTailCR     ->setEnabled( true );
            _ui->labelVerTailCT     ->setEnabled( true );
            _ui->labelVerTailTC     ->setEnabled( true );

            // data - landing gear
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateGUI()
{
    Aircraft *ac = _doc.getAircraft();

    // DATA

    // data - general
    _ui->comboBoxAircraftType->setCurrentIndex( ac->getType() );

    _ui->spinBoxMassEmpty   ->setValue( ac->getM_empty   () );
    _ui->spinBoxMassMaxTO   ->setValue( ac->getM_maxTO   () );
    _ui->spinBoxMassMaxLand ->setValue( ac->getM_maxLand () );

    _ui->spinBoxMaxNz     ->setValue( ac->getNzMax     () );
    _ui->spinBoxMaxNzLand ->setValue( ac->getNzMaxLand () );

    _ui->spinBoxStallV  ->setValue( ac->getStallV  () );
    _ui->spinBoxCruiseH ->setValue( ac->getCruiseH () );
    _ui->spinBoxCruiseV ->setValue( ac->getCruiseV () );
    _ui->spinBoxMachMax ->setValue( ac->getMachMax () );

    _ui->checkBoxNavyAircraft->setChecked( _doc.getAircraft()->getNavyAircraft() );

    // data - fuselage
    _ui->comboBoxCargoDoor->setCurrentIndex( ac->getCargoDoor() );

    _ui->spinBoxFuseLength ->setValue( ac->getFuseLength () );
    _ui->spinBoxFuseHeight ->setValue( ac->getFuseHeight () );
    _ui->spinBoxFuseWidth  ->setValue( ac->getFuseWidth  () );
    _ui->spinBoxNoseLength ->setValue( ac->getNoseLength () );
    _ui->spinBoxPressVol   ->setValue( ac->getPressVol   () );
    _ui->spinBoxWettedArea ->setValue( ac->getWettedArea () );

    _ui->checkBoxFuselageLG ->setChecked( ac->getFuselageLG () );
    _ui->checkBoxCargoRamp  ->setChecked( ac->getCargoRamp  () );

    // data - wing
    _ui->spinBoxWingArea  ->setValue( ac->getWingArea  () );
    _ui->spinBoxWingExp   ->setValue( ac->getWingExp   () );
    _ui->spinBoxWingSpan  ->setValue( ac->getWingSpan  () );
    _ui->spinBoxWingSweep ->setValue( ac->getWingSweep () );
    _ui->spinBoxWingCR    ->setValue( ac->getWingCR    () );
    _ui->spinBoxWingCT    ->setValue( ac->getWingCT    () );
    _ui->spinBoxWingTC    ->setValue( ac->getWingTC    () );
    _ui->spinBoxWingFuel  ->setValue( ac->getWingFuel  () );
    _ui->spinBoxCtrlArea  ->setValue( ac->getCtrlArea  () );
    _ui->spinBoxWingAR    ->setValue( ac->getWingAR    () );
    _ui->spinBoxWingTR    ->setValue( ac->getWingTR    () );

    _ui->checkBoxWingDelta ->setChecked( ac->getWingDelta () );
    _ui->checkBoxWingVar   ->setChecked( ac->getWingVar   () );

    // data - horizontal tail
    _ui->spinBoxHorTailArea  ->setValue( ac->getHorTailArea  () );
    _ui->spinBoxHorTailSpan  ->setValue( ac->getHorTailSpan  () );
    _ui->spinBoxHorTailSweep ->setValue( ac->getHorTailSweep () );
    _ui->spinBoxHorTailCR    ->setValue( ac->getHorTailCR    () );
    _ui->spinBoxHorTailCT    ->setValue( ac->getHorTailCT    () );
    _ui->spinBoxHorTailTC    ->setValue( ac->getHorTailTC    () );
    _ui->spinBoxElevArea     ->setValue( ac->getElevArea     () );
    _ui->spinBoxHorTailFW    ->setValue( ac->getHorTailFW    () );
    _ui->spinBoxHorTailArm   ->setValue( ac->getHorTailArm   () );
    _ui->spinBoxHorTailAR    ->setValue( ac->getHorTailAR    () );
    _ui->spinBoxHorTailTR    ->setValue( ac->getHorTailTR    () );

    _ui->checkBoxHorTailMoving  ->setChecked( ac->getHorTailMoving  () );
    _ui->checkBoxHorTailRolling ->setChecked( ac->getHorTailRolling () );

    // data - vertical tail
    _ui->spinBoxVerTailArea   ->setValue( ac->getVerTailArea   () );
    _ui->spinBoxVerTailHeight ->setValue( ac->getVerTailHeight () );
    _ui->spinBoxVerTailSweep  ->setValue( ac->getVerTailSweep  () );
    _ui->spinBoxVerTailCR     ->setValue( ac->getVerTailCR     () );
    _ui->spinBoxVerTailCT     ->setValue( ac->getVerTailCT     () );
    _ui->spinBoxVerTailTC     ->setValue( ac->getVerTailTC     () );
    _ui->spinBoxVerTailArm    ->setValue( ac->getVerTailArm    () );
    _ui->spinBoxRuddArea      ->setValue( ac->getRuddArea      () );
    _ui->spinBoxVerTailAR     ->setValue( ac->getVerTailAR     () );
    _ui->spinBoxVerTailTR     ->setValue( ac->getVerTailTR     () );

    _ui->checkBoxTailT        ->setChecked( ac->getTailT        () );
    _ui->checkBoxVerTailRotor ->setChecked( ac->getVerTailRotor () );

    // data - landing gear
    _ui->spinBoxMainGearLength ->setValue( ac->getMainGearLength () );
    _ui->spinBoxNoseGearLength ->setValue( ac->getNoseGearLength () );

    _ui->spinBoxMainGearWheels ->setValue( ac->getMainGearWheels () );
    _ui->spinBoxMainGearStruts ->setValue( ac->getMainGearStruts () );
    _ui->spinBoxNoseGearWheels ->setValue( ac->getNoseGearWheels () );

    _ui->checkBoxGearFixed  ->setChecked( ac->getGearFixed  () );
    _ui->checkBoxGearCross  ->setChecked( ac->getGearCross  () );
    _ui->checkBoxGearTripod ->setChecked( ac->getGearTripod () );

    _ui->checkBoxGearMainKneel ->setChecked( ac->getGearMainKneel () );
    _ui->checkBoxGearNoseKneel ->setChecked( ac->getGearNoseKneel () );

    // data - engine
    _ui->spinBoxEngineMass ->setValue( ac->getEngineMass() );

    // data - rotors
    _ui->spinBoxMainRotorDiameter  ->setValue( ac->getMainRotorRad    () * 2.0 );
    _ui->spinBoxMainRotorChord     ->setValue( ac->getMainRotorChord  () );
    _ui->spinBoxMainRotorRPM       ->setValue( ac->getMainRotorRPM    () );
    _ui->spinBoxTailRotorDiameter  ->setValue( ac->getTailRotorRad    () * 2.0 );
    _ui->spinBoxMainRotorGear      ->setValue( ac->getMainRotorGear   () );
    _ui->spinBoxPowerLimit         ->setValue( ac->getPowerLimit      () );
    _ui->spinBoxMainRotorTipVel    ->setValue( ac->getMainRotorTipVel () );
    _ui->spinBoxMainRotorBlades    ->setValue( ac->getMainRotorBlades () );

    // COMPONENTS

    _ui->listComponents->clear();

    Aircraft::Components components = ac->getComponents();
    Aircraft::Components::iterator it = components.begin();

    while ( it != components.end() )
    {
        QString name = (*it)->getName();
        _ui->listComponents->addItem( new QListWidgetItem( name, _ui->listComponents ) );

        it++;
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

    // Rayner: Aircraft Design, p.205, eq. 7.13
    double s_wet = 3.4 * ( ( a_top + a_side ) / 2.0 );

    _ui->spinBoxWettedArea->setValue( s_wet );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::updateWingAR()
{
    if ( _doc.getAircraft()->getWingArea() > 0.0 )
    {
        double ar = pow( _doc.getAircraft()->getWingSpan(), 2.0 ) / _doc.getAircraft()->getWingArea();
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
    if ( _doc.getAircraft()->getWingCR() > 0.0 )
    {
        double tr = _doc.getAircraft()->getWingCT() / _doc.getAircraft()->getWingCR();
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
    if ( _doc.getAircraft()->getHorTailArea() > 0.0 )
    {
        double ar = pow( _doc.getAircraft()->getHorTailSpan(), 2.0 ) / _doc.getAircraft()->getHorTailArea();
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
    if ( _doc.getAircraft()->getHorTailCR() > 0.0 )
    {
        double tr = _doc.getAircraft()->getHorTailCT() / _doc.getAircraft()->getHorTailCR();
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
    if ( _doc.getAircraft()->getVerTailArea() > 0.0 )
    {
        double ar = pow( _doc.getAircraft()->getVerTailHeight(), 2.0 ) / _doc.getAircraft()->getVerTailArea();
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
    if ( _doc.getAircraft()->getVerTailCR() > 0.0 )
    {
        double tr = _doc.getAircraft()->getVerTailCT() / _doc.getAircraft()->getVerTailCR();
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
    Aircraft::Components components = _doc.getAircraft()->getComponents();

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
    Aircraft::Components components = _doc.getAircraft()->getComponents();
    int currentRow = _ui->listComponents->currentRow();

    if ( currentRow >=0 && currentRow < (int)components.size() )
    {
        _doc.getAircraft()->delComponent( currentRow );
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
    Type type = FighterAttack;

    switch ( index )
    {
        case FighterAttack   : type = FighterAttack   ; break;
        case CargoTransport  : type = CargoTransport  ; break;
        case GeneralAviation : type = GeneralAviation ; break;
        case Helicopter      : type = Helicopter      ; break;
    }

    setAircraftType( type );

    _doc.getAircraft()->setType( type );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMassEmpty_valueChanged( double arg1 )
{
    _doc.getAircraft()->setM_empty( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMassMaxTO_valueChanged( double arg1 )
{
    _doc.getAircraft()->setM_maxTO( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMassMaxLand_valueChanged( double arg1 )
{
    _doc.getAircraft()->setM_maxLand( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMaxNz_valueChanged( double arg1 )
{
    _doc.getAircraft()->setNzMax( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMaxNzLand_valueChanged(double arg1)
{
    _doc.getAircraft()->setNzMaxLand( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxStallV_valueChanged( double arg1 )
{
    _doc.getAircraft()->setStallV( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxCruiseV_valueChanged( double arg1 )
{
    _doc.getAircraft()->setCruiseV( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxCruiseH_valueChanged( double arg1 )
{
    _doc.getAircraft()->setCruiseH( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMachMax_valueChanged( double arg1 )
{
    _doc.getAircraft()->setMachMax( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxNavyAircraft_toggled( bool checked )
{
    _doc.getAircraft()->setNavyAircraft( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_comboBoxCargoDoor_currentIndexChanged( int index )
{
    CargoDoor door = NoCargoDoor;

    switch ( index )
    {
        case NoCargoDoor       : door = NoCargoDoor       ; break;
        case OneSideCargoDoor  : door = OneSideCargoDoor  ; break;
        case TwoSideCargoDoor  : door = TwoSideCargoDoor  ; break;
        case AftClamshellDoor  : door = AftClamshellDoor  ; break;
        case TwoSideAndAftDoor : door = TwoSideAndAftDoor ; break;
    }

    _doc.getAircraft()->setCargoDoor( door );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxFuseLength_valueChanged( double arg1 )
{
    _doc.getAircraft()->setFuseLength( arg1 );
    _saved = false;
    updateTitleBar();
    updateWettedArea();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxFuseHeight_valueChanged( double arg1 )
{
    _doc.getAircraft()->setFuseHeight( arg1 );
    _saved = false;
    updateTitleBar();
    updateWettedArea();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxFuseWidth_valueChanged( double arg1 )
{
    _doc.getAircraft()->setFuseWidth( arg1 );
    _saved = false;
    updateTitleBar();
    updateWettedArea();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxNoseLength_valueChanged( double arg1 )
{
    _doc.getAircraft()->setNoseLength( arg1 );
    _saved = false;
    updateTitleBar();
    updateWettedArea();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxPressVol_valueChanged( double arg1 )
{
    _doc.getAircraft()->setPressVol( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWettedArea_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWettedArea( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxFuselageLG_toggled( bool checked )
{
    _doc.getAircraft()->setFuselageLG( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxCargoRamp_toggled( bool checked )
{
    _doc.getAircraft()->setCargoRamp( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingArea_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingArea( arg1 );
    _saved = false;
    updateTitleBar();
    updateWingAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingExp_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingExp( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingSpan_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingSpan( arg1 );
    _saved = false;
    updateTitleBar();
    updateWingAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingSweep_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingSweep( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingCR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingCR( arg1 );
    _saved = false;
    updateTitleBar();
    updateWingTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingCT_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingCT( arg1 );
    _saved = false;
    updateTitleBar();
    updateWingTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingTC_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingTC( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingFuel_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingFuel( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxCtrlArea_valueChanged( double arg1 )
{
    _doc.getAircraft()->setCtrlArea( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingAR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingAR( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxWingTR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setWingTR( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxWingDelta_toggled( bool checked )
{
    _doc.getAircraft()->setWingDelta( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxWingVar_toggled( bool checked )
{
    _doc.getAircraft()->setWingVar( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailArea_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailArea( arg1 );
    _saved = false;
    updateTitleBar();
    updateHorTailAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailSpan_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailSpan( arg1 );
    _saved = false;
    updateTitleBar();
    updateHorTailAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailSweep_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailSweep( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailCR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailCR( arg1 );
    _saved = false;
    updateTitleBar();
    updateHorTailTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailCT_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailCT( arg1 );
    _saved = false;
    updateTitleBar();
    updateHorTailTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailTC_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailTC( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxElevArea_valueChanged( double arg1 )
{
    _doc.getAircraft()->setElevArea( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailFW_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailFW( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailArm_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailArm( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailAR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailAR( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxHorTailTR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setHorTailTR( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxHorTailMoving_toggled( bool checked )
{
    _doc.getAircraft()->setHorTailMoving( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxHorTailRolling_toggled( bool checked )
{
    _doc.getAircraft()->setHorTailRolling( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailArea_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailArea( arg1 );
    _saved = false;
    updateTitleBar();
    updateVerTailAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailHeight_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailHeight( arg1 );
    _saved = false;
    updateTitleBar();
    updateVerTailAR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailSweep_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailSweep( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailCR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailCR( arg1 );
    _saved = false;
    updateTitleBar();
    updateVerTailTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailCT_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailCT( arg1 );
    _saved = false;
    updateTitleBar();
    updateVerTailTR();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailTC_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailTC( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailArm_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailArm( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxRuddArea_valueChanged( double arg1 )
{
    _doc.getAircraft()->setRuddArea( arg1 );
    _saved = false;
    updateTitleBar();
}

void MainWindow::on_spinBoxVerTailAR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailAR( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxVerTailTR_valueChanged( double arg1 )
{
    _doc.getAircraft()->setVerTailTR( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxTailT_toggled( bool checked )
{
    _doc.getAircraft()->setTailT( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxVerTailRotor_toggled( bool checked )
{
    _doc.getAircraft()->setVerTailRotor( checked );
    _saved = false;
    updateTitleBar();
}


////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainGearLength_valueChanged( double arg1 )
{
    _doc.getAircraft()->setMainGearLength( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxNoseGearLength_valueChanged( double arg1 )
{
    _doc.getAircraft()->setNoseGearLength( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainGearWheels_valueChanged( int arg1 )
{
    _doc.getAircraft()->setMainGearWheels( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainGearStruts_valueChanged( int arg1 )
{
    _doc.getAircraft()->setMainGearStruts( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxNoseGearWheels_valueChanged( int arg1 )
{
    _doc.getAircraft()->setNoseGearWheels( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearFixed_toggled( bool checked )
{
    _doc.getAircraft()->setGearFixed( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearCross_toggled( bool checked )
{
    _doc.getAircraft()->setGearCross( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearTripod_toggled( bool checked )
{
    _doc.getAircraft()->setGearTripod( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearMainKneel_toggled( bool checked )
{
    _doc.getAircraft()->setGearMainKneel( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_checkBoxGearNoseKneel_toggled( bool checked )
{
    _doc.getAircraft()->setGearNoseKneel( checked );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxEngineMass_valueChanged( double arg1 )
{
    _doc.getAircraft()->setEngineMass( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorDiameter_valueChanged( double arg1 )
{
    _doc.getAircraft()->setMainRotorRad( 0.5 * arg1 );
    _saved = false;
    updateTitleBar();
    updateRotorTipVel();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorChord_valueChanged( double arg1 )
{
    _doc.getAircraft()->setMainRotorChord( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorRPM_valueChanged( double arg1 )
{
    _doc.getAircraft()->setMainRotorRPM( arg1 );
    _saved = false;
    updateTitleBar();
    updateRotorTipVel();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxTailRotorDiameter_valueChanged( double arg1 )
{
    _doc.getAircraft()->setTailRotorRad( 0.5 * arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorGear_valueChanged( double arg1 )
{
    _doc.getAircraft()->setMainRotorGear( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxPowerLimit_valueChanged( double arg1 )
{
    _doc.getAircraft()->setPowerLimit( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorTipVel_valueChanged( double arg1 )
{
    _doc.getAircraft()->setMainRotorTipVel( arg1 );
    _saved = false;
    updateTitleBar();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_spinBoxMainRotorBlades_valueChanged( int arg1 )
{
    _doc.getAircraft()->setMainRotorBlades( arg1 );
    _saved = false;
    updateTitleBar();
}
