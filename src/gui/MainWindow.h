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
#ifndef MC_MASS_GUI_MAINWINDOW_H_
#define MC_MASS_GUI_MAINWINDOW_H_

#include <QMainWindow>
#include <QSettings>
#include <QShortcut>

#include <AircraftFile.h>

#include <gui/DockWidgetParams.h>
#include <gui/DockWidgetComponents.h>
#include <gui/DockWidgetResults.h>
#include <gui/RecentFileAction.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    using RecentFilesActions = QVector<RecentFileAction*>;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openFileFromCommandLine(QString filename);

protected:

    void closeEvent(QCloseEvent* event) override;

private:

    Ui::MainWindow* _ui;

    DockWidgetParams*     _dockParams     = nullptr;
    DockWidgetComponents* _dockComponents = nullptr;
    DockWidgetResults*    _dockResults    = nullptr;

    QShortcut* _sc_save   = nullptr;
    QShortcut* _sc_export = nullptr;

    AircraftFile _aircraftFile;

    QString _currentFile;

    RecentFilesActions _recentActions;

    int _recentFilesMax = 10;

    bool _saved = true;

    void addRecentFile(QString file = "");

    void askIfSave();

    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void exportFileAs();

    void readFile(QString fileName);
    void saveFile(QString fileName);
    void exportAs(QString fileName);

    void setCurrentFile(const QString& currentFile);

    void setSideDockAreasFullHeight(bool left, bool rght);

    void settingsRead();
    void settingsRead_RecentFiles(QSettings &settings);

    void settingsSave();
    void settingsSave_RecentFiles(QSettings &settings);

    void updateGUI();
    void updateTitleBar();

private slots:

    void on_aircraftChanged();
    void on_currentComponentChanged();

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExport_triggered();
    void on_actionExit_triggered();

    void on_actionClearRecent_triggered();

    void on_actionShowGrid_toggled(bool checked);
    void on_actionViewDefault_triggered();
    void on_actionViewTop_triggered();
    void on_actionViewBottom_triggered();
    void on_actionViewBack_triggered();
    void on_actionViewFront_triggered();
    void on_actionViewLeft_triggered();
    void on_actionViewRight_triggered();

    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();

    void recentFile_triggered(RecentFileAction* action);
};

#endif // MC_MASS_GUI_MAINWINDOW_H_
