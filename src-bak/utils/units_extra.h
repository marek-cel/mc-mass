#ifndef MC_MASS_UTILS_UNITS_EXTRA_H_
#define MC_MASS_UTILS_UNITS_EXTRA_H_

#include <units.h>

namespace units {

//------------------------------
//	PRESSURE UNITS
//------------------------------
#if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_PRESSURE_UNITS)
    UNIT_ADD(pressure, pounds_per_square_foot, pounds_per_square_foot, psf, compound_unit<force::pounds, inverse<squared<length::foot>>>)
#endif

//------------------------------
//	MOMENT OF INERIA UNITS
//------------------------------
#if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_MOMENT_OF_INERTIA_UNITS)
    UNIT_ADD(moment_of_inertia, kilogram_square_meter, kilogram_square_meter, kg_m2, compound_unit<mass::kilogram, squared<length::meter>>)
    UNIT_ADD(moment_of_inertia, slug_square_feet, slug_square_feet, slug_ft2, compound_unit<mass::slug, squared<length::feet>>)
#endif

//------------------------------
//	FIRST MOMENT OF MASS
//------------------------------
#if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_FIRST_MOMENT_OF_MASS_UNITS)
    UNIT_ADD(first_moment_of_mass, kilogram_meter, kilogram_meter, kg_m, compound_unit<mass::kilogram, length::meter>)
    UNIT_ADD(first_moment_of_mass, slug_feet, slug_feet, slug_ft, compound_unit<mass::slug, length::feet>)
#endif

//------------------------------
//	TEMPERATURE GRADIENT
//------------------------------
#if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_TEMPERATURE_GRADIENT_UNITS)
    UNIT_ADD(temperature_gradient, kelvins_per_kilometer, kelvins_per_kilometer, K_per_km, compound_unit<temperature::kelvin, inverse<length::kilometer>>)
#endif

namespace angular_velocity {
using rpm_t = revolutions_per_minute_t;
} // namespace angular_velocity

} // namespace units

#endif // MC_MASS_UTILS_UNITS_EXTRA_H_
