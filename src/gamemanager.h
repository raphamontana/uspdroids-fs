/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "worldmodel.h"

class GameManager
{
public:

    GameManager(WorldModel * wm);

    void initialize();

    /**
     * Physical Simulation: The soccer server has a physi-
     * cal simulator, which simulates movement of objects (ball
     * and players) and collisions between them. The simu-
     * lation is simplied so that it is easy to calculate the
     * changes in real-time, but the essence of soccer is not
     * lost.
     */
    void gameStep();

    void finalize();

    WorldModel * wm;

};

#endif // GAME_MANAGER_H
