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

#include <QtGui/QApplication>
#include "configuration.h"
#include "simulator.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    puts("USPDroids Football Simulator v2.5");
    puts("Copyright (C) 2010 Robot Learning Laboratory.\n");
    Configuration conf = Configuration::parse(argc, argv);
    Simulator uspdroidsfs(conf);
    QObject::connect(&uspdroidsfs, SIGNAL(quit()), &app, SLOT(quit()));
    QTimer::singleShot(0, &uspdroidsfs, SLOT(launch()));
    return(app.exec());
}
