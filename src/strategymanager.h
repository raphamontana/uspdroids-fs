#ifndef STRATEGYMANAGER_H
#define STRATEGYMANAGER_H

#include "worldmodel.h"
#include <QMutex>
#include <QtNetwork>
#include <QThread>

class StrategyManager : public QThread
{

    Q_OBJECT

public:

    StrategyManager(WorldModel * wm, quint16 portToListen1, quint16 portToListen2)
    {
        this->wm = wm;
        this->portToListen[0] = portToListen1;
        this->portToListen[1] = portToListen2;
        listenerSocket[0].bind(portToListen1);
        listenerSocket[1].bind(portToListen2);
    }

    void sendPositions()
    {
        QByteArray message;
        sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                wm->ball.x, wm->ball.y,
                wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
                wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
                wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy,
                wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
                wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
                wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy);
        mutex[0].lock();
        senderSocket[0].writeDatagram(message, address[0], portToSend[0]);
        mutex[0].unlock();

        sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                wm->ball.x, wm->ball.y,
                wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
                wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
                wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy,
                wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
                wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
                wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy);
        mutex[1].lock();
        senderSocket[1].writeDatagram(message, address[1], portToSend[1]);
        mutex[1].unlock();
    }

    void run()
    {
        bool received[2];
        received[0] = received[1] = false;
        decodeMessage(0, "");
    }

    WorldModel getComandos()
    {
        return(*wm);
    }

    void start()
    {
        connectedStrategies = 0;
        connect(&listenerSocket[0], SIGNAL(readyRead()), this, SLOT(connectMessage()));
        connect(&listenerSocket[1], SIGNAL(readyRead()), this, SLOT(connectMessage()));
    }

    void desconectarEstrategias()
    {
        disconnect(&listenerSocket[0], SIGNAL(readyRead()), this, SLOT(connectMessage1()));
        connect(&listenerSocket[0], SIGNAL(readyRead()), this, SLOT(receiveMessage1()));
    }

signals:

    void strategiesReady();

public slots:

    void connectMessage1()
    {
        mutex[0].lock();
        disconnect(&listenerSocket[0], SIGNAL(readyRead()), this, SLOT(connectMessage1()));
        connect(&listenerSocket[0], SIGNAL(readyRead()), this, SLOT(receiveMessage1()));
        mutex[0].unlock();
    }

    void receiveMessage1()
    {
    }

    void receiveMessage2()
    {
    }

private:

    QByteArray encodeMessage(int strategy)
    {
        QByteArray message;
        if (strategy == 0) {
            sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                    wm->ball.x, wm->ball.y,
                    wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
                    wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
                    wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy,
                    wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
                    wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
                    wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy);
            return(message);
        }
        else if (strategy == 1) {
            sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                    wm->ball.x, wm->ball.y,
                    wm->team[1].robot[0].x, wm->team[1].robot[0].y, wm->team[1].robot[0].angxy,
                    wm->team[1].robot[1].x, wm->team[1].robot[1].y, wm->team[1].robot[1].angxy,
                    wm->team[1].robot[2].x, wm->team[1].robot[2].y, wm->team[1].robot[2].angxy,
                    wm->team[0].robot[0].x, wm->team[0].robot[0].y, wm->team[0].robot[0].angxy,
                    wm->team[0].robot[1].x, wm->team[0].robot[1].y, wm->team[0].robot[1].angxy,
                    wm->team[0].robot[2].x, wm->team[0].robot[2].y, wm->team[0].robot[2].angxy);
            return(message);
        }
        else {
            message = "Bad encoded message.";
            return(message);
        }
    }

    void decodeMessage(int strategy, QByteArray message)
    {
        int read;
        if (strategy == 0 || strategy == 1) {
            read = sscanf(message.data(), "%d %d %d %d %d %d",
                   &wm->team[strategy].robot[0].leftWheel, &wm->team[strategy].robot[0].rightWheel,
                   &wm->team[strategy].robot[1].leftWheel, &wm->team[strategy].robot[1].rightWheel,
                   &wm->team[strategy].robot[2].leftWheel, &wm->team[strategy].robot[2].rightWheel);
            if (read != 6) {
                qWarning("Badly-formed message received from strategy.");
            }
            else {
                wm->team[strategy].robot[0].normalizeWheelsSpeeds();
                wm->team[strategy].robot[1].normalizeWheelsSpeeds();
                wm->team[strategy].robot[2].normalizeWheelsSpeeds();
            }
        }
        else {
            qWarning("Badly-formed message received.");
        }
    }

    WorldModel * wm;

    QMutex connectedStrategiesMutex;

    quint8 connectedStrategies;

    QMutex mutex[2];

    QUdpSocket listenerSocket[2];

    QUdpSocket senderSocket[2];

    QHostAddress address[2];

    quint16 portToListen[2];

    quint16 portToSend[2];

    QString teamName[2];

};

#endif // STRATEGYMANAGER_H
