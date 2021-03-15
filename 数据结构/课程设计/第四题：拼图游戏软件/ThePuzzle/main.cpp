#include "cover.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cover w;
    w.show();

    return a.exec();
}
