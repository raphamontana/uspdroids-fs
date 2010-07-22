#ifndef ODE_BOLA_H
#define ODE_BOLA_H

#include <ode/ode.h>


class ODE_Bola {
public:

    ODE_Bola(dWorldID world, dSpaceID space)
    {
        const double RAIO_BOLA = 0.02135;
        dMass mass;
        geom = dCreateSphere(space, RAIO_BOLA);
        body = dBodyCreate(world);
        dGeomSetBody(geom, body);
        dMassSetSphereTotal(&mass, 0.046, RAIO_BOLA);
        dBodySetMass(body, &mass);
        dBodySetPosition(body, 0, 0, 0.1);
        dBodySetLinearVel(body, 0, 0, 0);
        dBodySetAutoDisableLinearThreshold(body, 0.02);
        dBodySetLinearDamping(body, 0.05);
    }


    /*ODE_Bola(double massa, double raio, dWorldID world, dSpaceID space)
    {
        dMass mass;
        geom = dCreateSphere(space, raio);
        body = dBodyCreate(world);
        dGeomSetBody(geom, body);
        dMassSetSphereTotal(&mass, massa, raio);
        dBodySetMass(body, &mass);
        dBodySetPosition(body, 0, 0, 0.1);
        dBodySetLinearVel(body, 0, 0, 0);
    }
    */


    ~ODE_Bola()
    {
        dGeomDestroy(geom);
        dBodyDestroy(body);
    }


    dReal* getPosicao()
    {
        return (dReal*) dBodyGetPosition(body);
    }


    void setPosicao(double x, double y, double z)
    {
        dBodySetLinearVel(body, 0, 0, 0);
        dBodySetAngularVel(body, 0, 0, 0);
        dBodySetPosition(body, x, y, z);
    }

private:

    dBodyID body;

    dGeomID geom;

};

#endif // ODE_BOLA_H

