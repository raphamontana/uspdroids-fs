#ifndef GERENCIADORJOGO_H
#define GERENCIADORJOGO_H

#include "worldmodel.h"

class GameManager
{
public:

    GameManager(WorldModel * wm)
    {
        this->wm = wm;
    }

    void start()
    {
    }

    void getPosicoes()
    {
        wm->ball.x = 0;
    }

    void receberComandos()
    {
        wm->team[0].robot[0].setWheelsSpeed(0, 0);
    }

    void passoDeJogo()
    {
    }

    WorldModel * wm;

};

#endif // GERENCIADORJOGO_H
