/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "strategiesmanager.h"

StrategiesManager::StrategiesManager(WorldModel * wm, quint16 strategy1Port1, quint16 strategy1Port2, quint16 strategy2Port1, quint16 strategy2Port2)
{
    this->wm = wm;
    radio[0] = new RadioConnection(strategy1Port1);
    vision[0] = new VisionConnection(strategy1Port2);
    radio[1] = new RadioConnection(strategy2Port1);
    vision[1] = new VisionConnection(strategy2Port2);
}

void StrategiesManager::initialise()
{
    radio[0]->start();
    vision[0]->start();
    radio[1]->start();
    vision[1]->start();
}

void StrategiesManager::waitStrategies() {
    radio[0]->wait();
    vision[0]->wait();
    radio[1]->wait();
    vision[1]->wait();
}

void StrategiesManager::recvCommands()
{
    radio[0]->start();
    radio[1]->start();
    radio[0]->wait();
    radio[1]->wait();
    decodeMessage(0, radio[0]->getMessage());
    decodeMessage(1, radio[1]->getMessage());
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
    vision[0]->setMessageToSend(message);
    sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
            wm->ball.x, wm->ball.y,
            wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
            wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
            wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy,
            wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
            wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
            wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy);
    vision[1]->setMessageToSend(message);
    vision[0]->start();
    vision[1]->start();
    vision[0]->wait();
    vision[1]->wait();
}

void StrategiesManager::finalize()
{
    radio[0]->disconnectStrategy();
    radio[1]->disconnectStrategy();
    vision[0]->disconnectStrategy();
    vision[1]->disconnectStrategy();
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

const char * StrategiesManager::getTeamName(int i)
{
    //return(teamName.toStdString().data());
    if (i) return(radio[1]->getTeamName());
    else return(radio[0]->getTeamName());

}
