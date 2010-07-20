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
    this->port = port;
    state = unbinded;
    //socket->moveToThread(this);
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
    QByteArray datagram;
    switch (state) {
        case connected:
            if (socket->waitForReadyRead(17)) {
                datagram.resize(socket->pendingDatagramSize());
                datagram = socket->read(socket->pendingDatagramSize());
            }
            break;
        case sending:
            break;
        case unbinded:
            socket = new QUdpSocket;
            if (!socket->bind(port, QUdpSocket::DontShareAddress)) {
                puts("Could not bind the socket.");
                exit(0);
            }
            while (true) {
                socket->waitForReadyRead();
                datagram.resize(socket->pendingDatagramSize());
                socket->readDatagram(datagram.data(), socket->pendingDatagramSize(), &host, &portToSend);
                if (datagram.contains("Connection request")) {
                    datagram.remove(0, 20);
                    teamName = datagram.data();
                    socket->writeDatagram("Request aceppted.", host, portToSend);
                    break;
                }
            }
            printf("Team %s has connected.\n", datagram.data());
            state = sending;
            break;
        case disconnected:
            while (true) {
                socket->waitForReadyRead();
            }
            puts("One strategy has connected.");
            state = sending;
            break;

        default:
            break;
    }
}

//    void readMessage()
//    {
//        exit(1);
//        QByteArray datagram;
//        QHostAddress host;
//        quint16 port;
//        QMutexLocker locker(&mutex);
//        datagram.resize(socket.pendingDatagramSize());
//        socket.readDatagram(datagram.data(), socket.pendingDatagramSize(), &host, &port);
//        if (isConnected && (address == host && this->port == port)) {
//            if (datagram.data()[0] == 'O') {
//                commands = datagram;
//                messageReceived.release();
//            }
//            else if (datagram.contains("Strategy name: ")) {
//                datagram.remove(0, 16);
//                teamName = datagram.data();
//            }
//            else if (datagram == "Disconnection request") {
//                isConnected = false;
//            }
//        }
//        else if (datagram == "Connection request") {
//            isConnected = true;
//            address = host;
//            this->port = port;
//            socket.writeDatagram("Send the strategy name.", address, port);
//            puts("Strategy connected.");
//            connection.release();
//        }
//    }
