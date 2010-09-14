/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "simulator.h"

Simulator::Simulator(Configuration conf)
{
    this->conf = conf;
    isPaused = false;
    gm = new GameManager(&wm);
    sm = new StrategiesManager(&wm, conf.strategyPort1[0], conf.strategyPort2[0], conf.strategyPort1[1], conf.strategyPort2[1]);
    vm = new ViewersManager(&wm, conf.viewerPort);
}

Simulator::~Simulator()
{
    delete(gm);
    delete(sm);
    delete(vm);
}

void Simulator::initialise()
{
    puts("Initialising simulator...");
    gm->initialise();
    sm->initialise();
    vm->initialise();
    puts("Awaiting strategies connection...");
    sm->waitStrategies();
    puts("Strategies connected.");
    //sm->transmitData();
}

void Simulator::execute()
{
    quint32 chronometer;
    const unsigned int tenMinutes = 36000;        /// = 60fps * 60s * 10min
    while (conf.simulations-- > 0) {
        chronometer = 0;
        goals[0]    = 0;
        goals[1]    = 0;
        puts("Match started.");
        puts("First period.");
        gm->robotRelocation(Normal, chronometer);
        while (chronometer < tenMinutes) {
            pauseLock.lock();
            if (chronometer%60 == 0) {
                printf("Time: %dmin %ds\n", chronometer/3600, chronometer%3600/60);
                if (chronometer == 18000) {
                    puts("Second period.");
                    gm->robotRelocation(Normal, chronometer);
                }
            }
            sm->transmitData();
            vm->transmitData();
            gm->gameStep(0.008); /// Vision processing time: Simulate the delay between the image capture and the message received from the strategy.
            sm->recvCommands();
            vm->recvCommands();
            gm->gameStep(0.008);
            // Insert referee here!!!
            chronometer++;
            pauseLock.unlock();
        }
        puts("Time: 10min 0s");
        puts("End of match.");
        printf("Final score: %s %d x %d %s\n", sm->getTeamName(0), goals[0], goals[1], sm->getTeamName(1));
        if (goals[0] > goals[1]) {
            printf("%s won.\n", sm->getTeamName(0));
        } else if (goals[0] < goals[1]) {
            printf("%s won.\n", sm->getTeamName(1));
        } else puts("Draw.");
    }
}

void Simulator::finish()
{
    puts("Finalizing simulator.");
    gm->finalize();
    sm->finalize();
    vm->finalize();
    puts("Simulator stopped.");
}

void Simulator::launch()
{
    initialise();
    //execute();
    //finish();
    emit(quit());
}

void Simulator::pause()
{
    if (isPaused) {
        isPaused = false;
        pauseLock.unlock();
    }
    else {
        pauseLock.lock();
        isPaused = true;
    }
}
