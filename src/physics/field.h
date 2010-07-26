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
