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

#ifndef VIEWERS_MANAGER_H
#define VIEWERS_MANAGER_H

#include "worldmodel.h"
#include <QMutex>
#include <QtNetwork>
#include <QVector>

class ViewerManager : QObject
{

    Q_OBJECT

public:

    ViewerManager(WorldModel * wm, quint16 viewerPort)
    {
        this->wm = wm;
        this->viewerPort = viewerPort;
        listenerSocket.bind(viewerPort);
        connect(&listenerSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    }

    void initialize()
    {
    }

    void recvCommands()
    {
    }

    void transmitData()
    {
        mutex.lock();
        int size = addresses.size();
        if (size) {
            QByteArray message;
            sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                    wm->ball.x,                 wm->ball.y,                 wm->ball.z,
                    wm->team[0].robot[0].x,     wm->team[0].robot[0].y,     wm->team[0].robot[0].z,
                    wm->team[0].robot[0].angxy, wm->team[0].robot[0].angxz, wm->team[0].robot[0].angyz,
                    wm->team[0].robot[1].x,     wm->team[0].robot[1].y,     wm->team[0].robot[1].z,
                    wm->team[0].robot[1].angxy, wm->team[0].robot[1].angxz, wm->team[0].robot[1].angyz,
                    wm->team[0].robot[2].x,     wm->team[0].robot[2].y,     wm->team[0].robot[2].z,
                    wm->team[0].robot[2].angxy, wm->team[0].robot[2].angxz, wm->team[0].robot[2].angyz,
                    wm->team[1].robot[0].x,     wm->team[1].robot[0].y,     wm->team[1].robot[0].z,
                    wm->team[1].robot[0].angxy, wm->team[1].robot[0].angxz, wm->team[1].robot[0].angyz,
                    wm->team[1].robot[1].x,     wm->team[1].robot[1].y,     wm->team[1].robot[1].z,
                    wm->team[1].robot[1].angxy, wm->team[1].robot[1].angxz, wm->team[1].robot[1].angyz,
                    wm->team[1].robot[2].x,     wm->team[1].robot[2].y,     wm->team[1].robot[2].z,
                    wm->team[1].robot[2].angxy, wm->team[1].robot[2].angxz, wm->team[1].robot[2].angyz);
            for (register int i = 0; i < size; i++) {
                senderSocket.writeDatagram(message, addresses.at(i).first, addresses.at(i).second);
            }
        }
        mutex.unlock();
    }

    void finalize()
    {
        mutex.lock();
        for (register int i = 0; i < addresses.size(); i++) {
            senderSocket.writeDatagram("End of game", addresses.at(i).first, addresses.at(i).second);
        }
        addresses.clear();
        mutex.unlock();
    }

private slots:

    void receiveMessage()
    {
        QByteArray datagram;
        QHostAddress host;
        quint16 port;
        datagram.resize(listenerSocket.pendingDatagramSize());
        listenerSocket.readDatagram(datagram.data(), listenerSocket.pendingDatagramSize(), &host, &port);
        if (datagram == "Connection request") {
            QPair<QHostAddress, quint16> pair(host, port);
            mutex.lock();
            addresses.push_back(pair);
            mutex.unlock();
            senderSocket.writeDatagram("Request accepted", host, port);
        }
        else if (datagram == "Disconnection request") {
            QPair<QHostAddress, quint16> pair(host, port);
            mutex.lock();
            int index = addresses.indexOf(pair);
            if (index < addresses.size()){
                addresses.remove(index);
            }
            mutex.unlock();
        }
    }

private:

    WorldModel * wm;

    quint16 viewerPort;

    QUdpSocket listenerSocket;

    QUdpSocket senderSocket;

    QMutex mutex; //Protect the address list

    QVector< QPair<QHostAddress, quint16> > addresses;

};

#endif // VIEWERS_MANAGER_H
