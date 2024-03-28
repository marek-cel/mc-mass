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

#include <gui/DockWidgetParams.h>
#include <ui_DockWidgetParams.h>

#include <QFileDialog>
#include <QFileInfo>

#include <defs.h>

DockWidgetParams::DockWidgetParams(AircraftFile* aircraftFile, QWidget* parent)
    : QDockWidget(parent)
    , _ui(new Ui::DockWidgetParams)
    , _aircraftFile(aircraftFile)
{
    _ui->setupUi(this);

    _aircraft = _aircraftFile->GetAircraft();

    setAircraftType(AircraftData::FighterAttack);
    updateGUI();

    settingsRead();
}

DockWidgetParams::~DockWidgetParams()
{
    settingsSave();

    if ( _ui ) { delete _ui; } _ui = nullptr;
}

void DockWidgetParams::updateGUI()
{
    const AircraftData* data = _aircraft->GetData();

    // general
    _ui->comboBoxAircraftType->setCurrentIndex(data->type);

    _ui->spinBoxMassEmpty   ->setValue(_ui->comboBoxMassEmpty   ->convert(data->general.m_empty   ()));
    _ui->spinBoxMTOW        ->setValue(_ui->comboBoxMTOW        ->convert(data->general.mtow      ()));
    _ui->spinBoxMassMaxLand ->setValue(_ui->comboBoxMassMaxLand ->convert(data->general.m_maxLand ()));
    _ui->spinBoxMaxFuel     ->setValue(_ui->comboBoxMaxFuel     ->convert(data->general.m_maxFuel ()));

    _ui->spinBoxMaxNz     ->setValue( data->general.nz_max     );
    _ui->spinBoxMaxNzLand ->setValue( data->general.nz_maxLand );

    _ui->spinBoxStallV  ->setValue( _ui->comboBoxStallV  ->convert(data->general.v_stall  ()));
    _ui->spinBoxCruiseH ->setValue( _ui->comboBoxCruiseH ->convert(data->general.h_cruise ()));
    _ui->spinBoxCruiseV ->setValue( _ui->comboBoxCruiseV ->convert(data->general.v_cruise ()));
    _ui->spinBoxMachMax ->setValue(data->general.mach_max);

    _ui->checkBoxNavyAircraft->setChecked(data->general.navy_ac);

    // fuselage
    _ui->comboBoxCargoDoor->setCurrentIndex(data->fuselage.cargo_door);

    _ui->spinBoxFuseLength ->setValue(_ui->comboBoxFuseLength ->convert(data->fuselage.l()));
    _ui->spinBoxFuseHeight ->setValue(_ui->comboBoxFuseHeight ->convert(data->fuselage.h()));
    _ui->spinBoxFuseWidth  ->setValue(_ui->comboBoxFuseWidth  ->convert(data->fuselage.w()));

    _ui->spinBoxNoseLength->setValue(_ui->comboBoxNoseLength->convert(data->fuselage.l_n()));

    _ui->spinBoxPressVol    ->setValue(_ui->comboBoxPressVol    ->convert(data->fuselage.press_vol   ()));
    _ui->spinBoxWetAreaReal ->setValue(_ui->comboBoxWetAreaReal ->convert(data->fuselage.wetted_area ()));

    _ui->checkBoxFuselageLG ->setChecked( data->fuselage.landing_gear );
    _ui->checkBoxCargoRamp  ->setChecked( data->fuselage.cargo_ramp   );
    _ui->checkBoxWettedAreaOverride->setChecked(data->fuselage.wetted_area_override);

    // wing
    _ui->spinBoxWingArea    ->setValue(_ui->comboBoxWingArea    ->convert(data->wing.area      ()));
    _ui->spinBoxWingAreaExp ->setValue(_ui->comboBoxWingAreaExp ->convert(data->wing.area_exp  ()));
    _ui->spinBoxWingSpan    ->setValue(_ui->comboBoxWingSpan    ->convert(data->wing.span      ()));
    _ui->spinBoxWingSweep   ->setValue(_ui->comboBoxWingSweep   ->convert(data->wing.sweep     ()));
    _ui->spinBoxWingCRoot   ->setValue(_ui->comboBoxWingCRoot   ->convert(data->wing.c_root    ()));
    _ui->spinBoxWingCTip    ->setValue(_ui->comboBoxWingCTip    ->convert(data->wing.c_tip     ()));
    _ui->spinBoxWingFuel    ->setValue(_ui->comboBoxCtrlArea    ->convert(data->wing.fuel      ()));
    _ui->spinBoxCtrlArea    ->setValue(_ui->comboBoxWingFuel    ->convert(data->wing.ctrl_area ()));

    _ui->spinBoxWingTC->setValue(data->wing.tc);
    _ui->spinBoxWingAR->setValue(data->wing.ar);
    _ui->spinBoxWingTR->setValue(data->wing.tr);

    _ui->checkBoxWingDelta    ->setChecked( data->wing.delta     );
    _ui->checkBoxWingVarSweep ->setChecked( data->wing.var_sweep );

    // horizontal tail
    _ui->spinBoxHorTailArea  ->setValue(_ui->comboBoxHorTailArea  ->convert(data->hor_tail.area      ()));
    _ui->spinBoxHorTailSpan  ->setValue(_ui->comboBoxHorTailSpan  ->convert(data->hor_tail.span      ()));
    _ui->spinBoxHorTailSweep ->setValue(_ui->comboBoxHorTailSweep ->convert(data->hor_tail.sweep     ()));
    _ui->spinBoxHorTailCRoot ->setValue(_ui->comboBoxHorTailCRoot ->convert(data->hor_tail.c_root    ()));
    _ui->spinBoxHorTailCTip  ->setValue(_ui->comboBoxHorTailCTip  ->convert(data->hor_tail.c_tip     ()));
    _ui->spinBoxElevArea     ->setValue(_ui->comboBoxElevArea     ->convert(data->hor_tail.elev_area ()));
    _ui->spinBoxHorTailWF    ->setValue(_ui->comboBoxHorTailWF    ->convert(data->hor_tail.w_f       ()));
    _ui->spinBoxHorTailArm   ->setValue(_ui->comboBoxHorTailArm   ->convert(data->hor_tail.arm       ()));

    _ui->spinBoxHorTailTC->setValue(data->hor_tail.tc);
    _ui->spinBoxHorTailAR->setValue(data->hor_tail.ar);
    _ui->spinBoxHorTailTR->setValue(data->hor_tail.tr);

    _ui->checkBoxHorTailMoving  ->setChecked( data->hor_tail.moving  );
    _ui->checkBoxHorTailRolling ->setChecked( data->hor_tail.rolling );

    // vertical tail
    _ui->spinBoxVerTailArea   ->setValue(_ui->comboBoxVerTailArea   ->convert(data->ver_tail.area      ()));
    _ui->spinBoxVerTailHeight ->setValue(_ui->comboBoxVerTailHeight ->convert(data->ver_tail.height    ()));
    _ui->spinBoxVerTailSweep  ->setValue(_ui->comboBoxVerTailSweep  ->convert(data->ver_tail.sweep     ()));
    _ui->spinBoxVerTailCRoot  ->setValue(_ui->comboBoxVerTailCRoot  ->convert(data->ver_tail.c_root    ()));
    _ui->spinBoxVerTailCTip   ->setValue(_ui->comboBoxVerTailCTip   ->convert(data->ver_tail.c_tip     ()));
    _ui->spinBoxVerTailArm    ->setValue(_ui->comboBoxVerTailArm    ->convert(data->ver_tail.arm       ()));
    _ui->spinBoxRuddArea      ->setValue(_ui->comboBoxRuddArea      ->convert(data->ver_tail.rudd_area ()));

    _ui->spinBoxVerTailTC->setValue(data->ver_tail.tc);
    _ui->spinBoxVerTailAR->setValue(data->ver_tail.ar);
    _ui->spinBoxVerTailTR->setValue(data->ver_tail.tr);

    _ui->checkBoxTailT        ->setChecked( data->ver_tail.t_tail );
    _ui->checkBoxVerTailRotor ->setChecked( data->ver_tail.rotor  );

    // landing gear
    _ui->spinBoxMainGearLength->setValue(_ui->comboBoxMainGearLength->convert(data->landing_gear.main_l()));
    _ui->spinBoxNoseGearLength->setValue(_ui->comboBoxNoseGearLength->convert(data->landing_gear.nose_l()));

    _ui->spinBoxMainGearWheels->setValue(data->landing_gear.main_wheels);
    _ui->spinBoxMainGearStruts->setValue(data->landing_gear.main_struts);
    _ui->spinBoxNoseGearWheels->setValue(data->landing_gear.nose_wheels);

    _ui->checkBoxGearFixed  ->setChecked( data->landing_gear.fixed  );
    _ui->checkBoxGearCross  ->setChecked( data->landing_gear.cross  );
    _ui->checkBoxGearTripod ->setChecked( data->landing_gear.tripod );

    _ui->checkBoxGearMainKneel->setChecked(data->landing_gear.main_kneel);
    _ui->checkBoxGearNoseKneel->setChecked(data->landing_gear.nose_kneel);

    // engine
    _ui->spinBoxEngineMass->setValue(_ui->comboBoxEngineMass->convert(data->engine.mass()));

    // rotors
    _ui->spinBoxMainRotorDiameter ->setValue(_ui->comboBoxMainRotorDiameter ->convert(data->rotors.main_r      ()) * 2.0);
    _ui->spinBoxMainRotorChord    ->setValue(_ui->comboBoxMainRotorChord    ->convert(data->rotors.main_cb     ()));
    _ui->spinBoxTailRotorDiameter ->setValue(_ui->comboBoxTailRotorDiameter ->convert(data->rotors.tail_r      ()) * 2.0);
    _ui->spinBoxPowerLimit        ->setValue(_ui->comboBoxPowerLimit        ->convert(data->rotors.mcp         ()));
    _ui->spinBoxMainRotorTipVel   ->setValue(_ui->comboBoxMainRotorTipVel   ->convert(data->rotors.main_tip_vel()));

    _ui->spinBoxMainRotorRPM    ->setValue( data->rotors.main_rpm()      );
    _ui->spinBoxMainRotorGear   ->setValue( data->rotors.main_gear_ratio );
    _ui->spinBoxMainRotorBlades ->setValue( data->rotors.main_blades     );

    // model 3D
    _ui->lineEditModelFile->setText(data->model3d.file);
    _ui->spinBox_OffsetX->setValue(_ui->comboBox_OffsetX->convert(data->model3d.offset_x()));
    _ui->spinBox_OffsetY->setValue(_ui->comboBox_OffsetY->convert(data->model3d.offset_y()));
    _ui->spinBox_OffsetZ->setValue(_ui->comboBox_OffsetZ->convert(data->model3d.offset_z()));
    _ui->spinBox_RotationX->setValue(data->model3d.rotation_x());
    _ui->spinBox_RotationY->setValue(data->model3d.rotation_y());
    _ui->spinBox_RotationZ->setValue(data->model3d.rotation_z());
    _ui->spinBox_Scale->setValue(data->model3d.scale);
}

void DockWidgetParams::settingsRead()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("dock_parameters");
    settingsRead_UnitsCombos(settings);
    settings.endGroup();
}

void DockWidgetParams::settingsRead_UnitsCombos(QSettings& settings)
{
    settings.beginGroup("units_combos");

    // general
    _ui->comboBoxMassEmpty        ->setCurrentIndex(settings.value("mass_empty"   , 0).toInt());
    _ui->comboBoxMTOW             ->setCurrentIndex(settings.value("mtow"         , 0).toInt());
    _ui->comboBoxMassMaxLand      ->setCurrentIndex(settings.value("mass_landing" , 0).toInt());
    _ui->comboBoxStallV           ->setCurrentIndex(settings.value("stall_speed"  , 0).toInt());
    _ui->comboBoxCruiseV          ->setCurrentIndex(settings.value("cruise_speed" , 0).toInt());
    _ui->comboBoxCruiseH          ->setCurrentIndex(settings.value("cruise_alt"   , 0).toInt());

    // fuselage
    _ui->comboBoxFuseLength       ->setCurrentIndex(settings.value("fuselage_l"   , 0).toInt());
    _ui->comboBoxFuseWidth        ->setCurrentIndex(settings.value("fuselage_w"   , 0).toInt());
    _ui->comboBoxFuseHeight       ->setCurrentIndex(settings.value("fuselage_h"   , 0).toInt());
    _ui->comboBoxNoseLength       ->setCurrentIndex(settings.value("nose_length"  , 0).toInt());
    _ui->comboBoxPressVol         ->setCurrentIndex(settings.value("press_vol"    , 0).toInt());
    _ui->comboBoxWetAreaEst       ->setCurrentIndex(settings.value("wet_area_est" , 0).toInt());
    _ui->comboBoxWetAreaReal      ->setCurrentIndex(settings.value("wet_area_real", 0).toInt());

    // wing
    _ui->comboBoxWingArea         ->setCurrentIndex(settings.value("wing_area"    , 0).toInt());
    _ui->comboBoxWingAreaExp      ->setCurrentIndex(settings.value("wing_area_exp", 0).toInt());
    _ui->comboBoxWingSpan         ->setCurrentIndex(settings.value("wing_span"    , 0).toInt());
    _ui->comboBoxWingSweep        ->setCurrentIndex(settings.value("wing_sweep"   , 0).toInt());
    _ui->comboBoxWingCRoot        ->setCurrentIndex(settings.value("wing_c_root"  , 0).toInt());
    _ui->comboBoxWingCTip         ->setCurrentIndex(settings.value("wing_c_tip"   , 0).toInt());
    _ui->comboBoxWingFuel         ->setCurrentIndex(settings.value("wing_fuel"    , 0).toInt());
    _ui->comboBoxCtrlArea         ->setCurrentIndex(settings.value("wing_ctr_area", 0).toInt());

    // horizontal tail
    _ui->comboBoxHorTailArea      ->setCurrentIndex(settings.value("htail_area"   , 0).toInt());
    _ui->comboBoxHorTailSpan      ->setCurrentIndex(settings.value("htail_span"   , 0).toInt());
    _ui->comboBoxHorTailSweep     ->setCurrentIndex(settings.value("htail_sweep"  , 0).toInt());
    _ui->comboBoxHorTailCRoot     ->setCurrentIndex(settings.value("htail_c_root" , 0).toInt());
    _ui->comboBoxHorTailCTip      ->setCurrentIndex(settings.value("htail_c_tip"  , 0).toInt());
    _ui->comboBoxHorTailArm       ->setCurrentIndex(settings.value("htail_arm"    , 0).toInt());
    _ui->comboBoxElevArea         ->setCurrentIndex(settings.value("elev_area"    , 0).toInt());
    _ui->comboBoxHorTailWF        ->setCurrentIndex(settings.value("htail_wf"     , 0).toInt());

    // vertical tail
    _ui->comboBoxVerTailArea      ->setCurrentIndex(settings.value("vtail_area"   , 0).toInt());
    _ui->comboBoxVerTailHeight    ->setCurrentIndex(settings.value("vtail_height" , 0).toInt());
    _ui->comboBoxVerTailSweep     ->setCurrentIndex(settings.value("vtail_sweep"  , 0).toInt());
    _ui->comboBoxVerTailCRoot     ->setCurrentIndex(settings.value("vtail_c_root" , 0).toInt());
    _ui->comboBoxVerTailCTip      ->setCurrentIndex(settings.value("vtail_c_tip"  , 0).toInt());
    _ui->comboBoxVerTailArm       ->setCurrentIndex(settings.value("vtail_arm"    , 0).toInt());
    _ui->comboBoxRuddArea         ->setCurrentIndex(settings.value("rudd_area"    , 0).toInt());

    // landing gear
    _ui->comboBoxMainGearLength   ->setCurrentIndex(settings.value("lg_main_l"    , 0).toInt());
    _ui->comboBoxNoseGearLength   ->setCurrentIndex(settings.value("lg_nose_l"    , 0).toInt());

    // engine
    _ui->comboBoxEngineMass       ->setCurrentIndex(settings.value("engine_mass"  , 0).toInt());

    // rotors
    _ui->comboBoxMainRotorDiameter->setCurrentIndex(settings.value("main_rotor_d" , 0).toInt());
    _ui->comboBoxMainRotorChord   ->setCurrentIndex(settings.value("main_rotor_c" , 0).toInt());
    _ui->comboBoxTailRotorDiameter->setCurrentIndex(settings.value("tail_rotor_d" , 0).toInt());
    _ui->comboBoxPowerLimit       ->setCurrentIndex(settings.value("rotor_mcp"    , 0).toInt());
    _ui->comboBoxMainRotorTipVel  ->setCurrentIndex(settings.value("main_rotor_tv", 0).toInt());

    // 3D model
    _ui->comboBox_OffsetX->setCurrentIndex(settings.value("model_offset_x", 0).toInt());
    _ui->comboBox_OffsetY->setCurrentIndex(settings.value("model_offset_y", 0).toInt());
    _ui->comboBox_OffsetZ->setCurrentIndex(settings.value("model_offset_z", 0).toInt());


    settings.endGroup();
}

void DockWidgetParams::settingsSave()
{
    QSettings settings(ORG_NAME, APP_NAME);

    settings.beginGroup("dock_parameters");
    settingsSave_UnitsCombos(settings);
    settings.endGroup();
}

void DockWidgetParams::settingsSave_UnitsCombos(QSettings& settings)
{
    settings.beginGroup("units_combos");

    // general
    settings.setValue("main_rotor_tv", _ui->comboBoxMassEmpty        ->currentIndex());
    settings.setValue("rotor_mcp"    , _ui->comboBoxMTOW             ->currentIndex());
    settings.setValue("tail_rotor_d" , _ui->comboBoxMassMaxLand      ->currentIndex());
    settings.setValue("main_rotor_c" , _ui->comboBoxStallV           ->currentIndex());
    settings.setValue("main_rotor_d" , _ui->comboBoxCruiseV          ->currentIndex());
    settings.setValue("engine_mass"  , _ui->comboBoxCruiseH          ->currentIndex());

    // fuselage
    settings.setValue("lg_nose_l"    , _ui->comboBoxFuseLength       ->currentIndex());
    settings.setValue("lg_main_l"    , _ui->comboBoxFuseWidth        ->currentIndex());
    settings.setValue("rudd_area"    , _ui->comboBoxFuseHeight       ->currentIndex());
    settings.setValue("vtail_arm"    , _ui->comboBoxNoseLength       ->currentIndex());
    settings.setValue("vtail_c_tip"  , _ui->comboBoxPressVol         ->currentIndex());
    settings.setValue("vtail_c_root" , _ui->comboBoxWetAreaEst       ->currentIndex());
    settings.setValue("vtail_sweep"  , _ui->comboBoxWetAreaReal      ->currentIndex());

    // wing
    settings.setValue("vtail_height" , _ui->comboBoxWingArea         ->currentIndex());
    settings.setValue("vtail_area"   , _ui->comboBoxWingAreaExp      ->currentIndex());
    settings.setValue("htail_wf"     , _ui->comboBoxWingSpan         ->currentIndex());
    settings.setValue("elev_area"    , _ui->comboBoxWingSweep        ->currentIndex());
    settings.setValue("htail_arm"    , _ui->comboBoxWingCRoot        ->currentIndex());
    settings.setValue("htail_c_tip"  , _ui->comboBoxWingCTip         ->currentIndex());
    settings.setValue("htail_c_root" , _ui->comboBoxWingFuel         ->currentIndex());
    settings.setValue("htail_sweep"  , _ui->comboBoxCtrlArea         ->currentIndex());

    // horizontal tail
    settings.setValue("htail_span"   , _ui->comboBoxHorTailArea      ->currentIndex());
    settings.setValue("htail_area"   , _ui->comboBoxHorTailSpan      ->currentIndex());
    settings.setValue("wing_ctr_area", _ui->comboBoxHorTailSweep     ->currentIndex());
    settings.setValue("wing_fuel"    , _ui->comboBoxHorTailCRoot     ->currentIndex());
    settings.setValue("wing_c_tip"   , _ui->comboBoxHorTailCTip      ->currentIndex());
    settings.setValue("wing_c_root"  , _ui->comboBoxHorTailArm       ->currentIndex());
    settings.setValue("wing_sweep"   , _ui->comboBoxElevArea         ->currentIndex());
    settings.setValue("wing_span"    , _ui->comboBoxHorTailWF        ->currentIndex());

    // vertical tail
    settings.setValue("wing_area_exp", _ui->comboBoxVerTailArea      ->currentIndex());
    settings.setValue("wing_area"    , _ui->comboBoxVerTailHeight    ->currentIndex());
    settings.setValue("wet_area_real", _ui->comboBoxVerTailSweep     ->currentIndex());
    settings.setValue("wet_area_est" , _ui->comboBoxVerTailCRoot     ->currentIndex());
    settings.setValue("press_vol"    , _ui->comboBoxVerTailCTip      ->currentIndex());
    settings.setValue("nose_length"  , _ui->comboBoxVerTailArm       ->currentIndex());
    settings.setValue("fuselage_h"   , _ui->comboBoxRuddArea         ->currentIndex());

    // landing gear
    settings.setValue("fuselage_w"   , _ui->comboBoxMainGearLength   ->currentIndex());
    settings.setValue("fuselage_l"   , _ui->comboBoxNoseGearLength   ->currentIndex());

    // engine
    settings.setValue("cruise_alt"   , _ui->comboBoxEngineMass       ->currentIndex());

    // rotors
    settings.setValue("cruise_speed" , _ui->comboBoxMainRotorDiameter->currentIndex());
    settings.setValue("stall_speed"  , _ui->comboBoxMainRotorChord   ->currentIndex());
    settings.setValue("mass_landing" , _ui->comboBoxTailRotorDiameter->currentIndex());
    settings.setValue("mtow"         , _ui->comboBoxPowerLimit       ->currentIndex());
    settings.setValue("mass_empty"   , _ui->comboBoxMainRotorTipVel  ->currentIndex());

    // 3D model
    settings.setValue("model_offset_x", _ui->comboBox_OffsetX->currentIndex());
    settings.setValue("model_offset_y", _ui->comboBox_OffsetY->currentIndex());
    settings.setValue("model_offset_z", _ui->comboBox_OffsetZ->currentIndex());

    settings.endGroup();
}

void DockWidgetParams::setAircraftType(AircraftData::Type type)
{
    // data - general
    _ui->labelMassEmpty   ->setEnabled(false);
    _ui->labelMTOW        ->setEnabled(false);
    _ui->labelMassMaxLand ->setEnabled(false);
    _ui->labelMaxFuel     ->setEnabled(false);
    _ui->labelMaxNz       ->setEnabled(false);
    _ui->labelMaxNzLand   ->setEnabled(false);
    _ui->labelStallV      ->setEnabled(false);
    _ui->labelCruiseH     ->setEnabled(false);
    _ui->labelCruiseV     ->setEnabled(false);
    _ui->labelMachMax     ->setEnabled(false);

    _ui->labelMaxNzUnit->setEnabled(false);
    _ui->labelMaxNzLandUnit->setEnabled(false);

    _ui->spinBoxMassEmpty   ->setEnabled(false);
    _ui->spinBoxMTOW        ->setEnabled(false);
    _ui->spinBoxMassMaxLand ->setEnabled(false);
    _ui->spinBoxMaxFuel     ->setEnabled(false);
    _ui->spinBoxMaxNz       ->setEnabled(false);
    _ui->spinBoxMaxNzLand   ->setEnabled(false);
    _ui->spinBoxStallV      ->setEnabled(false);
    _ui->spinBoxCruiseH     ->setEnabled(false);
    _ui->spinBoxCruiseV     ->setEnabled(false);
    _ui->spinBoxMachMax     ->setEnabled(false);

    _ui->comboBoxMassEmpty   ->setEnabled(false);
    _ui->comboBoxMTOW        ->setEnabled(false);
    _ui->comboBoxMassMaxLand ->setEnabled(false);
    _ui->comboBoxMaxFuel     ->setEnabled(false);
    _ui->comboBoxStallV      ->setEnabled(false);
    _ui->comboBoxCruiseH     ->setEnabled(false);
    _ui->comboBoxCruiseV     ->setEnabled(false);

    _ui->checkBoxNavyAircraft->setEnabled(false);

    // data - fuselage
    _ui->comboBoxCargoDoor->setEnabled(false);

    _ui->labelFuseLength ->setEnabled(false);
    _ui->labelFuseHeight ->setEnabled(false);
    _ui->labelFuseWidth  ->setEnabled(false);
    _ui->labelNoseLength ->setEnabled(false);

    _ui->spinBoxFuseLength ->setEnabled(false);
    _ui->spinBoxFuseHeight ->setEnabled(false);
    _ui->spinBoxFuseWidth  ->setEnabled(false);
    _ui->spinBoxNoseLength ->setEnabled(false);

    _ui->comboBoxFuseLength ->setEnabled(false);
    _ui->comboBoxFuseHeight ->setEnabled(false);
    _ui->comboBoxFuseWidth  ->setEnabled(false);
    _ui->comboBoxNoseLength ->setEnabled(false);

    _ui->spinBoxWetAreaEst  ->setEnabled(false);
    _ui->spinBoxWetAreaReal ->setEnabled(false);
    _ui->spinBoxPressVol    ->setEnabled(false);

    _ui->comboBoxWetAreaEst  ->setEnabled(false);
    _ui->comboBoxWetAreaReal ->setEnabled(false);
    _ui->comboBoxPressVol    ->setEnabled(false);

    _ui->labelCargoDoor->setEnabled(false);

    _ui->labelWetAreaEst->setEnabled(false);
    _ui->labelWettedAreaReal->setEnabled(false);
    _ui->labelPressVol->setEnabled(false);

    _ui->checkBoxFuselageLG->setEnabled(false);
    _ui->checkBoxCargoRamp->setEnabled(false);
    _ui->checkBoxWettedAreaOverride->setEnabled(false);

    // data - wing
    _ui->labelWingArea    ->setEnabled(false);
    _ui->labelWingAreaExp ->setEnabled(false);
    _ui->labelWingSpan    ->setEnabled(false);
    _ui->labelWingSweep   ->setEnabled(false);
    _ui->labelWingCRoot   ->setEnabled(false);
    _ui->labelWingCTip    ->setEnabled(false);
    _ui->labelWingTC      ->setEnabled(false);
    _ui->labelWingFuel    ->setEnabled(false);
    _ui->labelCtrlArea    ->setEnabled(false);
    _ui->labelWingAR      ->setEnabled(false);
    _ui->labelWingTR      ->setEnabled(false);

    _ui->spinBoxWingArea    ->setEnabled(false);
    _ui->spinBoxWingAreaExp ->setEnabled(false);
    _ui->spinBoxWingSpan    ->setEnabled(false);
    _ui->spinBoxWingSweep   ->setEnabled(false);
    _ui->spinBoxWingCRoot   ->setEnabled(false);
    _ui->spinBoxWingCTip    ->setEnabled(false);
    _ui->spinBoxWingTC      ->setEnabled(false);
    _ui->spinBoxWingFuel    ->setEnabled(false);
    _ui->spinBoxCtrlArea    ->setEnabled(false);
    _ui->spinBoxWingAR      ->setEnabled(false);
    _ui->spinBoxWingTR      ->setEnabled(false);

    _ui->comboBoxWingArea    ->setEnabled(false);
    _ui->comboBoxWingAreaExp ->setEnabled(false);
    _ui->comboBoxWingSpan    ->setEnabled(false);
    _ui->comboBoxWingSweep   ->setEnabled(false);
    _ui->comboBoxWingCRoot   ->setEnabled(false);
    _ui->comboBoxWingCTip    ->setEnabled(false);
    _ui->comboBoxWingFuel    ->setEnabled(false);
    _ui->comboBoxCtrlArea    ->setEnabled(false);

    _ui->labelWingTCUnit->setEnabled(false);

    _ui->labelWingARUnit->setEnabled(false);
    _ui->labelWingTRUnit->setEnabled(false);

    _ui->checkBoxWingDelta    ->setEnabled(false);
    _ui->checkBoxWingVarSweep ->setEnabled(false);

    // data - horizontal tail
    _ui->labelHorTailArea  ->setEnabled(false);
    _ui->labelHorTailSpan  ->setEnabled(false);
    _ui->labelHorTailSweep ->setEnabled(false);
    _ui->labelHorTailCRoot ->setEnabled(false);
    _ui->labelHorTailCTip  ->setEnabled(false);
    _ui->labelHorTailTC    ->setEnabled(false);
    _ui->labelElevArea     ->setEnabled(false);
    _ui->labelHorTailWF    ->setEnabled(false);
    _ui->labelHorTailArm   ->setEnabled(false);
    _ui->labelHorTailAR    ->setEnabled(false);
    _ui->labelHorTailTR    ->setEnabled(false);

    _ui->spinBoxHorTailArea  ->setEnabled(false);
    _ui->spinBoxHorTailSpan  ->setEnabled(false);
    _ui->spinBoxHorTailSweep ->setEnabled(false);
    _ui->spinBoxHorTailCRoot ->setEnabled(false);
    _ui->spinBoxHorTailCTip  ->setEnabled(false);
    _ui->spinBoxHorTailTC    ->setEnabled(false);
    _ui->spinBoxElevArea     ->setEnabled(false);
    _ui->spinBoxHorTailWF    ->setEnabled(false);
    _ui->spinBoxHorTailArm   ->setEnabled(false);
    _ui->spinBoxHorTailAR    ->setEnabled(false);
    _ui->spinBoxHorTailTR    ->setEnabled(false);

    _ui->comboBoxHorTailArea  ->setEnabled(false);
    _ui->comboBoxHorTailSpan  ->setEnabled(false);
    _ui->comboBoxHorTailSweep ->setEnabled(false);
    _ui->comboBoxHorTailCRoot ->setEnabled(false);
    _ui->comboBoxHorTailCTip  ->setEnabled(false);
    _ui->comboBoxElevArea     ->setEnabled(false);
    _ui->comboBoxHorTailWF    ->setEnabled(false);
    _ui->comboBoxHorTailArm   ->setEnabled(false);

    _ui->checkBoxHorTailMoving  ->setEnabled(false);
    _ui->checkBoxHorTailRolling ->setEnabled(false);

    // data - vertical tail
    _ui->labelVerTailArea   ->setEnabled(false);
    _ui->labelVerTailHeight ->setEnabled(false);
    _ui->labelVerTailSweep  ->setEnabled(false);
    _ui->labelVerTailCRoot  ->setEnabled(false);
    _ui->labelVerTailCTip   ->setEnabled(false);
    _ui->labelVerTailTC     ->setEnabled(false);
    _ui->labelVerTailArm    ->setEnabled(false);
    _ui->labelRuddArea      ->setEnabled(false);
    _ui->labelVerTailAR     ->setEnabled(false);
    _ui->labelVerTailTR     ->setEnabled(false);

    _ui->spinBoxVerTailArea   ->setEnabled(false);
    _ui->spinBoxVerTailHeight ->setEnabled(false);
    _ui->spinBoxVerTailSweep  ->setEnabled(false);
    _ui->spinBoxVerTailCRoot  ->setEnabled(false);
    _ui->spinBoxVerTailCTip   ->setEnabled(false);
    _ui->spinBoxVerTailTC     ->setEnabled(false);
    _ui->spinBoxVerTailArm    ->setEnabled(false);
    _ui->spinBoxRuddArea      ->setEnabled(false);
    _ui->spinBoxVerTailAR     ->setEnabled(false);
    _ui->spinBoxVerTailTR     ->setEnabled(false);

    _ui->comboBoxVerTailArea   ->setEnabled(false);
    _ui->comboBoxVerTailHeight ->setEnabled(false);
    _ui->comboBoxVerTailSweep  ->setEnabled(false);
    _ui->comboBoxVerTailCRoot  ->setEnabled(false);
    _ui->comboBoxVerTailCTip   ->setEnabled(false);
    _ui->comboBoxVerTailArm    ->setEnabled(false);
    _ui->comboBoxRuddArea      ->setEnabled(false);

    _ui->checkBoxTailT        ->setEnabled(false);
    _ui->checkBoxVerTailRotor ->setEnabled(false);

    // data - landing gear
    _ui->labelMainGearLength ->setEnabled(false);
    _ui->labelNoseGearLength ->setEnabled(false);

    _ui->labelMainGearWheels ->setEnabled(false);
    _ui->labelMainGearStruts ->setEnabled(false);
    _ui->labelNoseGearWheels ->setEnabled(false);

    _ui->spinBoxMainGearLength ->setEnabled(false);
    _ui->spinBoxNoseGearLength ->setEnabled(false);

    _ui->comboBoxMainGearLength ->setEnabled(false);
    _ui->comboBoxNoseGearLength ->setEnabled(false);

    _ui->spinBoxMainGearWheels ->setEnabled(false);
    _ui->spinBoxMainGearStruts ->setEnabled(false);
    _ui->spinBoxNoseGearWheels ->setEnabled(false);

    _ui->checkBoxGearFixed  ->setEnabled(false);
    _ui->checkBoxGearCross  ->setEnabled(false);
    _ui->checkBoxGearTripod ->setEnabled(false);

    _ui->checkBoxGearMainKneel ->setEnabled(false);
    _ui->checkBoxGearNoseKneel ->setEnabled(false);

    // data - rotors
    _ui->labelMainRotorDiameter  ->setEnabled(false);
    _ui->labelMainRotorChord     ->setEnabled(false);
    _ui->labelMainRotorRPM       ->setEnabled(false);
    _ui->labelTailRotorDiameter  ->setEnabled(false);
    _ui->labelMainRotorGear      ->setEnabled(false);
    _ui->labelPowerLimit         ->setEnabled(false);
    _ui->labelMainRotorTipVel    ->setEnabled(false);
    _ui->labelMainRotorBlades    ->setEnabled(false);

    _ui->spinBoxMainRotorDiameter  ->setEnabled(false);
    _ui->spinBoxMainRotorChord     ->setEnabled(false);
    _ui->spinBoxMainRotorRPM       ->setEnabled(false);
    _ui->spinBoxTailRotorDiameter  ->setEnabled(false);
    _ui->spinBoxMainRotorGear      ->setEnabled(false);
    _ui->spinBoxPowerLimit         ->setEnabled(false);
    _ui->spinBoxMainRotorTipVel    ->setEnabled(false);
    _ui->spinBoxMainRotorBlades    ->setEnabled(false);

    _ui->comboBoxMainRotorDiameter  ->setEnabled(false);
    _ui->comboBoxMainRotorChord     ->setEnabled(false);
    _ui->comboBoxTailRotorDiameter  ->setEnabled(false);
    _ui->comboBoxPowerLimit         ->setEnabled(false);
    _ui->comboBoxMainRotorTipVel    ->setEnabled(false);

    if ( type == AircraftData::Helicopter )
    {
        // data - general
        _ui->labelMassEmpty   ->setEnabled(true);
        _ui->labelMTOW        ->setEnabled(true);
        _ui->labelMaxNz       ->setEnabled(true);
        _ui->labelMaxNzLand   ->setEnabled(true);

        _ui->spinBoxMassEmpty   ->setEnabled(true);
        _ui->spinBoxMTOW        ->setEnabled(true);
        _ui->spinBoxMaxNz       ->setEnabled(true);
        _ui->spinBoxMaxNzLand   ->setEnabled(true);

        _ui->comboBoxMassEmpty   ->setEnabled(true);
        _ui->comboBoxMTOW        ->setEnabled(true);

        _ui->labelMaxNzUnit->setEnabled(true);
        _ui->labelMaxNzLandUnit->setEnabled(true);

        // data - fuselage
        _ui->labelFuseLength ->setEnabled(true);
        _ui->labelFuseHeight ->setEnabled(true);
        _ui->labelFuseWidth  ->setEnabled(true);
        _ui->labelNoseLength ->setEnabled(true);

        _ui->spinBoxFuseLength ->setEnabled(true);
        _ui->spinBoxFuseHeight ->setEnabled(true);
        _ui->spinBoxFuseWidth  ->setEnabled(true);
        _ui->spinBoxNoseLength ->setEnabled(true);

        _ui->comboBoxFuseLength ->setEnabled(true);
        _ui->comboBoxFuseHeight ->setEnabled(true);
        _ui->comboBoxFuseWidth  ->setEnabled(true);
        _ui->comboBoxNoseLength ->setEnabled(true);

        _ui->labelWetAreaEst->setEnabled(true);
        _ui->spinBoxWetAreaEst->setEnabled(true);
        _ui->comboBoxWetAreaEst->setEnabled(true);

        _ui->checkBoxCargoRamp->setEnabled(true);
        _ui->checkBoxWettedAreaOverride->setEnabled(true);

        // data - horizontal tail
        _ui->labelHorTailArea ->setEnabled(true);
        _ui->labelHorTailSpan ->setEnabled(true);
        _ui->labelHorTailAR   ->setEnabled(true);

        _ui->spinBoxHorTailArea ->setEnabled(true);
        _ui->spinBoxHorTailSpan ->setEnabled(true);
        _ui->spinBoxHorTailAR   ->setEnabled(true);

        _ui->comboBoxHorTailArea ->setEnabled(true);
        _ui->comboBoxHorTailSpan ->setEnabled(true);

        // data - vertical tail
        _ui->labelVerTailArea   ->setEnabled(true);
        _ui->labelVerTailHeight ->setEnabled(true);
        _ui->labelVerTailAR     ->setEnabled(true);

        _ui->spinBoxVerTailArea   ->setEnabled(true);
        _ui->spinBoxVerTailHeight ->setEnabled(true);
        _ui->spinBoxVerTailAR     ->setEnabled(true);

        _ui->comboBoxVerTailArea   ->setEnabled(true);
        _ui->comboBoxVerTailHeight ->setEnabled(true);

        _ui->checkBoxVerTailRotor ->setEnabled(true);

        // data - rotors
        _ui->labelMainRotorDiameter  ->setEnabled(true);
        _ui->labelMainRotorChord     ->setEnabled(true);
        _ui->labelMainRotorRPM       ->setEnabled(true);
        _ui->labelTailRotorDiameter  ->setEnabled(true);
        _ui->labelMainRotorGear      ->setEnabled(true);
        _ui->labelPowerLimit         ->setEnabled(true);
        _ui->labelMainRotorTipVel    ->setEnabled(true);
        _ui->labelMainRotorBlades    ->setEnabled(true);

        _ui->spinBoxMainRotorDiameter  ->setEnabled(true);
        _ui->spinBoxMainRotorChord     ->setEnabled(true);
        _ui->spinBoxMainRotorRPM       ->setEnabled(true);
        _ui->spinBoxTailRotorDiameter  ->setEnabled(true);
        _ui->spinBoxMainRotorGear      ->setEnabled(true);
        _ui->spinBoxPowerLimit         ->setEnabled(true);
        _ui->spinBoxMainRotorTipVel    ->setEnabled(true);
        _ui->spinBoxMainRotorBlades    ->setEnabled(true);

        _ui->comboBoxMainRotorDiameter  ->setEnabled(true);
        _ui->comboBoxMainRotorChord     ->setEnabled(true);
        _ui->comboBoxTailRotorDiameter  ->setEnabled(true);
        _ui->comboBoxPowerLimit         ->setEnabled(true);
        _ui->comboBoxMainRotorTipVel    ->setEnabled(true);
    }
    else
    {
        // data - general
        _ui->labelMassEmpty   ->setEnabled(true);
        _ui->labelMTOW        ->setEnabled(true);
        _ui->labelMassMaxLand ->setEnabled(true);
        _ui->labelMaxFuel     ->setEnabled(true);
        _ui->labelMaxNz       ->setEnabled(true);
        _ui->labelMaxNzLand   ->setEnabled(true);

        _ui->spinBoxMassEmpty   ->setEnabled(true);
        _ui->spinBoxMTOW        ->setEnabled(true);
        _ui->spinBoxMassMaxLand ->setEnabled(true);
        _ui->spinBoxMaxFuel     ->setEnabled(true);
        _ui->spinBoxMaxNz       ->setEnabled(true);
        _ui->spinBoxMaxNzLand   ->setEnabled(true);

        _ui->labelMaxNzUnit->setEnabled(true);
        _ui->labelMaxNzLandUnit->setEnabled(true);

        _ui->comboBoxMassEmpty   ->setEnabled(true);
        _ui->comboBoxMTOW        ->setEnabled(true);
        _ui->comboBoxMassMaxLand ->setEnabled(true);
        _ui->comboBoxMaxFuel     ->setEnabled(true);

        // data - fuselage
        _ui->labelFuseLength ->setEnabled(true);
        _ui->labelFuseHeight ->setEnabled(true);
        _ui->labelFuseWidth  ->setEnabled(true);
        _ui->labelNoseLength ->setEnabled(true);

        _ui->spinBoxFuseLength ->setEnabled(true);
        _ui->spinBoxFuseHeight ->setEnabled(true);
        _ui->spinBoxFuseWidth  ->setEnabled(true);
        _ui->spinBoxNoseLength ->setEnabled(true);

        _ui->comboBoxFuseLength ->setEnabled(true);
        _ui->comboBoxFuseHeight ->setEnabled(true);
        _ui->comboBoxFuseWidth  ->setEnabled(true);
        _ui->comboBoxNoseLength ->setEnabled(true);

        _ui->labelWetAreaEst->setEnabled(true);
        _ui->spinBoxWetAreaEst->setEnabled(true);
        _ui->comboBoxWetAreaEst->setEnabled(true);
        _ui->checkBoxWettedAreaOverride->setEnabled(true);

        // data - wing
        _ui->labelWingArea    ->setEnabled(true);
        _ui->labelWingAreaExp ->setEnabled(true);
        _ui->labelWingSpan    ->setEnabled(true);
        _ui->labelWingSweep   ->setEnabled(true);
        _ui->labelWingCRoot   ->setEnabled(true);
        _ui->labelWingCTip    ->setEnabled(true);
        _ui->labelWingTC      ->setEnabled(true);
        _ui->labelWingAR      ->setEnabled(true);
        _ui->labelWingTR      ->setEnabled(true);

        _ui->spinBoxWingArea    ->setEnabled(true);
        _ui->spinBoxWingAreaExp ->setEnabled(true);
        _ui->spinBoxWingSpan    ->setEnabled(true);
        _ui->spinBoxWingSweep   ->setEnabled(true);
        _ui->spinBoxWingCRoot   ->setEnabled(true);
        _ui->spinBoxWingCTip    ->setEnabled(true);
        _ui->spinBoxWingTC      ->setEnabled(true);
        _ui->spinBoxWingAR      ->setEnabled(true);
        _ui->spinBoxWingTR      ->setEnabled(true);

        _ui->labelWingTCUnit->setEnabled(true);

        _ui->comboBoxWingArea    ->setEnabled(true);
        _ui->comboBoxWingAreaExp ->setEnabled(true);
        _ui->comboBoxWingSpan    ->setEnabled(true);
        _ui->comboBoxWingSweep   ->setEnabled(true);
        _ui->comboBoxWingCRoot   ->setEnabled(true);
        _ui->comboBoxWingCTip    ->setEnabled(true);

        _ui->labelWingARUnit->setEnabled(true);
        _ui->labelWingTRUnit->setEnabled(true);

        // data - horizontal tail
        _ui->labelHorTailArea ->setEnabled(true);
        _ui->labelHorTailAR   ->setEnabled(true);
        _ui->labelHorTailTR   ->setEnabled(true);

        _ui->spinBoxHorTailArea ->setEnabled(true);
        _ui->spinBoxHorTailAR   ->setEnabled(true);
        _ui->spinBoxHorTailTR   ->setEnabled(true);

        _ui->comboBoxHorTailArea ->setEnabled(true);

        // data - vertical tail
        _ui->labelVerTailArea   ->setEnabled(true);
        _ui->labelVerTailHeight ->setEnabled(true);
        _ui->labelVerTailSweep  ->setEnabled(true);
        _ui->labelVerTailAR     ->setEnabled(true);
        _ui->labelVerTailTR     ->setEnabled(true);

        _ui->spinBoxVerTailArea   ->setEnabled(true);
        _ui->spinBoxVerTailHeight ->setEnabled(true);
        _ui->spinBoxVerTailSweep  ->setEnabled(true);
        _ui->spinBoxVerTailAR     ->setEnabled(true);
        _ui->spinBoxVerTailTR     ->setEnabled(true);

        _ui->comboBoxVerTailArea   ->setEnabled(true);
        _ui->comboBoxVerTailHeight ->setEnabled(true);
        _ui->comboBoxVerTailSweep  ->setEnabled(true);

        _ui->checkBoxTailT->setEnabled(true);

        // data - landing gear
        _ui->labelMainGearLength ->setEnabled(true);
        _ui->labelNoseGearLength ->setEnabled(true);

        _ui->spinBoxMainGearLength ->setEnabled(true);
        _ui->spinBoxNoseGearLength ->setEnabled(true);

        _ui->comboBoxMainGearLength ->setEnabled(true);
        _ui->comboBoxNoseGearLength ->setEnabled(true);

        _ui->checkBoxGearFixed  ->setEnabled(true);

        if ( type == AircraftData::FighterAttack )
        {
            // data - general
            _ui->labelMachMax->setEnabled(true);
            _ui->spinBoxMachMax->setEnabled(true);

            _ui->checkBoxNavyAircraft->setEnabled(true);

            // data - wing
            _ui->labelCtrlArea  ->setEnabled(true);
            _ui->spinBoxCtrlArea  ->setEnabled(true);
            _ui->comboBoxCtrlArea  ->setEnabled(true);

            _ui->checkBoxWingDelta    ->setEnabled(true);
            _ui->checkBoxWingVarSweep ->setEnabled(true);

            // data - horizontal tail
            _ui->labelHorTailSpan  ->setEnabled(true);
            _ui->labelHorTailWF    ->setEnabled(true);

            _ui->spinBoxHorTailSpan  ->setEnabled(true);
            _ui->spinBoxHorTailWF    ->setEnabled(true);

            _ui->comboBoxHorTailSpan  ->setEnabled(true);
            _ui->comboBoxHorTailWF    ->setEnabled(true);

            _ui->checkBoxHorTailRolling ->setEnabled(true);

            // data - vertical tail
            _ui->labelVerTailArm    ->setEnabled(true);
            _ui->labelVerTailCRoot  ->setEnabled(true);
            _ui->labelVerTailCTip   ->setEnabled(true);
            _ui->labelRuddArea      ->setEnabled(true);

            _ui->spinBoxVerTailArm    ->setEnabled(true);
            _ui->spinBoxVerTailCRoot  ->setEnabled(true);
            _ui->spinBoxVerTailCTip   ->setEnabled(true);
            _ui->spinBoxRuddArea      ->setEnabled(true);

            _ui->comboBoxVerTailArm    ->setEnabled(true);
            _ui->comboBoxVerTailCRoot  ->setEnabled(true);
            _ui->comboBoxVerTailCTip   ->setEnabled(true);
            _ui->comboBoxRuddArea      ->setEnabled(true);

            // data - landing gear
            _ui->labelNoseGearWheels ->setEnabled(true);
            _ui->spinBoxNoseGearWheels ->setEnabled(true);

            _ui->checkBoxGearCross  ->setEnabled(true);
            _ui->checkBoxGearTripod ->setEnabled(true);
        }
        else if ( type == AircraftData::CargoTransport )
        {
            // data - general
            _ui->labelStallV->setEnabled(true);
            _ui->spinBoxStallV->setEnabled(true);
            _ui->comboBoxStallV->setEnabled(true);

            // data - fuselage
            _ui->labelCargoDoor->setEnabled(true);
            _ui->comboBoxCargoDoor->setEnabled(true);

            _ui->checkBoxFuselageLG->setEnabled(true);

            // data - wing
            _ui->labelCtrlArea  ->setEnabled(true);
            _ui->spinBoxCtrlArea  ->setEnabled(true);
            _ui->comboBoxCtrlArea  ->setEnabled(true);

            // data - horizontal tail
            _ui->labelHorTailSpan  ->setEnabled(true);
            _ui->labelHorTailSweep ->setEnabled(true);
            _ui->labelHorTailArm   ->setEnabled(true);
            _ui->labelElevArea     ->setEnabled(true);
            _ui->labelHorTailWF    ->setEnabled(true);

            _ui->spinBoxHorTailSpan  ->setEnabled(true);
            _ui->spinBoxHorTailSweep ->setEnabled(true);
            _ui->spinBoxHorTailArm   ->setEnabled(true);
            _ui->spinBoxElevArea     ->setEnabled(true);
            _ui->spinBoxHorTailWF    ->setEnabled(true);

            _ui->comboBoxHorTailSpan  ->setEnabled(true);
            _ui->comboBoxHorTailSweep ->setEnabled(true);
            _ui->comboBoxHorTailArm   ->setEnabled(true);
            _ui->comboBoxElevArea     ->setEnabled(true);
            _ui->comboBoxHorTailWF    ->setEnabled(true);

            _ui->checkBoxHorTailMoving  ->setEnabled(true);

            // data - vertical tail
            _ui->labelVerTailArm    ->setEnabled(true);
            _ui->labelVerTailTC     ->setEnabled(true);

            _ui->spinBoxVerTailArm    ->setEnabled(true);
            _ui->spinBoxVerTailTC     ->setEnabled(true);

            _ui->comboBoxVerTailArm    ->setEnabled(true);

            // data - landing gear
            _ui->labelMainGearWheels ->setEnabled(true);
            _ui->labelMainGearStruts ->setEnabled(true);
            _ui->labelNoseGearWheels ->setEnabled(true);

            _ui->spinBoxMainGearWheels ->setEnabled(true);
            _ui->spinBoxMainGearStruts ->setEnabled(true);
            _ui->spinBoxNoseGearWheels ->setEnabled(true);

            _ui->checkBoxGearMainKneel ->setEnabled(true);
            _ui->checkBoxGearNoseKneel ->setEnabled(true);
        }
        else if ( type == AircraftData::GeneralAviation )
        {
            // data - general
            _ui->labelCruiseH->setEnabled(true);
            _ui->labelCruiseV->setEnabled(true);

            _ui->spinBoxCruiseH->setEnabled(true);
            _ui->spinBoxCruiseV->setEnabled(true);

            _ui->comboBoxCruiseH->setEnabled(true);
            _ui->comboBoxCruiseV->setEnabled(true);

            // data - fuselage
            _ui->labelPressVol->setEnabled(true);
            _ui->spinBoxPressVol->setEnabled(true);
            _ui->comboBoxPressVol->setEnabled(true);

            // data - wing
            _ui->spinBoxWingFuel->setEnabled(true);
            _ui->comboBoxWingFuel->setEnabled(true);
            _ui->labelWingFuel->setEnabled(true);

            // data - horizontal tail
            _ui->labelHorTailSweep ->setEnabled(true);
            _ui->labelHorTailArm   ->setEnabled(true);
            _ui->labelHorTailCRoot ->setEnabled(true);
            _ui->labelHorTailCTip  ->setEnabled(true);
            _ui->labelHorTailTC    ->setEnabled(true);

            _ui->spinBoxHorTailSweep ->setEnabled(true);
            _ui->spinBoxHorTailArm   ->setEnabled(true);
            _ui->spinBoxHorTailCRoot ->setEnabled(true);
            _ui->spinBoxHorTailCTip  ->setEnabled(true);
            _ui->spinBoxHorTailTC    ->setEnabled(true);

            _ui->comboBoxHorTailSweep ->setEnabled(true);
            _ui->comboBoxHorTailArm   ->setEnabled(true);
            _ui->comboBoxHorTailCRoot ->setEnabled(true);
            _ui->comboBoxHorTailCTip  ->setEnabled(true);

            // data - vertical tail
            _ui->spinBoxVerTailCRoot ->setEnabled(true);
            _ui->spinBoxVerTailCTip  ->setEnabled(true);
            _ui->spinBoxVerTailTC    ->setEnabled(true);

            _ui->comboBoxVerTailCRoot ->setEnabled(true);
            _ui->comboBoxVerTailCTip  ->setEnabled(true);

            _ui->labelVerTailCRoot ->setEnabled(true);
            _ui->labelVerTailCTip  ->setEnabled(true);
            _ui->labelVerTailTC    ->setEnabled(true);

            // data - landing gear
        }
    }
}

void DockWidgetParams::updateWettedArea()
{
    double l_fuse = _ui->comboBoxFuseLength ->invert(_ui->spinBoxFuseLength ->value());
    double w_fuse = _ui->comboBoxFuseWidth  ->invert(_ui->spinBoxFuseWidth  ->value());
    double h_fuse = _ui->comboBoxFuseHeight ->invert(_ui->spinBoxFuseHeight ->value());
    double l_nose = _ui->comboBoxNoseLength ->invert(_ui->spinBoxNoseLength ->value());

    double a_top  = w_fuse * (l_fuse - l_nose) + 0.5 * w_fuse * l_nose;
    double a_side = h_fuse * (l_fuse - l_nose) + 0.5 * h_fuse * l_nose;

    // Raymer: Aircraft Design, p.205, eq. 7.13
    double s_wet = 3.4 * ((a_top + a_side) / 2.0);

    _ui->spinBoxWetAreaEst->setValue(_ui->comboBoxWetAreaEst->convert(s_wet));
}

void DockWidgetParams::updateWingAR()
{
    const AircraftData* data = _aircraft->GetData();
    if ( data->wing.area > 0.0_sq_m )
    {
        double ar = pow(data->wing.span(), 2.0) / data->wing.area();
        _ui->spinBoxWingAR->setValue(ar);
    }
    else
    {
        _ui->spinBoxWingAR->setValue(0.0);
    }
}

void DockWidgetParams::updateWingTR()
{
    const AircraftData* data = _aircraft->GetData();
    if ( data->wing.c_root > 0.0_m )
    {
        double tr = data->wing.c_tip / data->wing.c_root;
        _ui->spinBoxWingTR->setValue(tr);
    }
    else
    {
        _ui->spinBoxWingTR->setValue(0.0);
    }
}

void DockWidgetParams::updateHorTailAR()
{
    const AircraftData* data = _aircraft->GetData();
    if ( data->hor_tail.area > 0.0_sq_m )
    {
        double ar = pow(data->hor_tail.span(), 2.0) / data->hor_tail.area();
        _ui->spinBoxHorTailAR->setValue(ar);
    }
    else
    {
        _ui->spinBoxHorTailAR->setValue(0.0);
    }
}

void DockWidgetParams::updateHorTailTR()
{
    const AircraftData* data = _aircraft->GetData();
    if ( data->hor_tail.c_root > 0.0_m )
    {
        double tr = data->hor_tail.c_tip / data->hor_tail.c_root;
        _ui->spinBoxHorTailTR->setValue(tr);
    }
    else
    {
        _ui->spinBoxHorTailTR->setValue(0.0);
    }
}

void DockWidgetParams::updateVerTailAR()
{
    const AircraftData* data = _aircraft->GetData();
    if ( data->ver_tail.area > 0.0_sq_m )
    {
        double ar = pow(data->ver_tail.height(), 2.0) / data->ver_tail.area();
        _ui->spinBoxVerTailAR->setValue(ar);
    }
    else
    {
        _ui->spinBoxVerTailAR->setValue(0.0);
    }
}

void DockWidgetParams::updateVerTailTR()
{
    const AircraftData* data = _aircraft->GetData();
    if ( data->ver_tail.c_root > 0.0_m )
    {
        double tr = data->ver_tail.c_tip / data->ver_tail.c_root;
        _ui->spinBoxVerTailTR->setValue(tr);
    }
    else
    {
        _ui->spinBoxVerTailTR->setValue(0.0);
    }
}

void DockWidgetParams::updateRotorTipVel()
{
    double omg = 2.0 * M_PI * _ui->spinBoxMainRotorRPM->value() / 60.0;
    double rad = 0.5 * _ui->comboBoxMainRotorDiameter->invert(_ui->spinBoxMainRotorDiameter->value());
    double vel = omg * rad;
    _ui->spinBoxMainRotorTipVel->setValue(_ui->comboBoxMainRotorTipVel->convert(vel));
}

void DockWidgetParams::on_comboBoxAircraftType_currentIndexChanged(int index)
{
    AircraftData::Type type = AircraftData::FighterAttack;
    switch ( index )
    {
    case AircraftData::FighterAttack:
        type = AircraftData::FighterAttack;
        break;
    case AircraftData::CargoTransport:
        type = AircraftData::CargoTransport;
        break;
    case AircraftData::GeneralAviation:
        type = AircraftData::GeneralAviation;
        break;
    case AircraftData::Helicopter:
        type = AircraftData::Helicopter;
        break;
    }

    setAircraftType(type);
    _aircraft->GetData()->type = type;

    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMassEmpty_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxMassEmpty->invert(arg1);
    _aircraft->GetData()->general.m_empty = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMTOW_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxMTOW->invert(arg1);
    _aircraft->GetData()->general.mtow =  units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMassMaxLand_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxMassMaxLand->invert(arg1);
    _aircraft->GetData()->general.m_maxLand = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMaxFuel_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxMaxFuel->invert(arg1);
    _aircraft->GetData()->general.m_maxFuel = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMaxNz_valueChanged(double arg1)
{
    _aircraft->GetData()->general.nz_max = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMaxNzLand_valueChanged(double arg1)
{
    _aircraft->GetData()->general.nz_maxLand = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxStallV_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxStallV->invert(arg1);
    _aircraft->GetData()->general.v_stall = units::velocity::knot_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxCruiseV_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxCruiseV->invert(arg1);
    _aircraft->GetData()->general.v_cruise = units::velocity::knot_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxCruiseH_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxCruiseH->invert(arg1);
    _aircraft->GetData()->general.h_cruise = units::length::foot_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMachMax_valueChanged(double arg1)
{
    _aircraft->GetData()->general.mach_max = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxNavyAircraft_toggled(bool checked)
{
    _aircraft->GetData()->general.navy_ac = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_comboBoxCargoDoor_currentIndexChanged(int index)
{
    AircraftData::Fuselage::CargoDoor door = AircraftData::Fuselage::NoCargoDoor;
    switch ( index )
    {
    case AircraftData::Fuselage::NoCargoDoor:
        door = AircraftData::Fuselage::NoCargoDoor;
        break;
    case AircraftData::Fuselage::OneSideCargoDoor:
        door = AircraftData::Fuselage::OneSideCargoDoor;
        break;
    case AircraftData::Fuselage::TwoSideCargoDoor:
        door = AircraftData::Fuselage::TwoSideCargoDoor;
        break;
    case AircraftData::Fuselage::AftClamshellDoor:
        door = AircraftData::Fuselage::AftClamshellDoor;
        break;
    case AircraftData::Fuselage::TwoSideAndAftDoor:
        door = AircraftData::Fuselage::TwoSideAndAftDoor;
        break;
    }

    _aircraft->GetData()->fuselage.cargo_door = door;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxFuseLength_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxFuseLength->invert(arg1);
    _aircraft->GetData()->fuselage.l = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWettedArea();
}

void DockWidgetParams::on_spinBoxFuseHeight_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxFuseHeight->invert(arg1);
    _aircraft->GetData()->fuselage.h = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWettedArea();
}

void DockWidgetParams::on_spinBoxFuseWidth_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxFuseWidth->invert(arg1);
    _aircraft->GetData()->fuselage.w = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWettedArea();
}

void DockWidgetParams::on_spinBoxNoseLength_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxNoseLength->invert(arg1);
    _aircraft->GetData()->fuselage.l_n = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWettedArea();
}

void DockWidgetParams::on_spinBoxPressVol_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxPressVol->invert(arg1);
    _aircraft->GetData()->fuselage.press_vol = units::volume::cubic_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWetAreaEst_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWetAreaEst->invert(arg1);
    if ( !_aircraft->GetData()->fuselage.wetted_area_override )
    {
        _ui->spinBoxWetAreaReal->setValue(_ui->comboBoxWetAreaReal->convert(arg1_raw));
    }
}

void DockWidgetParams::on_spinBoxWetAreaReal_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWetAreaReal->invert(arg1);
    _aircraft->GetData()->fuselage.wetted_area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxFuselageLG_toggled(bool checked)
{
    _aircraft->GetData()->fuselage.landing_gear = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxCargoRamp_toggled(bool checked)
{
    _aircraft->GetData()->fuselage.cargo_ramp = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxWettedAreaOverride_toggled(bool checked)
{
    _aircraft->GetData()->fuselage.wetted_area_override = checked;
    _ui->labelWettedAreaReal->setEnabled(checked);
    _ui->spinBoxWetAreaReal->setEnabled(checked);
    _ui->comboBoxWetAreaReal->setEnabled(checked);

    if ( !checked )
    {
        double arg1_raw = _ui->comboBoxWetAreaEst->invert(_ui->spinBoxWetAreaEst->value());
        _ui->spinBoxWetAreaReal->setValue(_ui->comboBoxWetAreaReal->convert(arg1_raw));
    }

    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingArea_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWingArea->invert(arg1);
    _aircraft->GetData()->wing.area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWingAR();
}

void DockWidgetParams::on_spinBoxWingAreaExp_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWingAreaExp->invert(arg1);
    _aircraft->GetData()->wing.area_exp = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingSpan_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWingSpan->invert(arg1);
    _aircraft->GetData()->wing.span = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWingAR();
}

void DockWidgetParams::on_spinBoxWingSweep_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWingSweep->invert(arg1);
    _aircraft->GetData()->wing.sweep = units::angle::degree_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingCRoot_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWingCRoot->invert(arg1);
    _aircraft->GetData()->wing.c_root = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWingTR();
}

void DockWidgetParams::on_spinBoxWingCTip_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWingCTip->invert(arg1);
    _aircraft->GetData()->wing.c_tip = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWingTR();
}

void DockWidgetParams::on_spinBoxWingTC_valueChanged(double arg1)
{
    _aircraft->GetData()->wing.tc = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingFuel_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxWingFuel->invert(arg1);
    _aircraft->GetData()->wing.fuel = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxCtrlArea_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxCtrlArea->invert(arg1);
    _aircraft->GetData()->wing.ctrl_area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingAR_valueChanged(double arg1)
{
    _aircraft->GetData()->wing.ar = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingTR_valueChanged(double arg1)
{
    _aircraft->GetData()->wing.tr = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxWingDelta_toggled(bool checked)
{
    _aircraft->GetData()->wing.delta = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxWingVarSweep_toggled(bool checked)
{
    _aircraft->GetData()->wing.var_sweep = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailArea_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxHorTailArea->invert(arg1);
    _aircraft->GetData()->hor_tail.area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
    updateHorTailAR();
}

void DockWidgetParams::on_spinBoxHorTailSpan_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxHorTailSpan->invert(arg1);
    _aircraft->GetData()->hor_tail.span = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateHorTailAR();
}

void DockWidgetParams::on_spinBoxHorTailSweep_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxHorTailSweep->invert(arg1);
    _aircraft->GetData()->hor_tail.sweep = units::angle::degree_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailCRoot_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxHorTailCRoot->invert(arg1);
    _aircraft->GetData()->hor_tail.c_root = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateHorTailTR();
}

void DockWidgetParams::on_spinBoxHorTailCTip_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxHorTailCTip->invert(arg1);
    _aircraft->GetData()->hor_tail.c_tip = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateHorTailTR();
}

void DockWidgetParams::on_spinBoxHorTailTC_valueChanged(double arg1)
{
    _aircraft->GetData()->hor_tail.tc = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxElevArea_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxElevArea->invert(arg1);
    _aircraft->GetData()->hor_tail.elev_area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailWF_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxHorTailWF->invert(arg1);
    _aircraft->GetData()->hor_tail.w_f = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailArm_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxHorTailArm->invert(arg1);
    _aircraft->GetData()->hor_tail.arm = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailAR_valueChanged(double arg1)
{
    _aircraft->GetData()->hor_tail.ar = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailTR_valueChanged(double arg1)
{
    _aircraft->GetData()->hor_tail.tr = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxHorTailMoving_toggled(bool checked)
{
    _aircraft->GetData()->hor_tail.moving = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxHorTailRolling_toggled(bool checked)
{
    _aircraft->GetData()->hor_tail.rolling = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailArea_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxVerTailArea->invert(arg1);
    _aircraft->GetData()->ver_tail.area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
    updateVerTailAR();
}

void DockWidgetParams::on_spinBoxVerTailHeight_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxVerTailHeight->invert(arg1);
    _aircraft->GetData()->ver_tail.height = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateVerTailAR();
}

void DockWidgetParams::on_spinBoxVerTailSweep_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxVerTailSweep->invert(arg1);
    _aircraft->GetData()->ver_tail.sweep = units::angle::degree_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailCRoot_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxVerTailCRoot->invert(arg1);
    _aircraft->GetData()->ver_tail.c_root = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateVerTailTR();
}

void DockWidgetParams::on_spinBoxVerTailCTip_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxVerTailCTip->invert(arg1);
    _aircraft->GetData()->ver_tail.c_tip = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateVerTailTR();
}

void DockWidgetParams::on_spinBoxVerTailTC_valueChanged(double arg1)
{
    _aircraft->GetData()->ver_tail.tc = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailArm_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxVerTailArm->invert(arg1);
    _aircraft->GetData()->ver_tail.arm = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxRuddArea_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxRuddArea->invert(arg1);
    _aircraft->GetData()->ver_tail.rudd_area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailAR_valueChanged(double arg1)
{
    _aircraft->GetData()->ver_tail.ar = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailTR_valueChanged(double arg1)
{
    _aircraft->GetData()->ver_tail.tr = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxTailT_toggled(bool checked)
{
    _aircraft->GetData()->ver_tail.t_tail = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxVerTailRotor_toggled(bool checked)
{
    _aircraft->GetData()->ver_tail.rotor = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainGearLength_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxMainGearLength->invert(arg1);
    _aircraft->GetData()->landing_gear.main_l = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxNoseGearLength_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxNoseGearLength->invert(arg1);
    _aircraft->GetData()->landing_gear.nose_l = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainGearWheels_valueChanged(int arg1)
{
    _aircraft->GetData()->landing_gear.main_wheels = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainGearStruts_valueChanged(int arg1)
{
    _aircraft->GetData()->landing_gear.main_struts = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxNoseGearWheels_valueChanged(int arg1)
{
    _aircraft->GetData()->landing_gear.nose_wheels = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearFixed_toggled(bool checked)
{
    _aircraft->GetData()->landing_gear.fixed = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearCross_toggled(bool checked)
{
    _aircraft->GetData()->landing_gear.cross = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearTripod_toggled(bool checked)
{
    _aircraft->GetData()->landing_gear.tripod = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearMainKneel_toggled(bool checked)
{
    _aircraft->GetData()->landing_gear.main_kneel = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearNoseKneel_toggled(bool checked)
{
    _aircraft->GetData()->landing_gear.nose_kneel = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxEngineMass_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxEngineMass->invert(arg1);
    _aircraft->GetData()->engine.mass = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorDiameter_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxMainRotorDiameter->invert(arg1);
    _aircraft->GetData()->rotors.main_r = 0.5 * units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateRotorTipVel();
}

void DockWidgetParams::on_spinBoxMainRotorChord_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxMainRotorChord->invert(arg1);
    _aircraft->GetData()->rotors.main_cb = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorRPM_valueChanged(double arg1)
{
    _aircraft->GetData()->rotors.main_rpm = units::angular_velocity::rpm_t(arg1);
    emit(aircraftChanged());
    updateRotorTipVel();
}

void DockWidgetParams::on_spinBoxTailRotorDiameter_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxTailRotorDiameter->invert(arg1);
    _aircraft->GetData()->rotors.tail_r = 0.5 * units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorGear_valueChanged(double arg1)
{
    _aircraft->GetData()->rotors.main_gear_ratio = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxPowerLimit_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxPowerLimit->invert(arg1);
    _aircraft->GetData()->rotors.mcp = units::power::horsepower_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorTipVel_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBoxMainRotorTipVel->invert(arg1);
    _aircraft->GetData()->rotors.main_tip_vel = units::velocity::meters_per_second_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorBlades_valueChanged(int arg1)
{
    _aircraft->GetData()->rotors.main_blades = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_toolButtonBrowse_clicked()
{
    QDir proj_dir = QFileInfo(_aircraftFile->GetFile()).absoluteDir();
    QString file = proj_dir.absoluteFilePath(_ui->lineEditModelFile->text());

    QString caption = "Browse";
    QString dir = ( file.length() > 0 ) ? QFileInfo(file).path() : ".";
    QString filter;
    QString selected_filter;

    filter += "AC3D (*.ac)";
    filter += ";;";
    filter += "3D Studio (*.3ds)";
    filter += ";;";
    filter += "COLLADA (*.dae)";
    filter += ";;";
    filter += selected_filter = "OpenSceneGraph (*.osg *.osga *.osgb *.osgt *.ive)";
    filter += ";;";
    filter += "Wavefront OBJ (*.obj)";
    filter += ";;";
    filter += "STL (*.stl)";

    QString new_file = QFileDialog::getOpenFileName(this, caption, dir, filter, &selected_filter);

    if ( new_file.length() > 0 )
    {
        QDir proj_dir = QFileInfo(_aircraftFile->GetFile()).absoluteDir();
        new_file = proj_dir.relativeFilePath(new_file);

        _ui->lineEditModelFile->setText(new_file);
    }
}

void DockWidgetParams::on_lineEditModelFile_textChanged(const QString &arg1)
{
    _aircraft->GetData()->model3d.file = arg1;
    emit(aircraftChanged());
}


void DockWidgetParams::on_spinBox_OffsetX_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBox_OffsetX->invert(arg1);
    _aircraft->GetData()->model3d.offset_x = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_OffsetY_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBox_OffsetY->invert(arg1);
    _aircraft->GetData()->model3d.offset_y = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_OffsetZ_valueChanged(double arg1)
{
    double arg1_raw = _ui->comboBox_OffsetZ->invert(arg1);
    _aircraft->GetData()->model3d.offset_z = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_RotationX_valueChanged(double arg1)
{
    _aircraft->GetData()->model3d.rotation_x = units::angle::degree_t(arg1);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_RotationY_valueChanged(double arg1)
{
    _aircraft->GetData()->model3d.rotation_y = units::angle::degree_t(arg1);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_RotationZ_valueChanged(double arg1)
{
    _aircraft->GetData()->model3d.rotation_z = units::angle::degree_t(arg1);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_Scale_valueChanged(double arg1)
{
    _aircraft->GetData()->model3d.scale = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_comboBoxMassEmpty_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxMassEmpty, _ui->comboBoxMassEmpty);
}

void DockWidgetParams::on_comboBoxMTOW_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxMTOW, _ui->comboBoxMTOW);
}

void DockWidgetParams::on_comboBoxMassMaxLand_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxMassMaxLand, _ui->comboBoxMassMaxLand);
}

void DockWidgetParams::on_comboBoxMaxFuel_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxMaxFuel, _ui->comboBoxMaxFuel);
}

void DockWidgetParams::on_comboBoxStallV_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxStallV, _ui->comboBoxStallV);
}

void DockWidgetParams::on_comboBoxCruiseV_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxCruiseV, _ui->comboBoxCruiseV);
}

void DockWidgetParams::on_comboBoxCruiseH_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxCruiseH, _ui->comboBoxCruiseH);
}

void DockWidgetParams::on_comboBoxFuseLength_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxFuseLength, _ui->comboBoxFuseLength);
}

void DockWidgetParams::on_comboBoxFuseWidth_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxFuseWidth, _ui->comboBoxFuseWidth);
}

void DockWidgetParams::on_comboBoxFuseHeight_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxFuseHeight, _ui->comboBoxFuseHeight);
}

void DockWidgetParams::on_comboBoxNoseLength_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxNoseLength, _ui->comboBoxNoseLength);
}

void DockWidgetParams::on_comboBoxPressVol_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxPressVol, _ui->comboBoxPressVol);
}

void DockWidgetParams::on_comboBoxWetAreaEst_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWetAreaEst, _ui->comboBoxWetAreaEst);
}

void DockWidgetParams::on_comboBoxWetAreaReal_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWetAreaReal, _ui->comboBoxWetAreaReal);
}

void DockWidgetParams::on_comboBoxWingArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWingArea, _ui->comboBoxWingArea);
}

void DockWidgetParams::on_comboBoxWingAreaExp_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWingAreaExp, _ui->comboBoxWingAreaExp);
}

void DockWidgetParams::on_comboBoxWingSpan_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWingSpan, _ui->comboBoxWingSpan);
}

void DockWidgetParams::on_comboBoxWingSweep_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWingSweep, _ui->comboBoxWingSweep);
}

void DockWidgetParams::on_comboBoxWingCRoot_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWingCRoot, _ui->comboBoxWingCRoot);
}

void DockWidgetParams::on_comboBoxWingCTip_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWingCTip, _ui->comboBoxWingCTip);
}

void DockWidgetParams::on_comboBoxWingFuel_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxWingFuel, _ui->comboBoxWingFuel);
}

void DockWidgetParams::on_comboBoxCtrlArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxCtrlArea, _ui->comboBoxCtrlArea);
}

void DockWidgetParams::on_comboBoxHorTailArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxHorTailArea, _ui->comboBoxHorTailArea);
}

void DockWidgetParams::on_comboBoxHorTailSpan_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxHorTailSpan, _ui->comboBoxHorTailSpan);
}

void DockWidgetParams::on_comboBoxHorTailSweep_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxHorTailSweep, _ui->comboBoxHorTailSweep);
}

void DockWidgetParams::on_comboBoxHorTailCRoot_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxHorTailCRoot, _ui->comboBoxHorTailCRoot);
}

void DockWidgetParams::on_comboBoxHorTailCTip_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxHorTailCTip, _ui->comboBoxHorTailCTip);
}

void DockWidgetParams::on_comboBoxHorTailArm_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxHorTailArm, _ui->comboBoxHorTailArm);
}

void DockWidgetParams::on_comboBoxElevArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxElevArea, _ui->comboBoxElevArea);
}

void DockWidgetParams::on_comboBoxHorTailWF_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxHorTailWF, _ui->comboBoxHorTailWF);
}

void DockWidgetParams::on_comboBoxVerTailArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxVerTailArea, _ui->comboBoxVerTailArea);
}

void DockWidgetParams::on_comboBoxVerTailHeight_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxVerTailHeight, _ui->comboBoxVerTailHeight);
}

void DockWidgetParams::on_comboBoxVerTailSweep_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxVerTailSweep, _ui->comboBoxVerTailSweep);
}

void DockWidgetParams::on_comboBoxVerTailCRoot_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxVerTailCRoot, _ui->comboBoxVerTailCRoot);
}

void DockWidgetParams::on_comboBoxVerTailCTip_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxVerTailCTip, _ui->comboBoxVerTailCTip);
}

void DockWidgetParams::on_comboBoxVerTailArm_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxVerTailArm, _ui->comboBoxVerTailArm);
}

void DockWidgetParams::on_comboBoxRuddArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxRuddArea, _ui->comboBoxRuddArea);
}

void DockWidgetParams::on_comboBoxMainGearLength_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxMainGearLength, _ui->comboBoxMainGearLength);
}

void DockWidgetParams::on_comboBoxNoseGearLength_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxNoseGearLength, _ui->comboBoxNoseGearLength);
}

void DockWidgetParams::on_comboBoxEngineMass_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxEngineMass, _ui->comboBoxEngineMass);
}

void DockWidgetParams::on_comboBoxMainRotorDiameter_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxMainRotorDiameter, _ui->comboBoxMainRotorDiameter);
}

void DockWidgetParams::on_comboBoxMainRotorChord_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxMainRotorChord, _ui->comboBoxMainRotorChord);
}

void DockWidgetParams::on_comboBoxTailRotorDiameter_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxTailRotorDiameter, _ui->comboBoxTailRotorDiameter);
}

void DockWidgetParams::on_comboBoxPowerLimit_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxPowerLimit, _ui->comboBoxPowerLimit);
}

void DockWidgetParams::on_comboBoxMainRotorTipVel_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBoxMainRotorTipVel, _ui->comboBoxMainRotorTipVel);
}

void DockWidgetParams::on_comboBox_OffsetX_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_OffsetX, _ui->comboBox_OffsetX);
}

void DockWidgetParams::on_comboBox_OffsetY_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_OffsetY, _ui->comboBox_OffsetY);
}

void DockWidgetParams::on_comboBox_OffsetZ_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(_ui->spinBox_OffsetZ, _ui->comboBox_OffsetZ);
}
