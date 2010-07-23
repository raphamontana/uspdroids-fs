/********************************************************************************
** Form generated from reading UI file 'janelaprincipal.ui'
**
** Created: Thu 22. Jul 20:53:16 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JANELAPRINCIPAL_H
#define UI_JANELAPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JanelaPrincipal
{
public:
    QAction *actionExit;
    QAction *actionContents;
    QAction *actionAbout;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *simulatorTab;
    QWidget *monitorTab;
    QWidget *strategyTab_1;
    QWidget *strategyTab_2;
    QMenuBar *menuBar;
    QMenu *menuSystem;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *JanelaPrincipal)
    {
        if (JanelaPrincipal->objectName().isEmpty())
            JanelaPrincipal->setObjectName(QString::fromUtf8("JanelaPrincipal"));
        JanelaPrincipal->resize(800, 600);
        actionExit = new QAction(JanelaPrincipal);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionContents = new QAction(JanelaPrincipal);
        actionContents->setObjectName(QString::fromUtf8("actionContents"));
        actionAbout = new QAction(JanelaPrincipal);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(JanelaPrincipal);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 800, 580));
        simulatorTab = new QWidget();
        simulatorTab->setObjectName(QString::fromUtf8("simulatorTab"));
        tabWidget->addTab(simulatorTab, QString());
        monitorTab = new QWidget();
        monitorTab->setObjectName(QString::fromUtf8("monitorTab"));
        tabWidget->addTab(monitorTab, QString());
        strategyTab_1 = new QWidget();
        strategyTab_1->setObjectName(QString::fromUtf8("strategyTab_1"));
        tabWidget->addTab(strategyTab_1, QString());
        strategyTab_2 = new QWidget();
        strategyTab_2->setObjectName(QString::fromUtf8("strategyTab_2"));
        tabWidget->addTab(strategyTab_2, QString());
        JanelaPrincipal->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(JanelaPrincipal);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuSystem = new QMenu(menuBar);
        menuSystem->setObjectName(QString::fromUtf8("menuSystem"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        JanelaPrincipal->setMenuBar(menuBar);
        statusBar = new QStatusBar(JanelaPrincipal);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        JanelaPrincipal->setStatusBar(statusBar);

        menuBar->addAction(menuSystem->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuSystem->addAction(actionExit);
        menuHelp->addAction(actionContents);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);

        retranslateUi(JanelaPrincipal);
        QObject::connect(actionExit, SIGNAL(activated()), JanelaPrincipal, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(JanelaPrincipal);
    } // setupUi

    void retranslateUi(QMainWindow *JanelaPrincipal)
    {
        JanelaPrincipal->setWindowTitle(QApplication::translate("JanelaPrincipal", "JanelaPrincipal", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("JanelaPrincipal", "Exit", 0, QApplication::UnicodeUTF8));
        actionContents->setText(QApplication::translate("JanelaPrincipal", "Contents", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("JanelaPrincipal", "About", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(simulatorTab), QApplication::translate("JanelaPrincipal", "Simulator", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(monitorTab), QApplication::translate("JanelaPrincipal", "Monitor", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(strategyTab_1), QApplication::translate("JanelaPrincipal", "Strategy 1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(strategyTab_2), QApplication::translate("JanelaPrincipal", "Strategy 2", 0, QApplication::UnicodeUTF8));
        menuSystem->setTitle(QApplication::translate("JanelaPrincipal", "System", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("JanelaPrincipal", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class JanelaPrincipal: public Ui_JanelaPrincipal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JANELAPRINCIPAL_H
