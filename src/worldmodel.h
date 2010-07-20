/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef WORLD_MODEL_H
#define WORLD_MODEL_H

#include <QByteArray>
#include <stdio.h>

class SpatialLocation
{
public:

    SpatialLocation();

    void setSpatialLocation(int x, int y, int z, int angxy, int angxz, int angyz);

    void setPosition(int x, int y, int z);

    void setRotation(int angxy, int angxz, int angyz);

    int x, y, z;

    int angxy, angxz, angyz;

};

class RobotModel : public SpatialLocation
{
public:

    RobotModel();

    void setWheelsSpeed(int leftWheel, int rightWheel);

    void normalizeWheelsSpeeds();

    int leftWheel;

    int rightWheel;

};

class TeamModel
{
public:

    RobotModel robot[3];

};

class WorldModel
{
public:

    TeamModel team[2];

    SpatialLocation ball;

    void setInitialPosition(int period);

};

#endif // WORLD_MODEL_H
