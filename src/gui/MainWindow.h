/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/
#ifndef GUI_MAINWINDOW_H_
#define GUI_MAINWINDOW_H_

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include <QSettings>
#include <QShortcut>

#include <defs.h>

#include <DataFile.h>

#include <gui/RecentFileAction.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief Main window class.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    typedef std::vector< RecentFileAction* > RecentFilesActions;

    /** @brief Constructor. */
    explicit MainWindow( QWidget *parent = Q_NULLPTR );

    /** @brief Destructor. */
    virtual ~MainWindow();

protected:

    /** */
    void closeEvent( QCloseEvent *event );

private:

    Ui::MainWindow *_ui;                        ///< UI object

    QShortcut *_scSave;                         ///< key shortcut - save
    QShortcut *_scExport;                       ///< key shortcut - export

    DataFile _dataFile;                         ///< data file

    bool _saved;                                ///<

    QString _currentFile;                       ///<

    QStringList _recentFilesList;               ///<
    RecentFilesActions _recentFilesActions;     ///<

    void askIfSave();

    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void exportFileAs();

    void readFile( QString fileName );
    void saveFile( QString fileName );
    void exportAs( QString fileName );

    void settingsRead();
    void settingsRead_RecentFiles( QSettings &settings );

    void settingsSave();
    void settingsSave_RecentFiles( QSettings &settings );

    void addComponent();
    void editComponent();

    void setAircraftType( AircraftData::Type type );

    void updateGUI();
    void updateTitleBar();

    void updateWettedArea();
    void updateWingAR();
    void updateWingTR();
    void updateHorTailAR();
    void updateHorTailTR();
    void updateVerTailAR();
    void updateVerTailTR();
    void updateRotorTipVel();

    void updateRecentFiles( QString file = "" );

private slots:

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExport_triggered();
    void on_actionExit_triggered();

    void on_actionClearRecent_triggered();

    void recentFile_triggered( int id );

    void on_actionAbout_triggered();

    void on_listComponents_currentRowChanged( int currentRow );
    void on_listComponents_doubleClicked( const QModelIndex & );

    void on_pushButtonAdd_clicked();
    void on_pushButtonDel_clicked();
    void on_pushButtonEdit_clicked();

    void on_comboBoxAircraftType_currentIndexChanged( int index );

    void on_spinBoxMassEmpty_valueChanged   ( double arg1 );
    void on_spinBoxMTOW_valueChanged        ( double arg1 );
    void on_spinBoxMassMaxLand_valueChanged ( double arg1 );
    void on_spinBoxMaxNz_valueChanged       ( double arg1 );
    void on_spinBoxMaxNzLand_valueChanged   ( double arg1 );
    void on_spinBoxStallV_valueChanged      ( double arg1 );
    void on_spinBoxCruiseV_valueChanged     ( double arg1 );
    void on_spinBoxCruiseH_valueChanged     ( double arg1 );
    void on_spinBoxMachMax_valueChanged     ( double arg1 );
    void on_checkBoxNavyAircraft_toggled ( bool checked );

    void on_comboBoxCargoDoor_currentIndexChanged( int index );
    void on_spinBoxFuseLength_valueChanged ( double arg1 );
    void on_spinBoxFuseHeight_valueChanged ( double arg1 );
    void on_spinBoxFuseWidth_valueChanged  ( double arg1 );
    void on_spinBoxNoseLength_valueChanged ( double arg1 );
    void on_spinBoxPressVol_valueChanged   ( double arg1 );
    void on_spinBoxWettedAreaEstimated_valueChanged ( double arg1 );
    void on_spinBoxWettedAreaReal_valueChanged ( double arg1 );
    void on_checkBoxFuselageLG_toggled ( bool checked );
    void on_checkBoxCargoRamp_toggled  ( bool checked );
    void on_checkBoxWettedAreaOverride_toggled( bool checked );

    void on_spinBoxWingArea_valueChanged    ( double arg1 );
    void on_spinBoxWingAreaExp_valueChanged ( double arg1 );
    void on_spinBoxWingSpan_valueChanged    ( double arg1 );
    void on_spinBoxWingSweep_valueChanged   ( double arg1 );
    void on_spinBoxWingCRoot_valueChanged   ( double arg1 );
    void on_spinBoxWingCTip_valueChanged    ( double arg1 );
    void on_spinBoxWingTC_valueChanged      ( double arg1 );
    void on_spinBoxWingFuel_valueChanged    ( double arg1 );
    void on_spinBoxCtrlArea_valueChanged    ( double arg1 );
    void on_spinBoxWingAR_valueChanged      ( double arg1 );
    void on_spinBoxWingTR_valueChanged      ( double arg1 );
    void on_checkBoxWingDelta_toggled    ( bool checked );
    void on_checkBoxWingVarSweep_toggled ( bool checked );

    void on_spinBoxHorTailArea_valueChanged  ( double arg1 );
    void on_spinBoxHorTailSpan_valueChanged  ( double arg1 );
    void on_spinBoxHorTailSweep_valueChanged ( double arg1 );
    void on_spinBoxHorTailCRoot_valueChanged ( double arg1 );
    void on_spinBoxHorTailCTip_valueChanged  ( double arg1 );
    void on_spinBoxHorTailTC_valueChanged    ( double arg1 );
    void on_spinBoxElevArea_valueChanged     ( double arg1 );
    void on_spinBoxHorTailWF_valueChanged    ( double arg1 );
    void on_spinBoxHorTailArm_valueChanged   ( double arg1 );
    void on_spinBoxHorTailAR_valueChanged    ( double arg1 );
    void on_spinBoxHorTailTR_valueChanged    ( double arg1 );
    void on_checkBoxHorTailMoving_toggled  ( bool checked );
    void on_checkBoxHorTailRolling_toggled ( bool checked );

    void on_spinBoxVerTailArea_valueChanged   ( double arg1 );
    void on_spinBoxVerTailHeight_valueChanged ( double arg1 );
    void on_spinBoxVerTailSweep_valueChanged  ( double arg1 );
    void on_spinBoxVerTailCRoot_valueChanged  ( double arg1 );
    void on_spinBoxVerTailCTip_valueChanged   ( double arg1 );
    void on_spinBoxVerTailTC_valueChanged     ( double arg1 );
    void on_spinBoxVerTailArm_valueChanged    ( double arg1 );
    void on_spinBoxRuddArea_valueChanged      ( double arg1 );
    void on_spinBoxVerTailAR_valueChanged     ( double arg1 );
    void on_spinBoxVerTailTR_valueChanged     ( double arg1 );
    void on_checkBoxTailT_toggled        ( bool checked );
    void on_checkBoxVerTailRotor_toggled ( bool checked );

    void on_spinBoxMainGearLength_valueChanged ( double arg1 );
    void on_spinBoxNoseGearLength_valueChanged ( double arg1 );
    void on_spinBoxMainGearWheels_valueChanged ( int arg1 );
    void on_spinBoxMainGearStruts_valueChanged ( int arg1 );
    void on_spinBoxNoseGearWheels_valueChanged ( int arg1 );
    void on_checkBoxGearFixed_toggled  ( bool checked );
    void on_checkBoxGearCross_toggled  ( bool checked );
    void on_checkBoxGearTripod_toggled ( bool checked );
    void on_checkBoxGearMainKneel_toggled ( bool checked );
    void on_checkBoxGearNoseKneel_toggled ( bool checked );

    void on_spinBoxEngineMass_valueChanged( double arg1 );

    void on_spinBoxMainRotorDiameter_valueChanged ( double arg1 );
    void on_spinBoxMainRotorChord_valueChanged    ( double arg1 );
    void on_spinBoxMainRotorRPM_valueChanged      ( double arg1 );
    void on_spinBoxTailRotorDiameter_valueChanged ( double arg1 );
    void on_spinBoxMainRotorGear_valueChanged     ( double arg1 );
    void on_spinBoxPowerLimit_valueChanged        ( double arg1 );
    void on_spinBoxMainRotorTipVel_valueChanged   ( double arg1 );
    void on_spinBoxMainRotorBlades_valueChanged ( int arg1 );
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // GUI_MAINWINDOW_H_
