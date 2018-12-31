#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include "widget.h"

class EditWidget : public Widget
{
public:
    EditWidget(QWidget *parent = 0);

protected:
    void initPropertyTable();
    void initCenterWidget();
    void initParament();
};
#endif // EDITWIDGET_H
