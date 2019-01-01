#include "formwindow.h"
QList<WindowWidget *> WindowWidget::m_windowList;
WindowWidget *WindowWidget::m_curWin = NULL;
WindowWidget::WindowWidget(QWidget *parent) :
    Widget(parent)
{
    m_curWin = this;
    m_windowList.append(this);
    addWidget(this);
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
                this, SLOT(focusChanged(QWidget *, QWidget *)));
    connect(SEL, SIGNAL(sizeChanged(QWidget*,QRect,QRect)),
                this, SLOT(propertyChanged(QWidget*)));

    initPropertyTable();
    initCenterWidget();
    initParament();
}

void WindowWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));
}

void WindowWidget::initParament()
{
    m_Type = Window;
    Widget::initParament();
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
    setCurrent(w);
}

void WindowWidget::removeWidget(QWidget *w)
{
    Widget *rw = (Widget *)w;
    if (Window == rw->getType()){
        WindowWidget *win = (WindowWidget *)w;
        QWidgetList childs = win->m_childList;
        for(int i=0;i<childs.count();i++){
            win->removeWidget(childs[i]);
        }
        childs = win->m_graphList;
        for(int i=0;i<childs.count();i++){
            win->removeWidget(childs[i]);
        }
        childs = win->m_imageList;
        for(int i=0;i<childs.count();i++){
            win->removeWidget(childs[i]);
        }
        SEL->removeWidget(win);
        m_windowList.removeOne(win);
        //resetCurrentWidget一定在delete之前，要不然窗体删除后信号发送不出去了
        resetCurrentWidget();
        delete win;
    }else{
        SEL->removeWidget(w);
        switch (rw->getType()) {
        case Button:
        case Text:
        case Edit:
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
        delete w;
        resetCurrentWidget();
    } 
}

void WindowWidget::resetCurrentWidget()
{
    //重设当前窗口
    if (!m_childList.isEmpty()){
        setCurrent(m_childList.last());
    }else{
        if (!m_graphList.isEmpty()){
            setCurrent(m_graphList.last());
        }else{
            if (!m_imageList.isEmpty()){
                setCurrent(m_imageList.last());
            }else{
                //通知属性窗口更改
                if (m_windowList.isEmpty()){
                    m_curWin = NULL;
                    emit currentItemChanged((Widget *)NULL);
                }else{
                    setCurrent(m_windowList.last());
                }
            }
        }
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

void WindowWidget::setCurrent(QWidget *w)
{
    QWidget *curWidget = SEL->current();
    if (curWidget){
        SEL->hide(curWidget);
    }
    SEL->setCurrent(w);
    SEL->show(w);
    w->show();
    propertyChanged(w);
}

void WindowWidget::setWidgetProperty(QWidget *w)
{
    Widget *child = (Widget *)w;
    //设置graph的位置
    child->setRectangle(w->frameGeometry());
}

void WindowWidget::focusChanged(QWidget *old, QWidget *now)
{
    if (SEL->isContainWidget(now)){
        setCurrent(now);
        Widget *rw = (Widget *)now;
        if (Window == rw->getType()){
            m_curWin = (WindowWidget *)now;
        }else{
            if (m_childList.indexOf(now) > -1){
                m_curWin = this;
                now->raise();
            }
        }
    }
    //提升当前选中窗口为顶层
    m_curWin->raise();
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
    m_progresstext = new QLabel(QString("%1/%2").arg(0).arg(4));
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

    m_progress->setFormat(QString("%1%").arg(pos));
    m_progress->setValue(pos);
    m_progresstext->setText(QString("%1/%2").arg(step).arg(m_maxStep));
}

void ProgressBar::cancel_slt()
{
    emit cancel_sig(m_maxStep+10, 0);
    hide();
}

