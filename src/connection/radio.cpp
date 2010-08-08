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
}

void RadioConnection::run()
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
            send("Request aceppted.");
            break;
        }
    }
    printf("Team %s has connected.\n", teamName.data());
}

void RadioConnection::disconnectStrategy()
{
    socket->close();
    delete(socket);
}

void RadioConnection::send(QByteArray datagram)
{
    socket->writeDatagram(datagram, strategyAddress, strategyPort);
    socket->waitForBytesWritten();
}
