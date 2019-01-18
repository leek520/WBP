#ifndef ICONVIEWWIDGET_H
#define ICONVIEWWIDGET_H

#include "widget.h"

class IconviewWidget : public Widget
{
    Q_OBJECT
public:
    explicit IconviewWidget(QWidget *parent = 0);

protected:
    void initPropertyTable();
    void initParament();
    void paintEvent(QPaintEvent *event);
signals:
};

#endif // ICONVIEWWIDGET_H
