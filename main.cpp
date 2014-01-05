#include <QCoreApplication>
#include "mcamera.h"
#include "server.h"
int main (int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Server server;
    server.initialisation();
    return a.exec();
}
