#ifndef ODE_ROBO_H
#define ODE_ROBO_H

#include <ode/ode.h>


class ODE_Robo {
public:

    ODE_Robo(dWorldID world, dSpaceID space)
    {
        const double ALTURA_DO_CHAO = 0.020;
        const double VAO_DO_CHAO = 0.002;
        const double TAMANHO_ROBO = 0.075;
        const double TAMANHO_RODA = 0.010;
        const double MASSA_ROBO = 0.450;
        const double MASSA_RODA = 0.012;
        const double RAIO_RODA = 0.025;
        dMass mass;
        body = dBodyCreate(world);
        dBodySetPosition(body, 0, 0, ALTURA_DO_CHAO+TAMANHO_ROBO/2.0);
        dMassSetBoxTotal(&mass, MASSA_ROBO, TAMANHO_ROBO - 2*TAMANHO_RODA, TAMANHO_ROBO, TAMANHO_ROBO-VAO_DO_CHAO);
        dBodySetMass(body, &mass);
        geom = dCreateBox(space, TAMANHO_ROBO - 2*TAMANHO_RODA, TAMANHO_ROBO, TAMANHO_ROBO-VAO_DO_CHAO);
        dGeomSetBody(geom, body);
        dMass mroda;
        roda1b = dBodyCreate(world);
        roda2b = dBodyCreate(world);
        dQuaternion q;
        dQFromAxisAndAngle (q, 0, 1, 0, M_PI*0.5);
        dBodySetQuaternion (roda1b, q);
        dBodySetQuaternion (roda2b, q);
        dMassSetCylinderTotal(&mroda, MASSA_RODA, 2, RAIO_RODA, TAMANHO_RODA);
        dBodySetMass(roda1b, &mroda);
        dBodySetMass(roda2b, &mroda);
        roda1 = dCreateCylinder(space, RAIO_RODA, TAMANHO_RODA);
        roda2 = dCreateCylinder(space, RAIO_RODA, TAMANHO_RODA);
        dGeomSetBody(roda1, roda1b);
        dGeomSetBody(roda2, roda2b);
        dBodySetPosition(roda1b, (TAMANHO_ROBO - TAMANHO_RODA)/2.0, 0, ALTURA_DO_CHAO+RAIO_RODA-VAO_DO_CHAO);
        dBodySetPosition(roda2b, - (TAMANHO_ROBO - TAMANHO_RODA)/2.0, 0, ALTURA_DO_CHAO+RAIO_RODA-VAO_DO_CHAO);
        suspensao[0] = dJointCreateHinge(world, 0);
        dJointAttach(suspensao[0], body, roda1b);
        const dReal *a = dBodyGetPosition (roda1b);
        dJointSetHingeAnchor (suspensao[0], a[0], a[1], a[2]);
        dJointSetHingeAxis (suspensao[0], 1, 0, 0);
        suspensao[1] = dJointCreateHinge(world, 0);
        dJointAttach(suspensao[1], body, roda2b);
        const dReal *b = dBodyGetPosition (roda2b);
        dJointSetHingeAnchor (suspensao[1], b[0], b[1], b[2]);
        dJointSetHingeAxis (suspensao[1], 1, 0, 0);
    }


    ~ODE_Robo()
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


    double* getVelocidade()
    {
        return (double*) dBodyGetLinearVel(body);
    }


    void setVelocidade(double esq, double dir)
    {
        const int vel_max = 20;
        esq = ( esq > vel_max ) ? vel_max : ( esq < -vel_max ) ? -vel_max : esq;
        dir = ( dir > vel_max ) ? vel_max : ( dir < -vel_max ) ? -vel_max : dir;
        dJointSetHingeParam (suspensao[0],dParamVel, -dir);
        dJointSetHingeParam(suspensao[0], dParamFMax, 0.1);
        dJointSetHingeParam (suspensao[1],dParamVel, -esq);
        dJointSetHingeParam(suspensao[1], dParamFMax, 0.1);
    }


    dReal* getPosicao()
    {
        return((dReal*) dBodyGetPosition(body));
    }


    void setPosicao(double x, double y, double z)
    {
        const double TAMANHO_ROBO = 0.075;
        const double TAMANHO_RODA = 0.010;
        const double RAIO_RODA = 0.025;
        dBodySetLinearVel(body, 0, 0, 0);
        dBodySetAngularVel(body, 0, 0, 0);
        dMatrix3 R;
        dRFromEulerAngles(R, 0, 0, 0);
        dBodySetRotation(body, R);
        dBodySetPosition(body, x, y, z);
        dBodySetPosition(roda1b, x + (TAMANHO_ROBO - TAMANHO_RODA)/2.0, y, (z-TAMANHO_ROBO/2.0) + RAIO_RODA-0.005 );
        dBodySetPosition(roda2b, x - (TAMANHO_ROBO - TAMANHO_RODA)/2.0, y, (z-TAMANHO_ROBO/2.0) + RAIO_RODA-0.005 );
    }


    void getAngulo(int *angGraus)
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

private:

    dBodyID body;

    dGeomID geom;

    dBodyID roda1b;

    dBodyID roda2b;

    dGeomID roda1;

    dGeomID roda2;

    dJointID suspensao[2];
};

#endif // ODE_ROBO_H

