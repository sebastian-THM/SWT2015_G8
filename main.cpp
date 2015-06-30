#include "view_qt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View_QT w;
    w.show();

    return a.exec();
}
