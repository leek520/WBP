#include "scrollarea.h"

ScrollArea::ScrollArea(QWidget *parent) :
    QWidget(parent)
{
    setAcceptDrops(true);   //设置接收拖拽
}
void ScrollArea::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("action/name"))
    {
        m_dragMode = 1;
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
        QWidget::dragEnterEvent(event);
    }
}

void ScrollArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    m_dragMode = 0;
    QWidget::dragLeaveEvent(event);
}

void ScrollArea::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasFormat("action/name"))
    {
        event->acceptProposedAction();
        return;
    }
    QWidget::dragMoveEvent(event);
}

void ScrollArea::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasFormat("action/name"))
    {
        m_dragMode = 0; // 结束drag mode
        QString name = QString(event->mimeData()->data("action/name"));
        WidgetType type = StrToEnum(name);
        emit addWidgetSgn(type, event->pos());
        event->acceptProposedAction();
        return;
    }
    QWidget::dropEvent(event);
}

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    setObjectName("mdiArea");
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)), Qt::UniqueConnection);
}

void TabWidget::closeTab(int index)
{
    SEL->hide(this->widget(index)->findChild<WindowWidget *>());
    removeTab(index);
    if (count() == 0) return;
    if (index == 0){    //如果移除的是第一个
        (this->widget(index)->findChild<WindowWidget *>())->setFocus();
    }else if (index == count()){    //如果移除的是最后一个
        (this->widget(index-1)->findChild<WindowWidget *>())->setFocus();
    }else{      //其他位置
        (this->widget(index)->findChild<WindowWidget *>())->setFocus();
    }

}
