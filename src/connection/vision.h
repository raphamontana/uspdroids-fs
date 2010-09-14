/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef VISION_H
#define VISION_H

#include <QMutex>
#include <QSemaphore>
#include <QtNetwork>

/**
 * Class responsable for sending robots coordenates to the strategy.
 */
class VisionConnection : public QThread
{
public:

    VisionConnection(quint16 port);

    void disconnectStrategy();      /// Close the socket.

    void setMessageToSend(QByteArray datagram);   /// Set a message to be sent.

private:

    void run();                     /// Start a new thread to wait for the strategy connection.

    void connectStrategy();         /// Wait for the strategy connection.

    void send();                    /// Send a message to the strategy.

    QUdpSocket * socket;            ///  Object that allows you to send and receive UDP datagrams.

    quint16 port;                   /// Port to bind the socket.

    QHostAddress strategyAddress;   /// Address of the connected strategy.

    quint16 strategyPort;           /// Port of connection of the strategy.

    bool isConnected;

    QByteArray messageToSend;

};

#endif // VISION_H
