#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QObject>
#include <QScrollArea>
#include "common.h"
#include "widget.h"
class ScrollArea : public QScrollArea
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

#endif // SCROLLAREA_H
