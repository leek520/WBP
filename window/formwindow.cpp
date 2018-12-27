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
    if (Window == rw->getWidgetType()){
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

void FormWindow::setCurrent(QWidget *w)
{
    QWidget *curWidget = SEL->current();
    if (curWidget){
        SEL->hide(curWidget);
    }
    SEL->setCurrent(w);
    SEL->show(w);
    w->show();
}

void FormWindow::focusChanged(QWidget *old, QWidget *now)
{
    if (SEL->isContainWidget(now)){
        setCurrent(now);
        Widget *rw = (Widget *)now;
        if (Window == rw->getWidgetType()){
            m_curWin = (FormWindow *)now;
        }else{
            if (m_childList.indexOf(now) > -1){
                m_curWin = this;
            }
        }
    }

}
