/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef VIEWERS_MANAGER_H
#define VIEWERS_MANAGER_H

#include "worldmodel.h"
#include <QMutex>
#include <QtNetwork>
#include <QVector>

class ViewersManager : QObject
{

    Q_OBJECT

public:

    ViewersManager(WorldModel * wm, quint16 viewerPort);

    void initialise();

    void recvCommands();

    void transmitData();

    void finalize();

private slots:

    void receiveMessage();

private:

    WorldModel * wm;

    quint16 viewerPort;

    QUdpSocket listenerSocket;

    QUdpSocket senderSocket;

    QMutex mutex; //Protect the address list

    QVector< QPair<QHostAddress, quint16> > addresses;

};

#endif // VIEWERS_MANAGER_H
