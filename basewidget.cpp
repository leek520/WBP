#include "basewidget.h"


EPushButton::EPushButton(QWidget *parent) : QPushButton(parent)
{
    setObjectName("EPushButton");
    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);
}

void EPushButton::mouseMoveEvent(QMouseEvent *event)
{
    if (this->focusWidget() != this) return;
    event->ignore();
    if (event->buttons() & Qt::LeftButton){
       move(event->globalPos() - dragPosition);
    }
}

void EPushButton::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if (event->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
     {
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}
ELabel::ELabel(QWidget *parent) : QLabel(parent)
{
    setObjectName("ELabel");
    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);
}

void ELabel::mouseMoveEvent(QMouseEvent *event)
{
    if (this->focusWidget() != this) return;
    event->ignore();
    if (event->buttons() & Qt::LeftButton){
       move(event->globalPos() - dragPosition);
    }
}

void ELabel::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if (event->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
     {
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}
