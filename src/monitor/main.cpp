#include <QApplication>
#include "eyes.h"

int main(int argc, char *argv[])
{
    QApplication aplicacao(argc, argv);
    Eyes *campo = new Eyes();
    campo->setWindowTitle("Monitor USPDS");
    campo->setGeometry(100, 100, 800, 600);
    campo->show();
    return(aplicacao.exec());
}
