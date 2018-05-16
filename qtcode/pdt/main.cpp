#include "pdtwindow.h"
#include <QApplication>
#include <QTimeEdit>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pdtwindow w;
    w.show();

    return a.exec();
}
