#include "MainWindow.h"
#include <QtWidgets/QApplication>

#include "config.hpp"
#include "ElaApplication.h"
MC::mConfig MC::mConfig::mconfig;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    eApp->init();
    MainWindow w;
    w.show();
    return a.exec();
}
