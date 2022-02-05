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
#ifndef DEFS_H_
#define DEFS_H_

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

#define APP_NAME   "mc-mass"
#define APP_VER    "1.0"
#define ORG_NAME   "Marek_Cel"
#define ORG_DOMAIN "marekcel.pl"

////////////////////////////////////////////////////////////////////////////////

#define APP_TITLE "MC-Mass"

////////////////////////////////////////////////////////////////////////////////

#ifndef DELPTR
#define DELPTR( ptr ) \
{ \
    if ( ptr ) delete ptr; \
    ptr = nullptr; \
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef DELTAB
#define DELTAB( ptr ) \
{ \
    if ( ptr ) delete [] ptr; \
    ptr = nullptr; \
}
#endif

////////////////////////////////////////////////////////////////////////////////

#endif // DEFS_H_
