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

#include <mass/GearMain.h>

#include <mass/Atmosphere.h>
#include <mass/Units.h>

////////////////////////////////////////////////////////////////////////////////

const char GearMain::xml_tag[] = "gear_main";

////////////////////////////////////////////////////////////////////////////////

double GearMain::computeMass( Type type,
                              double m_empty,
                              double m_max_to,
                              double m_max_land,
                              double nz_max_land,
                              double m_gear_l,
                              double v_stall,
                              int m_gear_wheels,
                              int m_gear_struts,
                              bool navy_aircraft,
                              bool gear_fixed,
                              bool gear_cross,
                              bool gear_tripod,
                              bool m_gear_kneeling )
{
    double w_dg = Units::kg2lb( m_max_to );
    double w_0  = Units::kg2lb( m_empty  );

    // Rayner: Aircraft Design, p.568, table 15.2
    double m1 = 0.0;
    {
        double reduce = gear_fixed ? ( 0.014 * w_0 ) : 0.0;

        if ( type == FighterAttack )
        {
            double coeff = navy_aircraft ? 0.045 : 0.033;
            m1 = 0.85 * Units::lb2kg( coeff * w_dg - reduce );
        }

        if ( type == CargoTransport )
        {
            m1 = 0.85 * Units::lb2kg( 0.043 * w_dg - reduce );
        }

        if ( type == GeneralAviation )
        {
            m1 = 0.85 * Units::lb2kg( 0.057 * w_dg - reduce );
        }

        // NASA TP-2015-218751, p.233
        if ( type == Helicopter )
        {
            m1 = Units::lb2kg( 0.0325 * w_dg );
        }
    }

    double m2 = 0.0;
    {
        double m2_lb = 0.0;

        double w_l = Units::kg2lb( m_max_land );
        double n_l = 1.5 * nz_max_land;

        double l_m_in = Units::m2in( m_gear_l );

        // Rayner: Aircraft Design, p.572, eq.15.5
        if ( type == FighterAttack )
        {
            double k_cb  = gear_cross  ? 2.25  : 1.0;
            double k_tpg = gear_tripod ? 0.826 : 1.0;

            m2_lb = k_cb * k_tpg * pow( w_l * n_l, 0.25 ) * pow( l_m_in, 0.973 );
        }

        // Rayner: Aircraft Design, p.574, eq.15.29
        if ( type == CargoTransport )
        {
            double k_mp = m_gear_kneeling ? 1.126 : 1.0;

            m2_lb = 0.0106 * k_mp * pow( w_l, 0.888 ) * pow( n_l, 0.25 )
                    * pow( l_m_in, 0.4 ) * pow( (double)m_gear_wheels, 0.321 )
                    * pow( (double)m_gear_struts, -0.5 ) * pow( v_stall, 0.1 );
        }

        // Rayner: Aircraft Design, p.576, eq.15.50
        if ( type == GeneralAviation )
        {
            m2_lb = 0.095 * pow( n_l * w_l, 0.768 ) * pow( l_m_in / 12.0, 0.409 );
        }

        // NASA TP-2015-218751, p.233
        if ( type == Helicopter )
        {
            m2_lb = 0.4013 * pow( w_dg, 0.6662 ) * pow ( n_l, 0.536 );
        }

        m2 = Units::lb2kg( m2_lb );
    }

    std::cout << "GearMain:  " << m1 << "  " << m2 << std::endl;

    return ( m1 + m2 ) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////

GearMain::GearMain( const Aircraft *ac ) :
    Component( ac )
{
    setName( "Main Landing Gear" );
}

////////////////////////////////////////////////////////////////////////////////

GearMain::~GearMain() {}

////////////////////////////////////////////////////////////////////////////////

void GearMain::save( QDomDocument *doc, QDomElement *parentNode )
{
    QDomElement node = doc->createElement( GearMain::xml_tag );
    parentNode->appendChild( node );

    saveParameters( doc, &node );
}

////////////////////////////////////////////////////////////////////////////////

double GearMain::getComputedMass() const
{
    return computeMass( _ac->getType(),
                        _ac->getM_empty(),         // double m_empty,
                        _ac->getM_maxTO(),         // double m_max_to,
                        _ac->getM_maxLand(),       // double m_max_land,
                        _ac->getNzMaxLand(),       // double nz_max_land,
                        _ac->getMainGearLength(),  // double m_gear_l,
                        _ac->getStallV(),          // double v_stall,
                        _ac->getMainGearWheels(),  // int m_gear_wheels,
                        _ac->getMainGearStruts(),  // int m_gear_struts,
                        _ac->getNavyAircraft(),    // bool navy_aircraft,
                        _ac->getGearFixed(),       // bool gear_fixed,
                        _ac->getGearCross(),       // bool gear_cross,
                        _ac->getGearTripod(),      // bool gear_tripod,
                        _ac->getGearMainKneel() ); // bool m_gear_kneeling
}
