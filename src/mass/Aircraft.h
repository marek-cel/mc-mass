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
#ifndef AIRCRAFT_H
#define AIRCRAFT_H

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <QDomDocument>
#include <QDomElement>

#include <defs.h>
#include <Types.h>

#include <mass/Matrix3x3.h>
#include <mass/Vector3.h>

////////////////////////////////////////////////////////////////////////////////

class Component;

/**
 * @brief The Aircraft class.
 */
class Aircraft
{
public:

    typedef std::vector< Component* > Components;

    Aircraft();

    virtual ~Aircraft();

    /**
     * @brief read
     * @param parentNode
     * @return returns true on success and false on failure
     */
    bool read( QDomElement *parentNode );

    /**
     * Saves aircraft data.
     * @param doc
     * @param parentNode
     */
    void save( QDomDocument *doc, QDomElement *parentNode );

    /**
     * @brief Resets aircraft data. Removes all components.
     */
    void reset();

    /**
     * @brief Updates output data (total mass, cg position, inertia).
     */
    void update();

    inline const Components& getComponents() const { return _components; }

    Component* getComponent( int index );
    void addComponent( Component *component );
    void delComponent( int index );

    inline Vector3   getCenterOfMass  () const { return _centerOfMass;  }
    inline Matrix3x3 getInertiaMatrix () const { return _inertiaMatrix; }
    inline double    getMassTotal     () const { return _massTotal;     }

    inline Type getType() const { return _type; }

    // general

    inline double getM_empty   () const { return _m_empty    ; }
    inline double getM_maxTO   () const { return _m_maxTO    ; }
    inline double getM_maxLand () const { return _m_maxLand  ; }
    inline double getNzMax     () const { return _nz_max     ; }
    inline double getNzMaxLand () const { return _nz_maxLand ; }
    inline double getStallV    () const { return _stall_v    ; }
    inline double getCruiseH   () const { return _h_cruise   ; }
    inline double getCruiseV   () const { return _v_cruise   ; }
    inline double getMachMax   () const { return _mach_max   ; }

    inline bool getNavyAircraft() const { return _navy_ac; }

    // fuselage

    inline CargoDoor getCargoDoor() const { return _cargo_door; }

    inline double getFuseLength () const { return _fuse_l; }
    inline double getFuseHeight () const { return _fuse_h; }
    inline double getFuseWidth  () const { return _fuse_w; }
    inline double getNoseLength () const { return _nose_l; }

    inline double getWettedArea () const { return _wetted_area ; }
    inline double getPressVol   () const { return _press_vol   ; }
    inline bool getFuselageLG () const { return _fuselage_lg; }
    inline bool getCargoRamp  () const { return _cargo_ramp;  }

    // wing

    inline double getWingArea  () const  { return _wing_area  ; }
    inline double getWingExp   () const  { return _wing_exp   ; }
    inline double getWingSpan  () const  { return _wing_span  ; }
    inline double getWingSweep () const  { return _wing_sweep ; }
    inline double getWingCT    () const  { return _wing_c_t   ; }
    inline double getWingCR    () const  { return _wing_c_r   ; }
    inline double getWingAR    () const  { return _wing_ar    ; }
    inline double getWingTR    () const  { return _wing_tr    ; }
    inline double getWingTC    () const  { return _wing_tc    ; }
    inline double getWingFuel  () const  { return _wing_fuel  ; }
    inline double getCtrlArea  () const  { return _ctrl_area  ; }
    inline bool getWingDelta () const { return _wing_delta ; }
    inline bool getWingVar   () const { return _wing_var   ; }

    // horizontal tail

    inline double getHorTailArea  () const { return _h_tail_area  ; }
    inline double getHorTailSpan  () const { return _h_tail_span  ; }
    inline double getHorTailSweep () const { return _h_tail_sweep ; }
    inline double getHorTailCT    () const { return _h_tail_c_t   ; }
    inline double getHorTailCR    () const { return _h_tail_c_r   ; }
    inline double getHorTailTC    () const { return _h_tail_tc    ; }
    inline double getElevArea     () const { return _elev_area    ; }
    inline double getHorTailFW    () const { return _h_tail_fw    ; }
    inline double getHorTailArm   () const { return _h_tail_arm   ; }
    inline double getHorTailAR    () const { return _h_tail_ar    ; }
    inline double getHorTailTR    () const { return _h_tail_tr    ; }

    inline bool getHorTailMoving  () const { return _h_tail_moving;  }
    inline bool getHorTailRolling () const { return _h_tail_rolling; }

    // vertical tail

    inline double getVerTailArea   () const { return _v_tail_area   ; }
    inline double getVerTailHeight () const { return _v_tail_height ; }
    inline double getVerTailSweep  () const { return _v_tail_sweep  ; }
    inline double getVerTailCR     () const { return _v_tail_c_t    ; }
    inline double getVerTailCT     () const { return _v_tail_c_r    ; }
    inline double getVerTailTC     () const { return _v_tail_tc     ; }
    inline double getVerTailArm    () const { return _v_tail_arm    ; }
    inline double getRuddArea      () const { return _rudd_area     ; }
    inline double getVerTailAR     () const { return _v_tail_ar     ; }
    inline double getVerTailTR     () const { return _v_tail_tr     ; }

    inline bool getTailT() const { return _t_tail; }

    inline bool getVerTailRotor() const { return _v_tail_rotor; }

    // landing gear

    inline double getMainGearLength () const { return _m_gear_l; }
    inline double getNoseGearLength () const { return _n_gear_l; }

    inline int getMainGearWheels () const { return _m_gear_wheels; }
    inline int getMainGearStruts () const { return _m_gear_struts; }
    inline int getNoseGearWheels () const { return _n_gear_wheels; }

    inline bool getGearFixed  () const { return _gear_fixed;  }
    inline bool getGearCross  () const { return _gear_cross;  }
    inline bool getGearTripod () const { return _gear_tripod; }

    inline bool getGearMainKneel () const { return _m_gear_kneel; }
    inline bool getGearNoseKneel () const { return _n_gear_kneel; }

    // engine

    inline double getEngineMass() const { return _m_engine; }

    // rotors

    inline double getMainRotorRad    () const { return _m_rotor_r   ; }
    inline double getMainRotorChord  () const { return _m_blades_c  ; }
    inline double getMainRotorRPM    () const { return _m_rotor_rpm ; }
    inline double getMainRotorGear   () const { return _m_rotor_gear; }
    inline double getTailRotorRad    () const { return _t_rotor_r   ; }
    inline double getPowerLimit      () const { return _rotor_mcp   ; }
    inline double getMainRotorTipVel () const { return _m_rotor_tv  ; }

    inline int getMainRotorBlades() const { return _m_rotor_nb ; }


    inline void setType( Type type ) { _type = type; }

    // general

    inline void setM_empty   ( double m_empty   ) { _m_empty    = m_empty   ; }
    inline void setM_maxTO   ( double m_maxto   ) { _m_maxTO    = m_maxto   ; }
    inline void setM_maxLand ( double m_maxLand ) { _m_maxLand  = m_maxLand ; }
    inline void setNzMax     ( double nz_max    ) { _nz_max     = nz_max    ; }
    inline void setNzMaxLand ( double nz_max    ) { _nz_maxLand = nz_max    ; }
    inline void setStallV    ( double stall_v   ) { _stall_v    = stall_v   ; }
    inline void setCruiseH   ( double h_cruise  ) { _h_cruise   = h_cruise  ; }
    inline void setCruiseV   ( double v_cruise  ) { _v_cruise   = v_cruise  ; }
    inline void setMachMax   ( double mach_max  ) { _mach_max   = mach_max  ; }

    inline void setNavyAircraft( bool navy_ac) { _navy_ac = navy_ac; }

    // fuselage

    inline void setCargoDoor( CargoDoor cargo_door ) { _cargo_door = cargo_door; }

    inline void setFuseLength ( double fuse_l ) { _fuse_l = fuse_l; }
    inline void setFuseHeight ( double fuse_h ) { _fuse_h = fuse_h; }
    inline void setFuseWidth  ( double fuse_w ) { _fuse_w = fuse_w; }
    inline void setNoseLength ( double nose_l ) { _nose_l = nose_l; }

    inline void setWettedArea ( double wetted_area ) { _wetted_area = wetted_area ; }
    inline void setPressVol   ( double press_vol   ) { _press_vol   = press_vol   ; }
    inline void setFuselageLG ( bool fuselage_lg ) { _fuselage_lg = fuselage_lg ; }
    inline void setCargoRamp  ( bool cargo_ramp  ) { _cargo_ramp  = cargo_ramp  ; }

    // wing

    inline void setWingArea  ( double wing_area  ) { _wing_area  = wing_area  ; }
    inline void setWingExp   ( double wing_exp   ) { _wing_exp   = wing_exp   ; }
    inline void setWingSpan  ( double wing_span  ) { _wing_span  = wing_span  ; }
    inline void setWingSweep ( double wing_sweep ) { _wing_sweep = wing_sweep ; }
    inline void setWingCT    ( double wing_c_t   ) { _wing_c_t   = wing_c_t   ; }
    inline void setWingCR    ( double wing_c_r   ) { _wing_c_r   = wing_c_r   ; }
    inline void setWingAR    ( double wing_ar    ) { _wing_ar    = wing_ar    ; }
    inline void setWingTR    ( double wing_tr    ) { _wing_tr    = wing_tr    ; }
    inline void setWingTC    ( double wing_tc    ) { _wing_tc    = wing_tc    ; }
    inline void setWingFuel  ( double wing_fuel  ) { _wing_fuel  = wing_fuel  ; }
    inline void setCtrlArea  ( double ctrl_area  ) { _ctrl_area  = ctrl_area  ; }
    inline void setWingDelta ( bool wing_delta ) { _wing_delta = wing_delta ; }
    inline void setWingVar   ( bool wing_var   ) { _wing_var   = wing_var   ; }

    // horizontal tail

    inline void setHorTailArea  ( double h_tail_area  ) { _h_tail_area  = h_tail_area  ; }
    inline void setHorTailSpan  ( double h_tail_span  ) { _h_tail_span  = h_tail_span  ; }
    inline void setHorTailSweep ( double h_tail_sweep ) { _h_tail_sweep = h_tail_sweep ; }
    inline void setHorTailCT    ( double h_tail_c_t   ) { _h_tail_c_t   = h_tail_c_t   ; }
    inline void setHorTailCR    ( double h_tail_c_r   ) { _h_tail_c_r   = h_tail_c_r   ; }
    inline void setHorTailTC    ( double h_tail_tc    ) { _h_tail_tc    = h_tail_tc    ; }
    inline void setElevArea     ( double elev_area    ) { _elev_area    = elev_area    ; }
    inline void setHorTailFW    ( double h_tail_fw    ) { _h_tail_fw    = h_tail_fw    ; }
    inline void setHorTailArm   ( double h_tail_arm   ) { _h_tail_arm   = h_tail_arm   ; }
    inline void setHorTailAR    ( double h_tail_ar    ) { _h_tail_ar    = h_tail_ar    ; }
    inline void setHorTailTR    ( double h_tail_tr    ) { _h_tail_tr    = h_tail_tr    ; }

    inline void setHorTailMoving  ( bool h_tail_moving  ) { _h_tail_moving  = h_tail_moving  ; }
    inline void setHorTailRolling ( bool h_tail_rolling ) { _h_tail_rolling = h_tail_rolling ; }

    // vertical tail

    inline void setVerTailArea   ( double v_tail_area   ) { _v_tail_area   = v_tail_area   ; }
    inline void setVerTailHeight ( double v_tail_height ) { _v_tail_height = v_tail_height ; }
    inline void setVerTailSweep  ( double v_tail_sweep  ) { _v_tail_sweep  = v_tail_sweep  ; }
    inline void setVerTailCR     ( double v_tail_c_t    ) { _v_tail_c_t    = v_tail_c_t    ; }
    inline void setVerTailCT     ( double v_tail_c_r    ) { _v_tail_c_r    = v_tail_c_r    ; }
    inline void setVerTailTC     ( double v_tail_tc     ) { _v_tail_tc     = v_tail_tc     ; }
    inline void setVerTailArm    ( double v_tail_arm    ) { _v_tail_arm    = v_tail_arm    ; }
    inline void setRuddArea      ( double rudd_area     ) { _rudd_area     = rudd_area     ; }
    inline void setVerTailAR     ( double v_tail_ar     ) { _v_tail_ar     = v_tail_ar     ; }
    inline void setVerTailTR     ( double v_tail_tr     ) { _v_tail_tr     = v_tail_tr     ; }

    inline void setTailT( bool t_tail ) { _t_tail = t_tail; }

    inline void setVerTailRotor( bool v_tail_rotor ) { _v_tail_rotor = v_tail_rotor; }

    // landing gear

    inline void setMainGearLength ( double m_gear_l ) { _m_gear_l = m_gear_l; }
    inline void setNoseGearLength ( double n_gear_l ) { _n_gear_l = n_gear_l; }

    inline void setMainGearWheels ( int m_gear_wheels ) { _m_gear_wheels = m_gear_wheels; }
    inline void setMainGearStruts ( int m_gear_struts ) { _m_gear_struts = m_gear_struts; }
    inline void setNoseGearWheels ( int n_gear_wheels ) { _n_gear_wheels = n_gear_wheels; }

    inline void setGearFixed  ( bool gear_fixed  ) { _gear_fixed  = gear_fixed  ; }
    inline void setGearCross  ( bool gear_cross  ) { _gear_cross  = gear_cross  ; }
    inline void setGearTripod ( bool gear_tripod ) { _gear_tripod = gear_tripod ; }

    inline void setGearMainKneel ( bool m_gear_kneel ) { _m_gear_kneel = m_gear_kneel; }
    inline void setGearNoseKneel ( bool n_gear_kneel ) { _n_gear_kneel = n_gear_kneel; }

    // engine

    inline void setEngineMass( double m_engine ) { _m_engine = m_engine; }

    // rotors

    inline void setMainRotorRad    ( double m_rotor_r    ) { _m_rotor_r    = m_rotor_r    ; }
    inline void setMainRotorChord  ( double m_blades_c   ) { _m_blades_c   = m_blades_c   ; }
    inline void setMainRotorRPM    ( double m_rotor_rpm  ) { _m_rotor_rpm  = m_rotor_rpm  ; }
    inline void setMainRotorGear   ( double m_rotor_gear ) { _m_rotor_gear = m_rotor_gear ; }
    inline void setTailRotorRad    ( double t_rotor_r    ) { _t_rotor_r    = t_rotor_r    ; }
    inline void setPowerLimit      ( double rotor_mcp    ) { _rotor_mcp    = rotor_mcp    ; }
    inline void setMainRotorTipVel ( double m_rotor_tv   ) { _m_rotor_tv   = m_rotor_tv   ; }

    inline void setMainRotorBlades( int m_rotor_nb ) { _m_rotor_nb = m_rotor_nb ; }

private:

    Components _components;     ///< mass components

    Type _type;                 ///< [-] aircraft type

    // DATA

    // General
    double _m_empty;            ///< [kg] empty mass
    double _m_maxTO;            ///< [kg] maximum take-off mass
    double _m_maxLand;          ///< [kg] maximum landing mass
    double _nz_max;             ///< [-] Nz max
    double _nz_maxLand;         ///< [-] Nz max (landing)
    double _stall_v;            ///< [kts] stall speed
    double _h_cruise;           ///< [ft]  cruise altitude
    double _v_cruise;           ///< [kts] cruise speed
    double _mach_max;           ///< [-] maximum design Mach number

    bool _navy_ac;              ///< specifies if aircraft is navy carrier aircraft

    // Fuselage
    CargoDoor _cargo_door;      ///< cargo door type

    double _fuse_l;             ///< [m] fuselage length
    double _fuse_h;             ///< [m] fuselage height
    double _fuse_w;             ///< [m] fuselage width
    double _nose_l;             ///< [m] nose length

    double _wetted_area;        ///< [m^2] fuselage wetted area
    double _press_vol;          ///< [m^3] volume of pressurized section
    bool _fuselage_lg;          ///< specifies if main landing gear is fuselage mounted
    bool _cargo_ramp;           ///< specifies if helicopter has a cargo ramp

    // Wing
    double _wing_area;          ///< [m^2] wing area
    double _wing_exp;           ///< [m^2] wing exposed area
    double _wing_span;          ///< [m] wing span
    double _wing_sweep;         ///< [deg] wing sweep at 25% chord
    double _wing_c_t;           ///< [m] wing tip chord
    double _wing_c_r;           ///< [m] wing root chord
    double _wing_ar;            ///< [-] wing aspect ratio
    double _wing_tr;            ///< [-] wing taper ratio
    double _wing_tc;            ///< [-] wing thickness ratio
    double _wing_fuel;          ///< [kg] wing fuel capacity
    double _ctrl_area;          ///< [m^2] wing mounted control surface area
    bool _wing_delta;           ///< specifies if delta wing
    bool _wing_var;             ///< specifies if wing has variable sweep

    // Horizontal Tail
    double _h_tail_area;        ///< [m^2] horizontal tail area
    double _h_tail_span;        ///< [m] horizontal tail span
    double _h_tail_sweep;       ///< [deg] horizontal tail sweep at 25% MAC
    double _h_tail_c_t;         ///< [m] horizontal tail tip chord
    double _h_tail_c_r;         ///< [m] horizontal tail root chord
    double _h_tail_tc;          ///< [-] horizontal tail thickness ratio
    double _elev_area;          ///< [m^2] elevator area
    double _h_tail_fw;          ///< [m] fuselage width at horizontal tail intersection
    double _h_tail_arm;         ///< [m] horizontal tail arm
    double _h_tail_ar;          ///< [-] horizontal tail aspect ratio
    double _h_tail_tr;          ///< [-] horizontal tail taper ratio

    bool _h_tail_moving;        ///< specifies if horizontal tail is all moving
    bool _h_tail_rolling;       ///< specifies if horizontal tail is rolling

    // Vertical Tail
    double _v_tail_area;        ///< [m^2] vertical tail area
    double _v_tail_height;      ///< [m] vertical tail height
    double _v_tail_sweep;       ///< [deg] vertical tail sweep at 25% MAC
    double _v_tail_c_t;         ///< [m] vertical tail tip chord
    double _v_tail_c_r;         ///< [m] vertical tail root chord
    double _v_tail_tc;          ///< [-] vertical tail thickness ratio
    double _v_tail_arm;         ///< [m] vertical tail arm
    double _rudd_area;          ///< [m^2] rudder area
    double _v_tail_ar;          ///< [-] vertical tail aspect ratio
    double _v_tail_tr;          ///< [-] vertical tail taper ratio

    bool _t_tail;               ///< specifies if T-tail
    bool _v_tail_rotor;         ///< specifies if tail rotor is mounted on the vertical tail

    // Landing Gear
    double _m_gear_l;           ///< [m] extended main gear length
    double _n_gear_l;           ///< [m] extended nose gear length

    int _m_gear_wheels;         ///< main gear wheels number
    int _m_gear_struts;         ///< main gear struts number
    int _n_gear_wheels;         ///< nose gear wheels number

    bool _gear_fixed;           ///< specifies if gear is fixed
    bool _gear_cross;           ///< specifies if gear has a cross-beam (like F-111)
    bool _gear_tripod;          ///< specifies if gear is a tripod (like A-7)

    bool _m_gear_kneel;         ///< specifies if main gear is kneeling
    bool _n_gear_kneel;         ///< specifies if nose gear is kneeling

    // Engine
    double _m_engine;           ///< [kg] engine mass

    // Rotors
    double _m_rotor_r;          ///< [m]   main rotor radius
    double _m_blades_c;         ///< [m]   main rotor blades chord
    double _m_rotor_rpm;        ///< [rpm] main rotor rotation speed
    double _m_rotor_gear;       ///< [-]   main rotor gearing ratio
    double _t_rotor_r;          ///< [m]   tail rotor radius
    double _rotor_mcp;          ///< [hp]  drive system power limit (MCP)
    double _m_rotor_tv;         ///< [m/s] main rotor blade tip velocity

    int _m_rotor_nb;            ///< number of main rotor blades

    // RESULTS

    Vector3   _centerOfMass;    ///< [m] center of mass position
    Matrix3x3 _inertiaMatrix;   ///< [kg*m^2] inertia
    double _massTotal;          ///< [kg]


    void deleteAllComponents();
};

////////////////////////////////////////////////////////////////////////////////

#endif // AIRCRAFT_H
