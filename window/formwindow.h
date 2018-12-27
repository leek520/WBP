#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include "widget.h"
#include "widgetselection.h"

class FormWindow : public Widget
{
    Q_OBJECT
public:
    explicit FormWindow(QWidget *parent = 0);
    void addWidget(QWidget *w);
    void removeWidget(QWidget *w);
signals:
private:
    void setCurrent(QWidget *w);
private slots:
    void focusChanged(QWidget *old, QWidget *now);
private:
    QWidgetList m_childList;
    static QList<FormWindow *> m_windowList;
public:
    static FormWindow *m_curWin;
};

#endif // FORMWINDOW_H
