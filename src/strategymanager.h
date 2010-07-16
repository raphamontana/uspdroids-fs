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

#ifndef STRATEGIES_MANAGER_H
#define STRATEGIES_MANAGER_H

#include "strategyconnection.h"

class StrategyManager : QObject
{

    Q_OBJECT

public:

    /**
     *
     */
    StrategyManager(WorldModel * wm, quint16 portToListen0, quint16 portToListen1)
    {
        this->wm = wm;
        st[0] = new StrategyConnection(portToListen0);
        st[1] = new StrategyConnection(portToListen1);
    }

    /**
     *
     */
    void initialize()
    {
        st[0]->start();
        st[1]->start();
    }

    void waitStrategies() {
        st[0]->wait();
        st[1]->wait();
    }

    /**
     * Libera duas threads para receber mensagem das estrategias
     */
    void recvCommands()
    {
        st[0]->start();
        st[1]->start();
        st[0]->wait();
        st[1]->wait();
    }

    /**
     * Send the positions of the objects in the world model to the strategies.
     */
    void transmitData()
    {
        QByteArray message[2];
        sprintf(message[0].data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                wm->ball.x, wm->ball.y,
                wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
                wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
                wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy,
                wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
                wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
                wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy);
        sprintf(message[1].data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                wm->ball.x, wm->ball.y,
                wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
                wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
                wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy,
                wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
                wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
                wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy);
        //mutex[0].lock();
        //mutex[1].lock();
        //senderSocket[0].writeDatagram(message[0], address[0], portToSend[0]);
        //senderSocket[1].writeDatagram(message[1], address[1], portToSend[1]);
        //mutex[0].unlock();
        //mutex[1].unlock();
    }

    /**
     *
     */
    void disconnectStrategy()
    {
    }

    /**
     *
     */
    void finalize()
    {
        //disconnectStrategy(0);
        //disconnectStrategy(1);
    }

private:

    /**
     *
     */
    void decodeMessage(int strategy, QByteArray message)
    {
        int read;
        if (strategy == 0 || strategy == 1) {
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
        else {
            qWarning("Badly-formed message received.");
        }
    }

    WorldModel * wm;

    StrategyConnection * st[2];

};

#endif // STRATEGIES_MANAGER_H
