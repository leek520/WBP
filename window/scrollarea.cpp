#include "scrollarea.h"

ScrollArea::ScrollArea(QWidget *parent) :
    QScrollArea(parent)
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
