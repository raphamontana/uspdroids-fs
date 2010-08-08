#include "frontend.h"

FrontEnd::FrontEnd(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
}

void FrontEnd::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(600, 400);
    actionExit = new QAction(this);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionAbout = new QAction(this);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    pushButton = new QPushButton(centralWidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(250, 160, 90, 27));
    setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 600, 27));
    menuSimulator = new QMenu(menuBar);
    menuSimulator->setObjectName(QString::fromUtf8("menuSimulator"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    setMenuBar(menuBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    setStatusBar(statusBar);

    menuBar->addAction(menuSimulator->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuSimulator->addAction(actionExit);
    menuHelp->addAction(actionAbout);

    retranslateUi();
} // setupUi

FrontEnd::~FrontEnd()
{
}

void FrontEnd::retranslateUi()
{
    setWindowTitle(QApplication::translate("MainWindow", "USPDroids", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
    actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0, QApplication::UnicodeUTF8));
    menuSimulator->setTitle(QApplication::translate("MainWindow", "Simulator", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
} // retranslateUi
