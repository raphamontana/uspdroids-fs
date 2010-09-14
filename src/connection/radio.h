/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef RADIO_H
#define RADIO_H

#include <QMutex>
#include <QSemaphore>
#include <QtNetwork>

/**
 * Class responsable for receiveing commands from the strategy and propagate them to the simulator core.
 */
class RadioConnection : public QThread
{
public:

    RadioConnection(quint16 port);

    void disconnectStrategy();      /// Close the socket.

    QByteArray getMessage();        /// @return The message received.

    const char * getTeamName();     /// @return The name of the connected team.

private:

    void run();                     /// Start a new thread.

    void connectStrategy();         /// Wait for the strategy connection.

    void recv();                    /// Wait 17ms for a message from the strategy.

    QUdpSocket * socket;            ///  Object that allows you to send and receive UDP datagrams.

    quint16 port;                   /// Port to bind the socket.

    QByteArray teamName;            /// Name of the connected strategy.

    QHostAddress strategyAddress;   /// Address of the connected strategy.

    quint16 strategyPort;           /// Port of connection of the strategy.

    bool isConnected;

    QByteArray command;

};

#endif // RADIO_H
