#include "widget.h"
#include <QApplication>
//#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //手动加入以下代码，保证中文可以正常显示
   // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
   // QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    Widget w;
    w.show();

    return a.exec();
}
