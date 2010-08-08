/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef STRATEGY_CONNECTION_H
#define STRATEGY_CONNECTION_H

#include "../worldmodel.h"
#include <QMutex>
#include <QSemaphore>
#include <QtNetwork>

class StrategyConnection : public QThread
{

public:

    /**
     * Setup the port number and set the connection to its initial state
     */
    StrategyConnection(quint16 port);

    /**
     *
     */
    QByteArray getMessage();

    /**
     *
     */
    void setMessageToSend(QByteArray message);

    /**
     *
     */
    void disconnectStrategy();

    /**
     *
     */
    QString getTeamName();

    /**
     *
     */
    void run();

private:

    enum {unbinded, disconnected, receiving, sending} connectionStatus, state;

    QUdpSocket * socket;

    quint16 listenerPort;

    QHostAddress strategyAddress;

    quint16 strategyPort;

    QByteArray commands;

    QString teamName;

};

#endif // STRATEGY_CONNECTION_H
