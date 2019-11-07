#include "mainwidget.h"
#include <QApplication>
#include <QCoreApplication>
#include <QtDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("mc");
    MainWidget w;
    w.show();

    qDebug() << "applicationDirPath: " << a.applicationDirPath() << "\n qdir::currentPath: " << QDir::currentPath();
    QDir bin(QCoreApplication::applicationDirPath());
    /* Set working directory */
#if defined(Q_OS_MACOS)
    bin.cdUp();    /* Fix this on Mac because of the .app folder, */
    bin.cdUp();    /* which means that the actual executable is   */
    bin.cdUp();    /* three levels deep. Grrr.                    */
#endif
    QDir::setCurrent(bin.absolutePath());
    qDebug() << "after QDir::currentPath()" << QDir::currentPath();
    return a.exec();
}
