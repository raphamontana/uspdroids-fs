/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "simulator.h"

Simulator::Simulator(quint16 port0, quint16 port1, quint16 viewerPort)
{
    gm = new GameManager(&wm);
    sm = new StrategiesManager(&wm, port0, port1);
    vm = new ViewersManager(&wm, viewerPort);
}

Simulator::~Simulator()
{
    delete(gm);
    delete(sm);
    delete(vm);
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
