#ifndef WIDGET_H
#define WIDGET_H

#include <QFrame>
#include "common.h"
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);

signals:
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    QPoint dragPosition;   //鼠标拖动的位置
};

#endif // WIDGET_H
