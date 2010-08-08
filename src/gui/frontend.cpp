#include "frontend.h"

FrontEnd::FrontEnd(QWidget *parent) : QMainWindow(parent)
{
    QPixmap pixmap(":icons/splash.png");
    splash = new QSplashScreen(pixmap);
    splash->show();
//    if (access("viewer.exe", F_OK) == 0) {
//        //Achou
//    }
    setWindowIcon(QIcon(":/imagens/bola.png"));
    setGeometry(100, 100, 800, 600);
    setupUi();
}

void FrontEnd::setupUi()
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(600, 400);
    actionExit = new QAction(this);
    actionAbout = new QAction(this);
    centralWidget = new QWidget(this);
    pushButton = new QPushButton(centralWidget);
    pushButton->setGeometry(QRect(250, 160, 90, 27));
    setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setGeometry(QRect(0, 0, 600, 27));
    menuSimulator = new QMenu(menuBar);
    menuHelp = new QMenu(menuBar);
    setMenuBar(menuBar);
    statusBar = new QStatusBar(this);
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
    setWindowTitle(QString::fromUtf8("USPDroids Football Simulator"));
    actionExit->setText(QString::fromUtf8("Exit"));
    actionAbout->setText(QString::fromUtf8("About"));
    pushButton->setText(QString::fromUtf8("PushButton"));
    menuSimulator->setTitle(QString::fromUtf8("Simulator"));
    menuHelp->setTitle(QString::fromUtf8("Help"));
} // retranslateUi
