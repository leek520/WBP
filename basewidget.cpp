#include "basewidget.h"


EButton::EButton(QWidget *parent) : QPushButton(parent)
{
    setObjectName("Button");
    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);
    m_propertyList<<"text";
}

void EButton::mouseMoveEvent(QMouseEvent *event)
{
    if (this->focusWidget() != this) return;
    event->ignore();
    if (event->buttons() & Qt::LeftButton){
       move(event->globalPos() - dragPosition);
       emit currentItemChanged(this);
    }
}

void EButton::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if (event->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
     {
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}
EText::EText(QWidget *parent) : QLabel(parent)
{
    setObjectName("Text");
    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);
    setStyleSheet("border: 1px solid black;");
    m_propertyList<<"text";
}

void EText::mouseMoveEvent(QMouseEvent *event)
{
    if (this->focusWidget() != this) return;
    event->ignore();
    if (event->buttons() & Qt::LeftButton){
       move(event->globalPos() - dragPosition);
       emit currentItemChanged(this);
    }
}

void EText::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if (event->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
     {
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}
EEdit::EEdit(QWidget *parent) : QLineEdit(parent)
{
    setObjectName("Edit");
    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);
    m_propertyList<<"text";
}

void EEdit::mouseMoveEvent(QMouseEvent *event)
{
    if (this->focusWidget() != this) return;
    event->ignore();
    if (event->buttons() & Qt::LeftButton){
       move(event->globalPos() - dragPosition);
       emit currentItemChanged(this);
    }
}

void EEdit::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if (event->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
     {
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}
