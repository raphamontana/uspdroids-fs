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
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

class FrontEnd : public QMainWindow
{

    Q_OBJECT

public:

    FrontEnd(QWidget *parent = 0);

    ~FrontEnd();

private:

    void setupUi();

    void retranslateUi();

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
