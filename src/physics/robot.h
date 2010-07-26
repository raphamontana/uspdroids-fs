#ifndef ODE_ROBO_H
#define ODE_ROBO_H

#define dDOUBLE
#include <ode/ode.h>

/**
 * Classe que implementa um robo. O robo tambem eh um objeto.
 * Utiliza o corpo e a geometria de Objeto para o corpo do robo.
 * Faz especializacao do metodo setPosicao().
*/
class Robot
{

public:

    /**
     * Construtor preferencial
     * @param  world   mundo no qual o robo sera criado
     * @param  space   espaco no qual ele sera inserido
    */
    Robot(dWorldID world, dSpaceID space);

    /** Destrutor padrao */
    ~Robot();

    /**
     * Atribui uma velocidade para o robo
     * @param  dir velocidade desejada para a roda direita
     * @param  esq velocidade desejada para a roda esquerda
     */
    void setVelocidade(double esq, double dir);

    /**
     * Obtem a velocidade linear atual do robo
     * @return x,y,z da velocidade
     */
    double* getVelocidade();

    dReal getPosicao();

    /**
     * Atribui uma posicao para o robo. Especializacao de Objeto::setPosicao().
     * Recoloca o robo na posicao correta (caso tenha caido).
     * @param  x   posicao em x
     * @param  y   posicao em y
     * @param  z   posicao em z
     */
    void setPosicao(double x, double y, double z);

    void getAngulo(int *angGraus);

private:

    dBodyID body;

    dGeomID geom;

    /** Corpo da roda direita */
    dBodyID roda1b;

    /** Corpo da roda esquerda */
    dBodyID roda2b;

    /** Geometria da roda direita */
    dGeomID roda1;

    /** Geometria da roda esquerda */
    dGeomID roda2;

    /** Juntas entre as rodas e o corpo [direita, esquerda] */
    dJointID suspensao[2];

};

#endif // ODE_ROBO_H
