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
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _sc_save   = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(on_actionSave_triggered()));
    _sc_export = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_E), this, SLOT(on_actionExport_triggered()));
    _sc_undo   = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(on_actionUndo_triggered()));
    _sc_redo   = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this, SLOT(on_actionRedo_triggered()));
    _sc_redo_2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Shift + Qt::Key_Z), this, SLOT(on_actionRedo_triggered()));

    settingsRead();
}


MainWindow::~MainWindow()
{
    settingsSave();

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

}


void MainWindow::openFile()
{

}


void MainWindow::saveFile()
{

}


void MainWindow::saveFileAs()
{

}


void MainWindow::exportFileAs()
{

}


void MainWindow::readFile(QString fileName)
{

}


void MainWindow::saveFile(QString fileName)
{

}


void MainWindow::exportAs(QString fileName)
{

}


void MainWindow::undo()
{
    _cmd_mngr->undo();
}


void MainWindow::redo()
{
    _cmd_mngr->redo();
}


void MainWindow::settingsRead()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("main_window");

    restoreState(settings.value("state").toByteArray());
    restoreGeometry(settings.value("geometry").toByteArray());

    // bool grid_visible = settings.value("grid_visible" , 1).toBool();
    // _ui->actionShowGrid->setChecked(grid_visible);

    // settingsRead_RecentFiles(settings);

    settings.endGroup();
}


void MainWindow::settingsSave()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("main_window");

    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());

    // settings.setValue("grid_visible", _ui->actionShowGrid->isChecked() ? 1 : 0);

    // settingsSave_RecentFiles(settings);

    settings.endGroup();
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


void MainWindow::on_actionUndo_triggered()
{
    undo();
}


void MainWindow::on_actionRedo_triggered()
{
    redo();
}


void MainWindow::on_actionAbout_triggered()
{
    QDesktopServices::openUrl(QUrl("https://mc-tech.org/mc-mass/"));
}


void MainWindow::on_actionDocs_triggered()
{
    QDesktopServices::openUrl(QUrl("https://mc-tech.org/mc-mass/docs/"));
}


void MainWindow::recentFile_triggered(RecentFileAction* action)
{
    askIfSave();
    readFile(action->file());
}
