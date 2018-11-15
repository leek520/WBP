#ifndef EPUSHBUTTON_H
#define EPUSHBUTTON_H
#include "common.h"

class EPushButton : public QPushButton
{
public:
    EPushButton(QWidget *parent=0);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    QPoint dragPosition;   //鼠标拖动的位置
};
class ELabel : public QLabel
{
public:
    ELabel(QWidget *parent=0);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    QPoint dragPosition;   //鼠标拖动的位置
};
#endif // EPUSHBUTTON_H
