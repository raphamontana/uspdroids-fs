#ifndef FRONT_END_H
#define FRONT_END_H

#include <QMainWindow>

class FrontEnd : public QMainWindow {
    Q_OBJECT
public:
    FrontEnd(QWidget *parent = 0);
    ~FrontEnd();
};

#endif // FRONT_END_H
