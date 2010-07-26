/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "strategiesmanager.h"

StrategiesManager::StrategiesManager(WorldModel * wm, quint16 port0, quint16 port1)
{
    this->wm = wm;
    sc[0] = new StrategyConnection(port0);
    sc[1] = new StrategyConnection(port1);
}

void StrategiesManager::initialize()
{
    sc[0]->start();
    sc[1]->start();
}

void StrategiesManager::waitStrategies() {
    sc[0]->wait();
    sc[1]->wait();
    //wm->team[0].name = sc[0]->getTeamName();
}

void StrategiesManager::recvCommands()
{
    sc[0]->start();
    sc[1]->start();
    sc[0]->wait();
    sc[1]->wait();
    decodeMessage(0, sc[0]->getMessage());
    decodeMessage(1, sc[1]->getMessage());
}

void StrategiesManager::transmitData()
{
    QByteArray message;
    sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
            wm->ball.x, wm->ball.y,
            wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
            wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
            wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy,
            wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
            wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
            wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy);
    sc[0]->setMessageToSend(message);
    sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
            wm->ball.x, wm->ball.y,
            wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
            wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
            wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy,
            wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
            wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
            wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy);
    sc[1]->setMessageToSend(message);
    sc[0]->start();
    sc[1]->start();
    sc[0]->wait();
    sc[1]->wait();
}

void StrategiesManager::finalize()
{
    sc[0]->disconnectStrategy();
    sc[1]->disconnectStrategy();
}

void StrategiesManager::decodeMessage(int strategy, QByteArray message)
{
    int read;
    read = sscanf(message.data(), "%d %d %d %d %d %d",
           &wm->team[strategy].robot[0].leftWheel, &wm->team[strategy].robot[0].rightWheel,
           &wm->team[strategy].robot[1].leftWheel, &wm->team[strategy].robot[1].rightWheel,
           &wm->team[strategy].robot[2].leftWheel, &wm->team[strategy].robot[2].rightWheel);
    if (read != 6) {
        qWarning("Badly-formed message received from strategy.");
    }
    else {
        wm->team[strategy].robot[0].normalizeWheelsSpeeds();
        wm->team[strategy].robot[1].normalizeWheelsSpeeds();
        wm->team[strategy].robot[2].normalizeWheelsSpeeds();
    }
}
