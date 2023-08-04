
#include "../inc/fileapender.h"

FileApender::FileApender(){

}

FileApender::~FileApender(){
    textStream->flush();
    file->close();
}

FileApender::FileApender(const QString& filePath)
    :logFileName(filePath)
    ,file(new QFile(filePath))
    ,textStream(new QTextStream(file))
{
    file->open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);
}

ssize_t FileApender::writeLog(const QString &content){
    *textStream << content << "\n";
    textStream->flush();
    return content.size();
}
