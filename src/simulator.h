#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <QObject>
#include "strategymanager.h"
#include "gamemanager.h"
#include "viewermanager.h"
#include "worldmodel.h"

class Simulator : QObject
{

    Q_OBJECT

public:

    Simulator(unsigned int portToListen0, unsigned int portToListen1, unsigned int viewerPort)
    {
        gm = new GameManager(&wm);
        sm = new StrategyManager(&wm, portToListen0, portToListen1);
        vm = new ViewerManager(&wm, viewerPort);
        connect(sm, SIGNAL(strategiesReady()), this, SLOT(execute()));
    }

    ~Simulator()
    {
        delete(gm);
        delete(sm);
        delete(vm);
    }

    void start()
    {
        chronometer = 0;
        goals[0]    = 0;
        goals[1]    = 0;
        sm->start();
        gm->start();
        puts("Simulador iniciado.");
        puts("Aguardando conexao das estrategias...");
        puts("Estrategias conectadas.\nPartida iniciada.");
        gm->getPosicoes();
        sm->sendPositions();
    }

    void finish()
    {
        printf("Tempo: %dmin %ds\n", chronometer/3600, chronometer%3600/60);
        puts("Fim de partida.");
        printf("Placar final: Azul %d x %d Amarelo\n", goals[0], goals[1]);
        if (goals[0] > goals[1]) {
                printf("%s venceu.\n", teamName[0].toAscii().data());
        } else if (goals[0] < goals[1]) {
                printf("%s venceu.\n", teamName[1].toAscii().data());
        } else puts("Empate.");
        sm->desconectarEstrategias();
        vm->finalize();
        if (teamName[0] != NULL) teamName[0].clear();
        if (teamName[1] != NULL) teamName[1].clear();
        puts("Simulador encerrado.");
    }

private slots:

    void execute()
    {
        WorldModel wm;
        while (chronometer < 36000)//360 = 6 seg
        {
            sm->start();
            sm->wait(17);
            gm->passoDeJogo();
            sm->sendPositions();
            vm->transmitData();
            if (chronometer%60*16 == 0) {
                printf("Tempo: %dmin %ds\n", chronometer/3600, chronometer%3600/60);
            }
            chronometer++;
        }
    }

private:

    WorldModel wm;

    GameManager * gm;

    StrategyManager * sm;

    ViewerManager * vm;

    unsigned int chronometer;

    unsigned int goals[2];

    QString teamName[2];

};

#endif // SIMULATOR_H
