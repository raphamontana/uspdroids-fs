/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "gamemanager.h"

GameManager::GameManager(WorldModel * wm)
{
    this->wm = wm;
    dInitODE();
    world = dWorldCreate();
    dWorldSetGravity(world, 0, 0, -9.8);
    dWorldSetCFM(world, 1e-3);
    space = dHashSpaceCreate(0);
    campo = new ODE_Campo(space);
    bola = new ODE_Bola(world, space);
    equipe[0][0] = new ODE_Robo(world, space);
    equipe[0][1] = new ODE_Robo(world, space);
    equipe[0][2] = new ODE_Robo(world, space);
    equipe[1][0] = new ODE_Robo(world, space);
    equipe[1][1] = new ODE_Robo(world, space);
    equipe[1][2] = new ODE_Robo(world, space);
    contactgroup = dJointGroupCreate(0);
}

GameManager::~GameManager()
{
    delete(campo);
    delete(bola);
    delete(equipe[0][0]);
    delete(equipe[0][1]);
    delete(equipe[0][2]);
    delete(equipe[1][0]);
    delete(equipe[1][1]);
    delete(equipe[1][2]);
    dJointGroupDestroy(contactgroup);
    dSpaceDestroy(space);
    dWorldDestroy(world);
    dCloseODE();
}

void GameManager::initialize()
{
    wm->setInitialPosition(1);
}

void GameManager::gameStep()
{
    dSpaceCollide(space, this, &colisao);
    dWorldStep(world, 0.016);
    dJointGroupEmpty(contactgroup);
}

void GameManager::finalize()
{
}

void GameManager::colisao(void* data, dGeomID o1, dGeomID o2) {
    GameManager * gm = (GameManager *) data;
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);

    if (b1 && b2 && dAreConnectedExcluding(b1, b2, dJointTypeContact))
        return; // se estao conectados nao ha colisao

    const int N = 10;
    dContact contact[N];
    int n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            contact[i].surface.mode = dContactApprox1 | dContactBounce;
            if ( dGeomGetClass(o1) == dBoxClass && dGeomGetClass(o2) == dBoxClass ) {
                contact[i].surface.mu   = dInfinity;
            }
            else {
                contact[i].surface.mu   = 0.5;
            }
            if ( dGeomGetClass(o1) == dSphereClass || dGeomGetClass(o2) == dSphereClass ) {
                contact[i].surface.bounce = 0.3;
                contact[i].surface.bounce_vel = 0.2;
            } else {
                contact[i].surface.bounce = 0.0;
                contact[i].surface.bounce_vel = dInfinity;
            }
            dJointID c = dJointCreateContact (gm->world, gm->contactgroup, contact+i);
            dJointAttach(c, dGeomGetBody(o1), dGeomGetBody(o2));
        }
    }
}
