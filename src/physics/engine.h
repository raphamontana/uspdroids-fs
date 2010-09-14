/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "../worldmodel.h"

/**
 *
 */
class Engine
{

public:

    /**
     *
     */
    Engine();

    /**
     *
     */
    void setWheelsSpeed(WorldModel wm);

    /**
     *
     */
    WorldModel getWorldModel();

};

#endif // ENGINE_H
