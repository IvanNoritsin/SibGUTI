
#include "massiv.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Massiv w;
    w.show();
    return a.exec();
}
