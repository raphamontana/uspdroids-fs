#ifndef GERENCIADORVISUALIZADORES_H
#define GERENCIADORVISUALIZADORES_H

#include "worldmodel.h"
#include <QMutex>
#include <QtNetwork>
#include <QVector>

class ViewerManager : QObject
{

    Q_OBJECT

public:

    ViewerManager(WorldModel * wm, quint16 viewerPort)
    {
        this->wm = wm;
        this->viewerPort = viewerPort;
        listenerSocket.bind(viewerPort);
        connect(&listenerSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    }

    void transmitData()
    {
        mutex.lock();
        int size = addresses.size();
        if (size) {
            QByteArray message;
            sprintf(message.data(), "O %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                    wm->ball.x,                 wm->ball.y,                 wm->ball.z,
                    wm->team[0].robot[0].x,     wm->team[0].robot[0].y,     wm->team[0].robot[0].z,
                    wm->team[0].robot[0].angxy, wm->team[0].robot[0].angxz, wm->team[0].robot[0].angyz,
                    wm->team[0].robot[1].x,     wm->team[0].robot[1].y,     wm->team[0].robot[1].z,
                    wm->team[0].robot[1].angxy, wm->team[0].robot[1].angxz, wm->team[0].robot[1].angyz,
                    wm->team[0].robot[2].x,     wm->team[0].robot[2].y,     wm->team[0].robot[2].z,
                    wm->team[0].robot[2].angxy, wm->team[0].robot[2].angxz, wm->team[0].robot[2].angyz,
                    wm->team[1].robot[0].x,     wm->team[1].robot[0].y,     wm->team[1].robot[0].z,
                    wm->team[1].robot[0].angxy, wm->team[1].robot[0].angxz, wm->team[1].robot[0].angyz,
                    wm->team[1].robot[1].x,     wm->team[1].robot[1].y,     wm->team[1].robot[1].z,
                    wm->team[1].robot[1].angxy, wm->team[1].robot[1].angxz, wm->team[1].robot[1].angyz,
                    wm->team[1].robot[2].x,     wm->team[1].robot[2].y,     wm->team[1].robot[2].z,
                    wm->team[1].robot[2].angxy, wm->team[1].robot[2].angxz, wm->team[1].robot[2].angyz);
            for (register int i = 0; i < size; i++) {
                senderSocket.writeDatagram(message, addresses.at(i).first, addresses.at(i).second);
            }
        }
        mutex.unlock();
    }

    void finalize()
    {
        mutex.lock();
        for (register int i = 0; i < addresses.size(); i++) {
            senderSocket.writeDatagram("End of game", addresses.at(i).first, addresses.at(i).second);
        }
        addresses.clear();
        mutex.unlock();
    }

public slots:

    void receiveMessage()
    {
        QByteArray datagram;
        QHostAddress host;
        quint16 port;
        datagram.resize(listenerSocket.pendingDatagramSize());
        listenerSocket.readDatagram(datagram.data(), listenerSocket.pendingDatagramSize(), &host, &port);
        if (datagram == "Connection request") {
            QPair<QHostAddress, quint16> pair(host, port);
            mutex.lock();
            addresses.push_back(pair);
            mutex.unlock();
            senderSocket.writeDatagram("Request accepted", host, port);
        }
    }

private:

    WorldModel * wm;

    quint16 viewerPort;

    QUdpSocket listenerSocket;

    QUdpSocket senderSocket;

    QMutex mutex; //Protege a lista de enderecos;

    QVector< QPair<QHostAddress, quint16> > addresses;

};

#endif // GERENCIADORVISUALIZADORES_H
