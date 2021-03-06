#include "View.h"

#include <QApplication>
#include "Model.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("dilishes");
    QCoreApplication::setOrganizationDomain("dilishes.de");
    QCoreApplication::setApplicationName("Years Ago");
    QGuiApplication::setApplicationDisplayName("Years ago");

    View w;
#ifdef Q_OS_ANDROID
    w.showFullScreen();
#else
    w.show();
#endif
    return a.exec();
}
