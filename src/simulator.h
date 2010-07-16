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

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "gamemanager.h"
#include "strategymanager.h"
#include "viewermanager.h"
#include "worldmodel.h"

class Simulator
{
public:

    Simulator(unsigned int portToListen0, unsigned int portToListen1, unsigned int viewerPort)
    {
        gm = new GameManager(&wm);
        sm = new StrategyManager(&wm, portToListen0, portToListen1);
        vm = new ViewerManager(&wm, viewerPort);
    }

    ~Simulator()
    {
        delete(gm);
        delete(sm);
        delete(vm);
    }

    void initialize()
    {
        chronometer = 0;
        goals[0]    = 0;
        goals[1]    = 0;
        gm->initialize();
        sm->initialize();
        vm->initialize();
        puts("Simulator started.");
        puts("Awaiting strategies connection...");
        sm->waitStrategies();
        sm->transmitData();
        puts("Strategies connected.");
    }

    void execute()
    {
        unsigned int tenMinutes = 36000;
        puts("Match started.");
        while (chronometer < tenMinutes)
        {
            vm->recvCommands();
            sm->recvCommands();
            gm->gameStep();
            sm->transmitData();
            vm->transmitData();
            if (chronometer%60 == 0) {
                printf("Time: %dmin %ds\n", chronometer/3600, chronometer%3600/60);
            }
            chronometer++;
        }
    }

    void finish()
    {
        printf("Time: %dmin %ds\n", chronometer/3600, chronometer%3600/60);
        puts("End of match.");
        printf("Final score: %s %d x %d %s\n", teamName[0].toAscii().data(), goals[0], goals[1], teamName[1].toAscii().data());
        if (goals[0] > goals[1]) {
            printf("%s won.\n", teamName[0].toAscii().data());
        } else if (goals[0] < goals[1]) {
            printf("%s won.\n", teamName[1].toAscii().data());
        } else puts("Draw.");
        gm->finalize();
        sm->finalize();
        vm->finalize();
        if (teamName[0] != NULL) teamName[0].clear();
        if (teamName[1] != NULL) teamName[1].clear();
        puts("Simulator stopped.");
    }

private:

    WorldModel wm;

    GameManager * gm;

    StrategyManager * sm;

    ViewerManager * vm;

    unsigned int chronometer;

    unsigned int goals[2];

    QString teamName[2];

};

#endif // SIMULATOR_H
