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

#ifndef WORLD_MODEL_H
#define WORLD_MODEL_H

#include <QByteArray>
#include <stdio.h>

class SpatialLocation
{
public:

    SpatialLocation()
    {
        x     = y     = z     = 0;
        angxy = angxz = angyz = 0;
    }

    void setSpatialLocation(int x, int y, int z, int angxy, int angxz, int angyz)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->angxy = angxy;
        this->angxz = angxz;
        this->angyz = angyz;
    }

    void setPosition(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void setRotation(int angxy, int angxz, int angyz)
    {
        this->angxy = angxy;
        this->angxz = angxz;
        this->angyz = angyz;
    }

    int x, y, z;

    int angxy, angxz, angyz;

};

class RobotModel : public SpatialLocation
{
public:

    RobotModel() {
        leftWheel = rightWheel = 0;
    }

    void setWheelsSpeed(int leftWheel, int rightWheel)
    {
        this->leftWheel = leftWheel;
        this->rightWheel = rightWheel;
        normalizeWheelsSpeeds();
    }

    void normalizeWheelsSpeeds()
    {
        if (leftWheel < -100)      leftWheel  = -100;
        else if (leftWheel > 100)  leftWheel  =  100;
        if (rightWheel < -100)     rightWheel = -100;
        else if (rightWheel > 100) rightWheel =  100;
    }

    int leftWheel, rightWheel;

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

    void setInitialPosition(int period)
    {
        ball.setPosition(0, 0, 2);
        if (period == 1) {
            team[0].robot[0].setSpatialLocation(0,0,0,0,0,0);
            team[0].robot[1].setSpatialLocation(0,0,0,0,0,0);
            team[0].robot[2].setSpatialLocation(0,0,0,0,0,0);
            team[1].robot[0].setSpatialLocation(0,0,0,0,0,0);
            team[1].robot[1].setSpatialLocation(0,0,0,0,0,0);
            team[1].robot[2].setSpatialLocation(0,0,0,0,0,0);
        }
        else if (period == 2) {
            team[0].robot[0].setSpatialLocation(0,0,0,0,0,0);
            team[0].robot[1].setSpatialLocation(0,0,0,0,0,0);
            team[0].robot[2].setSpatialLocation(0,0,0,0,0,0);
            team[1].robot[0].setSpatialLocation(0,0,0,0,0,0);
            team[1].robot[1].setSpatialLocation(0,0,0,0,0,0);
            team[1].robot[2].setSpatialLocation(0,0,0,0,0,0);
        }
    }

};

#endif // WORLD_MODEL_H
