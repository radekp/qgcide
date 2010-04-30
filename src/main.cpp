#ifdef QTOPIA

#include <qtopiaapplication.h>
#include "qgcide.h"

QTOPIA_ADD_APPLICATION(QTOPIA_TARGET, QDictMainWindow)
QTOPIA_MAIN

#else // QTOPIA

#include <QtGui/QApplication>
#include "qgcide.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDictMainWindow w;
    w.show();
    return a.exec();
}

#endif // QTOPIA
