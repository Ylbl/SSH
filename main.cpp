#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "ElaApplication.h"
#include "MyConfig.h"
MyConfig MyConfig::myconfig;
int main(int argc, char *argv[])
{
    //qDebug()<<MyConfig::getInstance().my_email;
    QApplication a(argc, argv);
    eApp->init();
    MainWindow w;
    w.show();
    return a.exec();
}
