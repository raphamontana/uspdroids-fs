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

#include "gui/frontend.h"
#include "configuration.h"
#include "gamemanager.h"
#include "strategiesmanager.h"
#include "viewersmanager.h"
#include "worldmodel.h"

class Simulator : public QObject
{
    Q_OBJECT

public:

    Simulator(Configuration conf);

    ~Simulator();

signals:

    void quit();

public slots:

    void launch();

private:

    void initialize();

    void execute();

    void finish();

    WorldModel wm;

    GameManager * gm;

    StrategiesManager * sm;

    ViewersManager * vm;

    quint32 goals[2];

    Configuration conf;

};

#endif // SIMULATOR_H
