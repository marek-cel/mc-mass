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
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    dockParams_     = new DockWidgetParams(&aircraftFile_, this);
    dockComponents_ = new DockWidgetComponents(&aircraftFile_, this);
    dockResults_    = new DockWidgetResults(&aircraftFile_, this);

    dockParams_->setObjectName("DockParams");
    dockComponents_->setObjectName("DockComponents");
    dockResults_->setObjectName("DockComponents");

    addDockWidget(Qt::LeftDockWidgetArea, dockParams_);
    addDockWidget(Qt::RightDockWidgetArea, dockComponents_);
    addDockWidget(Qt::BottomDockWidgetArea, dockResults_);

    setSideDockAreasFullHeight(true, true);

    settingsRead();

    dockParams_->setVisible(true);
    dockComponents_->setVisible(true);
    dockResults_->setVisible(true);

    connect(dockParams_     , SIGNAL(aircraftChanged()), this, SLOT(on_aircraftChanged()));
    connect(dockComponents_ , SIGNAL(aircraftChanged()), this, SLOT(on_aircraftChanged()));
    connect(dockComponents_ , SIGNAL(currentComponentChanged()), this, SLOT(on_currentComponentChanged()));

    sc_save_   = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_triggered()));
    sc_export_ = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_E), this, SLOT(on_actionExport_triggered()));

    updateGUI();
}

MainWindow::~MainWindow()
{
    settingsSave();

    if ( sc_save_   ) { delete sc_save_;   } sc_save_   = nullptr;
    if ( sc_export_ ) { delete sc_export_; } sc_export_ = nullptr;

    if ( ui_ ) { delete ui_; } ui_ = nullptr;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    askIfSave();

    /////////////////////////////////
    QMainWindow::closeEvent( event );
    /////////////////////////////////
}

void MainWindow::askIfSave()
{
    if ( !saved_ )
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

    aircraftFile_.NewEmpty();

    updateGUI();
    updateTitleBar();
}

void MainWindow::openFile()
{
    askIfSave();

    QString caption = "Open...";
    QString dir = ( currentFile_.length() > 0 ) ? QFileInfo(currentFile_).absolutePath() : "";
    QString filter;
    QString selectedFilter;

    filter += selectedFilter = "MC-Mass Files (*.mcmass)";

    QString file = QFileDialog::getOpenFileName(this, caption, dir, filter, &selectedFilter);

    if ( file.length() > 0 )
    {
        QDir proj_dir = QFileInfo(file).absoluteDir();
        file = proj_dir.absoluteFilePath(file);
        setCurrentFile(file);
        updateRecentFiles(currentFile_);
        readFile(currentFile_);
    }

    updateGUI();
    saved_ = true;
    updateTitleBar();
}

void MainWindow::saveFile()
{
    if ( currentFile_.length() > 0 )
    {
        saveFile(currentFile_);
    }
    else
    {
        saveFileAs();
    }
}

void MainWindow::saveFileAs()
{
    QString caption = "Save as...";
    QString dir = ( currentFile_.length() > 0 ) ? QFileInfo(currentFile_).absolutePath() : ".";
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
        saveFile(currentFile_);
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
        QDir proj_dir = QFileInfo(fileName).absoluteDir();
        fileName = proj_dir.absoluteFilePath(fileName);

        if ( !aircraftFile_.ReadFile(fileName.toStdString().c_str()) )
        {
            QMessageBox::warning(
                this, APP_TITLE,
                tr("Cannot read file %1.").arg(fileName)
            );
        }
        else
        {
            setCurrentFile(fileName);
        }
    }

    updateGUI();
    saved_ = true;
    updateTitleBar();
}

void MainWindow::saveFile(QString fileName)
{
    if ( aircraftFile_.SaveFile(fileName.toStdString().c_str()) )
    {
        saved_ = true;
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
    if ( !aircraftFile_.ExportAs(fileName.toStdString().c_str()) )
    {
        QMessageBox::warning(
            this, APP_TITLE,
            tr("Cannot export file %1.").arg(fileName)
        );
    }
}

void MainWindow::setCurrentFile(const QString& currentFile)
{
    currentFile_ = currentFile;
    ui_->widgetCGI->getManagerCGI()->SetProjectDir(QFileInfo(currentFile_).absolutePath());
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
    ui_->actionShowGrid->setChecked(grid_visible);

    settingsRead_RecentFiles(settings);

    settings.endGroup();
}

void MainWindow::settingsRead_RecentFiles(QSettings& settings)
{
    recentFilesList_ = settings.value("recent_files").toStringList();
    updateRecentFiles();
}

void MainWindow::settingsSave()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("main_window");

    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());

    settings.setValue("grid_visible", ui_->actionShowGrid->isChecked() ? 1 : 0);

    settingsSave_RecentFiles(settings);

    settings.endGroup();
}

void MainWindow::settingsSave_RecentFiles(QSettings& settings)
{
    settings.setValue("recent_files", recentFilesList_);
}

void MainWindow::updateGUI()
{
    dockParams_->updateGUI();
    dockComponents_->updateGUI();
    dockResults_->updateGUI();

    const AircraftData* data = aircraftFile_.GetAircraftData();
    ui_->widgetCGI->getManagerCGI()->SetModelData(
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

    if ( currentFile_.length() > 0 )
    {
        title += " - " + QFileInfo(currentFile_).fileName();
    }

    if ( !saved_ ) title += " (*)";

    setWindowTitle(title);
}

void MainWindow::updateRecentFiles(QString file)
{
    for ( auto recentFilesAction : recentFilesActions_ )
    {
        disconnect(recentFilesAction, SIGNAL(triggered(int)), this, SLOT(recentFile_triggered(int)));
    }
    recentFilesActions_.clear();

    if ( file.length() > 0 )
    {
        recentFilesList_.push_front(file);

        while ( recentFilesList_.size() > 4 )
        {
            recentFilesList_.removeLast();
        }
    }

    ui_->menuRecentFiles->clear();

    int id = 0;
    for ( auto recentFile : recentFilesList_ )
    {
        RecentFileAction* action = new RecentFileAction(recentFile, ui_->menuRecentFiles, id);
        recentFilesActions_.push_back(action);
        connect(action, SIGNAL(triggered(int)), this, SLOT(recentFile_triggered(int)));
        ui_->menuRecentFiles->addAction(action);
        id++;
    }
}

void MainWindow::on_aircraftChanged()
{
    saved_ = false;
    updateTitleBar();
    updateGUI();
}

void MainWindow::on_currentComponentChanged()
{
    int index = dockComponents_->getCurrentComponentIndex();
    if ( index >= 0 )
    {
        const Component* component = aircraftFile_.GetAircraft()->GetComponent(index);

        PositionVector pos = component->GetPosition();

        units::length::meter_t l = component->GetLength();
        units::length::meter_t w = component->GetWidth();
        units::length::meter_t h = component->GetHeight();

        ui_->widgetCGI->getManagerCGI()->SetHighlightData(
                    true,
                    pos.x()(), pos.y()(), pos.z()(),
                    l(), w(), h()
        );
    }
    else
    {
        ui_->widgetCGI->getManagerCGI()->SetHighlightData(false);
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
    recentFilesList_.clear();
    recentFilesActions_.clear();
    updateRecentFiles();
}

void MainWindow::recentFile_triggered(int id)
{
    currentFile_ = recentFilesList_.at(id);
    readFile(currentFile_);
}

void MainWindow::on_actionShowGrid_toggled(bool checked)
{
    ui_->widgetCGI->getManagerCGI()->SetGridVisibility(checked);
}

void MainWindow::on_actionViewDefault_triggered()
{
    ui_->widgetCGI->resetView();
}

void MainWindow::on_actionViewTop_triggered()
{
    ui_->widgetCGI->topView();
}

void MainWindow::on_actionViewBottom_triggered()
{
    ui_->widgetCGI->bottomView();
}

void MainWindow::on_actionViewBack_triggered()
{
    ui_->widgetCGI->backView();
}

void MainWindow::on_actionViewFront_triggered()
{
    ui_->widgetCGI->frontView();
}

void MainWindow::on_actionViewLeft_triggered()
{
    ui_->widgetCGI->leftView();
}

void MainWindow::on_actionViewRight_triggered()
{
    ui_->widgetCGI->rightView();
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
