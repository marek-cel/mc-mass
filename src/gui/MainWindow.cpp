/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 *
 * This file is part of MC-Mass.
 *
 * MC-Mass is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MC-Mass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <gui/MainWindow.h>
#include <ui_MainWindow.h>

#include <QCloseEvent>
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include <defs.h>

namespace gui {


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _sc_redo = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Z), this, SLOT(on_actionRedo_triggered()));

    settingsRead();
}


MainWindow::~MainWindow()
{
    settingsSave();

    if ( _ui ) { delete _ui; } _ui = nullptr;
}


void MainWindow::openFileFromCommandLine(QString filename)
{
    // readFile(filename);
}


void MainWindow::closeEvent(QCloseEvent* event)
{
    // askIfSave();

    /////////////////////////////////
    QMainWindow::closeEvent( event );
    /////////////////////////////////
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
    // newFile();
}


void MainWindow::on_actionOpen_triggered()
{
    // openFile();
}


void MainWindow::on_actionSave_triggered()
{
    qDebug() << "Save action triggered";
    // saveFile();
}


void MainWindow::on_actionSaveAs_triggered()
{
    // saveFileAs();
}


void MainWindow::on_actionExport_triggered()
{
    qDebug() << "Export action triggered";
    // exportFileAs();
}


void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_actionUndo_triggered()
{
    qDebug() << "Undo action triggered";
    // undo();
}


void MainWindow::on_actionRedo_triggered()
{
    qDebug() << "Redo action triggered";
    // redo();
}


void MainWindow::on_actionViewDefault_triggered()
{
    qDebug() << "Default view";
    // _ui->widgetCGI->resetView();
}


void MainWindow::on_actionViewTop_triggered()
{
    qDebug() << "Top view";
    // _ui->widgetCGI->topView();
}


void MainWindow::on_actionViewBottom_triggered()
{
    qDebug() << "Bottom view";
    // _ui->widgetCGI->bottomView();
}


void MainWindow::on_actionViewLeft_triggered()
{
    qDebug() << "Left view";
    // _ui->widgetCGI->leftView();
}


void MainWindow::on_actionViewRight_triggered()
{
    qDebug() << "Right view";
    // _ui->widgetCGI->rightView();
}


void MainWindow::on_actionViewBack_triggered()
{
    qDebug() << "Back view";
    // _ui->widgetCGI->backView();
}


void MainWindow::on_actionViewFront_triggered()
{
    qDebug() << "Front view";
    // _ui->widgetCGI->frontView();
}


void MainWindow::on_actionAbout_triggered()
{
    QDesktopServices::openUrl(QUrl("https://mc-tech.org/mc-mass/"));
}


void MainWindow::on_actionDocs_triggered()
{
    QDesktopServices::openUrl(QUrl("https://mc-tech.org/mc-mass/docs/"));
}


} // namespace gui
