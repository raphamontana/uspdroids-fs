/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "simulator.h"

Simulator::Simulator(int argc, char * argv[])
{
    exec  = true;
    gui   = false;
    noia1 = false;
    noia2 = false;
    log   = false;
    simulations = 1;
    parser(argc, argv);
    gm = new GameManager(&wm);
    sm = new StrategiesManager(&wm, strategyPort1[0], strategyPort2[0], strategyPort1[1], strategyPort2[1]);
    vm = new ViewersManager(&wm, viewerPort);
}

Simulator::~Simulator()
{
    delete(gm);
    delete(sm);
    delete(vm);
}

void Simulator::parser(int argc, char * argv[])
{
    for (register int i = 1; i < argc; i++) {
        if (!strcmp("-loop", argv[i])) {
            sscanf(argv[++i], "%d", &simulations);
        }
        else if (!strcmp("-v", argv[i]) || !strcmp("--version", argv[i])) {
            puts("USPDroids Football Simulator version 2.5.0");
            exec = false;
        }
        else if (!strcmp("--license", argv[i])) {
            puts("USPDroids Football Simulator version 2.5.0\n");
            puts("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n");
            puts("This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n");
            puts("You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.");
            exec = false;
        }
        else if (!strcmp("-?", argv[i]) || !strcmp("-h", argv[i]) || !strcmp("--help", argv[i])) {
            printf("Unknown argument '%s'\n", argv[i]);
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
            exec = false;
        }
    }
    puts("USPDroids Football Simulator v2.5");
    puts("Copyright (C) 2010 Robot Learning Laboratory.\n");
    if (!exec) {
        emit(quit());
    }
    else if (gui) {
        Q_INIT_RESOURCE(icons);
        FrontEnd * fe = new FrontEnd();
        fe->show();
    }
    else {
        //setPort(26000, 26001, 26002, 26003, 25999);

        QTimer::singleShot(0, this, SLOT(launch()));
    }
}

void Simulator::initialize()
{
    puts("Initializing simulator...");
    wm.chronometer = 0;
    goals[0]    = 0;
    goals[1]    = 0;
    gm->initialize();
    sm->initialize();
    vm->initialize();
    puts("Awaiting strategies connection...");
    sm->waitStrategies();
    sm->transmitData();
    puts("Strategies connected.");
}

void Simulator::execute()
{
    while (simulations-- > 0) {
        QMutex pause;                   // Terminar o pause;
        puts("Match started.");
        unsigned int tenMinutes = 36000;
        while (wm.chronometer < tenMinutes)
        {
            pause.lock();
            sm->recvCommands();
            vm->recvCommands();
            gm->gameStep();
            sm->transmitData();
            vm->transmitData();
            if (wm.chronometer%60 == 0) {
                printf("Time: %dmin %ds\n", wm.chronometer/3600, wm.chronometer%3600/60);
                if (wm.chronometer == 18000) {
                    puts("Second period.");
                    gm->robotRelocation();
                }
            }
            wm.chronometer++;
            pause.unlock();
        }
    }
}

void Simulator::finish()
{
    printf("Time: %dmin %ds\n", wm.chronometer/3600, wm.chronometer%3600/60);
    puts("End of match.");
    printf("Final score: %s %d x %d %s\n", wm.team[0].name.toAscii().data(), goals[0], goals[1], wm.team[1].name.toAscii().data());
    if (goals[0] > goals[1]) {
        printf("%s won.\n", wm.team[0].name.toAscii().data());
    } else if (goals[0] < goals[1]) {
        printf("%s won.\n", wm.team[1].name.toAscii().data());
    } else puts("Draw.");
    puts("Finalizing simulator.");
    gm->finalize();
    sm->finalize();
    vm->finalize();
    puts("Simulator stopped.");
}

void Simulator::launch()
{
    initialize();
    execute();
    finish();
    emit(quit());
}
