/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "radio.h"

RadioConnection::RadioConnection(quint16 port)
{
    this->port = port;
    isConnected = false;
}

void RadioConnection::run()
{
    if (isConnected) {
        recv();
    }
    else connectStrategy();
}

void RadioConnection::connectStrategy()
{
    QByteArray datagram;
    socket = new QUdpSocket();
    if (!socket->bind(port, QUdpSocket::DontShareAddress)) {
        puts("Could not bind the socket.");
        exit(0);
    }
    while (true) {
        socket->waitForReadyRead();
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), socket->pendingDatagramSize(), &strategyAddress, &strategyPort);
        if (datagram.contains("Connection request")) {
            datagram.remove(0, 20);
            teamName = datagram.data();
            socket->write("Request aceppted.");
            break;
        }
    }
    isConnected = true;
    printf("Team %s has connected.\n", teamName.data());
}

void RadioConnection::disconnectStrategy()
{
    socket->close();
    delete(socket);
}

void RadioConnection::recv()
{
    QHostAddress host;
    quint16 port;
    QByteArray datagram;
    if (socket->waitForReadyRead(17)) {
        socket->readDatagram(datagram.data(), socket->pendingDatagramSize(), &host, &port);
        if (host == strategyAddress && port == strategyPort) {
            if (datagram.data()[0] == 'O') {
                command = datagram;
            }
            else if (datagram.contains("Disconnection request")) {
                //state = disconnected;
            }
        }
        else {
            socket->writeDatagram("Request rejected.", host, port);
        }
    }
}

QByteArray RadioConnection::getMessage()
{
    return(command);
}

const char * RadioConnection::getTeamName()
{
    return(teamName.data());
}
