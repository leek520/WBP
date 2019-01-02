#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include "widget.h"

class ButtonWidget : public Widget
{
public:
    ButtonWidget(QWidget *parent = 0);

protected:
    void initPropertyTable();
    void initCenterWidget();
    void initParament();
signals:
};

#endif // BUTTONWIDGET_H
