/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "configuration.h"

Configuration::Configuration()
{
    exec  = true;
    gui   = false;
    noia1 = false;
    noia2 = false;
    log   = false;
    simulations = 1;
    viewerPort = 25999;
    strategyPort1[0] = 26000;
    strategyPort1[1] = 26001;
    strategyPort2[0] = 26002;
    strategyPort2[1] = 26003;
}

Configuration Configuration::parse(int argc, char * argv[])
{
    Configuration conf;
    for (register int i = 1; i < argc; i++) {
        if (!strcmp("-loop", argv[i])) {
            sscanf(argv[++i], "%d", &conf.simulations);
        }
        else if (!strcmp("-v", argv[i]) || !strcmp("--version", argv[i])) {
            puts("USPDroids Football Simulator version 2.5.0");
            conf.exec = false;
        }
        else if (!strcmp("--license", argv[i])) {
            puts("USPDroids Football Simulator version 2.5.0\n");
            puts("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n");
            puts("This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n");
            puts("You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.");
            conf.exec = false;
        }
        else if (!strcmp("-?", argv[i]) || !strcmp("-h", argv[i]) || !strcmp("--help", argv[i])) {
            printf("Unknown argument '%s'\n", argv[i]);
        } else {
            puts("Use:");
            puts("  uspdroidsss [OPTIONS...]\n");
            puts("USPDroids Football Simulator version 2.5.0\n");
            puts("Help options:");
            puts("  -?, -h, --help\t\tShow the help options");
            puts("Application options:");
            puts("  -v, --version\t\t\tShow the version information and finish");
            puts("  --license\t\t\tShow information about the license and close");
            puts("  -noai1\t\t\tStart the team 1 without AI");
            puts("  -noai2\t\t\tStart the team 2 without AI");
            puts("  -loop <integer>\t\tNumber of simulations desired");
            conf.exec = false;
        }
    }
    return(conf);
}

bool Configuration::isConfOK()
{
    return(exec);
}

bool Configuration::useGUI()
{
    return(gui);
}
