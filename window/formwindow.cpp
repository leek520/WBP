#include "formwindow.h"
QList<FormWindow *> FormWindow::m_windowList;
FormWindow *FormWindow::m_curWin = NULL;
FormWindow::FormWindow(QWidget *parent) :
    Widget(Window, parent)
{
    m_curWin = this;
    m_windowList.append(this);
    addWidget(this);
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
                this, SLOT(focusChanged(QWidget *, QWidget *)));
    connect(SEL, SIGNAL(sizeChanged(QWidget*,QRect,QRect)),
                this, SLOT(propertyChanged(QWidget*)));
}

void FormWindow::addWidget(QWidget *w)
{
    if (w != this){
        m_childList.append(w);
    }
    SEL->addWidget(w);
    setCurrent(w);
}

void FormWindow::removeWidget(QWidget *w)
{
    Widget *rw = (Widget *)w;
    if (Window == rw->getType()){
        FormWindow *win = (FormWindow *)w;
        QWidgetList childs = win->m_childList;
        for(int i=0;i<childs.count();i++){
            win->removeWidget(childs[i]);
        }
        SEL->removeWidget(win);
        m_windowList.removeOne(win);
        delete win;
    }else{
        SEL->removeWidget(w);
        m_childList.removeOne(w);
        delete w;
    }
}

Widget *FormWindow::findImageWidget()
{
    for(int i=0;i<m_childList.count();i++){
        Widget *child = (Widget *)m_childList[i];
        if (child->getType() == Image){
            return child;
        }
    }
    return NULL;
}

QWidgetList FormWindow::getChildList()
{
    return m_childList;
}

QList<FormWindow *> FormWindow::getWindowList()
{
    return m_windowList;
}

void FormWindow::setCurrent(QWidget *w)
{
    QWidget *curWidget = SEL->current();
    if (curWidget){
        SEL->hide(curWidget);
    }
    SEL->setCurrent(w);
    SEL->show(w);
    w->show();
    emit currentItemChanged((Widget *)w);
}

void FormWindow::focusChanged(QWidget *old, QWidget *now)
{
    if (SEL->isContainWidget(now)){
        setCurrent(now);
        Widget *rw = (Widget *)now;
        if (Window == rw->getType()){
            m_curWin = (FormWindow *)now; 
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

void FormWindow::propertyChanged(QWidget *w)
{
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
