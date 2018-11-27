#include "formwindow.h"
QWidgetList EWindow::winList;
EWindow::EWindow(QWidget *parent) :
    QFrame(parent),
    sel(new Selection(parent))
{
    winList.append(this);
    addWidget(this);

    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);
    setObjectName("Window");
    setStyleSheet("QFrame#Window{background-color: #ffffff;border: 1px solid red;}");

    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    connect(sel, SIGNAL(sizeChanged(QWidget*,QRect,QRect)),
            this, SLOT(propertyChanged(QWidget*)));
}

EWindow::~EWindow()
{
    delete sel;
}

void EWindow::addWidget(QWidget *w)
{
    sel->addWidget(w);
    setCurrent(w);
}

void EWindow::setCurrent(QWidget *w)
{
    QWidget *curWidget = sel->current();
    if (curWidget){
        sel->hide(curWidget);
    }
    sel->setCurrent(w);
    sel->show(w);
    w->show();
    propertyChanged(w);
}

void EWindow::remove(QWidget *w)
{
    if (w->objectName() == "Window"){
        delete ((EWindow *)w);
    }else if (w->objectName() == "Button"){
        ((EWindow *)w->parentWidget())->sel->removeWidget(w);
        delete ((EButton *)w);
    }else if (w->objectName() == "Text"){
        ((EWindow *)w->parentWidget())->sel->removeWidget(w);
        delete ((EText *)w);
    }else if (w->objectName() == "Edit"){
        ((EWindow *)w->parentWidget())->sel->removeWidget(w);
        delete ((EEdit *)w);
    }

}

QWidgetList EWindow::childWidgets() const
{
    QWidgetList childwidgets;
    QWidgetList widgets = sel->selectedWidgets();
    for(int i=0;i<widgets.count();i++){
        if (widgets[i] != this){
            childwidgets.append(widgets[i]);
        }
    }
    return childwidgets;
}

QWidgetList EWindow::windowList()
{
    return winList;
}

void EWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (this->focusWidget() != this) return;
    event->ignore();
    if (event->buttons() & Qt::LeftButton){
       move(event->globalPos() - dragPosition);
       emit currentItemChanged(this);
    }
}

void EWindow::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if (event->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
     {
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}




void EWindow::focusChanged(QWidget *old, QWidget *now)
{
    if (sel->isContainWidget(old)){
        //old->setStyleSheet("border: none;");
    }

    if (sel->isContainWidget(now)){
        setCurrent(now);
    }
}

void EWindow::propertyChanged(QWidget *now)
{
    emit currentItemChanged(now);
}

