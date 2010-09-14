/*
    Copyright (C) 2010  Doi, Montanari, Silva

    This file is part of the USPDroids Football Simulator.

    The USPDroids Football Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/

#ifndef FRONT_END_H
#define FRONT_END_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSplashScreen>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <unistd.h>

class FrontEnd : public QMainWindow
{

    Q_OBJECT

public:

    FrontEnd(QWidget *parent = 0);

    ~FrontEnd();

private:

    void setupUi();

    void retranslateUi();

    QSplashScreen * splash;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuSimulator;
    QMenu *menuHelp;
    QStatusBar *statusBar;

};

#endif // FRONT_END_H
