/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef BALL_H
#define BALL_H

#define dDOUBLE
#include <ode/ode.h>

/**
 * Classe que implementa uma bola. A bola tambem eh um objeto.
 * Utiliza o corpo e a geometria de Objeto para implementar a bola.
 */
class Ball
{

public:

    /**
     * Construtor preferencial
     * @param  world   mundo no qual a bola sera criada
     * @param  space   espaco no qual ela sera inserida
    */
    Ball(dWorldID world, dSpaceID space);

    /**
     * Destrutor padrao
     */
    ~Ball();

    dReal* getPosicao();

    void setPosicao(double x, double y, double z);

private:

    dBodyID body;

    dGeomID geom;

};

#endif // BALL_H
