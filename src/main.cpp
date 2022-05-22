/****************************************************************************//*
 *  Copyright (C) 2022 Marek M. Cel
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

#include <QApplication>

#include <defs.h>

#include <gui/MainWindow.h>

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    setlocale( LC_ALL, "C" );

    QLocale::setDefault( QLocale::system() );

    QApplication *app = new QApplication( argc, argv );

    app->setApplicationName    ( APP_NAME   );
    app->setApplicationVersion ( APP_VER    );
    app->setOrganizationDomain ( ORG_DOMAIN );
    app->setOrganizationName   ( ORG_NAME   );

    mc::MainWindow *win = new mc::MainWindow();
    win->show();
    
    int result = app->exec();

    if ( win ) { delete win; } win = nullptr;
    if ( app ) { delete app; } app = nullptr;

    return result;
}
