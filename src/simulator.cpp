/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "simulator.h"

Simulator::Simulator(unsigned int portToListen0, unsigned int portToListen1, unsigned int viewerPort)
{
    gm = new GameManager(&wm);
    sm = new StrategiesManager(&wm, portToListen0, portToListen1);
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
    chronometer = 0;
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
    puts("Match started.");
    unsigned int tenMinutes = 36000;
    while (chronometer < tenMinutes)
    {
        sm->recvCommands();
        vm->recvCommands();
        gm->gameStep();
        sm->transmitData();
        vm->transmitData();
        if (chronometer%60 == 0) {
            printf("Time: %dmin %ds\n", chronometer/3600, chronometer%3600/60);
        }
        chronometer++;
    }
}

void Simulator::finish()
{
    printf("Time: %dmin %ds\n", chronometer/3600, chronometer%3600/60);
    puts("End of match.");
    printf("Final score: %s %d x %d %s\n", teamName[0].toAscii().data(), goals[0], goals[1], teamName[1].toAscii().data());
    if (goals[0] > goals[1]) {
        printf("%s won.\n", teamName[0].toAscii().data());
    } else if (goals[0] < goals[1]) {
        printf("%s won.\n", teamName[1].toAscii().data());
    } else puts("Draw.");
    puts("Finalizing simulator.");
    gm->finalize();
    sm->finalize();
    vm->finalize();
    teamName[0].clear();
    teamName[1].clear();
    puts("Simulator stopped.");
}
