
#ifndef FILEAPENDER_H
#define FILEAPENDER_H

#include "apender.h"
#include<QFile>
#include<QFileDevice>
#include<QTextStream>

class FileApender : public Apender
{
public:
    FileApender();
    ~FileApender(); //virtual must be override.
    FileApender(const QString& logPath);
    ssize_t writeLog(const QString& content);
private:
    QString logFileName;
    QFile* file;
    QTextStream* textStream;
};

#endif // FILEAPENDER_H
