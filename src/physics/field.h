/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef FIELD_H
#define FIELD_H

#define dDOUBLE
#include <ode/ode.h>

/**
 * Cria um ambiente (campo) na ODE
 */
class Field
{

public:

    /**
     * Construtor preferencial
     * @param  space   espaco no qual ele sera inserido
     * @ref ODE F.A.Q.
     */
    Field(dSpaceID space);

    /**
     * Destrutor padrao
     */
    ~Field();

private:

    /** O chao do ambiente */
    dGeomID chao;

    /** As paredes do campo */
    dGeomID parede[6];

    /** As paredes que formam o gol */
    dGeomID gol[6];

    /** As quinas do campo */
    dGeomID canto[4];

};

#endif // FIELD_H
