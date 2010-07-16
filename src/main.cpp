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

#include "simulator.h"

int main(int argc, char* argv[])
{
    Simulator * uspds;
    bool waitPlayCommand = false;             //Correct this after GUI insertion
    int loop = 1;
    for (register int i = 1; i < argc; i++) {
        if (!strcmp("-loop", argv[i])) {
            sscanf(argv[++i], "%d", &loop);
        }
        else if (!strcmp("-nowait", argv[i])) {
            waitPlayCommand = false;
        }
        else if (!strcmp("-v", argv[i]) || !strcmp("--version", argv[i])) {
            puts("USPDroids Soccer Simulator version 2.5.0");
            return(0);
        }
        else if (!strcmp("--license", argv[i])) {
            puts("USPDroids Football Simulator version 2.5.0\n");
            puts("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n");
            puts("This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n");
            puts("You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.");
            return(0);
        }
        else if (!strcmp("-?", argv[i]) || !strcmp("-h", argv[i]) || !strcmp("--help", argv[i])) {
            printf("Argumento '%s' desconhecido\n", argv[i]);
        } else {
            puts("Use:");
            puts("  uspds [OPTIONS...]\n");
            puts("Robot Football Simulator\n");
            puts("Help options:");
            puts("  -?, -h, --help\t\tShow the help options");
            puts("Application options:");
            puts("  -v, --version\t\t\tShow the version information and finish");
            puts("  --license\t\t\tShow information about the license and close");
            puts("  -noai1\t\t\tStart the team 1 without AI");
            puts("  -noai2\t\t\tStart the team 1 without AI");
            puts("  -loop <integer>\t\tNumber of simulations desired");
            return(0);
        }
    }
    uspds = new Simulator(26000, 26001, 25999);
    while (loop-- > 0) {
        uspds->initialize();
        if (waitPlayCommand) {
            //lock();
        }
        uspds->execute();
        uspds->finish();
    }
    delete(uspds);
    return 0;
}
