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
    dInitODE ();                            // inicializa a ODE
    world = dWorldCreate();                 // cria o mundo
    dWorldSetGravity(world, 0, 0, -9.8);    // seta o vetor gravidade
    dWorldSetERP(world, 0.4);
    dWorldSetCFM(world, 1e-7);              // seta a precisao
    space = dHashSpaceCreate(0);            // cria um espaco

    field = new Field(space);               // inicia o campo
    ball = new Ball(world, space);          // inicia bola
    team[0] = new Team(world, space);       // inicia team 0
    team[1] = new Team(world, space);       // inicia team 1
    contactgroup = dJointGroupCreate(0);    // cria o grupo de juntas
}

GameManager::~GameManager()
{
    delete(field);
    delete(ball);
    delete(team[0]);
    delete(team[1]);
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
    team[0]->setVelocidades(wm, 0);
    team[1]->setVelocidades(wm, 1);
    dSpaceCollide(space, this, &colisao);   // Encontra as colisoes do espaco e chama o callback
    dWorldStep(world, 0.016);               // Simula 16ms = 60fps
    dJointGroupEmpty(contactgroup);         // Limpa as interacoes
}

void GameManager::finalize()
{
}

void GameManager::robotRelocation()
{
    switch (gameState) {
        case Normal:
            wm->setInitialPosition(1);
            break;
        case FreeKick:
            break;
        case PenaltyKick:
            break;
        case GoalKick:
            break;
        case FreeBall:
            break;
    }
}

void GameManager::colisao(void* data, dGeomID o1, dGeomID o2) {
    GameManager * gm = (GameManager *) data;
    dBodyID b1 = dGeomGetBody(o1);  // obtendo os corpos correspondentes
    dBodyID b2 = dGeomGetBody(o2);

    if (b1 && b2 && dAreConnectedExcluding(b1, b2, dJointTypeContact)) {
        return; // se estao conectados nao ha colisao
    }

    const int N = 10;               // numero maximo de pontos de contato
    dContact contact[N];
    int n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact)); // verifica colisao
    if (n > 0) {
        for (int i=0; i<n; i++) {
            contact[i].surface.mode = dContactApprox1 | dContactBounce; // atrito e restituicao
            if ( dGeomGetClass(o1) == dBoxClass && dGeomGetClass(o2) == dBoxClass )
                contact[i].surface.mu = 10.0; // atrito entre robo e campo
            else
                contact[i].surface.mu = 0.9; // atrito entre robo e todo o resto

            if ( dGeomGetClass(o1) == dSphereClass || dGeomGetClass(o2) == dSphereClass ) { // somente a bola pinga
                contact[i].surface.bounce     = 0.3;
                contact[i].surface.bounce_vel = 0.2;
            } else {
                contact[i].surface.bounce     = 0.0;
                contact[i].surface.bounce_vel = dInfinity;
            }

            // liga os corpos que colidiram
            dJointID c = dJointCreateContact(gm->world, gm->contactgroup, contact+i);
            dJointAttach (c, dGeomGetBody(o1), dGeomGetBody(o2));
        }
    }
}
