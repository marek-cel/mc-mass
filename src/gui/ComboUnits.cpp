/****************************************************************************//*
 *  Copyright (C) 2025 Marek M. Cel
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

#include <gui/ComboUnits.h>

#include <limits>

void ComboUnits::switchUnits(QDoubleSpinBox* spinBox, ComboUnits* comboUnits)
{
    double val_raw = comboUnits->invertPrev(spinBox->value());
    spinBox->blockSignals(true);
    spinBox->setValue(comboUnits->convert(val_raw));
    spinBox->blockSignals(false);
}

ComboUnits::ComboUnits(QWidget* parent)
    : QComboBox(parent)
    , _index(currentIndex())
    , _index_prev(_index)
{
    _coefs.clear();
    _names.clear();

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(on_currentIndexChanged(int)));
}

ComboUnits::~ComboUnits() {}

double ComboUnits::convert(double value) const
{
    return value * _factor;
}

double ComboUnits::convertPrev(double value) const
{
    return value * _factor_prev;
}

double ComboUnits::invert(double value) const
{
    return value / _factor;
}

double ComboUnits::invertPrev(double value) const
{
    return value / _factor_prev;
}

double ComboUnits::getCoef(int index) const
{
    if ( index >= 0 && index < static_cast<int>(_coefs.size()) )
    {
        return _coefs[index];
    }

    return std::numeric_limits<double>::quiet_NaN();
}

void ComboUnits::on_currentIndexChanged( int index )
{
    _factor_prev = _factor;

    _index_prev = _index;
    _index = index;

    if ( index >= 0 && index < static_cast<int>(_coefs.size()) )
    {
        _factor = _coefs[index];
    }
}
