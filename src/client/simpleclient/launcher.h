/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "conexao.h"

class Launcher : public QObject
{
    Q_OBJECT

public slots:

    void launch()
    {
        Conexao conn("Montanari", QHostAddress::LocalHost);
        while (true) {
            conn.recebe();
            conn.envia();
        }
    }
};

#endif // LAUNCHER_H
