
#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "widget.h"



class MyWidget : public Widget
{
public:
    MyWidget();
public:
    void closeEvent(QCloseEvent* event);
};

#endif // MYWIDGET_H
