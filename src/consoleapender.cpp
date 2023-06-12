
#include "consoleapender.h"
#include<QDebug>

ConsoleApender::ConsoleApender()
{
}

ssize_t ConsoleApender::writeLog(const QString &content){
    qDebug()<<content<<"\n";
    return content.size();
}
