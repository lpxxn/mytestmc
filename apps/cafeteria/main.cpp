#include "mainwidget.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("mc");
    MainWidget w;
    w.show();

    return a.exec();
}
