/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef ODE_EQUIPE_H
#define ODE_EQUIPE_H

#include "../worldmodel.h"
#include "robot.h"

/**
 * Classe para a criacao de um time.
 * Instancia os robos.
 * Pode receber comandos para os robos e setar sua posicao
 */
class Team
{
public:

    /**
     * Construtor preferencial. Cria um time de 3 robos.
     * @param	world		mundo da simulacao
     * @param	space		espaco da simulacao
     * @param	side		lado do campo em que o time defende
     */
    Team(dWorldID world, dSpaceID space);

    /** Destrutor padrao */
    ~Team();


    void setVelocidades(WorldModel * wm, int team);

    /**
     * Obtem as posicoes dos robos do time
     * @param[out]     v   retorna um vetor de informacoes para o gerenciador de jogo
     */
    dReal getPosicao(int robo);


    dReal getAngulo(int team);

    /**
     * Atribui uma posicao para um robo
     * @param	n	numero do robo
     * @param	x	posicao em x
     * @param	y	posicao em y
     * @param	z	posicao em z
     */
    void setPosicao(int n, double x, double y, double z);

private:

    Robot * robo1;

    Robot * robo2;

    Robot * robo3;
};

#endif // ODE_EQUIPE_H
