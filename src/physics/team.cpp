/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "team.h"

Team::Team(dWorldID world, dSpaceID space)
{
    robo1 = new Robot(world, space);
    robo2 = new Robot(world, space);
    robo3 = new Robot(world, space);
}


Team::~Team()
{
    delete(robo1);
    delete(robo2);
    delete(robo3);
}


void Team::setVelocidades(WorldModel * wm, int team)
{
    robo1->setVelocidade(wm->team[team].robot[0].leftWheel, wm->team[team].robot[0].rightWheel);
    robo1->setVelocidade(wm->team[team].robot[1].leftWheel, wm->team[team].robot[1].rightWheel);
    robo1->setVelocidade(wm->team[team].robot[2].leftWheel, wm->team[team].robot[2].rightWheel);
}


dReal Team::getPosicao(int robo)
{
    if (robo == 0) return(robo1->getPosicao());
    else if (robo == 1) return(robo2->getPosicao());
    else return(robo3->getPosicao());
}


dReal Team::getAngulo(int team)
{
    dReal ang;
    return ang;
    /*
    if (team == 0)
         return(robo1->getAngulo());
    else return(robo2->getAngulo());
    */
}


void Team::setPosicao(int n, double x, double y, double z)
{
    if (n == 0) robo1->setPosicao(x, y, z);
    if (n == 1) robo2->setPosicao(x, y, z);
    if (n == 2) robo3->setPosicao(x, y, z);
}
