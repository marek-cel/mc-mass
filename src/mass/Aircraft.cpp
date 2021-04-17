/****************************************************************************//*
 * Copyright (C) 2021 Marek M. Cel
 *
 * Creative Commons Legal Code
 *
 * CC0 1.0 Universal
 *
 *     CREATIVE COMMONS CORPORATION IS NOT A LAW FIRM AND DOES NOT PROVIDE
 *     LEGAL SERVICES. DISTRIBUTION OF THIS DOCUMENT DOES NOT CREATE AN
 *     ATTORNEY-CLIENT RELATIONSHIP. CREATIVE COMMONS PROVIDES THIS
 *     INFORMATION ON AN "AS-IS" BASIS. CREATIVE COMMONS MAKES NO WARRANTIES
 *     REGARDING THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS
 *     PROVIDED HEREUNDER, AND DISCLAIMS LIABILITY FOR DAMAGES RESULTING FROM
 *     THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS PROVIDED
 *     HEREUNDER.
 *
 * Statement of Purpose
 *
 * The laws of most jurisdictions throughout the world automatically confer
 * exclusive Copyright and Related Rights (defined below) upon the creator
 * and subsequent owner(s) (each and all, an "owner") of an original work of
 * authorship and/or a database (each, a "Work").
 *
 * Certain owners wish to permanently relinquish those rights to a Work for
 * the purpose of contributing to a commons of creative, cultural and
 * scientific works ("Commons") that the public can reliably and without fear
 * of later claims of infringement build upon, modify, incorporate in other
 * works, reuse and redistribute as freely as possible in any form whatsoever
 * and for any purposes, including without limitation commercial purposes.
 * These owners may contribute to the Commons to promote the ideal of a free
 * culture and the further production of creative, cultural and scientific
 * works, or to gain reputation or greater distribution for their Work in
 * part through the use and efforts of others.
 *
 * For these and/or other purposes and motivations, and without any
 * expectation of additional consideration or compensation, the person
 * associating CC0 with a Work (the "Affirmer"), to the extent that he or she
 * is an owner of Copyright and Related Rights in the Work, voluntarily
 * elects to apply CC0 to the Work and publicly distribute the Work under its
 * terms, with knowledge of his or her Copyright and Related Rights in the
 * Work and the meaning and intended legal effect of CC0 on those rights.
 *
 * 1. Copyright and Related Rights. A Work made available under CC0 may be
 * protected by copyright and related or neighboring rights ("Copyright and
 * Related Rights"). Copyright and Related Rights include, but are not
 * limited to, the following:
 *
 *   i. the right to reproduce, adapt, distribute, perform, display,
 *      communicate, and translate a Work;
 *  ii. moral rights retained by the original author(s) and/or performer(s);
 * iii. publicity and privacy rights pertaining to a person's image or
 *      likeness depicted in a Work;
 *  iv. rights protecting against unfair competition in regards to a Work,
 *      subject to the limitations in paragraph 4(a), below;
 *   v. rights protecting the extraction, dissemination, use and reuse of data
 *      in a Work;
 *  vi. database rights (such as those arising under Directive 96/9/EC of the
 *      European Parliament and of the Council of 11 March 1996 on the legal
 *      protection of databases, and under any national implementation
 *      thereof, including any amended or successor version of such
 *      directive); and
 * vii. other similar, equivalent or corresponding rights throughout the
 *      world based on applicable law or treaty, and any national
 *      implementations thereof.
 *
 * 2. Waiver. To the greatest extent permitted by, but not in contravention
 * of, applicable law, Affirmer hereby overtly, fully, permanently,
 * irrevocably and unconditionally waives, abandons, and surrenders all of
 * Affirmer's Copyright and Related Rights and associated claims and causes
 * of action, whether now known or unknown (including existing as well as
 * future claims and causes of action), in the Work (i) in all territories
 * worldwide, (ii) for the maximum duration provided by applicable law or
 * treaty (including future time extensions), (iii) in any current or future
 * medium and for any number of copies, and (iv) for any purpose whatsoever,
 * including without limitation commercial, advertising or promotional
 * purposes (the "Waiver"). Affirmer makes the Waiver for the benefit of each
 * member of the public at large and to the detriment of Affirmer's heirs and
 * successors, fully intending that such Waiver shall not be subject to
 * revocation, rescission, cancellation, termination, or any other legal or
 * equitable action to disrupt the quiet enjoyment of the Work by the public
 * as contemplated by Affirmer's express Statement of Purpose.
 *
 * 3. Public License Fallback. Should any part of the Waiver for any reason
 * be judged legally invalid or ineffective under applicable law, then the
 * Waiver shall be preserved to the maximum extent permitted taking into
 * account Affirmer's express Statement of Purpose. In addition, to the
 * extent the Waiver is so judged Affirmer hereby grants to each affected
 * person a royalty-free, non transferable, non sublicensable, non exclusive,
 * irrevocable and unconditional license to exercise Affirmer's Copyright and
 * Related Rights in the Work (i) in all territories worldwide, (ii) for the
 * maximum duration provided by applicable law or treaty (including future
 * time extensions), (iii) in any current or future medium and for any number
 * of copies, and (iv) for any purpose whatsoever, including without
 * limitation commercial, advertising or promotional purposes (the
 * "License"). The License shall be deemed effective as of the date CC0 was
 * applied by Affirmer to the Work. Should any part of the License for any
 * reason be judged legally invalid or ineffective under applicable law, such
 * partial invalidity or ineffectiveness shall not invalidate the remainder
 * of the License, and in such case Affirmer hereby affirms that he or she
 * will not (i) exercise any of his or her remaining Copyright and Related
 * Rights in the Work or (ii) assert any associated claims and causes of
 * action with respect to the Work, in either case contrary to Affirmer's
 * express Statement of Purpose.
 *
 * 4. Limitations and Disclaimers.
 *
 *  a. No trademark or patent rights held by Affirmer are waived, abandoned,
 *     surrendered, licensed or otherwise affected by this document.
 *  b. Affirmer offers the Work as-is and makes no representations or
 *     warranties of any kind concerning the Work, express, implied,
 *     statutory or otherwise, including without limitation warranties of
 *     title, merchantability, fitness for a particular purpose, non
 *     infringement, or the absence of latent or other defects, accuracy, or
 *     the present or absence of errors, whether or not discoverable, all to
 *     the greatest extent permissible under applicable law.
 *  c. Affirmer disclaims responsibility for clearing rights of other persons
 *     that may apply to the Work or any use thereof, including without
 *     limitation any person's Copyright and Related Rights in the Work.
 *     Further, Affirmer disclaims responsibility for obtaining any necessary
 *     consents, permissions or other rights required for any use of the
 *     Work.
 *  d. Affirmer understands and acknowledges that Creative Commons is not a
 *     party to this document and has no duty or obligation with respect to
 *     this CC0 or use of the Work.
 ******************************************************************************/

#include <mass/Aircraft.h>

#include <Xml.h>

#include <mass/AllElse.h>
#include <mass/Engine.h>
#include <mass/Fuselage.h>
#include <mass/GearMain.h>
#include <mass/GearNose.h>
#include <mass/RotorDrive.h>
#include <mass/RotorHub.h>
#include <mass/RotorMain.h>
#include <mass/RotorTail.h>
#include <mass/TailHor.h>
#include <mass/TailVer.h>
#include <mass/Wing.h>

////////////////////////////////////////////////////////////////////////////////

Aircraft::Aircraft() :
    _type ( FighterAttack )
{
    reset();
}

////////////////////////////////////////////////////////////////////////////////

Aircraft::~Aircraft()
{
    deleteAllComponents();
}

////////////////////////////////////////////////////////////////////////////////

bool Aircraft::read( QDomElement *parentNode )
{
    if ( !parentNode->isNull() )
    {
        int type_temp = parentNode->attributeNode( "type" ).value().toInt();

        _type = FighterAttack;

        switch ( type_temp )
        {
            case FighterAttack   : _type = FighterAttack   ; break;
            case CargoTransport  : _type = CargoTransport  ; break;
            case GeneralAviation : _type = GeneralAviation ; break;
            case Helicopter      : _type = Helicopter      ; break;
        }

        QDomElement nodeData = parentNode->firstChildElement( "data" );
        QDomElement nodeComponents = parentNode->firstChildElement( "components" );

        if ( !nodeData.isNull() && !nodeComponents.isNull() )
        {
            // data
            QDomElement nodeM_empty   = nodeData.firstChildElement( "m_empty"     );
            QDomElement nodeM_maxTO   = nodeData.firstChildElement( "m_max_to"    );
            QDomElement nodeM_maxLand = nodeData.firstChildElement( "m_max_land"  );
            QDomElement nodeNzMax     = nodeData.firstChildElement( "nz_max"      );
            QDomElement nodeNzMaxLand = nodeData.firstChildElement( "nz_max_land" );
            QDomElement nodeStallV    = nodeData.firstChildElement( "stall_v"     );
            QDomElement nodeCruiseH   = nodeData.firstChildElement( "h_cruise"    );
            QDomElement nodeCruiseV   = nodeData.firstChildElement( "v_cruise"    );
            QDomElement nodeMachMax   = nodeData.firstChildElement( "mach_max"    );
            QDomElement nodeNavyAC    = nodeData.firstChildElement( "navy_ac"     );

            QDomElement nodeCargoDoor  = nodeData.firstChildElement( "cargo_door"  );
            QDomElement nodeFuseL      = nodeData.firstChildElement( "fuse_l"      );
            QDomElement nodeFuseH      = nodeData.firstChildElement( "fuse_h"      );
            QDomElement nodeFuseW      = nodeData.firstChildElement( "fuse_w"      );
            QDomElement nodeNoseL      = nodeData.firstChildElement( "nose_l"      );
            QDomElement nodeWettedArea = nodeData.firstChildElement( "wetted_area" );
            QDomElement nodePressVol   = nodeData.firstChildElement( "press_vol"   );
            QDomElement nodeFuselageLG = nodeData.firstChildElement( "fuselage_lg" );
            QDomElement nodeCargoRamp  = nodeData.firstChildElement( "cargo_ramp"  );

            QDomElement nodeWingArea  = nodeData.firstChildElement( "wing_area"  );
            QDomElement nodeWingExp   = nodeData.firstChildElement( "wing_exp"   );
            QDomElement nodeWingSpan  = nodeData.firstChildElement( "wing_span"  );
            QDomElement nodeWingSweep = nodeData.firstChildElement( "wing_sweep" );
            QDomElement nodeWingCT    = nodeData.firstChildElement( "wing_c_t"   );
            QDomElement nodeWingCR    = nodeData.firstChildElement( "wing_c_r"   );
            QDomElement nodeWingAR    = nodeData.firstChildElement( "wing_ar"    );
            QDomElement nodeWingTR    = nodeData.firstChildElement( "wing_tr"    );
            QDomElement nodeWingTC    = nodeData.firstChildElement( "wing_tc"    );
            QDomElement nodeWingFule  = nodeData.firstChildElement( "wing_fuel"  );
            QDomElement nodeCtrlArea  = nodeData.firstChildElement( "ctrl_area"  );
            QDomElement nodeWingDelta = nodeData.firstChildElement( "wing_delta" );
            QDomElement nodeWingVar   = nodeData.firstChildElement( "wing_var"   );

            QDomElement nodeHorTailArea  = nodeData.firstChildElement( "h_tail_area"    );
            QDomElement nodeHorTailSpan  = nodeData.firstChildElement( "h_tail_span"    );
            QDomElement nodeHorTailSweep = nodeData.firstChildElement( "h_tail_sweep"   );
            QDomElement nodeHorTailCT    = nodeData.firstChildElement( "h_tail_c_t"     );
            QDomElement nodeHorTailCR    = nodeData.firstChildElement( "h_tail_c_r"     );
            QDomElement nodeHorTailTC    = nodeData.firstChildElement( "h_tail_tc"      );
            QDomElement nodeElevArea     = nodeData.firstChildElement( "elev_area"      );
            QDomElement nodeHorTailFW    = nodeData.firstChildElement( "h_tail_fw"      );
            QDomElement nodeHorTailArm   = nodeData.firstChildElement( "h_tail_arm"     );
            QDomElement nodeHorTailAR    = nodeData.firstChildElement( "h_tail_ar"      );
            QDomElement nodeHorTailTR    = nodeData.firstChildElement( "h_tail_tr"      );
            QDomElement nodeHorTailMoving  = nodeData.firstChildElement( "h_tail_moving"  );
            QDomElement nodeHorTailRolling = nodeData.firstChildElement( "h_tail_rolling" );

            QDomElement nodeVerTailArea   = nodeData.firstChildElement( "v_tail_area"   );
            QDomElement nodeVerTailHeight = nodeData.firstChildElement( "v_tail_height"  );
            QDomElement nodeVerTailSweep  = nodeData.firstChildElement( "v_tail_sweep"   );
            QDomElement nodeVerTailCT     = nodeData.firstChildElement( "v_tail_c_t"     );
            QDomElement nodeVerTailCR     = nodeData.firstChildElement( "v_tail_c_r"     );
            QDomElement nodeVerTailTC     = nodeData.firstChildElement( "v_tail_tc"      );
            QDomElement nodeVerTailArm    = nodeData.firstChildElement( "v_tail_arm"     );
            QDomElement nodeRuddArea      = nodeData.firstChildElement( "rudd_area"      );
            QDomElement nodeVerTailAR     = nodeData.firstChildElement( "v_tail_ar"      );
            QDomElement nodeVerTailTR     = nodeData.firstChildElement( "v_tail_tr"      );
            QDomElement nodeTailT         = nodeData.firstChildElement( "t_tail" );
            QDomElement nodeVerTailRotor  = nodeData.firstChildElement( "v_tail_rotor" );

            QDomElement nodeMainGearL      = nodeData.firstChildElement( "m_gear_l"      );
            QDomElement nodeNoseGearL      = nodeData.firstChildElement( "n_gear_l"      );
            QDomElement nodeMainGearWheels = nodeData.firstChildElement( "m_gear_wheels" );
            QDomElement nodeMainGearStruts = nodeData.firstChildElement( "m_gear_struts" );
            QDomElement nodeNoseGearWheels = nodeData.firstChildElement( "n_gear_wheels" );
            QDomElement nodeGearFixed      = nodeData.firstChildElement( "gear_fixed"    );
            QDomElement nodeGearCross      = nodeData.firstChildElement( "gear_cross"    );
            QDomElement nodeGearTripod     = nodeData.firstChildElement( "gear_tripod"   );
            QDomElement nodeMainGearKneel  = nodeData.firstChildElement( "m_gear_kneel"  );
            QDomElement nodeNoseGearKneel  = nodeData.firstChildElement( "n_gear_kneel"  );

            QDomElement nodeM_engine = nodeData.firstChildElement( "m_engine" );

            QDomElement nodeMainRotorRad    = nodeData.firstChildElement( "m_rotor_r"    );
            QDomElement nodeMainRotorChord  = nodeData.firstChildElement( "m_blades_c"   );
            QDomElement nodeMainRotorRPM    = nodeData.firstChildElement( "m_rotor_rpm"  );
            QDomElement nodeMainRotorGear   = nodeData.firstChildElement( "m_rotor_gear" );
            QDomElement nodeTailRotorRad    = nodeData.firstChildElement( "t_rotor_r"    );
            QDomElement nodePowerLimit      = nodeData.firstChildElement( "rotor_mcp"    );
            QDomElement nodeMainRotorTipVel = nodeData.firstChildElement( "m_rotor_tv"   );
            QDomElement nodeMainRotorBlades = nodeData.firstChildElement( "m_rotor_nb"   );

            if ( !nodeM_empty   .isNull()
              && !nodeM_maxTO   .isNull()
              && !nodeM_maxLand .isNull()
              && !nodeNzMax     .isNull()
              && !nodeNzMaxLand .isNull()
              && !nodeStallV    .isNull()
              && !nodeCruiseH   .isNull()
              && !nodeCruiseV   .isNull()
              && !nodeMachMax   .isNull()
              && !nodeNavyAC    .isNull()

              && !nodeCargoDoor  .isNull()
              && !nodeFuseL      .isNull()
              && !nodeFuseH      .isNull()
              && !nodeFuseW      .isNull()
              && !nodeNoseL      .isNull()
              && !nodeWettedArea .isNull()
              && !nodePressVol   .isNull()
              && !nodeFuselageLG .isNull()
              && !nodeCargoRamp  .isNull()

              && !nodeWingArea  .isNull()
              && !nodeWingExp   .isNull()
              && !nodeWingSpan  .isNull()
              && !nodeWingSweep .isNull()
              && !nodeWingCT    .isNull()
              && !nodeWingCR    .isNull()
              && !nodeWingAR    .isNull()
              && !nodeWingTR    .isNull()
              && !nodeWingTC    .isNull()
              && !nodeWingFule  .isNull()
              && !nodeCtrlArea  .isNull()
              && !nodeWingDelta .isNull()
              && !nodeWingVar   .isNull()

              && !nodeHorTailArea  .isNull()
              && !nodeHorTailSpan  .isNull()
              && !nodeHorTailSweep .isNull()
              && !nodeHorTailCT    .isNull()
              && !nodeHorTailCR    .isNull()
              && !nodeHorTailTC    .isNull()
              && !nodeElevArea     .isNull()
              && !nodeHorTailFW    .isNull()
              && !nodeHorTailArm   .isNull()
              && !nodeHorTailAR    .isNull()
              && !nodeHorTailTR    .isNull()
              && !nodeHorTailMoving  .isNull()
              && !nodeHorTailRolling .isNull()

              && !nodeVerTailArea   .isNull()
              && !nodeVerTailHeight .isNull()
              && !nodeVerTailSweep  .isNull()
              && !nodeVerTailCT     .isNull()
              && !nodeVerTailCR     .isNull()
              && !nodeVerTailTC     .isNull()
              && !nodeVerTailArm    .isNull()
              && !nodeRuddArea      .isNull()
              && !nodeVerTailAR     .isNull()
              && !nodeVerTailTR     .isNull()
              && !nodeTailT         .isNull()
              && !nodeVerTailRotor  .isNull()

              && !nodeMainGearL      .isNull()
              && !nodeNoseGearL      .isNull()
              && !nodeMainGearWheels .isNull()
              && !nodeMainGearStruts .isNull()
              && !nodeNoseGearWheels .isNull()
              && !nodeGearFixed      .isNull()
              && !nodeGearCross      .isNull()
              && !nodeGearTripod     .isNull()
              && !nodeMainGearKneel  .isNull()
              && !nodeNoseGearKneel  .isNull()

              && !nodeM_engine .isNull()

              && !nodeMainRotorRad    .isNull()
              && !nodeMainRotorChord  .isNull()
              && !nodeMainRotorRPM    .isNull()
              && !nodeMainRotorGear   .isNull()
              && !nodeTailRotorRad    .isNull()
              && !nodePowerLimit      .isNull()
              && !nodeMainRotorTipVel .isNull()
              && !nodeMainRotorBlades .isNull()
               )
            {
                // general
                _m_empty    = nodeM_empty   .text().toDouble();
                _m_maxTO    = nodeM_maxTO   .text().toDouble();
                _m_maxLand  = nodeM_maxLand .text().toDouble();
                _nz_max     = nodeNzMax     .text().toDouble();
                _nz_maxLand = nodeNzMaxLand .text().toDouble();
                _stall_v    = nodeStallV    .text().toDouble();
                _h_cruise   = nodeCruiseH   .text().toDouble();
                _v_cruise   = nodeCruiseV   .text().toDouble();
                _mach_max   = nodeMachMax   .text().toDouble();

                _navy_ac = nodeNavyAC.text().toInt();

                // fuselage
                int cargo_door_temp = nodeCargoDoor.text().toInt();

                _cargo_door = NoCargoDoor;

                switch ( cargo_door_temp )
                {
                    case NoCargoDoor       : _cargo_door = NoCargoDoor       ; break;
                    case OneSideCargoDoor  : _cargo_door = OneSideCargoDoor  ; break;
                    case TwoSideCargoDoor  : _cargo_door = TwoSideCargoDoor  ; break;
                    case AftClamshellDoor  : _cargo_door = AftClamshellDoor  ; break;
                    case TwoSideAndAftDoor : _cargo_door = TwoSideAndAftDoor ; break;
                }

                _fuse_l = nodeFuseL.text().toDouble();
                _fuse_h = nodeFuseH.text().toDouble();
                _fuse_w = nodeFuseW.text().toDouble();
                _nose_l = nodeNoseL.text().toDouble();

                _wetted_area = nodeWettedArea .text().toDouble();
                _press_vol   = nodePressVol   .text().toDouble();
                _fuselage_lg = nodeFuselageLG .text().toInt();
                _cargo_ramp  = nodeCargoRamp  .text().toInt();

                // wing
                _wing_area  = nodeWingArea  .text().toDouble();
                _wing_exp   = nodeWingExp   .text().toDouble();
                _wing_span  = nodeWingSpan  .text().toDouble();
                _wing_sweep = nodeWingSweep .text().toDouble();
                _wing_c_t   = nodeWingCT    .text().toDouble();
                _wing_c_r   = nodeWingCR    .text().toDouble();
                _wing_ar    = nodeWingAR    .text().toDouble();
                _wing_tr    = nodeWingTR    .text().toDouble();
                _wing_tc    = nodeWingTC    .text().toDouble();
                _wing_fuel  = nodeWingFule  .text().toDouble();
                _ctrl_area  = nodeCtrlArea  .text().toDouble();
                _wing_delta = nodeWingDelta .text().toInt();
                _wing_var   = nodeWingVar   .text().toInt();

                // horizontal tail
                _h_tail_area  = nodeHorTailArea   .text().toDouble();
                _h_tail_span  = nodeHorTailSpan   .text().toDouble();
                _h_tail_sweep = nodeHorTailSweep  .text().toDouble();
                _h_tail_c_t   = nodeHorTailCT     .text().toDouble();
                _h_tail_c_r   = nodeHorTailCR     .text().toDouble();
                _h_tail_tc    = nodeHorTailTC     .text().toDouble();
                _elev_area    = nodeElevArea      .text().toDouble();
                _h_tail_fw    = nodeHorTailFW     .text().toDouble();
                _h_tail_arm   = nodeHorTailArm    .text().toDouble();
                _h_tail_ar    = nodeHorTailAR     .text().toDouble();
                _h_tail_tr    = nodeHorTailTR     .text().toDouble();

                _h_tail_moving  = nodeHorTailMoving  .text().toInt();
                _h_tail_rolling = nodeHorTailRolling .text().toInt();

                // vertical tail
                _v_tail_area   = nodeVerTailArea   .text().toDouble();
                _v_tail_height = nodeVerTailHeight .text().toDouble();
                _v_tail_sweep  = nodeVerTailSweep  .text().toDouble();
                _v_tail_c_t    = nodeVerTailCT     .text().toDouble();
                _v_tail_c_r    = nodeVerTailCR     .text().toDouble();
                _v_tail_tc     = nodeVerTailTC     .text().toDouble();
                _v_tail_arm    = nodeVerTailArm    .text().toDouble();
                _rudd_area     = nodeRuddArea      .text().toDouble();
                _v_tail_ar     = nodeVerTailAR     .text().toDouble();
                _v_tail_tr     = nodeVerTailTR     .text().toDouble();

                _t_tail = nodeTailT.text().toInt();

                _v_tail_rotor = nodeVerTailRotor.text().toInt();

                // landing gear
                _m_gear_l      = nodeMainGearL      .text().toDouble();
                _n_gear_l      = nodeNoseGearL      .text().toDouble();
                _m_gear_wheels = nodeMainGearWheels .text().toInt();
                _m_gear_struts = nodeMainGearStruts .text().toInt();
                _n_gear_wheels = nodeNoseGearWheels .text().toInt();
                _gear_fixed    = nodeGearFixed      .text().toInt();
                _gear_cross    = nodeGearCross      .text().toInt();
                _gear_tripod   = nodeGearTripod     .text().toInt();
                _m_gear_kneel  = nodeMainGearKneel  .text().toInt();
                _n_gear_kneel  = nodeNoseGearKneel  .text().toInt();

                // engine
                _m_engine = nodeM_engine.text().toDouble();

                // rotors
                _m_rotor_r    = nodeMainRotorRad    .text().toDouble();
                _m_blades_c   = nodeMainRotorChord  .text().toDouble();
                _m_rotor_rpm  = nodeMainRotorRPM    .text().toDouble();
                _m_rotor_gear = nodeMainRotorGear   .text().toDouble();
                _t_rotor_r    = nodeTailRotorRad    .text().toDouble();
                _rotor_mcp    = nodePowerLimit      .text().toDouble();
                _m_rotor_tv   = nodeMainRotorTipVel .text().toDouble();
                _m_rotor_nb   = nodeMainRotorBlades .text().toInt();

                // components
                QDomElement nodeComponent = nodeComponents.firstChildElement();

                while ( !nodeComponent.isNull() )
                {
                    Component *temp = NULLPTR;

                    if      ( nodeComponent.tagName() == AllElse::xml_tag )
                    {
                        temp = new AllElse( this );
                    }
                    else if ( nodeComponent.tagName() == Engine::xml_tag )
                    {
                        temp = new Engine( this );
                    }
                    else if ( nodeComponent.tagName() == Fuselage::xml_tag )
                    {
                        temp = new Fuselage( this );
                    }
                    else if ( nodeComponent.tagName() == GearMain::xml_tag )
                    {
                        temp = new GearMain( this );
                    }
                    else if ( nodeComponent.tagName() == GearNose::xml_tag )
                    {
                        temp = new GearNose( this );
                    }
                    else if ( nodeComponent.tagName() == RotorDrive::xml_tag )
                    {
                        temp = new RotorDrive( this );
                    }
                    else if ( nodeComponent.tagName() == RotorHub::xml_tag )
                    {
                        temp = new RotorHub( this );
                    }
                    else if ( nodeComponent.tagName() == RotorMain::xml_tag )
                    {
                        temp = new RotorMain( this );
                    }
                    else if ( nodeComponent.tagName() == RotorTail::xml_tag )
                    {
                        temp = new RotorTail( this );
                    }
                    else if ( nodeComponent.tagName() == TailHor::xml_tag )
                    {
                        temp = new TailHor( this );
                    }
                    else if ( nodeComponent.tagName() == TailVer::xml_tag )
                    {
                        temp = new TailVer( this );
                    }
                    else if ( nodeComponent.tagName() == Wing::xml_tag )
                    {
                        temp = new Wing( this );
                    }

                    if ( temp )
                    {
                        temp->read( &nodeComponent );
                        _components.push_back( temp );
                    }

                    nodeComponent = nodeComponent.nextSiblingElement();
                }

                update();

                return true;
            }
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomAttr nodeType = doc->createAttribute( "type" );
    nodeType.setValue( QString::number( getType() ) );
    parentNode->setAttributeNode( nodeType );

    // data
    QDomElement nodeData = doc->createElement( "data" );
    parentNode->appendChild( nodeData );

    // data - general
    Xml::saveTextNode( doc, &nodeData, "m_empty"     , _m_empty    );
    Xml::saveTextNode( doc, &nodeData, "m_max_to"    , _m_maxTO    );
    Xml::saveTextNode( doc, &nodeData, "m_max_land"  , _m_maxLand  );
    Xml::saveTextNode( doc, &nodeData, "nz_max"      , _nz_max     );
    Xml::saveTextNode( doc, &nodeData, "nz_max_land" , _nz_maxLand );
    Xml::saveTextNode( doc, &nodeData, "stall_v"     , _stall_v    );
    Xml::saveTextNode( doc, &nodeData, "h_cruise"    , _h_cruise   );
    Xml::saveTextNode( doc, &nodeData, "v_cruise"    , _v_cruise   );
    Xml::saveTextNode( doc, &nodeData, "mach_max"    , _mach_max   );

    Xml::saveTextNode( doc, &nodeData, "navy_ac", _navy_ac );

    // data - fuselage
    Xml::saveTextNode( doc, &nodeData, "cargo_door" , QString::number( _cargo_door ) );

    Xml::saveTextNode( doc, &nodeData, "fuse_l" , _fuse_l );
    Xml::saveTextNode( doc, &nodeData, "fuse_h" , _fuse_h );
    Xml::saveTextNode( doc, &nodeData, "fuse_w" , _fuse_w );
    Xml::saveTextNode( doc, &nodeData, "nose_l" , _nose_l );

    Xml::saveTextNode( doc, &nodeData, "wetted_area" , _wetted_area );
    Xml::saveTextNode( doc, &nodeData, "press_vol"   , _press_vol   );
    Xml::saveTextNode( doc, &nodeData, "fuselage_lg" , _fuselage_lg );
    Xml::saveTextNode( doc, &nodeData, "cargo_ramp"  , _cargo_ramp  );

    // data - wing
    Xml::saveTextNode( doc, &nodeData, "wing_area"  , _wing_area  );
    Xml::saveTextNode( doc, &nodeData, "wing_exp"   , _wing_exp   );
    Xml::saveTextNode( doc, &nodeData, "wing_span"  , _wing_span  );
    Xml::saveTextNode( doc, &nodeData, "wing_sweep" , _wing_sweep );
    Xml::saveTextNode( doc, &nodeData, "wing_c_t"   , _wing_c_t   );
    Xml::saveTextNode( doc, &nodeData, "wing_c_r"   , _wing_c_r   );
    Xml::saveTextNode( doc, &nodeData, "wing_ar"    , _wing_ar    );
    Xml::saveTextNode( doc, &nodeData, "wing_tr"    , _wing_tr    );
    Xml::saveTextNode( doc, &nodeData, "wing_tc"    , _wing_tc    );
    Xml::saveTextNode( doc, &nodeData, "wing_fuel"  , _wing_fuel  );
    Xml::saveTextNode( doc, &nodeData, "ctrl_area"  , _ctrl_area  );
    Xml::saveTextNode( doc, &nodeData, "wing_delta" , _wing_delta );
    Xml::saveTextNode( doc, &nodeData, "wing_var"   , _wing_var   );

    // data - horizontal tail
    Xml::saveTextNode( doc, &nodeData, "h_tail_area"  , _h_tail_area  );
    Xml::saveTextNode( doc, &nodeData, "h_tail_span"  , _h_tail_span  );
    Xml::saveTextNode( doc, &nodeData, "h_tail_sweep" , _h_tail_sweep );
    Xml::saveTextNode( doc, &nodeData, "h_tail_c_t"   , _h_tail_c_t   );
    Xml::saveTextNode( doc, &nodeData, "h_tail_c_r"   , _h_tail_c_r   );
    Xml::saveTextNode( doc, &nodeData, "h_tail_tc"    , _h_tail_tc    );
    Xml::saveTextNode( doc, &nodeData, "elev_area"    , _elev_area    );
    Xml::saveTextNode( doc, &nodeData, "h_tail_fw"    , _h_tail_fw    );
    Xml::saveTextNode( doc, &nodeData, "h_tail_arm"   , _h_tail_arm   );
    Xml::saveTextNode( doc, &nodeData, "h_tail_ar"    , _h_tail_ar    );
    Xml::saveTextNode( doc, &nodeData, "h_tail_tr"    , _h_tail_tr    );

    Xml::saveTextNode( doc, &nodeData, "h_tail_moving"  , _h_tail_moving  );
    Xml::saveTextNode( doc, &nodeData, "h_tail_rolling" , _h_tail_rolling );

    // data - vertical tail
    Xml::saveTextNode( doc, &nodeData, "v_tail_area"   , _v_tail_area   );
    Xml::saveTextNode( doc, &nodeData, "v_tail_height" , _v_tail_height );
    Xml::saveTextNode( doc, &nodeData, "v_tail_sweep"  , _v_tail_sweep  );
    Xml::saveTextNode( doc, &nodeData, "v_tail_c_t"    , _v_tail_c_t    );
    Xml::saveTextNode( doc, &nodeData, "v_tail_c_r"    , _v_tail_c_r    );
    Xml::saveTextNode( doc, &nodeData, "v_tail_tc"     , _v_tail_tc     );
    Xml::saveTextNode( doc, &nodeData, "v_tail_arm"    , _v_tail_arm    );
    Xml::saveTextNode( doc, &nodeData, "rudd_area"     , _rudd_area     );
    Xml::saveTextNode( doc, &nodeData, "v_tail_ar"     , _v_tail_ar     );
    Xml::saveTextNode( doc, &nodeData, "v_tail_tr"     , _v_tail_tr     );

    Xml::saveTextNode( doc, &nodeData, "t_tail", _t_tail );

    Xml::saveTextNode( doc, &nodeData, "v_tail_rotor", _v_tail_rotor );

    // data - landing gear
    Xml::saveTextNode( doc, &nodeData, "m_gear_l"      , _m_gear_l      );
    Xml::saveTextNode( doc, &nodeData, "n_gear_l"      , _n_gear_l      );
    Xml::saveTextNode( doc, &nodeData, "m_gear_wheels" , _m_gear_wheels );
    Xml::saveTextNode( doc, &nodeData, "m_gear_struts" , _m_gear_struts );
    Xml::saveTextNode( doc, &nodeData, "n_gear_wheels" , _n_gear_wheels );
    Xml::saveTextNode( doc, &nodeData, "gear_fixed"    , _gear_fixed    );
    Xml::saveTextNode( doc, &nodeData, "gear_cross"    , _gear_cross    );
    Xml::saveTextNode( doc, &nodeData, "gear_tripod"   , _gear_tripod   );
    Xml::saveTextNode( doc, &nodeData, "m_gear_kneel"  , _m_gear_kneel  );
    Xml::saveTextNode( doc, &nodeData, "n_gear_kneel"  , _n_gear_kneel  );

    // data - engine
    Xml::saveTextNode( doc, &nodeData, "m_engine"  , _m_engine );

    // rotors
    Xml::saveTextNode( doc, &nodeData, "m_rotor_r"    , _m_rotor_r    );
    Xml::saveTextNode( doc, &nodeData, "m_blades_c"   , _m_blades_c   );
    Xml::saveTextNode( doc, &nodeData, "m_rotor_rpm"  , _m_rotor_rpm  );
    Xml::saveTextNode( doc, &nodeData, "m_rotor_gear" , _m_rotor_gear );
    Xml::saveTextNode( doc, &nodeData, "t_rotor_r"    , _t_rotor_r    );
    Xml::saveTextNode( doc, &nodeData, "rotor_mcp"    , _rotor_mcp    );
    Xml::saveTextNode( doc, &nodeData, "m_rotor_tv"   , _m_rotor_tv   );

    Xml::saveTextNode( doc, &nodeData, "m_rotor_nb"  , _m_rotor_nb   );

    // components
    QDomElement componentsNode = doc->createElement( "components" );
    parentNode->appendChild( componentsNode );

    for ( Aircraft::Components::iterator it = _components.begin(); it != _components.end(); it++ )
    {
        (*it)->save( doc, &componentsNode );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::reset()
{
    _type = FighterAttack;

    // general
    _m_empty    = 0.0;
    _m_maxTO    = 0.0;
    _m_maxLand  = 0.0;
    _nz_max     = 1.0;
    _nz_maxLand = 1.0;
    _stall_v    = 0.0;
    _h_cruise   = 0.0;
    _v_cruise   = 0.0;
    _mach_max   = 0.0;
    _navy_ac = false;

    // fuselage
    _cargo_door = NoCargoDoor;
    _fuse_l = 0.0;
    _fuse_h = 0.0;
    _fuse_w = 0.0;
    _nose_l = 0.0;
    _wetted_area = 0.0;
    _press_vol   = 0.0;
    _fuselage_lg = false;
    _cargo_ramp  = false;

    // wing
    _wing_area  = 0.0;
    _wing_exp   = 0.0;
    _wing_span  = 0.0;
    _wing_sweep = 0.0;
    _wing_c_t   = 0.0;
    _wing_c_r   = 0.0;
    _wing_ar    = 0.0;
    _wing_tr    = 0.0;
    _wing_tc    = 0.0;
    _wing_fuel  = 0.0;
    _ctrl_area  = 0.0;
    _wing_delta = false;
    _wing_var   = false;

    // horizontal tail
    _h_tail_area  = 0.0;
    _h_tail_span  = 0.0;
    _h_tail_sweep = 0.0;
    _h_tail_c_t   = 0.0;
    _h_tail_c_r   = 0.0;
    _h_tail_tc    = 0.0;
    _elev_area    = 0.0;
    _h_tail_fw    = 0.0;
    _h_tail_arm   = 0.0;
    _h_tail_ar    = 0.0;
    _h_tail_tr    = 0.0;
    _h_tail_moving  = false;
    _h_tail_rolling = false;

    // vertical tail
    _v_tail_area   = 0.0;
    _v_tail_height = 0.0;
    _v_tail_sweep  = 0.0;
    _v_tail_c_t    = 0.0;
    _v_tail_c_r    = 0.0;
    _v_tail_tc     = 0.0;
    _v_tail_arm    = 0.0;
    _rudd_area     = 0.0;
    _v_tail_ar     = 0.0;
    _v_tail_tr     = 0.0;
    _t_tail = false;
    _v_tail_rotor = false;

    // landing gear
    _m_gear_l = 0.0;
    _n_gear_l = 0.0;
    _m_gear_wheels = 0;
    _m_gear_struts = 0;
    _n_gear_wheels = 0;
    _gear_fixed   = false;
    _gear_cross   = false;
    _gear_tripod  = false;
    _m_gear_kneel = false;
    _n_gear_kneel = false;

    // engine
    _m_engine = 0.0;

    // rotors
    _m_rotor_r   = 0.0;
    _m_blades_c  = 0.0;
    _m_rotor_rpm = 0.0;
    _m_rotor_gear = 1.0;
    _t_rotor_r   = 0.0;
    _rotor_mcp   = 0.0;
    _m_rotor_tv  = 0.0;
    _m_rotor_nb = 0;

    // RESULTS
    _centerOfMass.set( 0.0, 0.0, 0.0 );

    _inertiaMatrix.set( 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0 );

    _massTotal = 0.0;

    deleteAllComponents();
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::update()
{
    double m = 0.0;
    Vector3 s;
    Matrix3x3 i;

    for ( Components::iterator it = _components.begin(); it != _components.end(); it++ )
    {
        m += (*it)->getMass();
        s += (*it)->getMass() * (*it)->getPosition();
        i += (*it)->getInertia();
    }

    _centerOfMass = ( m > 0.0 ) ? ( s * ( 1.0 / m ) ) : Vector3();
    _inertiaMatrix = i;
    _massTotal = m;
}

////////////////////////////////////////////////////////////////////////////////

Component* Aircraft::getComponent( int index )
{
    Components::iterator it = _components.begin() + index;

    if ( it != _components.end() )
    {
        return (*it);
    }

    return NULLPTR;
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::addComponent( Component *component )
{
    _components.push_back( component );
    update();
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::delComponent( int index )
{
    Components::iterator it = _components.begin() + index;

    if ( it != _components.end() )
    {
        DELPTR( *it );
        _components.erase( it );
    }

    update();
}

////////////////////////////////////////////////////////////////////////////////

void Aircraft::deleteAllComponents()
{
    Components::iterator it = _components.begin();

    while ( it != _components.end() )
    {
        DELPTR( *it );
        it = _components.erase( it );
    }

    update();
}
