#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include "common.h"

#define WigetEntry(ptr, type) \
        ((type == Window) ? (QLabel *)ptr :\
         (type == Button) ? (QLabel *)ptr :\
         (type == Text) ? (QLabel *)ptr :\
         (type == Edit) ? (QLabel *)ptr :\
         ptr)

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(WidgetType type= Window, QWidget *parent = 0);
    WidgetType getWidgetType();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);
signals:
    void MouseButtonDblClick(QWidget *w);
private:
    QPoint dragPosition;   //鼠标拖动的位置
    QWidget *m_CentralWidget;
    WidgetType m_type;
};

#endif // WIDGET_H
