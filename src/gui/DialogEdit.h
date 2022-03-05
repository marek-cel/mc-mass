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
#ifndef GUI_DIALOGEDIT_H_
#define GUI_DIALOGEDIT_H_

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <components/Component.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogEdit;
}

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

class DialogEdit : public QDialog
{
    Q_OBJECT

public:

    static void edit( QWidget *parent, Component *component );

    explicit DialogEdit( QWidget *parent = Q_NULLPTR, const Component *component = Q_NULLPTR );

    virtual ~DialogEdit();

    void updateComponent( Component *component );

private:

    Ui::DialogEdit *_ui;            ///<

    const Component *_component;    ///<

    void updateMass();

private slots:

    void on_spinBox_X_valueChanged( double arg1 );
    void on_spinBox_Y_valueChanged( double arg1 );
    void on_spinBox_Z_valueChanged( double arg1 );
    void on_spinBox_L_valueChanged( double arg1 );
    void on_spinBox_W_valueChanged( double arg1 );
    void on_spinBox_H_valueChanged( double arg1 );
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // GUI_DIALOGEDIT_H_
