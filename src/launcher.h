/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "simulator.h"

class Launcher : public QObject
{
    Q_OBJECT

public:

    Launcher(int argc, char* argv[]);

signals:

    void quit();

public slots:

    void launch();

private:

    bool exec;

    bool gui;

    bool noia1;

    bool noia2;

    bool log;

    bool debug;

    int loop;

    bool waitPlayCommand;
};

#endif // LAUNCHER_H
