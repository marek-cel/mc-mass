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

#include <gui/MainWindow.h>
#include <ui_MainWindow.h>

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

#include <defs.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _dockParams     = new DockWidgetParams(&_aircraftFile, this);
    _dockComponents = new DockWidgetComponents(&_aircraftFile, this);
    _dockResults    = new DockWidgetResults(&_aircraftFile, this);

    _dockParams     ->setObjectName("DockParams");
    _dockComponents ->setObjectName("DockComponents");
    _dockResults    ->setObjectName("DockComponents");

    addDockWidget( Qt::LeftDockWidgetArea   , _dockParams     );
    addDockWidget( Qt::RightDockWidgetArea  , _dockComponents );
    addDockWidget( Qt::BottomDockWidgetArea , _dockResults    );

    setSideDockAreasFullHeight(true, true);

    settingsRead();

    _dockParams     ->setVisible(true);
    _dockComponents ->setVisible(true);
    _dockResults    ->setVisible(true);

    connect(_dockParams     , SIGNAL(aircraftChanged()), this, SLOT(on_aircraftChanged()));
    connect(_dockComponents , SIGNAL(aircraftChanged()), this, SLOT(on_aircraftChanged()));
    connect(_dockComponents , SIGNAL(currentComponentChanged()), this, SLOT(on_currentComponentChanged()));

    _sc_save   = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_triggered()));
    _sc_export = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_E), this, SLOT(on_actionExport_triggered()));

    updateGUI();
}

MainWindow::~MainWindow()
{
    settingsSave();

    if ( _sc_save   ) { delete _sc_save;   } _sc_save   = nullptr;
    if ( _sc_export ) { delete _sc_export; } _sc_export = nullptr;

    if ( _ui ) { delete _ui; } _ui = nullptr;
}

void MainWindow::openFileFromCommandLine(QString filename)
{
    readFile(filename);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    askIfSave();

    /////////////////////////////////
    QMainWindow::closeEvent( event );
    /////////////////////////////////
}

void MainWindow::addRecentFile(QString file)
{
    QStringList recent_files;
    for ( auto action : _recentActions )
    {
        action->disconnect();
        recent_files.push_back(action->file());
    }

    _recentActions.clear();
    _ui->menuRecentFiles->clear();

    if ( file.length() > 0 )
    {
#       ifdef WIN32
        if ( recent_files.contains(file, Qt::CaseInsensitive) )
#       else
        if ( recent_files.contains(file, Qt::CaseSensitive) )
#       endif
        {
            recent_files.move(recent_files.indexOf(file),0);
        }
        else
        {
            recent_files.push_front(file);
        }
    }

    for ( int i = 0; i < recent_files.size() && i < _recentFilesMax; ++i )
    {
        RecentFileAction* action = new RecentFileAction(recent_files.at(i), _ui->menuRecentFiles);
        _recentActions.push_back(action);

        connect(action, SIGNAL(triggered(RecentFileAction*)), SLOT(recentFile_triggered(RecentFileAction*)));
        _ui->menuRecentFiles->addAction(action);
    }
}

void MainWindow::askIfSave()
{
    if ( !_saved )
    {
        QString title = windowTitle();
        QString text = tr("Current file has unsaved changes.");

        QMessageBox::StandardButton result =
                QMessageBox::question(this, title, text,
                                      QMessageBox::Save | QMessageBox::Discard,
                                      QMessageBox::Save);

        if ( result == QMessageBox::Save )
        {
            saveFile();
        }
    }
}

void MainWindow::newFile()
{
    askIfSave();

    setCurrentFile("");

    _aircraftFile.NewEmpty();

    updateGUI();
    updateTitleBar();
}

void MainWindow::openFile()
{
    askIfSave();

    QString caption = "Open...";
    QString dir = ( _currentFile.length() > 0 ) ? QFileInfo(_currentFile).absolutePath() : "";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "MC-Mass Files (*.mcmass)";

    QString file = QFileDialog::getOpenFileName(this, caption, dir, filter, &selectedFilter);

    if ( file.length() > 0 )
    {
        QDir proj_dir = QFileInfo(file).absoluteDir();
        file = proj_dir.absoluteFilePath(file);
        setCurrentFile(file);
        addRecentFile(_currentFile);
        readFile(_currentFile);
    }

    updateGUI();
    _saved = true;
    updateTitleBar();
}

void MainWindow::saveFile()
{
    if ( _currentFile.length() > 0 )
    {
        saveFile(_currentFile);
    }
    else
    {
        saveFileAs();
    }
}

void MainWindow::saveFileAs()
{
    QString caption = "Save as...";
    QString dir = ( _currentFile.length() > 0 ) ? QFileInfo(_currentFile).absolutePath() : ".";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "MC-Mass Files (*.mcmass)";

    QString newFile = QFileDialog::getSaveFileName(
        this, caption, dir, filter, &selectedFilter
    );

    if ( newFile.length() > 0 )
    {
        QDir proj_dir = QFileInfo(newFile).absoluteDir();
        newFile = proj_dir.absoluteFilePath(newFile);
        setCurrentFile(newFile);
        saveFile(_currentFile);
    }
}

void MainWindow::exportFileAs()
{
    QString fileName = "";

    QString caption = "Export as...";
    QString dir = ( fileName.length() > 0 ) ? QFileInfo(fileName).absolutePath() : ".";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "Text File (*.txt)";

    fileName = QFileDialog::getSaveFileName(
        this, caption, dir, filter, &selectedFilter
    );

    if ( fileName.length() > 0 )
    {
        exportAs(fileName);
    }
}

void MainWindow::readFile(QString fileName)
{
    if ( QFileInfo(fileName).suffix() == QString("mcmass") )
    {
        QFileInfo fileInfo(fileName);
        QDir proj_dir = fileInfo.absoluteDir();
        QString fileFullPath = proj_dir.absoluteFilePath(fileInfo.fileName());

        if ( !_aircraftFile.ReadFile(fileFullPath.toStdString().c_str()) )
        {
            QMessageBox::warning(
                this, APP_TITLE,
                tr("Cannot read file %1.").arg(fileFullPath)
            );
        }
        else
        {
            setCurrentFile(fileFullPath);
            addRecentFile(fileFullPath);
        }
    }

    updateGUI();
    _saved = true;
    updateTitleBar();
}

void MainWindow::saveFile(QString fileName)
{
    if ( _aircraftFile.SaveFile(fileName.toStdString().c_str()) )
    {
        _saved = true;
    }
    else
    {
        QMessageBox::warning(
            this, APP_TITLE,
            tr("Cannot save file %1.").arg(fileName)
        );
    }

    updateGUI();
    updateTitleBar();
}

void MainWindow::exportAs(QString fileName)
{
    if ( !_aircraftFile.ExportAs(fileName.toStdString().c_str()) )
    {
        QMessageBox::warning(
            this, APP_TITLE,
            tr("Cannot export file %1.").arg(fileName)
        );
    }
}

void MainWindow::setCurrentFile(const QString& currentFile)
{
    _currentFile = currentFile;
    _ui->widgetCGI->getManagerCGI()->setProjectDir(QFileInfo(_currentFile).absolutePath());
}

void MainWindow::setSideDockAreasFullHeight(bool left, bool rght)
{
    if ( left )
    {
        setCorner( Qt::TopLeftCorner    , Qt::LeftDockWidgetArea );
        setCorner( Qt::BottomLeftCorner , Qt::LeftDockWidgetArea );
    }
    else
    {
        setCorner( Qt::TopLeftCorner    , Qt::TopDockWidgetArea    );
        setCorner( Qt::BottomLeftCorner , Qt::BottomDockWidgetArea );
    }

    if ( rght )
    {
        setCorner( Qt::TopRightCorner    , Qt::RightDockWidgetArea );
        setCorner( Qt::BottomRightCorner , Qt::RightDockWidgetArea );
    }
    else
    {
        setCorner( Qt::TopRightCorner    , Qt::TopDockWidgetArea    );
        setCorner( Qt::BottomRightCorner , Qt::BottomDockWidgetArea );
    }
}

void MainWindow::settingsRead()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("main_window");

    restoreState(settings.value("state").toByteArray());
    restoreGeometry(settings.value("geometry").toByteArray());

    bool grid_visible = settings.value("grid_visible" , 1).toBool();
    _ui->actionShowGrid->setChecked(grid_visible);

    settingsRead_RecentFiles(settings);

    settings.endGroup();
}

void MainWindow::settingsRead_RecentFiles(QSettings& settings)
{
    QStringList recent_files = settings.value("recent_files").toStringList();
    for ( auto file : recent_files )
    {
        RecentFileAction* action = new RecentFileAction(file, _ui->menuRecentFiles);
        _recentActions.push_back(action);
        connect(action, SIGNAL(triggered(RecentFileAction*)), SLOT(recentFile_triggered(RecentFileAction*)));
        _ui->menuRecentFiles->addAction(action);
    }
}

void MainWindow::settingsSave()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("main_window");

    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());

    settings.setValue("grid_visible", _ui->actionShowGrid->isChecked() ? 1 : 0);

    settingsSave_RecentFiles(settings);

    settings.endGroup();
}

void MainWindow::settingsSave_RecentFiles(QSettings& settings)
{
    QStringList recent_files;
    for ( auto action : _recentActions )
    {
        recent_files.push_back(action->file());
    }

    settings.setValue("recent_files", recent_files);
}

void MainWindow::updateGUI()
{
    _dockParams     ->updateGUI();
    _dockComponents ->updateGUI();
    _dockResults    ->updateGUI();

    const AircraftData* data = _aircraftFile.GetAircraftData();
    _ui->widgetCGI->getManagerCGI()->setModelData(
                data->model3d.file,
                data->model3d.offset_x(),
                data->model3d.offset_y(),
                data->model3d.offset_z(),
                angle::radian_t(data->model3d.rotation_x)(),
                angle::radian_t(data->model3d.rotation_y)(),
                angle::radian_t(data->model3d.rotation_z)(),
                data->model3d.scale
    );
}

void MainWindow::updateTitleBar()
{
    QString title = APP_TITLE;

    if ( _currentFile.length() > 0 )
    {
        title += " - " + QFileInfo(_currentFile).fileName();
    }

    if ( !_saved ) title += " (*)";

    setWindowTitle(title);
}

void MainWindow::on_aircraftChanged()
{
    _saved = false;
    updateTitleBar();
    updateGUI();
}

void MainWindow::on_currentComponentChanged()
{
    int index = _dockComponents->getCurrentComponentIndex();
    if ( index >= 0 )
    {
        const Component* component = _aircraftFile.GetAircraft()->GetComponent(index);

        PositionVector pos = component->GetPosition();

        units::length::meter_t l = component->GetLength();
        units::length::meter_t w = component->GetWidth();
        units::length::meter_t h = component->GetHeight();

        _ui->widgetCGI->getManagerCGI()->setHighlightData(
                    true,
                    pos.x()(), pos.y()(), pos.z()(),
                    l(), w(), h()
        );
    }
    else
    {
        _ui->widgetCGI->getManagerCGI()->setHighlightData(false);
    }
}

void MainWindow::on_actionNew_triggered()
{
    newFile();
}

void MainWindow::on_actionOpen_triggered()
{
    openFile();
}

void MainWindow::on_actionSave_triggered()
{
    saveFile();
}

void MainWindow::on_actionSaveAs_triggered()
{
    saveFileAs();
}

void MainWindow::on_actionExport_triggered()
{
    exportFileAs();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionClearRecent_triggered()
{
    for ( auto action : _recentActions )
    {
        action->disconnect(this, SLOT(recentFile_triggered(RecentFileAction*)));
    }
    _recentActions.clear();
    _ui->menuRecentFiles->clear();
}

void MainWindow::on_actionShowGrid_toggled(bool checked)
{
    _ui->widgetCGI->getManagerCGI()->setGridVisibility(checked);
}

void MainWindow::on_actionViewDefault_triggered()
{
    _ui->widgetCGI->resetView();
}

void MainWindow::on_actionViewTop_triggered()
{
    _ui->widgetCGI->topView();
}

void MainWindow::on_actionViewBottom_triggered()
{
    _ui->widgetCGI->bottomView();
}

void MainWindow::on_actionViewBack_triggered()
{
    _ui->widgetCGI->backView();
}

void MainWindow::on_actionViewFront_triggered()
{
    _ui->widgetCGI->frontView();
}

void MainWindow::on_actionViewLeft_triggered()
{
    _ui->widgetCGI->leftView();
}

void MainWindow::on_actionViewRight_triggered()
{
    _ui->widgetCGI->rightView();
}

void MainWindow::on_actionAbout_triggered()
{
    QFile aboutHtmlFile(":/gui/html/about.html");

    QString aboutWinTitle;
    QString aboutInfoText;

    aboutWinTitle = tr("About");

    if ( aboutHtmlFile.open(QIODevice::ReadOnly) )
    {
        aboutInfoText = aboutHtmlFile.readAll();
        aboutHtmlFile.close();
    }

    QMessageBox::about(this, aboutWinTitle, aboutInfoText);
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::recentFile_triggered(RecentFileAction* action)
{
    askIfSave();
    readFile(action->file());
}
