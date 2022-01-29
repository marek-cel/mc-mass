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
 *
 ******************************************************************************/

#include <gui/DialogEdit.h>
#include <ui_DialogEdit.h>

namespace mc
{

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::edit( QWidget *parent, Component *component )
{
    DialogEdit *dialog = new DialogEdit( parent, component );

    if ( dialog->exec() == QDialog::Accepted )
    {
        dialog->updateComponent( component );
    }

    DELPTR( dialog );
}

////////////////////////////////////////////////////////////////////////////////

DialogEdit::DialogEdit( QWidget *parent, const Component *component ) :
    QDialog( parent ),
    _ui( new Ui::DialogEdit ),
    _component ( component )
{
    _ui->setupUi( this );

    if ( _component )
    {
        _ui->lineEdit_Name->setText( _component->getName() );

        _ui->spinBox_Mass->setValue( _component->getMass() );

        _ui->spinBox_X->setValue( _component->getPosition().x() );
        _ui->spinBox_Y->setValue( _component->getPosition().y() );
        _ui->spinBox_Z->setValue( _component->getPosition().z() );

        _ui->spinBox_L->setValue( _component->getLength () );
        _ui->spinBox_W->setValue( _component->getWidth  () );
        _ui->spinBox_H->setValue( _component->getHeight () );

        updateMass();
    }
}

////////////////////////////////////////////////////////////////////////////////

DialogEdit::~DialogEdit()
{
    DELPTR( _ui );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::updateComponent( Component *component )
{
    if ( component )
    {
        component->setName( _ui->lineEdit_Name->text().toStdString().c_str() );

        component->setMass( _ui->spinBox_Mass->value() );

        Vector3 position;

        position.x() = _ui->spinBox_X->value();
        position.y() = _ui->spinBox_Y->value();
        position.z() = _ui->spinBox_Z->value();

        component->setPosition( position );

        component->setLength ( _ui->spinBox_L->value() );
        component->setWidth  ( _ui->spinBox_W->value() );
        component->setHeight ( _ui->spinBox_H->value() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::updateMass()
{
    _ui->spinBoxComputedMass->setValue( _component->getComputedMass() );
}

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::on_spinBox_X_valueChanged( double /*arg1*/ )
{
    updateMass();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::on_spinBox_Y_valueChanged( double /*arg1*/ )
{
    updateMass();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::on_spinBox_Z_valueChanged( double /*arg1*/ )
{
    updateMass();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::on_spinBox_L_valueChanged( double /*arg1*/ )
{
    updateMass();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::on_spinBox_W_valueChanged( double /*arg1*/ )
{
    updateMass();
}

////////////////////////////////////////////////////////////////////////////////

void DialogEdit::on_spinBox_H_valueChanged( double /*arg1*/ )
{
    updateMass();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace mc
