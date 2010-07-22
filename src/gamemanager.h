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

#define dDOUBLE
#include <ode/ode.h>
#include "physics/ball.h"
#include "physics/field.h"
#include "physics/robot.h"
#include "worldmodel.h"

/**
 * @class GameManager
 * @brief Provide an abstraction to the physic engine.
 *
 * Details of the class.
 */
class GameManager
{

public:

    /**
     * @brief Create a GameManager.
     * @param wm a WorldModel object
     *
     * Get the world model address from the simulator.
     */
    GameManager(WorldModel * wm);

    /**
     * @brief Destroy allocated objects.
     *
     * Finalize the manager.
     */
    ~GameManager();

    /**
     * @brief Simple initialize the manager.
     *
     * Finalize the manager.
     */
    void initialize();

    /**
     * @brief Execute one game step
     *
     * Physical Simulation: The soccer server has a physical
     * simulator, which simulates movement of objects (ball
     * and players) and collisions between them. The simulation
     * is simplified so that it is easy to calculate the
     * changes in real-time, but the essence of soccer is not
     * lost.
     */
    void gameStep();

    /**
     * @brief Finalize the manager.
     *
     * Finalize the manager.
     */
    void finalize();

private:

    static void colisao(void* data, dGeomID o1, dGeomID o2);

    /**
     * @brief The world model.
     *
     * It is used to communicate with the others modules from
     * the simulator.
     */
    WorldModel * wm;

    dWorldID world;

    dSpaceID space;

    ODE_Campo *campo;

    ODE_Bola *bola;

    ODE_Robo* equipe[2][3];

    dJointGroupID contactgroup;
};                          // end of class GameManager

#endif // GAME_MANAGER_H
