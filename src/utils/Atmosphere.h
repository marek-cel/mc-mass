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
#ifndef UTILS_ATMOSPHERE_H_
#define UTILS_ATMOSPHERE_H_

////////////////////////////////////////////////////////////////////////////////

namespace mc
{

/**
 * @brief US Standard Atmosphere class.
 *
 * This class is used to compute altitude depend atmospheric data. It is
 * based on U.S. Standard Atmosphere 1976 extended by user defined sea level
 * conditions. User defined sea level conditions affect only the lowest layer
 * up to 11,000 m above mean sea level.
 * Model is valid up to 84,852 meters above mean sea level.
 *
 * <h3>Refernces:</h3>
 * <ul>
 *   <li><a href="https://ntrs.nasa.gov/citations/19770009539">US Standard Atmosphere 1976, NASA, TM-X-74335</a></li>
 * </ul>
 */
class Atmosphere
{
public:

    /** Gas species indeces. */
    enum GasSpeciesIndeces
    {
        N2 = 0,                         ///< index of Nitrogen       (N2)  in tables _m_i and _f_i
        O2,                             ///< index of Oxygen         (O2)  in tables _m_i and _f_i
        Ar,                             ///< index of Argon          (Ar)  in tables _m_i and _f_i
        CO2,                            ///< index of Carbon Dioxide (C02) in tables _m_i and _f_i
        Ne,                             ///< index of Neon           (Ne)  in tables _m_i and _f_i
        He,                             ///< index of Helium         (He)  in tables _m_i and _f_i
        Kr,                             ///< index of Krypton        (Kr)  in tables _m_i and _f_i
        Xe,                             ///< index of Xenon          (Xe)  in tables _m_i and _f_i
        CH4,                            ///< index of Methane        (CH4) in tables _m_i and _f_i
        H2                              ///< index of Hydrogen       (H2)  in tables _m_i and _f_i
    };

    static const double _m_i[ 10 ];     ///< [kg/kmol] molecular weight
    static const double _f_i[ 10 ];     ///< [-] fractional volume

    static const double _h_b[ 7 ];      ///< [m] altitude values
    static const double _p_b[ 7 ];      ///< [Pa] pressure values
    static const double _t_b[ 7 ];      ///< [K] temperature values
    static const double _l_b[ 7 ];      ///< [K/m] temperature gradients

    static const double _m;             ///< [kg/kmol] mean molecular weight
    static const double _r;             ///< [J/(kmol*K)] universal gas constant
    static const double _s;             ///< [K] Sutherland constant
    static const double _beta;          ///< [kg/(s*m*K^0.5)] a constant used in computing dynamic viscosity
    static const double _gamma;         ///< [-] a constant taken to represent the ratio of specific heat at constant pressure to the specific heat at constant volume (cp/cv)

    static const double _std_sl_t;      ///< [K]  standard sea level temperature (288.15 K or 15 deg C)
    static const double _std_sl_p;      ///< [Pa] standard sea level pressure (1013.25 hPa)
    static const double _std_sl_rho;    ///< [kg/m^3] standard sea level density (1.225 kg/m^3)

    static const double _g;             ///< [m/s^2] standard gravitional acceleration

    static double getDensity( double altitude );

    /** @brief Constructor. */
    Atmosphere();

    /** @brief Destructor. */
    virtual ~Atmosphere();

    /**
     * @brief Updates atmosphere due to altitude.
     * @param altitude [m] altitude above sea level
     */
    virtual void update( double altitude );

    inline double getTemperature()  const { return _temperature;  }
    inline double getPressure()     const { return _pressure;     }
    inline double getDensity()      const { return _density;      }
    inline double getSpeedOfSound() const { return _speedOfSound; }
    inline double getDynViscosity() const { return _dynViscosity; }
    inline double getKinViscosity() const { return _kinViscosity; }

private:

    double _temperature;        ///< [K] air temperature
    double _pressure;           ///< [Pa] air static pressure
    double _density;            ///< [kg/m^3] air density
    double _speedOfSound;       ///< [m/s] speed of sound
    double _dynViscosity;       ///< [Pa*s] dynamic viscosity
    double _kinViscosity;       ///< [m^2/s] kinematic viscosity
};

} // namespace mc

////////////////////////////////////////////////////////////////////////////////

#endif // UTILS_ATMOSPHERE_H_
