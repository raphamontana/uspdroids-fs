/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "vision.h"
#include <QApplication>

VisionConnection::VisionConnection(quint16 port)
{
    this->port = port;
    isConnected = false;
}

void VisionConnection::run()
{
    if (isConnected) {
        send();
    }
    else connectStrategy();
}

void VisionConnection::connectStrategy()
{
    QByteArray datagram;
    socket = new QUdpSocket();
    // Binds this socket to the address and the port
    if (!socket->bind(port, QUdpSocket::DontShareAddress)) {
        puts("Could not bind the socket.");
        QApplication::exit(0);
    }
    while (true) {
        socket->waitForReadyRead();
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), socket->pendingDatagramSize(), &strategyAddress, &strategyPort);
        if (datagram.contains("Connection request")) {
            socket->write("Request aceppted.");
            break;
        }
    }
    isConnected = true;
}
void VisionConnection::disconnectStrategy()
{
    socket->close();
    delete(socket);
}

void VisionConnection::setMessageToSend(QByteArray datagram)
{
    messageToSend = datagram;
}

void VisionConnection::send()
{
    socket->writeDatagram(messageToSend, strategyAddress, strategyPort);
    socket->waitForBytesWritten();
}
