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

#include <QMutex>
#include "gui/frontend.h"
#include "configuration.h"
#include "gamemanager.h"
#include "strategiesmanager.h"
#include "viewersmanager.h"
#include "worldmodel.h"

/**
 * The main class of the program.
 * This class is responsable for connect the strategies, initialise, execute and terminate the simulations.
 */
class Simulator : public QObject
{
    Q_OBJECT

public:

    Simulator(Configuration conf);  /// Alloc resources for the simulator.

    ~Simulator();           /// Free allocated resources.

signals:

    void quit();            /// Signal emitted to the application when the simulator is ready to exit.

public slots:

    void launch();          /// Receives the signal to start the match when doesn't use the GUI.

    void pause();           /// Receives the signal to pause/continue the match.

private:

    void initialise();      /// Initialise the managers.

    void execute();         /// Reset and start the match.

    void finish();          /// Finalize the managers.

    bool isPaused;
    QMutex pauseLock;       /// The pause system.

    WorldModel wm;          /// Object that stores the global positioning.

    GameManager * gm;       /// Core manager.

    StrategiesManager * sm; /// Manages connection with the strategies.

    ViewersManager * vm;    /// Manages connection with the viewers.

    quint32 goals[2];       /// Score of each team.

    Configuration conf;     /// Configuration object of the simulator.

};

#endif // SIMULATOR_H
