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
#include "gamemanager.h"
#include "strategiesmanager.h"
#include "viewersmanager.h"
#include "worldmodel.h"

class Simulator : public QObject
{
    Q_OBJECT

public:

    Simulator(int argc, char * argv[]);

    ~Simulator();

signals:

    void quit();

public slots:

    void launch();

private:

    void parser(int argc, char * argv[]);

    void initialize();

    void execute();

    void finish();

    WorldModel wm;

    GameManager * gm;

    StrategiesManager * sm;

    ViewersManager * vm;

    quint16 strategyPort1[2];

    quint16 strategyPort2[2];

    quint16 viewerPort;

    quint32 goals[2];

    //Starters flags
    int simulations;    /// Number of executions.
    bool exec;          /// Start or not the simulator.
    bool noia1;         /// Do not start the strategy for team 1.
    bool noia2;         /// Do not start the strategy for team 2.
    bool log;           /// Saves a log file of the game.
    bool gui;           /// Show the graphical user interface.
};

#endif // SIMULATOR_H
