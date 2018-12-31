#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include "widget.h"

class TextWidget : public Widget
{
public:
    TextWidget(QWidget *parent = 0);

protected:
    void initPropertyTable();
    void initParament();
};
#endif // TEXTWIDGET_H
