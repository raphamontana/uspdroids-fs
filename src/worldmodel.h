#ifndef WORLDMODEL_H
#define WORLDMODEL_H

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

};

#endif // WORLDMODEL_H
