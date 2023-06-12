
#ifndef APENDER_H
#define APENDER_H

#include<QString>

class Apender{
public:
    Apender() {}
    virtual ~Apender() = default;
    virtual ssize_t writeLog(const QString&) = 0; //基类定义了虚函数为定义，基类不定义得标0
};

#endif // APENDER_H
