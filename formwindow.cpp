#include "formwindow.h"

FormWindow::FormWindow(QWidget *parent) :
    QFrame(parent),
    sel(new Selection(parent)),
    prop({{10,10,800,480,"Window",0x00ffff},})
{
    addWidget(this);

    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);
    setGeometry(prop.baseProp.xPos,
                prop.baseProp.yPos,
                prop.baseProp.xSize,
                prop.baseProp.ySize);
    setObjectName("FormWindow");
    setStyleSheet("QFrame#FormWindow{background-color: #ffffff;border: 1px solid red;}");

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

void FormWindow::propteryChanged()
{
    QRect rect = frameGeometry();
    prop.baseProp.xPos = rect.left();
    prop.baseProp.yPos = rect.top();
    prop.baseProp.xSize = rect.width();
    prop.baseProp.ySize = rect.height();


}

void FormWindow::focusChanged(QWidget *old, QWidget *now)
{
    if (sel->isWidgetSelected(old)){
        //old->setStyleSheet("border: none;");
    }

    if (sel->isWidgetSelected(now)){
        setCurrent(now);
        //now->setStyleSheet("border: 1px solid blue;");
        propteryChanged();
    }
}

