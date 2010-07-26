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
