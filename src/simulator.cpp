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
    if (!conf.exec) {
        emit(quit());
    }
    else if (conf.gui) {
        Q_INIT_RESOURCE(icons);
        FrontEnd * fe = new FrontEnd();
        fe->show();
    }
    else {
        QTimer::singleShot(0, this, SLOT(launch()));
    }
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
    while (conf.simulations-- > 0) {
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
