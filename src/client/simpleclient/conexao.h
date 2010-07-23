#ifndef CONEXAO_H
#define CONEXAO_H

#include <QCoreApplication>
#include <QByteArray>
#include <QtNetwork>

class SleeperThread : QThread
{
public:
    static void msleep(unsigned long msecs) {
        QThread::msleep(msecs);
    }
};

class Conexao
{
public:
    Conexao(QString teamName, QHostAddress host) {
        datagram = "Connection request: ";
        datagram.append(teamName);
        socket.connectToHost(host, 26000, QIODevice::ReadWrite);
        puts("Awaiting server connection...");
        socket.waitForConnected();
        while (!socket.hasPendingDatagrams()) {
            socket.write(datagram);
            SleeperThread::msleep(1000);
        }
        datagram.resize(socket.pendingDatagramSize());
        datagram = socket.read(socket.pendingDatagramSize());
        if (datagram != "Request aceppted.") {
            socket.disconnectFromHost();
            socket.connectToHost(host, 26001, QIODevice::ReadWrite);
            socket.waitForConnected();
            while (!socket.hasPendingDatagrams()) {
                socket.write(datagram);
                SleeperThread::msleep(1000);
            }
            datagram.resize(socket.pendingDatagramSize());
            datagram = socket.read(socket.pendingDatagramSize());
            if (datagram != "Request aceppted") {
                puts("Connection rejected!");
                exit(0);
            }
        }
        puts("Connected!");
    }

    ~Conexao()
    {
        socket.disconnectFromHost();
    }

    void recebe()
    {
        socket.waitForReadyRead();
        datagram.resize(socket.pendingDatagramSize());
        datagram = socket.read(socket.pendingDatagramSize());
    }

    void envia()
    {
        socket.write("0 0 0 0 0 0");
        socket.waitForBytesWritten();
    }

private:

    QUdpSocket socket;

    QByteArray datagram;

};

#endif // CONEXAO_H
