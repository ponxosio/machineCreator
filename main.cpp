#include "mainwindow.h"
#include <QApplication>

#include <util/logutils.h>

INITIALIZE_NULL_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    el::Helpers::setStorage(sharedLoggingRepository());

    el::Configurations c("./configuration/log_machineCreator.ini");
    el::Loggers::reconfigureAllLoggers(c);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
