/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "strategyconnection.h"

StrategyConnection::StrategyConnection(quint16 port)
{
    portToListen = port;
    state = unbinded;
}

QByteArray StrategyConnection::getMessage()
{
    return commands;
}

void StrategyConnection::setMessageToSend(QByteArray message)
{
    commands = message;
}

void StrategyConnection::disconnectStrategy()
{
    state = disconnected;
}

void StrategyConnection::run()
{
    QHostAddress host;
    quint16 port;
    QByteArray datagram;
    datagram.resize(1024);
    switch (state) {
        case receiving:
            if (socket->waitForReadyRead(17)) {
                socket->readDatagram(datagram.data(), socket->pendingDatagramSize(), &host, &port);
                if (host == addressToSend && port == portToSend) {
                    if (datagram.data()[0] == 'O') {
                        commands = datagram;
                    }
                    else if (datagram == "Disconnection request") {
                        state = disconnected;
                    }
                }
                else {
                    socket->writeDatagram("Request rejected.", host, port);
                }
            }
            state = sending;
            break;
        case sending:
            socket->writeDatagram(commands, addressToSend, portToSend);
            state = receiving;
            break;
        case unbinded:
            socket = new QUdpSocket;
            if (!socket->bind(portToListen, QUdpSocket::DontShareAddress)) {
                puts("Could not bind the socket.");
                exit(0);
            }
            while (true) {
                socket->waitForReadyRead();
                socket->readDatagram(datagram.data(), socket->pendingDatagramSize(), &addressToSend, &portToSend);
                if (datagram.contains("Connection request")) {
                    datagram.remove(0, 20);
                    teamName = datagram.data();
                    socket->writeDatagram("Request aceppted.", addressToSend, portToSend);
                    break;
                }
            }
            printf("Team %s has connected.\n", datagram.data());
        case disconnected:
            while (true) {
                socket->waitForReadyRead();
                socket->readDatagram(datagram.data(), socket->pendingDatagramSize(), &addressToSend, &portToSend);
                if (datagram.contains("Connection request")) {
                    datagram.remove(0, 20);
                    teamName = datagram.data();
                    socket->writeDatagram("Request aceppted.", addressToSend, portToSend);
                    break;
                }
            }
            printf("Team %s has connected.\n", datagram.data());
            state = sending;
            break;
        default:
            break;
    }
}
