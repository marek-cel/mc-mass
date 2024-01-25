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
    , ui_(new Ui::DockWidgetParams)
    , aircraftFile_(aircraftFile)
{
    ui_->setupUi(this);

    aircraft_ = aircraftFile_->GetAircraft();

    setAircraftType(AircraftData::FighterAttack);
    updateGUI();

    settingsRead();
}

DockWidgetParams::~DockWidgetParams()
{
    settingsSave();

    if ( ui_ ) { delete ui_; } ui_ = nullptr;
}

void DockWidgetParams::updateGUI()
{
    const AircraftData* data = aircraft_->GetData();

    // general
    ui_->comboBoxAircraftType->setCurrentIndex(data->type);

    ui_->spinBoxMassEmpty   ->setValue(ui_->comboBoxMassEmpty   ->convert(data->general.m_empty   ()));
    ui_->spinBoxMTOW        ->setValue(ui_->comboBoxMTOW        ->convert(data->general.mtow      ()));
    ui_->spinBoxMassMaxLand ->setValue(ui_->comboBoxMassMaxLand ->convert(data->general.m_maxLand ()));

    ui_->spinBoxMaxNz     ->setValue( data->general.nz_max     );
    ui_->spinBoxMaxNzLand ->setValue( data->general.nz_maxLand );

    ui_->spinBoxStallV  ->setValue( ui_->comboBoxStallV  ->convert(data->general.v_stall  ()));
    ui_->spinBoxCruiseH ->setValue( ui_->comboBoxCruiseH ->convert(data->general.h_cruise ()));
    ui_->spinBoxCruiseV ->setValue( ui_->comboBoxCruiseV ->convert(data->general.v_cruise ()));
    ui_->spinBoxMachMax ->setValue(data->general.mach_max);

    ui_->checkBoxNavyAircraft->setChecked(data->general.navy_ac);

    // fuselage
    ui_->comboBoxCargoDoor->setCurrentIndex(data->fuselage.cargo_door);

    ui_->spinBoxFuseLength ->setValue(ui_->comboBoxFuseLength ->convert(data->fuselage.l()));
    ui_->spinBoxFuseHeight ->setValue(ui_->comboBoxFuseHeight ->convert(data->fuselage.h()));
    ui_->spinBoxFuseWidth  ->setValue(ui_->comboBoxFuseWidth  ->convert(data->fuselage.w()));

    ui_->spinBoxNoseLength->setValue(ui_->comboBoxNoseLength->convert(data->fuselage.l_n()));

    ui_->spinBoxPressVol    ->setValue(ui_->comboBoxPressVol    ->convert(data->fuselage.press_vol   ()));
    ui_->spinBoxWetAreaReal ->setValue(ui_->comboBoxWetAreaReal ->convert(data->fuselage.wetted_area ()));

    ui_->checkBoxFuselageLG ->setChecked( data->fuselage.landing_gear );
    ui_->checkBoxCargoRamp  ->setChecked( data->fuselage.cargo_ramp   );
    ui_->checkBoxWettedAreaOverride->setChecked(data->fuselage.wetted_area_override);

    // wing
    ui_->spinBoxWingArea    ->setValue(ui_->comboBoxWingArea    ->convert(data->wing.area      ()));
    ui_->spinBoxWingAreaExp ->setValue(ui_->comboBoxWingAreaExp ->convert(data->wing.area_exp  ()));
    ui_->spinBoxWingSpan    ->setValue(ui_->comboBoxWingSpan    ->convert(data->wing.span      ()));
    ui_->spinBoxWingSweep   ->setValue(ui_->comboBoxWingSweep   ->convert(data->wing.sweep     ()));
    ui_->spinBoxWingCRoot   ->setValue(ui_->comboBoxWingCRoot   ->convert(data->wing.c_root    ()));
    ui_->spinBoxWingCTip    ->setValue(ui_->comboBoxWingCTip    ->convert(data->wing.c_tip     ()));
    ui_->spinBoxWingFuel    ->setValue(ui_->comboBoxCtrlArea    ->convert(data->wing.fuel      ()));
    ui_->spinBoxCtrlArea    ->setValue(ui_->comboBoxWingFuel    ->convert(data->wing.ctrl_area ()));

    ui_->spinBoxWingTC->setValue(data->wing.tc);
    ui_->spinBoxWingAR->setValue(data->wing.ar);
    ui_->spinBoxWingTR->setValue(data->wing.tr);

    ui_->checkBoxWingDelta    ->setChecked( data->wing.delta     );
    ui_->checkBoxWingVarSweep ->setChecked( data->wing.var_sweep );

    // horizontal tail
    ui_->spinBoxHorTailArea  ->setValue(ui_->comboBoxHorTailArea  ->convert(data->hor_tail.area      ()));
    ui_->spinBoxHorTailSpan  ->setValue(ui_->comboBoxHorTailSpan  ->convert(data->hor_tail.span      ()));
    ui_->spinBoxHorTailSweep ->setValue(ui_->comboBoxHorTailSweep ->convert(data->hor_tail.sweep     ()));
    ui_->spinBoxHorTailCRoot ->setValue(ui_->comboBoxHorTailCRoot ->convert(data->hor_tail.c_root    ()));
    ui_->spinBoxHorTailCTip  ->setValue(ui_->comboBoxHorTailCTip  ->convert(data->hor_tail.c_tip     ()));
    ui_->spinBoxElevArea     ->setValue(ui_->comboBoxElevArea     ->convert(data->hor_tail.elev_area ()));
    ui_->spinBoxHorTailWF    ->setValue(ui_->comboBoxHorTailWF    ->convert(data->hor_tail.w_f       ()));
    ui_->spinBoxHorTailArm   ->setValue(ui_->comboBoxHorTailArm   ->convert(data->hor_tail.arm       ()));

    ui_->spinBoxHorTailTC->setValue(data->hor_tail.tc);
    ui_->spinBoxHorTailAR->setValue(data->hor_tail.ar);
    ui_->spinBoxHorTailTR->setValue(data->hor_tail.tr);

    ui_->checkBoxHorTailMoving  ->setChecked( data->hor_tail.moving  );
    ui_->checkBoxHorTailRolling ->setChecked( data->hor_tail.rolling );

    // vertical tail
    ui_->spinBoxVerTailArea   ->setValue(ui_->comboBoxVerTailArea   ->convert(data->ver_tail.area      ()));
    ui_->spinBoxVerTailHeight ->setValue(ui_->comboBoxVerTailHeight ->convert(data->ver_tail.height    ()));
    ui_->spinBoxVerTailSweep  ->setValue(ui_->comboBoxVerTailSweep  ->convert(data->ver_tail.sweep     ()));
    ui_->spinBoxVerTailCRoot  ->setValue(ui_->comboBoxVerTailCRoot  ->convert(data->ver_tail.c_root    ()));
    ui_->spinBoxVerTailCTip   ->setValue(ui_->comboBoxVerTailCTip   ->convert(data->ver_tail.c_tip     ()));
    ui_->spinBoxVerTailArm    ->setValue(ui_->comboBoxVerTailArm    ->convert(data->ver_tail.arm       ()));
    ui_->spinBoxRuddArea      ->setValue(ui_->comboBoxRuddArea      ->convert(data->ver_tail.rudd_area ()));

    ui_->spinBoxVerTailTC->setValue(data->ver_tail.tc);
    ui_->spinBoxVerTailAR->setValue(data->ver_tail.ar);
    ui_->spinBoxVerTailTR->setValue(data->ver_tail.tr);

    ui_->checkBoxTailT        ->setChecked( data->ver_tail.t_tail );
    ui_->checkBoxVerTailRotor ->setChecked( data->ver_tail.rotor  );

    // landing gear
    ui_->spinBoxMainGearLength->setValue(ui_->comboBoxMainGearLength->convert(data->landing_gear.main_l()));
    ui_->spinBoxNoseGearLength->setValue(ui_->comboBoxNoseGearLength->convert(data->landing_gear.nose_l()));

    ui_->spinBoxMainGearWheels->setValue(data->landing_gear.main_wheels);
    ui_->spinBoxMainGearStruts->setValue(data->landing_gear.main_struts);
    ui_->spinBoxNoseGearWheels->setValue(data->landing_gear.nose_wheels);

    ui_->checkBoxGearFixed  ->setChecked( data->landing_gear.fixed  );
    ui_->checkBoxGearCross  ->setChecked( data->landing_gear.cross  );
    ui_->checkBoxGearTripod ->setChecked( data->landing_gear.tripod );

    ui_->checkBoxGearMainKneel->setChecked(data->landing_gear.main_kneel);
    ui_->checkBoxGearNoseKneel->setChecked(data->landing_gear.nose_kneel);

    // engine
    ui_->spinBoxEngineMass->setValue(ui_->comboBoxEngineMass->convert(data->engine.mass()));

    // rotors
    ui_->spinBoxMainRotorDiameter ->setValue(ui_->comboBoxMainRotorDiameter ->convert(data->rotors.main_r      ()) * 2.0);
    ui_->spinBoxMainRotorChord    ->setValue(ui_->comboBoxMainRotorChord    ->convert(data->rotors.main_cb     ()));
    ui_->spinBoxTailRotorDiameter ->setValue(ui_->comboBoxTailRotorDiameter ->convert(data->rotors.tail_r      ()) * 2.0);
    ui_->spinBoxPowerLimit        ->setValue(ui_->comboBoxPowerLimit        ->convert(data->rotors.mcp         ()));
    ui_->spinBoxMainRotorTipVel   ->setValue(ui_->comboBoxMainRotorTipVel   ->convert(data->rotors.main_tip_vel()));

    ui_->spinBoxMainRotorRPM    ->setValue( data->rotors.main_rpm()      );
    ui_->spinBoxMainRotorGear   ->setValue( data->rotors.main_gear_ratio );
    ui_->spinBoxMainRotorBlades ->setValue( data->rotors.main_blades     );

    // model 3D
    ui_->lineEditModelFile->setText(data->model3d.file);
    ui_->spinBox_OffsetX->setValue(ui_->comboBox_OffsetX->convert(data->model3d.offset_x()));
    ui_->spinBox_OffsetY->setValue(ui_->comboBox_OffsetY->convert(data->model3d.offset_y()));
    ui_->spinBox_OffsetZ->setValue(ui_->comboBox_OffsetZ->convert(data->model3d.offset_z()));
    ui_->spinBox_RotationX->setValue(data->model3d.rotation_x());
    ui_->spinBox_RotationY->setValue(data->model3d.rotation_y());
    ui_->spinBox_RotationZ->setValue(data->model3d.rotation_z());
    ui_->spinBox_Scale->setValue(data->model3d.scale);
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
    ui_->comboBoxMassEmpty        ->setCurrentIndex(settings.value("mass_empty"   , 0).toInt());
    ui_->comboBoxMTOW             ->setCurrentIndex(settings.value("mtow"         , 0).toInt());
    ui_->comboBoxMassMaxLand      ->setCurrentIndex(settings.value("mass_landing" , 0).toInt());
    ui_->comboBoxStallV           ->setCurrentIndex(settings.value("stall_speed"  , 0).toInt());
    ui_->comboBoxCruiseV          ->setCurrentIndex(settings.value("cruise_speed" , 0).toInt());
    ui_->comboBoxCruiseH          ->setCurrentIndex(settings.value("cruise_alt"   , 0).toInt());

    // fuselage
    ui_->comboBoxFuseLength       ->setCurrentIndex(settings.value("fuselage_l"   , 0).toInt());
    ui_->comboBoxFuseWidth        ->setCurrentIndex(settings.value("fuselage_w"   , 0).toInt());
    ui_->comboBoxFuseHeight       ->setCurrentIndex(settings.value("fuselage_h"   , 0).toInt());
    ui_->comboBoxNoseLength       ->setCurrentIndex(settings.value("nose_length"  , 0).toInt());
    ui_->comboBoxPressVol         ->setCurrentIndex(settings.value("press_vol"    , 0).toInt());
    ui_->comboBoxWetAreaEst       ->setCurrentIndex(settings.value("wet_area_est" , 0).toInt());
    ui_->comboBoxWetAreaReal      ->setCurrentIndex(settings.value("wet_area_real", 0).toInt());

    // wing
    ui_->comboBoxWingArea         ->setCurrentIndex(settings.value("wing_area"    , 0).toInt());
    ui_->comboBoxWingAreaExp      ->setCurrentIndex(settings.value("wing_area_exp", 0).toInt());
    ui_->comboBoxWingSpan         ->setCurrentIndex(settings.value("wing_span"    , 0).toInt());
    ui_->comboBoxWingSweep        ->setCurrentIndex(settings.value("wing_sweep"   , 0).toInt());
    ui_->comboBoxWingCRoot        ->setCurrentIndex(settings.value("wing_c_root"  , 0).toInt());
    ui_->comboBoxWingCTip         ->setCurrentIndex(settings.value("wing_c_tip"   , 0).toInt());
    ui_->comboBoxWingFuel         ->setCurrentIndex(settings.value("wing_fuel"    , 0).toInt());
    ui_->comboBoxCtrlArea         ->setCurrentIndex(settings.value("wing_ctr_area", 0).toInt());

    // horizontal tail
    ui_->comboBoxHorTailArea      ->setCurrentIndex(settings.value("htail_area"   , 0).toInt());
    ui_->comboBoxHorTailSpan      ->setCurrentIndex(settings.value("htail_span"   , 0).toInt());
    ui_->comboBoxHorTailSweep     ->setCurrentIndex(settings.value("htail_sweep"  , 0).toInt());
    ui_->comboBoxHorTailCRoot     ->setCurrentIndex(settings.value("htail_c_root" , 0).toInt());
    ui_->comboBoxHorTailCTip      ->setCurrentIndex(settings.value("htail_c_tip"  , 0).toInt());
    ui_->comboBoxHorTailArm       ->setCurrentIndex(settings.value("htail_arm"    , 0).toInt());
    ui_->comboBoxElevArea         ->setCurrentIndex(settings.value("elev_area"    , 0).toInt());
    ui_->comboBoxHorTailWF        ->setCurrentIndex(settings.value("htail_wf"     , 0).toInt());

    // vertical tail
    ui_->comboBoxVerTailArea      ->setCurrentIndex(settings.value("vtail_area"   , 0).toInt());
    ui_->comboBoxVerTailHeight    ->setCurrentIndex(settings.value("vtail_height" , 0).toInt());
    ui_->comboBoxVerTailSweep     ->setCurrentIndex(settings.value("vtail_sweep"  , 0).toInt());
    ui_->comboBoxVerTailCRoot     ->setCurrentIndex(settings.value("vtail_c_root" , 0).toInt());
    ui_->comboBoxVerTailCTip      ->setCurrentIndex(settings.value("vtail_c_tip"  , 0).toInt());
    ui_->comboBoxVerTailArm       ->setCurrentIndex(settings.value("vtail_arm"    , 0).toInt());
    ui_->comboBoxRuddArea         ->setCurrentIndex(settings.value("rudd_area"    , 0).toInt());

    // landing gear
    ui_->comboBoxMainGearLength   ->setCurrentIndex(settings.value("lg_main_l"    , 0).toInt());
    ui_->comboBoxNoseGearLength   ->setCurrentIndex(settings.value("lg_nose_l"    , 0).toInt());

    // engine
    ui_->comboBoxEngineMass       ->setCurrentIndex(settings.value("engine_mass"  , 0).toInt());

    // rotors
    ui_->comboBoxMainRotorDiameter->setCurrentIndex(settings.value("main_rotor_d" , 0).toInt());
    ui_->comboBoxMainRotorChord   ->setCurrentIndex(settings.value("main_rotor_c" , 0).toInt());
    ui_->comboBoxTailRotorDiameter->setCurrentIndex(settings.value("tail_rotor_d" , 0).toInt());
    ui_->comboBoxPowerLimit       ->setCurrentIndex(settings.value("rotor_mcp"    , 0).toInt());
    ui_->comboBoxMainRotorTipVel  ->setCurrentIndex(settings.value("main_rotor_tv", 0).toInt());

    // 3D model
    ui_->comboBox_OffsetX->setCurrentIndex(settings.value("model_offset_x", 0).toInt());
    ui_->comboBox_OffsetY->setCurrentIndex(settings.value("model_offset_y", 0).toInt());
    ui_->comboBox_OffsetZ->setCurrentIndex(settings.value("model_offset_z", 0).toInt());


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
    settings.setValue("main_rotor_tv", ui_->comboBoxMassEmpty        ->currentIndex());
    settings.setValue("rotor_mcp"    , ui_->comboBoxMTOW             ->currentIndex());
    settings.setValue("tail_rotor_d" , ui_->comboBoxMassMaxLand      ->currentIndex());
    settings.setValue("main_rotor_c" , ui_->comboBoxStallV           ->currentIndex());
    settings.setValue("main_rotor_d" , ui_->comboBoxCruiseV          ->currentIndex());
    settings.setValue("engine_mass"  , ui_->comboBoxCruiseH          ->currentIndex());

    // fuselage
    settings.setValue("lg_nose_l"    , ui_->comboBoxFuseLength       ->currentIndex());
    settings.setValue("lg_main_l"    , ui_->comboBoxFuseWidth        ->currentIndex());
    settings.setValue("rudd_area"    , ui_->comboBoxFuseHeight       ->currentIndex());
    settings.setValue("vtail_arm"    , ui_->comboBoxNoseLength       ->currentIndex());
    settings.setValue("vtail_c_tip"  , ui_->comboBoxPressVol         ->currentIndex());
    settings.setValue("vtail_c_root" , ui_->comboBoxWetAreaEst       ->currentIndex());
    settings.setValue("vtail_sweep"  , ui_->comboBoxWetAreaReal      ->currentIndex());

    // wing
    settings.setValue("vtail_height" , ui_->comboBoxWingArea         ->currentIndex());
    settings.setValue("vtail_area"   , ui_->comboBoxWingAreaExp      ->currentIndex());
    settings.setValue("htail_wf"     , ui_->comboBoxWingSpan         ->currentIndex());
    settings.setValue("elev_area"    , ui_->comboBoxWingSweep        ->currentIndex());
    settings.setValue("htail_arm"    , ui_->comboBoxWingCRoot        ->currentIndex());
    settings.setValue("htail_c_tip"  , ui_->comboBoxWingCTip         ->currentIndex());
    settings.setValue("htail_c_root" , ui_->comboBoxWingFuel         ->currentIndex());
    settings.setValue("htail_sweep"  , ui_->comboBoxCtrlArea         ->currentIndex());

    // horizontal tail
    settings.setValue("htail_span"   , ui_->comboBoxHorTailArea      ->currentIndex());
    settings.setValue("htail_area"   , ui_->comboBoxHorTailSpan      ->currentIndex());
    settings.setValue("wing_ctr_area", ui_->comboBoxHorTailSweep     ->currentIndex());
    settings.setValue("wing_fuel"    , ui_->comboBoxHorTailCRoot     ->currentIndex());
    settings.setValue("wing_c_tip"   , ui_->comboBoxHorTailCTip      ->currentIndex());
    settings.setValue("wing_c_root"  , ui_->comboBoxHorTailArm       ->currentIndex());
    settings.setValue("wing_sweep"   , ui_->comboBoxElevArea         ->currentIndex());
    settings.setValue("wing_span"    , ui_->comboBoxHorTailWF        ->currentIndex());

    // vertical tail
    settings.setValue("wing_area_exp", ui_->comboBoxVerTailArea      ->currentIndex());
    settings.setValue("wing_area"    , ui_->comboBoxVerTailHeight    ->currentIndex());
    settings.setValue("wet_area_real", ui_->comboBoxVerTailSweep     ->currentIndex());
    settings.setValue("wet_area_est" , ui_->comboBoxVerTailCRoot     ->currentIndex());
    settings.setValue("press_vol"    , ui_->comboBoxVerTailCTip      ->currentIndex());
    settings.setValue("nose_length"  , ui_->comboBoxVerTailArm       ->currentIndex());
    settings.setValue("fuselage_h"   , ui_->comboBoxRuddArea         ->currentIndex());

    // landing gear
    settings.setValue("fuselage_w"   , ui_->comboBoxMainGearLength   ->currentIndex());
    settings.setValue("fuselage_l"   , ui_->comboBoxNoseGearLength   ->currentIndex());

    // engine
    settings.setValue("cruise_alt"   , ui_->comboBoxEngineMass       ->currentIndex());

    // rotors
    settings.setValue("cruise_speed" , ui_->comboBoxMainRotorDiameter->currentIndex());
    settings.setValue("stall_speed"  , ui_->comboBoxMainRotorChord   ->currentIndex());
    settings.setValue("mass_landing" , ui_->comboBoxTailRotorDiameter->currentIndex());
    settings.setValue("mtow"         , ui_->comboBoxPowerLimit       ->currentIndex());
    settings.setValue("mass_empty"   , ui_->comboBoxMainRotorTipVel  ->currentIndex());

    // 3D model
    settings.setValue("model_offset_x", ui_->comboBox_OffsetX->currentIndex());
    settings.setValue("model_offset_y", ui_->comboBox_OffsetY->currentIndex());
    settings.setValue("model_offset_z", ui_->comboBox_OffsetZ->currentIndex());

    settings.endGroup();
}

void DockWidgetParams::setAircraftType(AircraftData::Type type)
{
    // data - general
    ui_->labelMassEmpty   ->setEnabled(false);
    ui_->labelMTOW        ->setEnabled(false);
    ui_->labelMassMaxLand ->setEnabled(false);
    ui_->labelMaxNz       ->setEnabled(false);
    ui_->labelMaxNzLand   ->setEnabled(false);
    ui_->labelStallV      ->setEnabled(false);
    ui_->labelCruiseH     ->setEnabled(false);
    ui_->labelCruiseV     ->setEnabled(false);
    ui_->labelMachMax     ->setEnabled(false);

    ui_->labelMaxNzUnit->setEnabled(false);
    ui_->labelMaxNzLandUnit->setEnabled(false);

    ui_->spinBoxMassEmpty   ->setEnabled(false);
    ui_->spinBoxMTOW        ->setEnabled(false);
    ui_->spinBoxMassMaxLand ->setEnabled(false);
    ui_->spinBoxMaxNz       ->setEnabled(false);
    ui_->spinBoxMaxNzLand   ->setEnabled(false);
    ui_->spinBoxStallV      ->setEnabled(false);
    ui_->spinBoxCruiseH     ->setEnabled(false);
    ui_->spinBoxCruiseV     ->setEnabled(false);
    ui_->spinBoxMachMax     ->setEnabled(false);

    ui_->comboBoxMassEmpty   ->setEnabled(false);
    ui_->comboBoxMTOW        ->setEnabled(false);
    ui_->comboBoxMassMaxLand ->setEnabled(false);
    ui_->comboBoxStallV      ->setEnabled(false);
    ui_->comboBoxCruiseH     ->setEnabled(false);
    ui_->comboBoxCruiseV     ->setEnabled(false);

    ui_->checkBoxNavyAircraft->setEnabled(false);

    // data - fuselage
    ui_->comboBoxCargoDoor->setEnabled(false);

    ui_->labelFuseLength ->setEnabled(false);
    ui_->labelFuseHeight ->setEnabled(false);
    ui_->labelFuseWidth  ->setEnabled(false);
    ui_->labelNoseLength ->setEnabled(false);

    ui_->spinBoxFuseLength ->setEnabled(false);
    ui_->spinBoxFuseHeight ->setEnabled(false);
    ui_->spinBoxFuseWidth  ->setEnabled(false);
    ui_->spinBoxNoseLength ->setEnabled(false);

    ui_->comboBoxFuseLength ->setEnabled(false);
    ui_->comboBoxFuseHeight ->setEnabled(false);
    ui_->comboBoxFuseWidth  ->setEnabled(false);
    ui_->comboBoxNoseLength ->setEnabled(false);

    ui_->spinBoxWetAreaEst  ->setEnabled(false);
    ui_->spinBoxWetAreaReal ->setEnabled(false);
    ui_->spinBoxPressVol    ->setEnabled(false);

    ui_->comboBoxWetAreaEst  ->setEnabled(false);
    ui_->comboBoxWetAreaReal ->setEnabled(false);
    ui_->comboBoxPressVol    ->setEnabled(false);

    ui_->labelCargoDoor->setEnabled(false);

    ui_->labelWetAreaEst->setEnabled(false);
    ui_->labelWettedAreaReal->setEnabled(false);
    ui_->labelPressVol->setEnabled(false);

    ui_->checkBoxFuselageLG->setEnabled(false);
    ui_->checkBoxCargoRamp->setEnabled(false);
    ui_->checkBoxWettedAreaOverride->setEnabled(false);

    // data - wing
    ui_->labelWingArea    ->setEnabled(false);
    ui_->labelWingAreaExp ->setEnabled(false);
    ui_->labelWingSpan    ->setEnabled(false);
    ui_->labelWingSweep   ->setEnabled(false);
    ui_->labelWingCRoot   ->setEnabled(false);
    ui_->labelWingCTip    ->setEnabled(false);
    ui_->labelWingTC      ->setEnabled(false);
    ui_->labelWingFuel    ->setEnabled(false);
    ui_->labelCtrlArea    ->setEnabled(false);
    ui_->labelWingAR      ->setEnabled(false);
    ui_->labelWingTR      ->setEnabled(false);

    ui_->spinBoxWingArea    ->setEnabled(false);
    ui_->spinBoxWingAreaExp ->setEnabled(false);
    ui_->spinBoxWingSpan    ->setEnabled(false);
    ui_->spinBoxWingSweep   ->setEnabled(false);
    ui_->spinBoxWingCRoot   ->setEnabled(false);
    ui_->spinBoxWingCTip    ->setEnabled(false);
    ui_->spinBoxWingTC      ->setEnabled(false);
    ui_->spinBoxWingFuel    ->setEnabled(false);
    ui_->spinBoxCtrlArea    ->setEnabled(false);
    ui_->spinBoxWingAR      ->setEnabled(false);
    ui_->spinBoxWingTR      ->setEnabled(false);

    ui_->comboBoxWingArea    ->setEnabled(false);
    ui_->comboBoxWingAreaExp ->setEnabled(false);
    ui_->comboBoxWingSpan    ->setEnabled(false);
    ui_->comboBoxWingSweep   ->setEnabled(false);
    ui_->comboBoxWingCRoot   ->setEnabled(false);
    ui_->comboBoxWingCTip    ->setEnabled(false);
    ui_->comboBoxWingFuel    ->setEnabled(false);
    ui_->comboBoxCtrlArea    ->setEnabled(false);

    ui_->labelWingTCUnit->setEnabled(false);

    ui_->labelWingARUnit->setEnabled(false);
    ui_->labelWingTRUnit->setEnabled(false);

    ui_->checkBoxWingDelta    ->setEnabled(false);
    ui_->checkBoxWingVarSweep ->setEnabled(false);

    // data - horizontal tail
    ui_->labelHorTailArea  ->setEnabled(false);
    ui_->labelHorTailSpan  ->setEnabled(false);
    ui_->labelHorTailSweep ->setEnabled(false);
    ui_->labelHorTailCRoot ->setEnabled(false);
    ui_->labelHorTailCTip  ->setEnabled(false);
    ui_->labelHorTailTC    ->setEnabled(false);
    ui_->labelElevArea     ->setEnabled(false);
    ui_->labelHorTailWF    ->setEnabled(false);
    ui_->labelHorTailArm   ->setEnabled(false);
    ui_->labelHorTailAR    ->setEnabled(false);
    ui_->labelHorTailTR    ->setEnabled(false);

    ui_->spinBoxHorTailArea  ->setEnabled(false);
    ui_->spinBoxHorTailSpan  ->setEnabled(false);
    ui_->spinBoxHorTailSweep ->setEnabled(false);
    ui_->spinBoxHorTailCRoot ->setEnabled(false);
    ui_->spinBoxHorTailCTip  ->setEnabled(false);
    ui_->spinBoxHorTailTC    ->setEnabled(false);
    ui_->spinBoxElevArea     ->setEnabled(false);
    ui_->spinBoxHorTailWF    ->setEnabled(false);
    ui_->spinBoxHorTailArm   ->setEnabled(false);
    ui_->spinBoxHorTailAR    ->setEnabled(false);
    ui_->spinBoxHorTailTR    ->setEnabled(false);

    ui_->comboBoxHorTailArea  ->setEnabled(false);
    ui_->comboBoxHorTailSpan  ->setEnabled(false);
    ui_->comboBoxHorTailSweep ->setEnabled(false);
    ui_->comboBoxHorTailCRoot ->setEnabled(false);
    ui_->comboBoxHorTailCTip  ->setEnabled(false);
    ui_->comboBoxElevArea     ->setEnabled(false);
    ui_->comboBoxHorTailWF    ->setEnabled(false);
    ui_->comboBoxHorTailArm   ->setEnabled(false);

    ui_->checkBoxHorTailMoving  ->setEnabled(false);
    ui_->checkBoxHorTailRolling ->setEnabled(false);

    // data - vertical tail
    ui_->labelVerTailArea   ->setEnabled(false);
    ui_->labelVerTailHeight ->setEnabled(false);
    ui_->labelVerTailSweep  ->setEnabled(false);
    ui_->labelVerTailCRoot  ->setEnabled(false);
    ui_->labelVerTailCTip   ->setEnabled(false);
    ui_->labelVerTailTC     ->setEnabled(false);
    ui_->labelVerTailArm    ->setEnabled(false);
    ui_->labelRuddArea      ->setEnabled(false);
    ui_->labelVerTailAR     ->setEnabled(false);
    ui_->labelVerTailTR     ->setEnabled(false);

    ui_->spinBoxVerTailArea   ->setEnabled(false);
    ui_->spinBoxVerTailHeight ->setEnabled(false);
    ui_->spinBoxVerTailSweep  ->setEnabled(false);
    ui_->spinBoxVerTailCRoot  ->setEnabled(false);
    ui_->spinBoxVerTailCTip   ->setEnabled(false);
    ui_->spinBoxVerTailTC     ->setEnabled(false);
    ui_->spinBoxVerTailArm    ->setEnabled(false);
    ui_->spinBoxRuddArea      ->setEnabled(false);
    ui_->spinBoxVerTailAR     ->setEnabled(false);
    ui_->spinBoxVerTailTR     ->setEnabled(false);

    ui_->comboBoxVerTailArea   ->setEnabled(false);
    ui_->comboBoxVerTailHeight ->setEnabled(false);
    ui_->comboBoxVerTailSweep  ->setEnabled(false);
    ui_->comboBoxVerTailCRoot  ->setEnabled(false);
    ui_->comboBoxVerTailCTip   ->setEnabled(false);
    ui_->comboBoxVerTailArm    ->setEnabled(false);
    ui_->comboBoxRuddArea      ->setEnabled(false);

    ui_->checkBoxTailT        ->setEnabled(false);
    ui_->checkBoxVerTailRotor ->setEnabled(false);

    // data - landing gear
    ui_->labelMainGearLength ->setEnabled(false);
    ui_->labelNoseGearLength ->setEnabled(false);

    ui_->labelMainGearWheels ->setEnabled(false);
    ui_->labelMainGearStruts ->setEnabled(false);
    ui_->labelNoseGearWheels ->setEnabled(false);

    ui_->spinBoxMainGearLength ->setEnabled(false);
    ui_->spinBoxNoseGearLength ->setEnabled(false);

    ui_->comboBoxMainGearLength ->setEnabled(false);
    ui_->comboBoxNoseGearLength ->setEnabled(false);

    ui_->spinBoxMainGearWheels ->setEnabled(false);
    ui_->spinBoxMainGearStruts ->setEnabled(false);
    ui_->spinBoxNoseGearWheels ->setEnabled(false);

    ui_->checkBoxGearFixed  ->setEnabled(false);
    ui_->checkBoxGearCross  ->setEnabled(false);
    ui_->checkBoxGearTripod ->setEnabled(false);

    ui_->checkBoxGearMainKneel ->setEnabled(false);
    ui_->checkBoxGearNoseKneel ->setEnabled(false);

    // data - rotors
    ui_->labelMainRotorDiameter  ->setEnabled(false);
    ui_->labelMainRotorChord     ->setEnabled(false);
    ui_->labelMainRotorRPM       ->setEnabled(false);
    ui_->labelTailRotorDiameter  ->setEnabled(false);
    ui_->labelMainRotorGear      ->setEnabled(false);
    ui_->labelPowerLimit         ->setEnabled(false);
    ui_->labelMainRotorTipVel    ->setEnabled(false);
    ui_->labelMainRotorBlades    ->setEnabled(false);

    ui_->spinBoxMainRotorDiameter  ->setEnabled(false);
    ui_->spinBoxMainRotorChord     ->setEnabled(false);
    ui_->spinBoxMainRotorRPM       ->setEnabled(false);
    ui_->spinBoxTailRotorDiameter  ->setEnabled(false);
    ui_->spinBoxMainRotorGear      ->setEnabled(false);
    ui_->spinBoxPowerLimit         ->setEnabled(false);
    ui_->spinBoxMainRotorTipVel    ->setEnabled(false);
    ui_->spinBoxMainRotorBlades    ->setEnabled(false);

    ui_->comboBoxMainRotorDiameter  ->setEnabled(false);
    ui_->comboBoxMainRotorChord     ->setEnabled(false);
    ui_->comboBoxTailRotorDiameter  ->setEnabled(false);
    ui_->comboBoxPowerLimit         ->setEnabled(false);
    ui_->comboBoxMainRotorTipVel    ->setEnabled(false);

    if ( type == AircraftData::Helicopter )
    {
        // data - general
        ui_->labelMassEmpty   ->setEnabled(true);
        ui_->labelMTOW        ->setEnabled(true);
        ui_->labelMaxNz       ->setEnabled(true);
        ui_->labelMaxNzLand   ->setEnabled(true);

        ui_->spinBoxMassEmpty   ->setEnabled(true);
        ui_->spinBoxMTOW        ->setEnabled(true);
        ui_->spinBoxMaxNz       ->setEnabled(true);
        ui_->spinBoxMaxNzLand   ->setEnabled(true);

        ui_->comboBoxMassEmpty   ->setEnabled(true);
        ui_->comboBoxMTOW        ->setEnabled(true);

        ui_->labelMaxNzUnit->setEnabled(true);
        ui_->labelMaxNzLandUnit->setEnabled(true);

        // data - fuselage
        ui_->labelFuseLength ->setEnabled(true);
        ui_->labelFuseHeight ->setEnabled(true);
        ui_->labelFuseWidth  ->setEnabled(true);
        ui_->labelNoseLength ->setEnabled(true);

        ui_->spinBoxFuseLength ->setEnabled(true);
        ui_->spinBoxFuseHeight ->setEnabled(true);
        ui_->spinBoxFuseWidth  ->setEnabled(true);
        ui_->spinBoxNoseLength ->setEnabled(true);

        ui_->comboBoxFuseLength ->setEnabled(true);
        ui_->comboBoxFuseHeight ->setEnabled(true);
        ui_->comboBoxFuseWidth  ->setEnabled(true);
        ui_->comboBoxNoseLength ->setEnabled(true);

        ui_->labelWetAreaEst->setEnabled(true);
        ui_->spinBoxWetAreaEst->setEnabled(true);
        ui_->comboBoxWetAreaEst->setEnabled(true);

        ui_->checkBoxCargoRamp->setEnabled(true);
        ui_->checkBoxWettedAreaOverride->setEnabled(true);

        // data - horizontal tail
        ui_->labelHorTailArea ->setEnabled(true);
        ui_->labelHorTailSpan ->setEnabled(true);
        ui_->labelHorTailAR   ->setEnabled(true);

        ui_->spinBoxHorTailArea ->setEnabled(true);
        ui_->spinBoxHorTailSpan ->setEnabled(true);
        ui_->spinBoxHorTailAR   ->setEnabled(true);

        ui_->comboBoxHorTailArea ->setEnabled(true);
        ui_->comboBoxHorTailSpan ->setEnabled(true);

        // data - vertical tail
        ui_->labelVerTailArea   ->setEnabled(true);
        ui_->labelVerTailHeight ->setEnabled(true);
        ui_->labelVerTailAR     ->setEnabled(true);

        ui_->spinBoxVerTailArea   ->setEnabled(true);
        ui_->spinBoxVerTailHeight ->setEnabled(true);
        ui_->spinBoxVerTailAR     ->setEnabled(true);

        ui_->comboBoxVerTailArea   ->setEnabled(true);
        ui_->comboBoxVerTailHeight ->setEnabled(true);

        ui_->checkBoxVerTailRotor ->setEnabled(true);

        // data - rotors
        ui_->labelMainRotorDiameter  ->setEnabled(true);
        ui_->labelMainRotorChord     ->setEnabled(true);
        ui_->labelMainRotorRPM       ->setEnabled(true);
        ui_->labelTailRotorDiameter  ->setEnabled(true);
        ui_->labelMainRotorGear      ->setEnabled(true);
        ui_->labelPowerLimit         ->setEnabled(true);
        ui_->labelMainRotorTipVel    ->setEnabled(true);
        ui_->labelMainRotorBlades    ->setEnabled(true);

        ui_->spinBoxMainRotorDiameter  ->setEnabled(true);
        ui_->spinBoxMainRotorChord     ->setEnabled(true);
        ui_->spinBoxMainRotorRPM       ->setEnabled(true);
        ui_->spinBoxTailRotorDiameter  ->setEnabled(true);
        ui_->spinBoxMainRotorGear      ->setEnabled(true);
        ui_->spinBoxPowerLimit         ->setEnabled(true);
        ui_->spinBoxMainRotorTipVel    ->setEnabled(true);
        ui_->spinBoxMainRotorBlades    ->setEnabled(true);

        ui_->comboBoxMainRotorDiameter  ->setEnabled(true);
        ui_->comboBoxMainRotorChord     ->setEnabled(true);
        ui_->comboBoxTailRotorDiameter  ->setEnabled(true);
        ui_->comboBoxPowerLimit         ->setEnabled(true);
        ui_->comboBoxMainRotorTipVel    ->setEnabled(true);
    }
    else
    {
        // data - general
        ui_->labelMassEmpty   ->setEnabled(true);
        ui_->labelMTOW        ->setEnabled(true);
        ui_->labelMassMaxLand ->setEnabled(true);
        ui_->labelMaxNz       ->setEnabled(true);
        ui_->labelMaxNzLand   ->setEnabled(true);

        ui_->spinBoxMassEmpty   ->setEnabled(true);
        ui_->spinBoxMTOW        ->setEnabled(true);
        ui_->spinBoxMassMaxLand ->setEnabled(true);
        ui_->spinBoxMaxNz       ->setEnabled(true);
        ui_->spinBoxMaxNzLand   ->setEnabled(true);

        ui_->labelMaxNzUnit->setEnabled(true);
        ui_->labelMaxNzLandUnit->setEnabled(true);

        ui_->comboBoxMassEmpty   ->setEnabled(true);
        ui_->comboBoxMTOW        ->setEnabled(true);
        ui_->comboBoxMassMaxLand ->setEnabled(true);

        // data - fuselage
        ui_->labelFuseLength ->setEnabled(true);
        ui_->labelFuseHeight ->setEnabled(true);
        ui_->labelFuseWidth  ->setEnabled(true);
        ui_->labelNoseLength ->setEnabled(true);

        ui_->spinBoxFuseLength ->setEnabled(true);
        ui_->spinBoxFuseHeight ->setEnabled(true);
        ui_->spinBoxFuseWidth  ->setEnabled(true);
        ui_->spinBoxNoseLength ->setEnabled(true);

        ui_->comboBoxFuseLength ->setEnabled(true);
        ui_->comboBoxFuseHeight ->setEnabled(true);
        ui_->comboBoxFuseWidth  ->setEnabled(true);
        ui_->comboBoxNoseLength ->setEnabled(true);

        ui_->labelWetAreaEst->setEnabled(true);
        ui_->spinBoxWetAreaEst->setEnabled(true);
        ui_->comboBoxWetAreaEst->setEnabled(true);
        ui_->checkBoxWettedAreaOverride->setEnabled(true);

        // data - wing
        ui_->labelWingArea    ->setEnabled(true);
        ui_->labelWingAreaExp ->setEnabled(true);
        ui_->labelWingSpan    ->setEnabled(true);
        ui_->labelWingSweep   ->setEnabled(true);
        ui_->labelWingCRoot   ->setEnabled(true);
        ui_->labelWingCTip    ->setEnabled(true);
        ui_->labelWingTC      ->setEnabled(true);
        ui_->labelWingAR      ->setEnabled(true);
        ui_->labelWingTR      ->setEnabled(true);

        ui_->spinBoxWingArea    ->setEnabled(true);
        ui_->spinBoxWingAreaExp ->setEnabled(true);
        ui_->spinBoxWingSpan    ->setEnabled(true);
        ui_->spinBoxWingSweep   ->setEnabled(true);
        ui_->spinBoxWingCRoot   ->setEnabled(true);
        ui_->spinBoxWingCTip    ->setEnabled(true);
        ui_->spinBoxWingTC      ->setEnabled(true);
        ui_->spinBoxWingAR      ->setEnabled(true);
        ui_->spinBoxWingTR      ->setEnabled(true);

        ui_->labelWingTCUnit->setEnabled(true);

        ui_->comboBoxWingArea    ->setEnabled(true);
        ui_->comboBoxWingAreaExp ->setEnabled(true);
        ui_->comboBoxWingSpan    ->setEnabled(true);
        ui_->comboBoxWingSweep   ->setEnabled(true);
        ui_->comboBoxWingCRoot   ->setEnabled(true);
        ui_->comboBoxWingCTip    ->setEnabled(true);

        ui_->labelWingARUnit->setEnabled(true);
        ui_->labelWingTRUnit->setEnabled(true);

        // data - horizontal tail
        ui_->labelHorTailArea ->setEnabled(true);
        ui_->labelHorTailAR   ->setEnabled(true);
        ui_->labelHorTailTR   ->setEnabled(true);

        ui_->spinBoxHorTailArea ->setEnabled(true);
        ui_->spinBoxHorTailAR   ->setEnabled(true);
        ui_->spinBoxHorTailTR   ->setEnabled(true);

        ui_->comboBoxHorTailArea ->setEnabled(true);

        // data - vertical tail
        ui_->labelVerTailArea   ->setEnabled(true);
        ui_->labelVerTailHeight ->setEnabled(true);
        ui_->labelVerTailSweep  ->setEnabled(true);
        ui_->labelVerTailAR     ->setEnabled(true);
        ui_->labelVerTailTR     ->setEnabled(true);

        ui_->spinBoxVerTailArea   ->setEnabled(true);
        ui_->spinBoxVerTailHeight ->setEnabled(true);
        ui_->spinBoxVerTailSweep  ->setEnabled(true);
        ui_->spinBoxVerTailAR     ->setEnabled(true);
        ui_->spinBoxVerTailTR     ->setEnabled(true);

        ui_->comboBoxVerTailArea   ->setEnabled(true);
        ui_->comboBoxVerTailHeight ->setEnabled(true);
        ui_->comboBoxVerTailSweep  ->setEnabled(true);

        ui_->checkBoxTailT->setEnabled(true);

        // data - landing gear
        ui_->labelMainGearLength ->setEnabled(true);
        ui_->labelNoseGearLength ->setEnabled(true);

        ui_->spinBoxMainGearLength ->setEnabled(true);
        ui_->spinBoxNoseGearLength ->setEnabled(true);

        ui_->comboBoxMainGearLength ->setEnabled(true);
        ui_->comboBoxNoseGearLength ->setEnabled(true);

        ui_->checkBoxGearFixed  ->setEnabled(true);

        if ( type == AircraftData::FighterAttack )
        {
            // data - general
            ui_->labelMachMax->setEnabled(true);
            ui_->spinBoxMachMax->setEnabled(true);

            ui_->checkBoxNavyAircraft->setEnabled(true);

            // data - wing
            ui_->labelCtrlArea  ->setEnabled(true);
            ui_->spinBoxCtrlArea  ->setEnabled(true);
            ui_->comboBoxCtrlArea  ->setEnabled(true);

            ui_->checkBoxWingDelta    ->setEnabled(true);
            ui_->checkBoxWingVarSweep ->setEnabled(true);

            // data - horizontal tail
            ui_->labelHorTailSpan  ->setEnabled(true);
            ui_->labelHorTailWF    ->setEnabled(true);

            ui_->spinBoxHorTailSpan  ->setEnabled(true);
            ui_->spinBoxHorTailWF    ->setEnabled(true);

            ui_->comboBoxHorTailSpan  ->setEnabled(true);
            ui_->comboBoxHorTailWF    ->setEnabled(true);

            ui_->checkBoxHorTailRolling ->setEnabled(true);

            // data - vertical tail
            ui_->labelVerTailArm    ->setEnabled(true);
            ui_->labelVerTailCRoot  ->setEnabled(true);
            ui_->labelVerTailCTip   ->setEnabled(true);
            ui_->labelRuddArea      ->setEnabled(true);

            ui_->spinBoxVerTailArm    ->setEnabled(true);
            ui_->spinBoxVerTailCRoot  ->setEnabled(true);
            ui_->spinBoxVerTailCTip   ->setEnabled(true);
            ui_->spinBoxRuddArea      ->setEnabled(true);

            ui_->comboBoxVerTailArm    ->setEnabled(true);
            ui_->comboBoxVerTailCRoot  ->setEnabled(true);
            ui_->comboBoxVerTailCTip   ->setEnabled(true);
            ui_->comboBoxRuddArea      ->setEnabled(true);

            // data - landing gear
            ui_->labelNoseGearWheels ->setEnabled(true);
            ui_->spinBoxNoseGearWheels ->setEnabled(true);

            ui_->checkBoxGearCross  ->setEnabled(true);
            ui_->checkBoxGearTripod ->setEnabled(true);
        }
        else if ( type == AircraftData::CargoTransport )
        {
            // data - general
            ui_->labelStallV->setEnabled(true);
            ui_->spinBoxStallV->setEnabled(true);
            ui_->comboBoxStallV->setEnabled(true);

            // data - fuselage
            ui_->labelCargoDoor->setEnabled(true);
            ui_->comboBoxCargoDoor->setEnabled(true);

            ui_->checkBoxFuselageLG->setEnabled(true);

            // data - wing
            ui_->labelCtrlArea  ->setEnabled(true);
            ui_->spinBoxCtrlArea  ->setEnabled(true);
            ui_->comboBoxCtrlArea  ->setEnabled(true);

            // data - horizontal tail
            ui_->labelHorTailSpan  ->setEnabled(true);
            ui_->labelHorTailSweep ->setEnabled(true);
            ui_->labelHorTailArm   ->setEnabled(true);
            ui_->labelElevArea     ->setEnabled(true);
            ui_->labelHorTailWF    ->setEnabled(true);

            ui_->spinBoxHorTailSpan  ->setEnabled(true);
            ui_->spinBoxHorTailSweep ->setEnabled(true);
            ui_->spinBoxHorTailArm   ->setEnabled(true);
            ui_->spinBoxElevArea     ->setEnabled(true);
            ui_->spinBoxHorTailWF    ->setEnabled(true);

            ui_->comboBoxHorTailSpan  ->setEnabled(true);
            ui_->comboBoxHorTailSweep ->setEnabled(true);
            ui_->comboBoxHorTailArm   ->setEnabled(true);
            ui_->comboBoxElevArea     ->setEnabled(true);
            ui_->comboBoxHorTailWF    ->setEnabled(true);

            ui_->checkBoxHorTailMoving  ->setEnabled(true);

            // data - vertical tail
            ui_->labelVerTailArm    ->setEnabled(true);
            ui_->labelVerTailTC     ->setEnabled(true);

            ui_->spinBoxVerTailArm    ->setEnabled(true);
            ui_->spinBoxVerTailTC     ->setEnabled(true);

            ui_->comboBoxVerTailArm    ->setEnabled(true);

            // data - landing gear
            ui_->labelMainGearWheels ->setEnabled(true);
            ui_->labelMainGearStruts ->setEnabled(true);
            ui_->labelNoseGearWheels ->setEnabled(true);

            ui_->spinBoxMainGearWheels ->setEnabled(true);
            ui_->spinBoxMainGearStruts ->setEnabled(true);
            ui_->spinBoxNoseGearWheels ->setEnabled(true);

            ui_->checkBoxGearMainKneel ->setEnabled(true);
            ui_->checkBoxGearNoseKneel ->setEnabled(true);
        }
        else if ( type == AircraftData::GeneralAviation )
        {
            // data - general
            ui_->labelCruiseH->setEnabled(true);
            ui_->labelCruiseV->setEnabled(true);

            ui_->spinBoxCruiseH->setEnabled(true);
            ui_->spinBoxCruiseV->setEnabled(true);

            ui_->comboBoxCruiseH->setEnabled(true);
            ui_->comboBoxCruiseV->setEnabled(true);

            // data - fuselage
            ui_->labelPressVol->setEnabled(true);
            ui_->spinBoxPressVol->setEnabled(true);
            ui_->comboBoxPressVol->setEnabled(true);

            // data - wing
            ui_->spinBoxWingFuel->setEnabled(true);
            ui_->comboBoxWingFuel->setEnabled(true);
            ui_->labelWingFuel->setEnabled(true);

            // data - horizontal tail
            ui_->labelHorTailSweep ->setEnabled(true);
            ui_->labelHorTailArm   ->setEnabled(true);
            ui_->labelHorTailCRoot ->setEnabled(true);
            ui_->labelHorTailCTip  ->setEnabled(true);
            ui_->labelHorTailTC    ->setEnabled(true);

            ui_->spinBoxHorTailSweep ->setEnabled(true);
            ui_->spinBoxHorTailArm   ->setEnabled(true);
            ui_->spinBoxHorTailCRoot ->setEnabled(true);
            ui_->spinBoxHorTailCTip  ->setEnabled(true);
            ui_->spinBoxHorTailTC    ->setEnabled(true);

            ui_->comboBoxHorTailSweep ->setEnabled(true);
            ui_->comboBoxHorTailArm   ->setEnabled(true);
            ui_->comboBoxHorTailCRoot ->setEnabled(true);
            ui_->comboBoxHorTailCTip  ->setEnabled(true);

            // data - vertical tail
            ui_->spinBoxVerTailCRoot ->setEnabled(true);
            ui_->spinBoxVerTailCTip  ->setEnabled(true);
            ui_->spinBoxVerTailTC    ->setEnabled(true);

            ui_->comboBoxVerTailCRoot ->setEnabled(true);
            ui_->comboBoxVerTailCTip  ->setEnabled(true);

            ui_->labelVerTailCRoot ->setEnabled(true);
            ui_->labelVerTailCTip  ->setEnabled(true);
            ui_->labelVerTailTC    ->setEnabled(true);

            // data - landing gear
        }
    }
}

void DockWidgetParams::updateWettedArea()
{
    double l_fuse = ui_->comboBoxFuseLength ->invert(ui_->spinBoxFuseLength ->value());
    double w_fuse = ui_->comboBoxFuseWidth  ->invert(ui_->spinBoxFuseWidth  ->value());
    double h_fuse = ui_->comboBoxFuseHeight ->invert(ui_->spinBoxFuseHeight ->value());
    double l_nose = ui_->comboBoxNoseLength ->invert(ui_->spinBoxNoseLength ->value());

    double a_top  = w_fuse * (l_fuse - l_nose) + 0.5 * w_fuse * l_nose;
    double a_side = h_fuse * (l_fuse - l_nose) + 0.5 * h_fuse * l_nose;

    // Raymer: Aircraft Design, p.205, eq. 7.13
    double s_wet = 3.4 * ((a_top + a_side) / 2.0);

    ui_->spinBoxWetAreaEst->setValue(ui_->comboBoxWetAreaEst->convert(s_wet));
}

void DockWidgetParams::updateWingAR()
{
    const AircraftData* data = aircraft_->GetData();
    if ( data->wing.area > 0.0_sq_m )
    {
        double ar = pow(data->wing.span(), 2.0) / data->wing.area();
        ui_->spinBoxWingAR->setValue(ar);
    }
    else
    {
        ui_->spinBoxWingAR->setValue(0.0);
    }
}

void DockWidgetParams::updateWingTR()
{
    const AircraftData* data = aircraft_->GetData();
    if ( data->wing.c_root > 0.0_m )
    {
        double tr = data->wing.c_tip / data->wing.c_root;
        ui_->spinBoxWingTR->setValue(tr);
    }
    else
    {
        ui_->spinBoxWingTR->setValue(0.0);
    }
}

void DockWidgetParams::updateHorTailAR()
{
    const AircraftData* data = aircraft_->GetData();
    if ( data->hor_tail.area > 0.0_sq_m )
    {
        double ar = pow(data->hor_tail.span(), 2.0) / data->hor_tail.area();
        ui_->spinBoxHorTailAR->setValue(ar);
    }
    else
    {
        ui_->spinBoxHorTailAR->setValue(0.0);
    }
}

void DockWidgetParams::updateHorTailTR()
{
    const AircraftData* data = aircraft_->GetData();
    if ( data->hor_tail.c_root > 0.0_m )
    {
        double tr = data->hor_tail.c_tip / data->hor_tail.c_root;
        ui_->spinBoxHorTailTR->setValue(tr);
    }
    else
    {
        ui_->spinBoxHorTailTR->setValue(0.0);
    }
}

void DockWidgetParams::updateVerTailAR()
{
    const AircraftData* data = aircraft_->GetData();
    if ( data->ver_tail.area > 0.0_sq_m )
    {
        double ar = pow(data->ver_tail.height(), 2.0) / data->ver_tail.area();
        ui_->spinBoxVerTailAR->setValue(ar);
    }
    else
    {
        ui_->spinBoxVerTailAR->setValue(0.0);
    }
}

void DockWidgetParams::updateVerTailTR()
{
    const AircraftData* data = aircraft_->GetData();
    if ( data->ver_tail.c_root > 0.0_m )
    {
        double tr = data->ver_tail.c_tip / data->ver_tail.c_root;
        ui_->spinBoxVerTailTR->setValue(tr);
    }
    else
    {
        ui_->spinBoxVerTailTR->setValue(0.0);
    }
}

void DockWidgetParams::updateRotorTipVel()
{
    double omg = 2.0 * M_PI * ui_->spinBoxMainRotorRPM->value() / 60.0;
    double rad = 0.5 * ui_->comboBoxMainRotorDiameter->invert(ui_->spinBoxMainRotorDiameter->value());
    double vel = omg * rad;
    ui_->spinBoxMainRotorTipVel->setValue(ui_->comboBoxMainRotorTipVel->convert(vel));
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
    aircraft_->GetData()->type = type;

    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMassEmpty_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxMassEmpty->invert(arg1);
    aircraft_->GetData()->general.m_empty = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMTOW_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxMTOW->invert(arg1);
    aircraft_->GetData()->general.mtow =  units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMassMaxLand_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxMassMaxLand->invert(arg1);
    aircraft_->GetData()->general.m_maxLand = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMaxNz_valueChanged(double arg1)
{
    aircraft_->GetData()->general.nz_max = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMaxNzLand_valueChanged(double arg1)
{
    aircraft_->GetData()->general.nz_maxLand = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxStallV_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxStallV->invert(arg1);
    aircraft_->GetData()->general.v_stall = units::velocity::knot_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxCruiseV_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxCruiseV->invert(arg1);
    aircraft_->GetData()->general.v_cruise = units::velocity::knot_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxCruiseH_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxCruiseH->invert(arg1);
    aircraft_->GetData()->general.h_cruise = units::length::foot_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMachMax_valueChanged(double arg1)
{
    aircraft_->GetData()->general.mach_max = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxNavyAircraft_toggled(bool checked)
{
    aircraft_->GetData()->general.navy_ac = checked;
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

    aircraft_->GetData()->fuselage.cargo_door = door;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxFuseLength_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxFuseLength->invert(arg1);
    aircraft_->GetData()->fuselage.l = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWettedArea();
}

void DockWidgetParams::on_spinBoxFuseHeight_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxFuseHeight->invert(arg1);
    aircraft_->GetData()->fuselage.h = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWettedArea();
}

void DockWidgetParams::on_spinBoxFuseWidth_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxFuseWidth->invert(arg1);
    aircraft_->GetData()->fuselage.w = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWettedArea();
}

void DockWidgetParams::on_spinBoxNoseLength_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxNoseLength->invert(arg1);
    aircraft_->GetData()->fuselage.l_n = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWettedArea();
}

void DockWidgetParams::on_spinBoxPressVol_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxPressVol->invert(arg1);
    aircraft_->GetData()->fuselage.press_vol = units::volume::cubic_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWetAreaEst_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWetAreaEst->invert(arg1);
    if ( !aircraft_->GetData()->fuselage.wetted_area_override )
    {
        ui_->spinBoxWetAreaReal->setValue(ui_->comboBoxWetAreaReal->convert(arg1_raw));
    }
}

void DockWidgetParams::on_spinBoxWetAreaReal_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWetAreaReal->invert(arg1);
    aircraft_->GetData()->fuselage.wetted_area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxFuselageLG_toggled(bool checked)
{
    aircraft_->GetData()->fuselage.landing_gear = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxCargoRamp_toggled(bool checked)
{
    aircraft_->GetData()->fuselage.cargo_ramp = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxWettedAreaOverride_toggled(bool checked)
{
    aircraft_->GetData()->fuselage.wetted_area_override = checked;
    ui_->labelWettedAreaReal->setEnabled(checked);
    ui_->spinBoxWetAreaReal->setEnabled(checked);
    ui_->comboBoxWetAreaReal->setEnabled(checked);

    if ( !checked )
    {
        double arg1_raw = ui_->comboBoxWetAreaEst->invert(ui_->spinBoxWetAreaEst->value());
        ui_->spinBoxWetAreaReal->setValue(ui_->comboBoxWetAreaReal->convert(arg1_raw));
    }

    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingArea_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWingArea->invert(arg1);
    aircraft_->GetData()->wing.area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWingAR();
}

void DockWidgetParams::on_spinBoxWingAreaExp_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWingAreaExp->invert(arg1);
    aircraft_->GetData()->wing.area_exp = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingSpan_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWingSpan->invert(arg1);
    aircraft_->GetData()->wing.span = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWingAR();
}

void DockWidgetParams::on_spinBoxWingSweep_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWingSweep->invert(arg1);
    aircraft_->GetData()->wing.sweep = units::angle::degree_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingCRoot_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWingCRoot->invert(arg1);
    aircraft_->GetData()->wing.c_root = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWingTR();
}

void DockWidgetParams::on_spinBoxWingCTip_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWingCTip->invert(arg1);
    aircraft_->GetData()->wing.c_tip = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateWingTR();
}

void DockWidgetParams::on_spinBoxWingTC_valueChanged(double arg1)
{
    aircraft_->GetData()->wing.tc = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingFuel_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxWingFuel->invert(arg1);
    aircraft_->GetData()->wing.fuel = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxCtrlArea_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxCtrlArea->invert(arg1);
    aircraft_->GetData()->wing.ctrl_area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingAR_valueChanged(double arg1)
{
    aircraft_->GetData()->wing.ar = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxWingTR_valueChanged(double arg1)
{
    aircraft_->GetData()->wing.tr = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxWingDelta_toggled(bool checked)
{
    aircraft_->GetData()->wing.delta = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxWingVarSweep_toggled(bool checked)
{
    aircraft_->GetData()->wing.var_sweep = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailArea_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxHorTailArea->invert(arg1);
    aircraft_->GetData()->hor_tail.area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
    updateHorTailAR();
}

void DockWidgetParams::on_spinBoxHorTailSpan_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxHorTailSpan->invert(arg1);
    aircraft_->GetData()->hor_tail.span = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateHorTailAR();
}

void DockWidgetParams::on_spinBoxHorTailSweep_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxHorTailSweep->invert(arg1);
    aircraft_->GetData()->hor_tail.sweep = units::angle::degree_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailCRoot_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxHorTailCRoot->invert(arg1);
    aircraft_->GetData()->hor_tail.c_root = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateHorTailTR();
}

void DockWidgetParams::on_spinBoxHorTailCTip_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxHorTailCTip->invert(arg1);
    aircraft_->GetData()->hor_tail.c_tip = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateHorTailTR();
}

void DockWidgetParams::on_spinBoxHorTailTC_valueChanged(double arg1)
{
    aircraft_->GetData()->hor_tail.tc = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxElevArea_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxElevArea->invert(arg1);
    aircraft_->GetData()->hor_tail.elev_area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailWF_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxHorTailWF->invert(arg1);
    aircraft_->GetData()->hor_tail.w_f = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailArm_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxHorTailArm->invert(arg1);
    aircraft_->GetData()->hor_tail.arm = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailAR_valueChanged(double arg1)
{
    aircraft_->GetData()->hor_tail.ar = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxHorTailTR_valueChanged(double arg1)
{
    aircraft_->GetData()->hor_tail.tr = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxHorTailMoving_toggled(bool checked)
{
    aircraft_->GetData()->hor_tail.moving = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxHorTailRolling_toggled(bool checked)
{
    aircraft_->GetData()->hor_tail.rolling = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailArea_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxVerTailArea->invert(arg1);
    aircraft_->GetData()->ver_tail.area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
    updateVerTailAR();
}

void DockWidgetParams::on_spinBoxVerTailHeight_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxVerTailHeight->invert(arg1);
    aircraft_->GetData()->ver_tail.height = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateVerTailAR();
}

void DockWidgetParams::on_spinBoxVerTailSweep_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxVerTailSweep->invert(arg1);
    aircraft_->GetData()->ver_tail.sweep = units::angle::degree_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailCRoot_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxVerTailCRoot->invert(arg1);
    aircraft_->GetData()->ver_tail.c_root = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateVerTailTR();
}

void DockWidgetParams::on_spinBoxVerTailCTip_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxVerTailCTip->invert(arg1);
    aircraft_->GetData()->ver_tail.c_tip = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateVerTailTR();
}

void DockWidgetParams::on_spinBoxVerTailTC_valueChanged(double arg1)
{
    aircraft_->GetData()->ver_tail.tc = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailArm_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxVerTailArm->invert(arg1);
    aircraft_->GetData()->ver_tail.arm = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxRuddArea_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxRuddArea->invert(arg1);
    aircraft_->GetData()->ver_tail.rudd_area = units::area::square_meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailAR_valueChanged(double arg1)
{
    aircraft_->GetData()->ver_tail.ar = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxVerTailTR_valueChanged(double arg1)
{
    aircraft_->GetData()->ver_tail.tr = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxTailT_toggled(bool checked)
{
    aircraft_->GetData()->ver_tail.t_tail = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxVerTailRotor_toggled(bool checked)
{
    aircraft_->GetData()->ver_tail.rotor = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainGearLength_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxMainGearLength->invert(arg1);
    aircraft_->GetData()->landing_gear.main_l = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxNoseGearLength_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxNoseGearLength->invert(arg1);
    aircraft_->GetData()->landing_gear.nose_l = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainGearWheels_valueChanged(int arg1)
{
    aircraft_->GetData()->landing_gear.main_wheels = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainGearStruts_valueChanged(int arg1)
{
    aircraft_->GetData()->landing_gear.main_struts = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxNoseGearWheels_valueChanged(int arg1)
{
    aircraft_->GetData()->landing_gear.nose_wheels = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearFixed_toggled(bool checked)
{
    aircraft_->GetData()->landing_gear.fixed = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearCross_toggled(bool checked)
{
    aircraft_->GetData()->landing_gear.cross = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearTripod_toggled(bool checked)
{
    aircraft_->GetData()->landing_gear.tripod = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearMainKneel_toggled(bool checked)
{
    aircraft_->GetData()->landing_gear.main_kneel = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_checkBoxGearNoseKneel_toggled(bool checked)
{
    aircraft_->GetData()->landing_gear.nose_kneel = checked;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxEngineMass_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxEngineMass->invert(arg1);
    aircraft_->GetData()->engine.mass = units::mass::kilogram_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorDiameter_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxMainRotorDiameter->invert(arg1);
    aircraft_->GetData()->rotors.main_r = 0.5 * units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
    updateRotorTipVel();
}

void DockWidgetParams::on_spinBoxMainRotorChord_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxMainRotorChord->invert(arg1);
    aircraft_->GetData()->rotors.main_cb = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorRPM_valueChanged(double arg1)
{
    aircraft_->GetData()->rotors.main_rpm = units::angular_velocity::rpm_t(arg1);
    emit(aircraftChanged());
    updateRotorTipVel();
}

void DockWidgetParams::on_spinBoxTailRotorDiameter_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxTailRotorDiameter->invert(arg1);
    aircraft_->GetData()->rotors.tail_r = 0.5 * units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorGear_valueChanged(double arg1)
{
    aircraft_->GetData()->rotors.main_gear_ratio = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxPowerLimit_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxPowerLimit->invert(arg1);
    aircraft_->GetData()->rotors.mcp = units::power::horsepower_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorTipVel_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBoxMainRotorTipVel->invert(arg1);
    aircraft_->GetData()->rotors.main_tip_vel = units::velocity::meters_per_second_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBoxMainRotorBlades_valueChanged(int arg1)
{
    aircraft_->GetData()->rotors.main_blades = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_toolButtonBrowse_clicked()
{
    QDir proj_dir = QFileInfo(aircraftFile_->GetFile()).absoluteDir();
    QString file = proj_dir.absoluteFilePath(ui_->lineEditModelFile->text());

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
        QDir proj_dir = QFileInfo(aircraftFile_->GetFile()).absoluteDir();
        new_file = proj_dir.relativeFilePath(new_file);

        ui_->lineEditModelFile->setText(new_file);
    }
}

void DockWidgetParams::on_lineEditModelFile_textChanged(const QString &arg1)
{
    aircraft_->GetData()->model3d.file = arg1;
    emit(aircraftChanged());
}


void DockWidgetParams::on_spinBox_OffsetX_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBox_OffsetX->invert(arg1);
    aircraft_->GetData()->model3d.offset_x = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_OffsetY_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBox_OffsetY->invert(arg1);
    aircraft_->GetData()->model3d.offset_y = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_OffsetZ_valueChanged(double arg1)
{
    double arg1_raw = ui_->comboBox_OffsetZ->invert(arg1);
    aircraft_->GetData()->model3d.offset_z = units::length::meter_t(arg1_raw);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_RotationX_valueChanged(double arg1)
{
    aircraft_->GetData()->model3d.rotation_x = units::angle::degree_t(arg1);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_RotationY_valueChanged(double arg1)
{
    aircraft_->GetData()->model3d.rotation_y = units::angle::degree_t(arg1);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_RotationZ_valueChanged(double arg1)
{
    aircraft_->GetData()->model3d.rotation_z = units::angle::degree_t(arg1);
    emit(aircraftChanged());
}

void DockWidgetParams::on_spinBox_Scale_valueChanged(double arg1)
{
    aircraft_->GetData()->model3d.scale = arg1;
    emit(aircraftChanged());
}

void DockWidgetParams::on_comboBoxMassEmpty_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxMassEmpty, ui_->comboBoxMassEmpty);
}

void DockWidgetParams::on_comboBoxMTOW_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxMTOW, ui_->comboBoxMTOW);
}

void DockWidgetParams::on_comboBoxMassMaxLand_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxMassMaxLand, ui_->comboBoxMassMaxLand);
}

void DockWidgetParams::on_comboBoxStallV_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxStallV, ui_->comboBoxStallV);
}

void DockWidgetParams::on_comboBoxCruiseV_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxCruiseV, ui_->comboBoxCruiseV);
}

void DockWidgetParams::on_comboBoxCruiseH_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxCruiseH, ui_->comboBoxCruiseH);
}

void DockWidgetParams::on_comboBoxFuseLength_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxFuseLength, ui_->comboBoxFuseLength);
}

void DockWidgetParams::on_comboBoxFuseWidth_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxFuseWidth, ui_->comboBoxFuseWidth);
}

void DockWidgetParams::on_comboBoxFuseHeight_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxFuseHeight, ui_->comboBoxFuseHeight);
}

void DockWidgetParams::on_comboBoxNoseLength_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxNoseLength, ui_->comboBoxNoseLength);
}

void DockWidgetParams::on_comboBoxPressVol_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxPressVol, ui_->comboBoxPressVol);
}

void DockWidgetParams::on_comboBoxWetAreaEst_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWetAreaEst, ui_->comboBoxWetAreaEst);
}

void DockWidgetParams::on_comboBoxWetAreaReal_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWetAreaReal, ui_->comboBoxWetAreaReal);
}

void DockWidgetParams::on_comboBoxWingArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWingArea, ui_->comboBoxWingArea);
}

void DockWidgetParams::on_comboBoxWingAreaExp_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWingAreaExp, ui_->comboBoxWingAreaExp);
}

void DockWidgetParams::on_comboBoxWingSpan_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWingSpan, ui_->comboBoxWingSpan);
}

void DockWidgetParams::on_comboBoxWingSweep_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWingSweep, ui_->comboBoxWingSweep);
}

void DockWidgetParams::on_comboBoxWingCRoot_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWingCRoot, ui_->comboBoxWingCRoot);
}

void DockWidgetParams::on_comboBoxWingCTip_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWingCTip, ui_->comboBoxWingCTip);
}

void DockWidgetParams::on_comboBoxWingFuel_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxWingFuel, ui_->comboBoxWingFuel);
}

void DockWidgetParams::on_comboBoxCtrlArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxCtrlArea, ui_->comboBoxCtrlArea);
}

void DockWidgetParams::on_comboBoxHorTailArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxHorTailArea, ui_->comboBoxHorTailArea);
}

void DockWidgetParams::on_comboBoxHorTailSpan_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxHorTailSpan, ui_->comboBoxHorTailSpan);
}

void DockWidgetParams::on_comboBoxHorTailSweep_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxHorTailSweep, ui_->comboBoxHorTailSweep);
}

void DockWidgetParams::on_comboBoxHorTailCRoot_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxHorTailCRoot, ui_->comboBoxHorTailCRoot);
}

void DockWidgetParams::on_comboBoxHorTailCTip_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxHorTailCTip, ui_->comboBoxHorTailCTip);
}

void DockWidgetParams::on_comboBoxHorTailArm_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxHorTailArm, ui_->comboBoxHorTailArm);
}

void DockWidgetParams::on_comboBoxElevArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxElevArea, ui_->comboBoxElevArea);
}

void DockWidgetParams::on_comboBoxHorTailWF_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxHorTailWF, ui_->comboBoxHorTailWF);
}

void DockWidgetParams::on_comboBoxVerTailArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxVerTailArea, ui_->comboBoxVerTailArea);
}

void DockWidgetParams::on_comboBoxVerTailHeight_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxVerTailHeight, ui_->comboBoxVerTailHeight);
}

void DockWidgetParams::on_comboBoxVerTailSweep_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxVerTailSweep, ui_->comboBoxVerTailSweep);
}

void DockWidgetParams::on_comboBoxVerTailCRoot_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxVerTailCRoot, ui_->comboBoxVerTailCRoot);
}

void DockWidgetParams::on_comboBoxVerTailCTip_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxVerTailCTip, ui_->comboBoxVerTailCTip);
}

void DockWidgetParams::on_comboBoxVerTailArm_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxVerTailArm, ui_->comboBoxVerTailArm);
}

void DockWidgetParams::on_comboBoxRuddArea_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxRuddArea, ui_->comboBoxRuddArea);
}

void DockWidgetParams::on_comboBoxMainGearLength_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxMainGearLength, ui_->comboBoxMainGearLength);
}

void DockWidgetParams::on_comboBoxNoseGearLength_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxNoseGearLength, ui_->comboBoxNoseGearLength);
}

void DockWidgetParams::on_comboBoxEngineMass_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxEngineMass, ui_->comboBoxEngineMass);
}

void DockWidgetParams::on_comboBoxMainRotorDiameter_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxMainRotorDiameter, ui_->comboBoxMainRotorDiameter);
}

void DockWidgetParams::on_comboBoxMainRotorChord_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxMainRotorChord, ui_->comboBoxMainRotorChord);
}

void DockWidgetParams::on_comboBoxTailRotorDiameter_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxTailRotorDiameter, ui_->comboBoxTailRotorDiameter);
}

void DockWidgetParams::on_comboBoxPowerLimit_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxPowerLimit, ui_->comboBoxPowerLimit);
}

void DockWidgetParams::on_comboBoxMainRotorTipVel_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBoxMainRotorTipVel, ui_->comboBoxMainRotorTipVel);
}

void DockWidgetParams::on_comboBox_OffsetX_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_OffsetX, ui_->comboBox_OffsetX);
}

void DockWidgetParams::on_comboBox_OffsetY_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_OffsetY, ui_->comboBox_OffsetY);
}

void DockWidgetParams::on_comboBox_OffsetZ_currentIndexChanged(int /*index*/)
{
    ComboUnits::switchUnits(ui_->spinBox_OffsetZ, ui_->comboBox_OffsetZ);
}
