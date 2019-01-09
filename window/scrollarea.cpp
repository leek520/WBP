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
    connect(this, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeTab(int)), Qt::UniqueConnection);
}

void TabWidget::setCurrentItem(QWidget *w)
{
    //根据类型取出父窗体
    QWidget *curTab = NULL;
    Widget *win = NULL;
    Widget *now = (Widget *)w;
    if (Window == now->getType()){
        win = now;
    }else{
        win = (Widget *)now->parentWidget();
    }

    //判断父窗体是否存在tab列表中
    curTab = win->parentWidget();
    bool find = false;
    for(int i=0;i<count();i++){
        if (widget(i) == curTab){
            find = true;
            break;
        }
    }
    //如果存在，设为cur,如果不存在重新添加tab
    if (!find){
        addTab(curTab, QString("Window-%1").arg(win->getId()));
    }
    setCurrentWidget(curTab);
}

void TabWidget::removeWidget(QWidget *w)
{
    for(int i=0;i<count();i++){
        if (widget(i) == w){
            removeTab(i);
        }
    }
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
