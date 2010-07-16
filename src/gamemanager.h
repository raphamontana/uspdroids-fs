/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The USPDroids Football Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the USPDroids Football Simulator.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "worldmodel.h"

class GameManager
{
public:

    GameManager(WorldModel * wm)
    {
        this->wm = wm;
    }

    void initialize()
    {
    }

    /**
     * Physical Simulation: The soccer server has a physi-
     * cal simulator, which simulates movement of objects (ball
     * and players) and collisions between them. The simu-
     * lation is simplied so that it is easy to calculate the
     * changes in real-time, but the essence of soccer is not
     * lost.
     */
    void gameStep()
    {
    }

    void finalize()
    {
    }

    WorldModel * wm;

};

#endif // GAME_MANAGER_H
