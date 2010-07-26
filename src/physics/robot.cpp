/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#include "robot.h"

Robot::Robot(dWorldID world, dSpaceID space)
{
    /** Constantes para auxiliar a criacao do robo */
    const double ALTURA_DO_CHAO = 0.010;
    const double VAO_DO_CHAO = 0.0007;
    const double TAMANHO_ROBO = 0.075;
    const double TAMANHO_RODA = 0.005;
    const double MASSA_ROBO = 1.500;
    const double MASSA_RODA = 0.050;
    const double RAIO_RODA = 0.025;
    /**
     * Robo de 7 (+0.5 das rodas) x 7.5 x 7.5 (cm), massa de 600g + (50g por roda)
     * As rodas tem 3cm de raio e 0.5cm de largura
     */

    // corpo principal do robo
    dMass mass;
    body = dBodyCreate(world); // cria o corpo
    dBodySetPosition(body, 0, 0, ALTURA_DO_CHAO+TAMANHO_ROBO/2.0); // seta a posicao inicial do objeto
    dMassSetBoxTotal(&mass, MASSA_ROBO, TAMANHO_ROBO - 2*TAMANHO_RODA, TAMANHO_ROBO, TAMANHO_ROBO-VAO_DO_CHAO); // atribui a massa de um cubo
    dBodySetMass(body, &mass); // linka a massa com o objeto
    geom = dCreateBox(space, TAMANHO_ROBO - 2*TAMANHO_RODA, TAMANHO_ROBO, TAMANHO_ROBO-VAO_DO_CHAO); // cria a geometria do corpo
    dGeomSetBody(geom, body); // linka a geometria ao corpo

    // cria as rodas
    dMass mroda; // massa das rodas
    roda1b = dBodyCreate(world); // cria o objeto
    roda2b = dBodyCreate(world);
    dQuaternion q; // auxiliar para poder rotacionar as rodas
    dQFromAxisAndAngle (q, 0, 1, 0, M_PI*0.5);
    dBodySetQuaternion (roda1b, q);
    dBodySetQuaternion (roda2b, q);
    dMassSetCylinderTotal(&mroda, MASSA_RODA, 2, RAIO_RODA, TAMANHO_RODA);
    dBodySetMass(roda1b, &mroda); // linkando corpos e massas
    dBodySetMass(roda2b, &mroda);
    roda1 = dCreateCylinder(space, RAIO_RODA, TAMANHO_RODA);
    roda2 = dCreateCylinder(space, RAIO_RODA, TAMANHO_RODA);
    dGeomSetBody(roda1, roda1b); // linkando geometrias e corpos
    dGeomSetBody(roda2, roda2b);
    dBodySetPosition(roda1b, (TAMANHO_ROBO - TAMANHO_RODA)/2.0, 0, ALTURA_DO_CHAO+RAIO_RODA-VAO_DO_CHAO); // posicionando as rodas
    dBodySetPosition(roda2b, - (TAMANHO_ROBO - TAMANHO_RODA)/2.0, 0, ALTURA_DO_CHAO+RAIO_RODA-VAO_DO_CHAO);

    // cria as juntas
    suspensao[0] = dJointCreateHinge(world, 0); // direita
    dJointAttach(suspensao[0], body, roda1b);
    const dReal *a = dBodyGetPosition (roda1b);
    dJointSetHingeAnchor (suspensao[0], a[0], a[1], a[2]);
    dJointSetHingeAxis (suspensao[0], 1, 0, 0);

    suspensao[1] = dJointCreateHinge(world, 0); // esquerda
    dJointAttach(suspensao[1], body, roda2b);
    const dReal *b = dBodyGetPosition (roda2b);
    dJointSetHingeAnchor (suspensao[1], b[0], b[1], b[2]);
    dJointSetHingeAxis (suspensao[1], 1, 0, 0);
}


Robot::~Robot()
{
    dJointDestroy(suspensao[0]);
    dJointDestroy(suspensao[1]);
    dBodyDestroy(roda1b);
    dBodyDestroy(roda2b);
    dGeomDestroy(roda1);
    dGeomDestroy(roda2);
    dBodyDestroy(body);
    dGeomDestroy(geom);
}


double * Robot::getVelocidade()
{
    return (double*) dBodyGetLinearVel(body);
}

void Robot::setVelocidade(double esq, double dir)
{
    /** Velocidade maxima para as juntas: 20 * Raio da roda (2,5cm) = 0.5m/s */
    /** @todo Definir um padrao para esta velocidade */

    // (14g.cm / 5450rpm -> ActionMotors : redução 7.5:1)
    //double rpm = 5450; // rpm
    //double torque = 0.001372931; // N.m
    //double reducao = 7.5/1;

    //( 5mN.m/ 8000 rpm -> Fallhauber : redução 10:1 )
    double rpm = 8000;
    double torque = 0.005;
    double reducao = 10.0/1;

    double vel_max = ((rpm / 60.0) / reducao) * M_PI;
    torque = torque*reducao;

    dir = ( dir > vel_max ) ? vel_max : ( dir < -vel_max ) ? -vel_max : dir;
    esq = ( esq > vel_max ) ? vel_max : ( esq < -vel_max ) ? -vel_max : esq;

    //seta velocidades das rodas
    dJointSetHingeParam (suspensao[0],dParamVel, -dir); // Velocidade angular maxima (Hz)
    dJointSetHingeParam(suspensao[0], dParamFMax, torque); // Torque (N.m)
    dJointSetHingeParam (suspensao[1],dParamVel, -esq);
    dJointSetHingeParam(suspensao[1], dParamFMax, torque);
}

dReal* Robot::getPosicao()
{
    return((dReal*) dBodyGetPosition(body));
}

void Robot::setPosicao(double x, double y, double z)
{
    const double TAMANHO_ROBO = 0.075;
    const double TAMANHO_RODA = 0.010;
    const double RAIO_RODA = 0.025;
    dBodySetLinearVel(body, 0, 0, 0);
    dBodySetAngularVel(body, 0, 0, 0);
    dMatrix3 R; // rotacionar robos caidos
    dRFromEulerAngles(R, 0, 0, 0);
    dBodySetRotation(body, R);
    dBodySetPosition(body, x, y, z);
    dBodySetPosition(roda1b, x + (TAMANHO_ROBO - TAMANHO_RODA)/2.0, y, (z-TAMANHO_ROBO/2.0) + RAIO_RODA-0.005 );
    dBodySetPosition(roda2b, x - (TAMANHO_ROBO - TAMANHO_RODA)/2.0, y, (z-TAMANHO_ROBO/2.0) + RAIO_RODA-0.005 );
}

void Robot::getAngulo(int *angGraus)
{
    const dReal* aux = dBodyGetRotation(body);
    double angle_x, angle_y, angle_z;
    double tr_x, tr_y;
    double C;
    const double RADIANS = 180.0/M_PI;
    angle_y = asin(aux[2]);
    C = cos(angle_y);
    angle_y *= RADIANS;
    if (fabs(C) > 0.005)
    {
        tr_x     =  aux[10] / C;
        tr_y     = -aux[6]  / C;
        angle_x  = atan2( tr_y, tr_x ) * RADIANS;
        tr_x     =  aux[0] / C;
        tr_y     = -aux[1] / C;
        angle_z  = atan2( tr_y, tr_x ) * RADIANS;
    }
    else {
        angle_x  = 0;
        tr_x     = aux[5];
        tr_y     = aux[4];
        angle_z  = atan2( tr_y, tr_x ) * RADIANS;
    }
            angle_z = ceil(angle_z);
            angle_y = ceil(angle_y);
            angle_x = ceil(angle_x);
    if      (angle_x <   0) angle_x += 360;
    else if (angle_x >= 360) angle_x -= 360;
    if      (angle_y <   0) angle_y += 360;
    else if (angle_y >= 360) angle_y -= 360;
    if      (angle_z <   0) angle_z += 360;
    else if (angle_z >= 360) angle_z -= 360;
    angGraus[0] = angle_z; // xy
    angGraus[1] = angle_y; // xz
    angGraus[2] = angle_x; // yz
}
