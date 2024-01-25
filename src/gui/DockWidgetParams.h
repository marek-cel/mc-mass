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
#ifndef MC_MASS_GUI_DOCKWIDGETPARAMS_H_
#define MC_MASS_GUI_DOCKWIDGETPARAMS_H_

#include <QDockWidget>
#include <QSettings>

#include <AircraftFile.h>

namespace Ui {
class DockWidgetParams;
}

class DockWidgetParams : public QDockWidget
{
    Q_OBJECT

public:

    explicit DockWidgetParams(AircraftFile* aircraftFile, QWidget *parent = nullptr);

    ~DockWidgetParams();

    void updateGUI();

signals:

    void aircraftChanged();

private:

    Ui::DockWidgetParams* ui_;
    AircraftFile* aircraftFile_ = nullptr;
    Aircraft* aircraft_ = nullptr;

    void settingsRead();
    void settingsRead_UnitsCombos(QSettings &settings);

    void settingsSave();
    void settingsSave_UnitsCombos(QSettings &settings);

    void setAircraftType(AircraftData::Type type);

    void updateWettedArea();
    void updateWingAR();
    void updateWingTR();
    void updateHorTailAR();
    void updateHorTailTR();
    void updateVerTailAR();
    void updateVerTailTR();
    void updateRotorTipVel();

private slots:

    void on_comboBoxAircraftType_currentIndexChanged(int index);

    void on_spinBoxMassEmpty_valueChanged   (double arg1);
    void on_spinBoxMTOW_valueChanged        (double arg1);
    void on_spinBoxMassMaxLand_valueChanged (double arg1);
    void on_spinBoxMaxNz_valueChanged       (double arg1);
    void on_spinBoxMaxNzLand_valueChanged   (double arg1);
    void on_spinBoxStallV_valueChanged      (double arg1);
    void on_spinBoxCruiseV_valueChanged     (double arg1);
    void on_spinBoxCruiseH_valueChanged     (double arg1);
    void on_spinBoxMachMax_valueChanged     (double arg1);
    void on_checkBoxNavyAircraft_toggled (bool checked);

    void on_comboBoxCargoDoor_currentIndexChanged(int index);
    void on_spinBoxFuseLength_valueChanged  (double arg1);
    void on_spinBoxFuseHeight_valueChanged  (double arg1);
    void on_spinBoxFuseWidth_valueChanged   (double arg1);
    void on_spinBoxNoseLength_valueChanged  (double arg1);
    void on_spinBoxPressVol_valueChanged    (double arg1);
    void on_spinBoxWetAreaEst_valueChanged  (double arg1);
    void on_spinBoxWetAreaReal_valueChanged (double arg1);
    void on_checkBoxFuselageLG_toggled (bool checked);
    void on_checkBoxCargoRamp_toggled  (bool checked);
    void on_checkBoxWettedAreaOverride_toggled(bool checked);

    void on_spinBoxWingArea_valueChanged    (double arg1);
    void on_spinBoxWingAreaExp_valueChanged (double arg1);
    void on_spinBoxWingSpan_valueChanged    (double arg1);
    void on_spinBoxWingSweep_valueChanged   (double arg1);
    void on_spinBoxWingCRoot_valueChanged   (double arg1);
    void on_spinBoxWingCTip_valueChanged    (double arg1);
    void on_spinBoxWingTC_valueChanged      (double arg1);
    void on_spinBoxWingFuel_valueChanged    (double arg1);
    void on_spinBoxCtrlArea_valueChanged    (double arg1);
    void on_spinBoxWingAR_valueChanged      (double arg1);
    void on_spinBoxWingTR_valueChanged      (double arg1);
    void on_checkBoxWingDelta_toggled    (bool checked);
    void on_checkBoxWingVarSweep_toggled (bool checked);

    void on_spinBoxHorTailArea_valueChanged  (double arg1);
    void on_spinBoxHorTailSpan_valueChanged  (double arg1);
    void on_spinBoxHorTailSweep_valueChanged (double arg1);
    void on_spinBoxHorTailCRoot_valueChanged (double arg1);
    void on_spinBoxHorTailCTip_valueChanged  (double arg1);
    void on_spinBoxHorTailTC_valueChanged    (double arg1);
    void on_spinBoxElevArea_valueChanged     (double arg1);
    void on_spinBoxHorTailWF_valueChanged    (double arg1);
    void on_spinBoxHorTailArm_valueChanged   (double arg1);
    void on_spinBoxHorTailAR_valueChanged    (double arg1);
    void on_spinBoxHorTailTR_valueChanged    (double arg1);
    void on_checkBoxHorTailMoving_toggled  (bool checked);
    void on_checkBoxHorTailRolling_toggled (bool checked);

    void on_spinBoxVerTailArea_valueChanged   (double arg1);
    void on_spinBoxVerTailHeight_valueChanged (double arg1);
    void on_spinBoxVerTailSweep_valueChanged  (double arg1);
    void on_spinBoxVerTailCRoot_valueChanged  (double arg1);
    void on_spinBoxVerTailCTip_valueChanged   (double arg1);
    void on_spinBoxVerTailTC_valueChanged     (double arg1);
    void on_spinBoxVerTailArm_valueChanged    (double arg1);
    void on_spinBoxRuddArea_valueChanged      (double arg1);
    void on_spinBoxVerTailAR_valueChanged     (double arg1);
    void on_spinBoxVerTailTR_valueChanged     (double arg1);
    void on_checkBoxTailT_toggled        (bool checked);
    void on_checkBoxVerTailRotor_toggled (bool checked);

    void on_spinBoxMainGearLength_valueChanged (double arg1);
    void on_spinBoxNoseGearLength_valueChanged (double arg1);
    void on_spinBoxMainGearWheels_valueChanged (int arg1);
    void on_spinBoxMainGearStruts_valueChanged (int arg1);
    void on_spinBoxNoseGearWheels_valueChanged (int arg1);
    void on_checkBoxGearFixed_toggled     (bool checked);
    void on_checkBoxGearCross_toggled     (bool checked);
    void on_checkBoxGearTripod_toggled    (bool checked);
    void on_checkBoxGearMainKneel_toggled (bool checked);
    void on_checkBoxGearNoseKneel_toggled (bool checked);

    void on_spinBoxEngineMass_valueChanged(double arg1);

    void on_spinBoxMainRotorDiameter_valueChanged (double arg1);
    void on_spinBoxMainRotorChord_valueChanged    (double arg1);
    void on_spinBoxMainRotorRPM_valueChanged      (double arg1);
    void on_spinBoxTailRotorDiameter_valueChanged (double arg1);
    void on_spinBoxMainRotorGear_valueChanged     (double arg1);
    void on_spinBoxPowerLimit_valueChanged        (double arg1);
    void on_spinBoxMainRotorTipVel_valueChanged   (double arg1);
    void on_spinBoxMainRotorBlades_valueChanged (int arg1);

    void on_toolButtonBrowse_clicked();

    void on_lineEditModelFile_textChanged(const QString &arg1);
    void on_spinBox_OffsetX_valueChanged(double arg1);
    void on_spinBox_OffsetY_valueChanged(double arg1);
    void on_spinBox_OffsetZ_valueChanged(double arg1);
    void on_spinBox_RotationX_valueChanged(double arg1);
    void on_spinBox_RotationY_valueChanged(double arg1);
    void on_spinBox_RotationZ_valueChanged(double arg1);
    void on_spinBox_Scale_valueChanged(double arg1);

    void on_comboBoxMassEmpty_currentIndexChanged(int index);
    void on_comboBoxMTOW_currentIndexChanged(int index);
    void on_comboBoxMassMaxLand_currentIndexChanged(int index);
    void on_comboBoxStallV_currentIndexChanged(int index);
    void on_comboBoxCruiseV_currentIndexChanged(int index);
    void on_comboBoxCruiseH_currentIndexChanged(int index);

    void on_comboBoxFuseLength_currentIndexChanged(int index);
    void on_comboBoxFuseWidth_currentIndexChanged(int index);
    void on_comboBoxFuseHeight_currentIndexChanged(int index);
    void on_comboBoxNoseLength_currentIndexChanged(int index);
    void on_comboBoxPressVol_currentIndexChanged(int index);
    void on_comboBoxWetAreaEst_currentIndexChanged(int index);
    void on_comboBoxWetAreaReal_currentIndexChanged(int index);

    void on_comboBoxWingArea_currentIndexChanged(int index);
    void on_comboBoxWingAreaExp_currentIndexChanged(int index);
    void on_comboBoxWingSpan_currentIndexChanged(int index);
    void on_comboBoxWingSweep_currentIndexChanged(int index);
    void on_comboBoxWingCRoot_currentIndexChanged(int index);
    void on_comboBoxWingCTip_currentIndexChanged(int index);
    void on_comboBoxWingFuel_currentIndexChanged(int index);
    void on_comboBoxCtrlArea_currentIndexChanged(int index);

    void on_comboBoxHorTailArea_currentIndexChanged(int index);
    void on_comboBoxHorTailSpan_currentIndexChanged(int index);
    void on_comboBoxHorTailSweep_currentIndexChanged(int index);
    void on_comboBoxHorTailCRoot_currentIndexChanged(int index);
    void on_comboBoxHorTailCTip_currentIndexChanged(int index);
    void on_comboBoxHorTailArm_currentIndexChanged(int index);
    void on_comboBoxElevArea_currentIndexChanged(int index);
    void on_comboBoxHorTailWF_currentIndexChanged(int index);

    void on_comboBoxVerTailArea_currentIndexChanged(int index);
    void on_comboBoxVerTailHeight_currentIndexChanged(int index);
    void on_comboBoxVerTailSweep_currentIndexChanged(int index);
    void on_comboBoxVerTailCRoot_currentIndexChanged(int index);
    void on_comboBoxVerTailCTip_currentIndexChanged(int index);
    void on_comboBoxVerTailArm_currentIndexChanged(int index);
    void on_comboBoxRuddArea_currentIndexChanged(int index);

    void on_comboBoxMainGearLength_currentIndexChanged(int index);
    void on_comboBoxNoseGearLength_currentIndexChanged(int index);

    void on_comboBoxEngineMass_currentIndexChanged(int index);

    void on_comboBoxMainRotorDiameter_currentIndexChanged(int index);
    void on_comboBoxMainRotorChord_currentIndexChanged(int index);
    void on_comboBoxTailRotorDiameter_currentIndexChanged(int index);
    void on_comboBoxPowerLimit_currentIndexChanged(int index);
    void on_comboBoxMainRotorTipVel_currentIndexChanged(int index);

    void on_comboBox_OffsetX_currentIndexChanged(int index);
    void on_comboBox_OffsetY_currentIndexChanged(int index);
    void on_comboBox_OffsetZ_currentIndexChanged(int index);
};

#endif // MC_MASS_GUI_DOCKWIDGETPARAMS_H_
