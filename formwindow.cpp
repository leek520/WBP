#include "formwindow.h"
QWidgetList FormWindow::winList;
FormWindow::FormWindow(QWidget *parent) :
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
}

FormWindow::~FormWindow()
{
    delete sel;
}

void FormWindow::addWidget(QWidget *w)
{
    sel->addWidget(w);
    setCurrent(w);
}

void FormWindow::setCurrent(QWidget *w)
{
    QWidget *curWidget = sel->current();
    if (curWidget){
        sel->hide(curWidget);
    }
    sel->setCurrent(w);
    sel->show(w);
}

QWidgetList FormWindow::childWidgets() const
{
    return sel->selectedWidgets();
}

QWidgetList FormWindow::windowList()
{
    return winList;
}

void FormWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (this->focusWidget() != this) return;
    event->ignore();
    if (event->buttons() & Qt::LeftButton){
       move(event->globalPos() - dragPosition);
    }
}

void FormWindow::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if (event->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
     {
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}


void FormWindow::focusChanged(QWidget *old, QWidget *now)
{
    if (sel->isWidgetSelected(old)){
        //old->setStyleSheet("border: none;");
    }

    if (sel->isWidgetSelected(now)){
        setCurrent(now);
    }
}

