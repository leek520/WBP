#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include "common.h"
#include "widgetselection.h"
#include "basewidget.h"
class EWindow : public QFrame
{
    Q_OBJECT
public:
    explicit EWindow(QWidget *parent = 0);
    ~EWindow();
    void addWidget(QWidget *w);
    void setCurrent(QWidget *w);
    void remove(QWidget *w);
    QWidgetList childWidgets() const;
    static QWidgetList windowList();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    void getPropertyList();
signals:
    void currentItemChanged(QWidget *now);
public slots:
    void focusChanged(QWidget *old, QWidget *now);
    void propertyChanged(QWidget *now);
public:
    QStringList m_propertyList;
private:
    Selection *sel;
    QPoint dragPosition;   //鼠标拖动的位置
    static QWidgetList winList;
public:


};

#endif // FORMWINDOW_H
