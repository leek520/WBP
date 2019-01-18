#include "formwindow.h"
QList<WindowWidget *> WindowWidget::m_windowList;
WindowWidget *WindowWidget::m_curWin = NULL;
WindowWidget::WindowWidget(QWidget *parent) :
    Widget(parent)
{
    m_curWin = this;
    m_windowList.append(this);
    addWidget(this);
    setAcceptDrops(true);   //设置接收拖拽
    connect(SEL, SIGNAL(sizeChanged(QWidget*,QRect,QRect)),
                this, SLOT(propertyChanged(QWidget*)));

    initPropertyTable();
    initCenterWidget();
    initParament();
}

WindowWidget::~WindowWidget()
{

}

void WindowWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));
    m_propTable << qMakePair(QVariant::Bool, QString("Permanent"));

}

void WindowWidget::initParament()
{
    m_Type = Window;
    Widget::initParament();
    m_Id = m_windowList.count();
    if (m_Id == 1){
        m_Permanent = true;
    }else
    {
        m_Permanent = false;
    }
}

void WindowWidget::addWidget(QWidget *w)
{
    if (w != this){
        Widget *child = (Widget *)w;
        switch (child->getType()) {
        case Window:
            break;
        case Button:
        case Text:
        case Edit:
        case Iconview:
            m_childList.append(w);
            break;
        case Image:
            m_imageList.append(w);
            break;
        case Line:
        case Rect:
        case Circle:
            m_graphList.append(w);
            break;
        default:
            break;
        }
    }
    SEL->addWidget(w);
    setCurrentItem(w);
}

void WindowWidget::removeWidget(QWidget *w)
{
    SEL->removeWidget(w);
    if (w == this){
        for(int i=0;i<m_childList.count();i++){
            removeWidget(m_childList[i]);
        }
        for(int i=0;i<m_graphList.count();i++){
            removeWidget(m_graphList[i]);
        }
        for(int i=0;i<m_imageList.count();i++){
            removeWidget(m_imageList[i]);
        }
        m_windowList.removeOne(this);
        delete this;
    }else{
        Widget *child = (Widget *)w;
        switch (child->getType()) {
        case Button:
        case Text:
        case Edit:
        case Iconview:
            m_childList.removeOne(w);
            break;
        case Image:
            m_imageList.removeOne(w);
            break;
        case Line:
        case Rect:
        case Circle:
            m_graphList.removeOne(w);
            break;
        default:
            break;
        }
        delete child;
    }
}

void WindowWidget::refreshAll()
{
    for(int i=0;i<m_windowList.count();i++){
        QWidgetList childList = m_windowList[i]->getChildList(2);
        for(int j=0;j<childList.count();j++){
            ((Widget *)childList[j])->refresh();
        }
        childList = m_windowList[i]->getChildList(1);
        for(int j=0;j<childList.count();j++){
            ((Widget *)childList[j])->refresh();
        }
        childList = m_windowList[i]->getChildList(0);
        for(int j=0;j<childList.count();j++){
            ((Widget *)childList[j])->refresh();
        }
        m_windowList[i]->repaint();
    }
}

QWidgetList WindowWidget::getChildList(int type)
{
    switch (type) {
    case 0:
        return m_childList;
    case 1:
        return m_imageList;
    case 2:
        return m_graphList;
    default:
        break;
    }

}

QList<WindowWidget *> WindowWidget::getWindowList()
{
    return m_windowList;
}

bool WindowWidget::staticCheck()
{
    QString msg;
    //1.查看是否有window具有重复ID
    QList<int> usedId;
    for(int i=0;i<m_windowList.count();i++){
        int id = m_windowList[i]->getId();
        int index = usedId.indexOf(id);
        if (index >= 0){
            msg = QString("窗口%1和窗口%2ID重复，请检查！").arg(index).arg(i);
            QMessageBox::critical(m_windowList[i], tr("错误"), msg, QMessageBox::Yes, QMessageBox::Yes);
            return false;
        }else{
            usedId.append(id);
        }
    }
    //2.给子窗体分配静态ID
    for(int i=0;i<m_windowList.count();i++){
        int id = m_windowList[i]->getId();
        QWidgetList childs = m_windowList[i]->getChildList(0);
        for(int j=0;j<childs.count();j++){
            Widget *child = (Widget *)childs[j];
            child->setId(CAL_ID(id, j));
        }
    }
    return true;
}
//https://blog.csdn.net/iamshaofa/article/details/17629897
/******************************************************************************
* @brief:
* @author:leek
* @date 2018/10/10
*******************************************************************************/
void WindowWidget::dragEnterEvent(QDragEnterEvent *event)
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

void WindowWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    m_dragMode = 0;
    QWidget::dragLeaveEvent(event);
}

void WindowWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasFormat("action/name"))
    {
        event->acceptProposedAction();
        return;
    }
    QWidget::dragMoveEvent(event);
}

void WindowWidget::dropEvent(QDropEvent *event)
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
void WindowWidget::setCurrentItem(QWidget *w)
{
    QWidget *curWidget = SEL->current();
    if (curWidget){
        SEL->hide(curWidget);
    }
    if (w == this){
        checkContainWidget((Widget *)w);
    }
    SEL->setCurrent(w);
    SEL->show(w);
    w->show();
    w->raise();
    propertyChanged(w);
}
Widget* WindowWidget::findContainWidget(Widget *w)
{
    Widget *dstChild = NULL;
    QRect rect = w->frameGeometry();
    QWidgetList childList = m_childList + m_imageList + m_graphList;
    for(int i=0;i<childList.count();i++){
        Widget *now = (Widget *)childList[i];
        if (now == w) continue;
        QRect nowRect = now->frameGeometry();
        QPoint pos = this->mapFromGlobal(QCursor::pos());
        if (rect.contains(nowRect, true)){
            now->raise();
            if (nowRect.contains(pos, true)){
                dstChild = now;
            }
        }
    }
    if (dstChild){
        if (!findContainWidget(dstChild)){
            return dstChild;
        }
    }
    return NULL;
}
void WindowWidget::checkContainWidget(Widget *w)
{
    Widget *cur = findContainWidget(w);
    if (cur)
        cur->setFocus();
}

void WindowWidget::setWidgetProperty(QWidget *w)
{
    Widget *child = (Widget *)w;
    //设置graph的位置
    child->setRectangle(w->frameGeometry());
}



void WindowWidget::propertyChanged(QWidget *w)
{
    ((Widget *)w)->setPosProperty();
    ((Widget *)w)->update();
    emit currentItemChanged((Widget *)w);
}

ProgressBar::ProgressBar(QWidget *parent) : QWidget(parent)
{

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);

    m_progress = new QProgressBar(this);
    m_progress->setFixedHeight(30);
    m_progress->setAlignment(Qt::AlignCenter);
    m_progress->setRange(0,100);
    m_progress->setFormat(QString("%1%").arg(0));

    QLabel *pLabel = new QLabel("请稍候...");
    m_progresstext = new QLabel(QString("%1/%2").arg(0).arg(0));
    QPushButton *cancel = new QPushButton("取消");
    cancel->setFixedHeight(30);
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancel_slt()));
    layout->addWidget(pLabel);//添加到状态栏的左边
    layout->addWidget(m_progress);
    layout->addWidget(m_progresstext);//添加到状态栏的左边
    layout->addWidget(cancel);//添加到状态栏的左边
}

void ProgressBar::setMaxStep(int max)
{
    m_maxStep = max;
}

void ProgressBar::setValue(int step, int pos)
{
    if (step > m_maxStep){
        hide();
    }else{
       show();
    }
    if (pos>100) pos = 100;
    m_progress->setFormat(QString("%1%").arg(pos));
    m_progress->setValue(pos);
    m_progresstext->setText(QString("%1/%2").arg(step).arg(m_maxStep));
}

void ProgressBar::cancel_slt()
{
    emit cancel_sig(0xff, 0);
    hide();
}

