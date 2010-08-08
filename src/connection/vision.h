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

class VisionConnection
{
public:

    VisionConnection(quint16 port);

    void receive();

    void run();

private:

    QUdpSocket * socket;

    quint16 port;

};

#endif // VISION_H
