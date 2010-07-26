/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "gamemanager.h"
#include "strategiesmanager.h"
#include "viewersmanager.h"
#include "worldmodel.h"

class Simulator
{
public:

    Simulator(quint16 port0, quint16 port1, quint16 viewerPort);

    ~Simulator();

    void initialize();

    void execute();

    void finish();

private:

    WorldModel wm;

    GameManager * gm;

    StrategiesManager * sm;

    ViewersManager * vm;

    quint32 goals[2];

};

#endif // SIMULATOR_H
