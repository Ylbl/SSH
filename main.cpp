#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "ElaApplication.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    eApp->init();
    MainWindow w;
    w.show();
    return a.exec();
}
