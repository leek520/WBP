#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QObject>
#include <QScrollArea>
#include "common.h"
#include "widget.h"
#include "formwindow.h"
class ScrollArea : public QWidget
{
    Q_OBJECT
public:
    ScrollArea(QWidget *parent = 0);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
signals:
    void addWidgetSgn(WidgetType type, QPoint pos);
private:
    int m_dragMode;
    QWidget *m_centarWiget;
};
class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget *parent = 0);
    void setCurrentItem(QWidget *w);
    void removeWidget(QWidget *w);
private slots:
    void closeTab(int index);
};
#endif // SCROLLAREA_H
