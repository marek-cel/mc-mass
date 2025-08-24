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
#ifndef MC_MASS_GUI_MAINWINDOW_H_
#define MC_MASS_GUI_MAINWINDOW_H_

#include <QMainWindow>
#include <QShortcut>

namespace Ui {
class MainWindow;
}

namespace gui {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void openFileFromCommandLine(QString filename);

protected:

    void closeEvent(QCloseEvent* event) override;

private:

    Ui::MainWindow* _ui;

    QShortcut* _sc_redo = nullptr;  ///< redo alternative shortcut (Shift+Ctrl+Z)

    void settingsRead();
    void settingsSave();

private slots:

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExport_triggered();
    void on_actionExit_triggered();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void on_actionViewDefault_triggered();
    void on_actionViewTop_triggered();
    void on_actionViewBottom_triggered();
    void on_actionViewLeft_triggered();
    void on_actionViewRight_triggered();
    void on_actionViewBack_triggered();
    void on_actionViewFront_triggered();

    void on_actionDocs_triggered();
    void on_actionAbout_triggered();
};

} // namespace gui

#endif // MC_MASS_GUI_MAINWINDOW_H_
