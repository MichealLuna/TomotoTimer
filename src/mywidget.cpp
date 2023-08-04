
#include "../inc/mywidget.h"
#include<QCloseEvent>
MyWidget::MyWidget()
{

}

void MyWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}
