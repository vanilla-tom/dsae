#include "MazeUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MazeUI w;
    w.show();
    return a.exec();
}
