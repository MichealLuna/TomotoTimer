
#ifndef CONSOLEAPENDER_H
#define CONSOLEAPENDER_H

#include "apender.h"



class ConsoleApender : public Apender
{
public:
    ConsoleApender();
    ~ConsoleApender() = default;
    ssize_t writeLog(const QString &);
};

#endif // CONSOLEAPENDER_H
