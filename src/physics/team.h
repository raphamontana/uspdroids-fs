#ifndef ODE_EQUIPE_H
#define ODE_EQUIPE_H

#include <ode/ode.h>

#include "../mensagens.h"
#include "ode_robo.h"

class ODE_Equipe
{
public:

    ODE_Equipe(dWorldID world, dSpaceID space, int lado)
    {
        robo1 = new ODE_Robo(world, space);
        robo2 = new ODE_Robo(world, space);
        robo3 = new ODE_Robo(world, space);
        if (lado == 0) {
            robo1->setPosicao(0.30,        -0.20,        0.10);
            robo2->setPosicao(0.30 + 0.20, -0.20 + 0.20, 0.10);
            robo3->setPosicao(0.30 + 0.40, -0.20 + 0.40, 0.10);
        }
        else if (lado == 1) {
            robo1->setPosicao(-0.50,        0.-0, 0.10);
            robo2->setPosicao(-0.50 + 0.10, 0.10, 0.10);
            robo3->setPosicao(-0.50 + 0.20, 0.20, 0.10);
        }
        else {
            robo1->setPosicao(0.0, 0.0, 0.0);
            robo2->setPosicao(0.0, 0.0, 0.0);
            robo3->setPosicao(0.0, 0.0, 0.0);
        }
    }


    ~ODE_Equipe()
    {
        delete(robo1);
        delete(robo2);
        delete(robo3);
    }


    void setVelocidades(Mensagem_Radio* mr, int team)
    {
        robo1->setVelocidade(mr->velocidade[team][0][0], mr->velocidade[team][0][1]);
        robo2->setVelocidade(mr->velocidade[team][1][0], mr->velocidade[team][1][1]);
        robo3->setVelocidade(mr->velocidade[team][2][0], mr->velocidade[team][2][1]);
    }


    dReal* getPosicao(int robo)
    {
        if (robo == 0) return(robo1->getPosicao());
        else if (robo == 1) return(robo2->getPosicao());
        else return(robo3->getPosicao());
    }


    dReal* getAngulo(int team)
    {
        if (team == 0)
             return(robo1->getAngulo());
        else return(robo2->getAngulo());
    }


    void setPosicao(int n, double x, double y, double z)
    {
        if (n == 0) robo1->setPosicao(x, y, z);
        if (n == 1) robo2->setPosicao(x, y, z);
        if (n == 2) robo3->setPosicao(x, y, z);
    }

private:

    ODE_Robo* robo1;

    ODE_Robo* robo2;

    ODE_Robo* robo3;
};

#endif // ODE_EQUIPE_H
