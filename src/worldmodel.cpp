/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "worldmodel.h"

SpatialLocation::SpatialLocation()
{
    x     = y     = z     = 0;
    angxy = angxz = angyz = 0;
}

void SpatialLocation::setSpatialLocation(int x, int y, int z, int angxy, int angxz, int angyz)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->angxy = angxy;
    this->angxz = angxz;
    this->angyz = angyz;
}

void SpatialLocation::setPosition(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void SpatialLocation::setRotation(int angxy, int angxz, int angyz)
{
    this->angxy = angxy;
    this->angxz = angxz;
    this->angyz = angyz;
}

RobotModel::RobotModel()
{
    leftWheel = rightWheel = 0;
}

void RobotModel::setWheelsSpeed(int leftWheel, int rightWheel)
{
    this->leftWheel = leftWheel;
    this->rightWheel = rightWheel;
    normalizeWheelsSpeeds();
}

void RobotModel::normalizeWheelsSpeeds()
{
    if (leftWheel < -100)      leftWheel  = -100;
    else if (leftWheel > 100)  leftWheel  =  100;
    if (rightWheel < -100)     rightWheel = -100;
    else if (rightWheel > 100) rightWheel =  100;
}

void WorldModel::setInitialPosition(int period)
{
    int randomx, randomy;
    srand(time(NULL));          // Initialize random number generator.
    ball.setPosition(0, 0, 3);
    if (period == 1) {
        team[0].robot[0].setSpatialLocation(-75, 0, 5, 0, 0, 0);
        randomx = ((rand() % 21)-10);
        randomy = ((rand() % 21)-10);
        team[0].robot[1].setSpatialLocation(-20+randomx, 20+randomy, 5, 0, 0, 0);
        randomx = ((rand() % 21)-10);
        randomy = ((rand() % 21)-10);
        team[0].robot[2].setSpatialLocation(-20+randomx,-20+randomy, 5, 0, 0, 0);
        team[1].robot[0].setSpatialLocation( 75, 0, 5, 0, 0, 0);
        randomx = ((rand() % 21)-10);
        randomy = ((rand() % 21)-10);
        team[1].robot[1].setSpatialLocation( 20+randomx, 20+randomy, 5, 0, 0, 0);
        randomx = ((rand() % 21)-10);
        randomy = ((rand() % 21)-10);
        team[1].robot[2].setSpatialLocation( 20+randomx,-20+randomy, 5, 0, 0, 0);
    }
    else if (period == 2) {
        team[0].robot[0].setSpatialLocation( 75, 0, 5, 0, 0, 0);
        randomx = ((rand() % 21)-10);
        randomy = ((rand() % 21)-10);
        team[0].robot[1].setSpatialLocation( 20+randomx, 20+randomy, 5, 0, 0, 0);
        randomx = ((rand() % 21)-10);
        randomy = ((rand() % 21)-10);
        team[0].robot[2].setSpatialLocation( 20+randomx,-20+randomy, 5, 0, 0, 0);
        team[1].robot[0].setSpatialLocation(-75, 0, 5, 0, 0, 0);
        randomx = ((rand() % 21)-10);
        randomy = ((rand() % 21)-10);
        team[1].robot[1].setSpatialLocation(-20+randomx, 20+randomy, 5, 0, 0, 0);
        randomx = ((rand() % 21)-10);
        randomy = ((rand() % 21)-10);
        team[1].robot[2].setSpatialLocation(-20+randomx,-20+randomy, 5, 0, 0, 0);
    }
}
