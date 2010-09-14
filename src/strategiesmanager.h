/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef STRATEGIES_MANAGER_H
#define STRATEGIES_MANAGER_H

#include "connection/strategyconnection.h"

class StrategiesManager
{
public:

    /**
     * Obtem o endereco do modelo de mundo
     */
    StrategiesManager(WorldModel * wm, quint16 port0, quint16 port1, quint16 port2, quint16 port3);

    /**
     *
     */
    void initialise();

    /**
     *
     */
    void waitStrategies();

    /**
     * Libera duas threads para receber mensagem das estrategias
     */
    void recvCommands();

    /**
     * Send the positions of the objects in the world model to the strategies.
     */
    void transmitData();

    /**
     * Access the strategies name.
     * @param i number of the strategy (0 or 1).
     * @return the name of the ith strategy.
     */
    const char * getTeamName(int i);

    /**
     *
     */
    void finalize();

private:

    void decodeMessage(int strategy, QByteArray message);

    WorldModel * wm;                /// Contains

    RadioConnection * radio[2];     /// Radio

    VisionConnection * vision[2];   /// Vision

};

#endif // STRATEGIES_MANAGER_H
