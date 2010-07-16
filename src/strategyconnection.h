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

#ifndef STRATEGY_CONNECTION_H
#define STRATEGY_CONNECTION_H

#include "strategyconnection.h"
#include "worldmodel.h"
#include <QMutex>
#include <QSemaphore>
#include <QtNetwork>

class StrategyConnection : public QThread
{

    Q_OBJECT

public:

    StrategyConnection(quint16 port)
    {
        isConnected = false;
        socket.bind(port);
        connect(&socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
        socket.blockSignals(true);
    }

protected:

    void run()
    {
        socket.blockSignals(false);
        if (isConnected) {
            messageReceived.tryAcquire(1, 17);
        }
        else {
            connection.acquire();
        }
        socket.blockSignals(true);
    }

private slots:

    void readMessage()
    {
        QByteArray datagram;
        QHostAddress host;
        quint16 port;
        mutex.lock();
        datagram.resize(socket.pendingDatagramSize());
        socket.readDatagram(datagram.data(), socket.pendingDatagramSize(), &host, &port);
        if (isConnected) {
            if (address == host && this->port == port){
                if (datagram.data()[0] == 'O') {
                    messageReceived.release();
                }
            }
            else if (datagram == "Strategy name: ") {
                teamName = datagram.data();
            }
            else if (datagram == "Disconnection request") {
            }
        }
        else if (datagram == "Connection request") {
            isConnected = true;
            address = host;
            this->port = port;
            socket.writeDatagram("Send the strategy name.", address, port);
            connection.release();
        }
        mutex.unlock();
    }

private:

    bool isConnected;

    //Only allows to be received one message per time
    QMutex mutex;

    QUdpSocket socket;

    QHostAddress address;

    quint16 port;

    QSemaphore connection;

    QSemaphore messageReceived;

    QString teamName;

};

#endif // STRATEGY_CONNECTION_H
