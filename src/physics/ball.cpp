/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "ball.h"

Ball::Ball(dWorldID world, dSpaceID space)
{
    /// massa em kg, raio em m
    /// 46g de massa e 21.35mm de raio
    const double MASSA_BOLA = 0.046;
    const double RAIO_BOLA = 0.02135;
    dMass mass;
    geom = dCreateSphere(space, RAIO_BOLA); // cria a geometria do corpo
    body = dBodyCreate(world); // cria o corpo
    dGeomSetBody(geom, body); // linka a geometria ao corpo
    dMassSetSphereTotal(&mass, MASSA_BOLA, RAIO_BOLA); // atribui a massa de uma esfera
    dBodySetMass(body, &mass); // linka a massa com o objeto
    dBodySetPosition(body, 0, 0, 0.1); // seta a posicao inicial do objeto
    dBodySetLinearVel(body, 0, 0, 0); // seta a velocidade inicial do objeto

    dBodySetAutoDisableLinearThreshold(body, 0.02); // seta um limite para desativar o objeto
    dBodySetLinearDamping(body, 0.05); // seta atrito dinamico
}

Ball::~Ball()
{
    dGeomDestroy(geom);
    dBodyDestroy(body);
}

dReal* Ball::getPosicao()
{
    return (dReal*) dBodyGetPosition(body);
}

void Ball::setPosicao(double x, double y, double z)
{
    dBodySetLinearVel(body, 0, 0, 0);
    dBodySetAngularVel(body, 0, 0, 0);
    dBodySetPosition(body, x, y, z);
}
