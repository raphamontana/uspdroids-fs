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
#include "radio.h"
#include "vision.h"

class StrategyConnection : public QThread
{

public:

    /**
     * Setup the port number and set the connection to its initial state
     */
    StrategyConnection(quint16 port1, quint16 port2);

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
    const char * getTeamName();

private:

    RadioConnection * radio;

    VisionConnection * vision;

    enum {unbinded, disconnected, receiving, sending} connectionStatus, state;

    QHostAddress strategyAddress;

    quint16 strategyPort;

    QByteArray commands;

    QString teamName;

};

#endif // STRATEGY_CONNECTION_H
