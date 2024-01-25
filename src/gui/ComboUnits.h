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
#ifndef MC_MASS_GUI_COMBOUNITS_H_
#define MC_MASS_GUI_COMBOUNITS_H_

#include <vector>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QVector>

/**
 * @brief Units selection abstract combo box.
 */
class ComboUnits : public QComboBox
{
    Q_OBJECT

public:

    static void switchUnits(QDoubleSpinBox* spinBox, ComboUnits* comboUnits);

    /** @brief Constructor. */
    explicit ComboUnits(QWidget* parent = nullptr);
    
    /** @brief Destructor. */
    virtual ~ComboUnits();

    virtual double convert(double value) const;
    virtual double convertPrev(double value) const;

    virtual double invert(double value) const;
    virtual double invertPrev(double value) const;

    virtual double getCoef(int index) const;

    inline double getFactor() const { return factor_; }

protected:

    double factor_ = 1.0;       ///< [-]
    double factor_prev_ = 1.0;  ///< [-]

    int index_;                 ///<
    int index_prev_;            ///<

    QVector<double>  coefs_;    ///< [-] convertion factors
    QVector<QString> names_;    ///< units names

public slots:

    /** */
    virtual void on_currentIndexChanged(int index);
};

#endif // MC_MASS_GUI_COMBOUNITS_H_
