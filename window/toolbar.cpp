#include "toolbar.h"
QAction *ToolBar::pressAct = NULL;
ToolBar::ToolBar(const QString &title, QWidget *parent) :
    QToolBar(title, parent)
{

}

void ToolBar::addAction(QAction *action)
{
    QToolButton *btn = new QToolButton(this);
    btn->setDefaultAction(action);
    btn->installEventFilter(this);
    this->addWidget(btn);
}

bool ToolBar::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *me = (QMouseEvent *)event;
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        me->ignore();
        if (me->button() == Qt::LeftButton){  //每当按下鼠标左键就记录一下位置
            pressAct = ((QToolButton *)watched)->defaultAction();
        }
        break;
    case QEvent::MouseButtonRelease:
        me->ignore();
        if (me->button() == Qt::LeftButton){  //每当按下鼠标左键就记录一下位置
//            setCursor(QCursor(Qt::ArrowCursor));
            pressAct = NULL;
        }
        break;
    default:

        break;
    }
    return QWidget::eventFilter(watched, event);
}

