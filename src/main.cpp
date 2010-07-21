/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The USPDroids Football Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the USPDroids Football Simulator.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtCore/QCoreApplication>
#include "launcher.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    Launcher launcher(argc, argv);
    QTimer::singleShot(0, &launcher, SLOT(launch()));
    QTimer::singleShot(0, &app, SLOT(quit()));
    return(app.exec());
}
