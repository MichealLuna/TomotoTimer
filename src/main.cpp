//#include "widget.h"
#include "../inc/mywidget.h"

#include <QApplication>
#include<QFile>

//#define DefaultQSS

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    #ifdef DefaultQSS
    QFile styleFile(":/qss/default.qss");
    styleFile.open(QFile::ReadOnly);
    QString style(styleFile.readAll());
    a.setStyleSheet(style);
    #endif

    Widget w;
    w.show();
    return a.exec();
}
