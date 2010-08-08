#ifndef STRATEGIES_MANAGER_H
#define STRATEGIES_MANAGER_H

#include "connection/strategyconnection.h"

class StrategiesManager
{
public:
    /**
     * Obtem o endereco do modelo de mundo
     */
    StrategiesManager(WorldModel * wm, quint16 port0, quint16 port1);

    /**
     *
     */
    void initialize();

    /**
     *
     */
    void waitStrategies();

    /**
     * Libera duas threads para receber mensagem das estrategias
     */
    void recvCommands();

    /**
     * Send the positions of the objects in the world model to the strategies.
     */
    void transmitData();

    /**
     *
     */
    void finalize();

private:

    /**
     *
     */
    void decodeMessage(int strategy, QByteArray message);

    /**
     *
     */
    WorldModel * wm;

    /**
     *
     */
    StrategyConnection * sc[2];

};

#endif // STRATEGIES_MANAGER_H
