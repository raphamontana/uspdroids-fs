#ifndef ODE_CAMPO_H
#define ODE_CAMPO_H

#include <ode/ode.h>


class ODE_Campo {
public:

    ODE_Campo(dSpaceID space)
    {
        const double CAMPO_LARGURA = 1.50;
        const double CAMPO_ALTURA  = 1.30;
        // objetos estaticos devem ser dGeomID sem dBodyID associados (vide FAQ da ODE)
        chao = dCreatePlane (space,0.0,0.0,1.0,0.0);

        // cria as paredes e as posiciona
        parede[0] = dCreateBox(space, 1.50, 0.025, 0.05);
        dGeomSetPosition(parede[0], 0, -CAMPO_ALTURA/2.0 - 0.0125, 0.025);
        parede[1] = dCreateBox(space, 1.50, 0.025, 0.05);
        dGeomSetPosition(parede[1], 0, CAMPO_ALTURA/2.0 + 0.0125, 0.025);
        parede[2] = dCreateBox(space, 0.025, 0.45, 0.05);
        dGeomSetPosition(parede[2], CAMPO_LARGURA/2.0 + 0.0125, CAMPO_ALTURA/3.0, 0.025);
        parede[3] = dCreateBox(space, 0.025, 0.45, 0.05);
        dGeomSetPosition(parede[3], CAMPO_LARGURA/2.0 + 0.0125, -CAMPO_ALTURA/3.0, 0.025);
        parede[4] = dCreateBox(space, 0.025, 0.45, 0.05);
        dGeomSetPosition(parede[4], -CAMPO_LARGURA/2.0 - 0.0125, -CAMPO_ALTURA/3.0, 0.025);
        parede[5] = dCreateBox(space, 0.025, 0.45, 0.05);
        dGeomSetPosition(parede[5], -CAMPO_LARGURA/2.0 - 0.0125, CAMPO_ALTURA/3.0, 0.025);

        // cria os gols
        gol[0] =  dCreateBox(space, 0.10, 0.025, 0.05);
        dGeomSetPosition(gol[0], -CAMPO_LARGURA/2.0 - 0.075, CAMPO_ALTURA/3.0 - 0.225 + 0.0125, 0.025);
        gol[1] =  dCreateBox(space, 0.10, 0.025, 0.05);
        dGeomSetPosition(gol[1], -CAMPO_LARGURA/2.0 - 0.075, -CAMPO_ALTURA/3.0 + 0.225 - 0.0125, 0.025);
        gol[2] =  dCreateBox(space, 0.10, 0.025, 0.05);
        dGeomSetPosition(gol[2], CAMPO_LARGURA/2.0 + 0.075, CAMPO_ALTURA/3.0 - 0.225 + 0.0125, 0.025);
        gol[3] =  dCreateBox(space, 0.10, 0.025, 0.05);
        dGeomSetPosition(gol[3], CAMPO_LARGURA/2.0 + 0.075, -CAMPO_ALTURA/3.0 + 0.225 - 0.0125, 0.025);
        gol[4] =  dCreateBox(space, 0.025, 0.425, 0.05);
        dGeomSetPosition(gol[4], -CAMPO_LARGURA/2.0 - 0.1125, 0, 0.025);
        gol[5] =  dCreateBox(space, 0.025, 0.425, 0.05);
        dGeomSetPosition(gol[5], CAMPO_LARGURA/2.0 + 0.1125, 0, 0.025);

        // cria as quinas do campo
        canto[0] = dCreateBox(space, 0.30, 1.07, 0.05);
        dQuaternion q; // apoio para rotacionar o cubo usado pra fazer a quina
        dQFromAxisAndAngle (q, 0, 0, 1, -M_PI/4.0);
        dGeomSetQuaternion(canto[0], q);
        dGeomSetPosition(canto[0], 0.3535+CAMPO_LARGURA/2.0, 0.3535+CAMPO_ALTURA/2.0, 0.025);
        canto[1] = dCreateBox(space, 0.30, 1.07, 0.05);
        dQFromAxisAndAngle (q, 0, 0, 1, M_PI/4.0);
        dGeomSetQuaternion(canto[1], q);
        dGeomSetPosition(canto[1], -0.3535-CAMPO_LARGURA/2.0, 0.3535+CAMPO_ALTURA/2.0, 0.025);
        canto[2] = dCreateBox(space, 0.30, 1.07, 0.05);
        dQFromAxisAndAngle (q, 0, 0, 1, -M_PI/4.0);
        dGeomSetQuaternion(canto[2], q);
        dGeomSetPosition(canto[2], -0.3535-CAMPO_LARGURA/2.0, -0.3535-CAMPO_ALTURA/2.0, 0.025);
        canto[3] = dCreateBox(space, 0.30, 1.07, 0.05);
        dQFromAxisAndAngle (q, 0, 0, 1, M_PI/4.0);
        dGeomSetQuaternion(canto[3], q);
        dGeomSetPosition(canto[3], 0.3535+CAMPO_LARGURA/2.0, -0.3535-CAMPO_ALTURA/2.0, 0.025);
    }


    ~ODE_Campo()
    {
        for ( int i = 0; i < 6; i++ ) {
            dGeomDestroy(parede[i]);
            dGeomDestroy(gol[i]);
        }
        for ( int i = 0; i < 4; i++ ) {
            dGeomDestroy(canto[i]);
        }
    }

private:
    dGeomID chao;

    dGeomID parede[6];

    dGeomID gol[6];

    dGeomID canto[4];
};

#endif // ODE_CAMPO_H

