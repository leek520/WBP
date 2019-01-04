#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "widget.h"

class ImageWidget : public Widget
{
public:
    ImageWidget(QWidget *parent = 0);

protected:
    void initPropertyTable();
    void initParament();
    void paintEvent(QPaintEvent *event);
};
class LineWidget : public Widget
{
public:
    LineWidget(QWidget *parent = 0);

protected:
    void initPropertyTable();
    void initParament();
    void paintEvent(QPaintEvent *event);
private:

};
class RectWidget : public Widget
{
public:
    RectWidget(QWidget *parent = 0);

protected:
    void initPropertyTable();
    void initParament();
    void paintEvent(QPaintEvent *event);
private:

};
class CircleWidget : public Widget
{
public:
    CircleWidget(QWidget *parent = 0);

protected:
    void initPropertyTable();
    void initParament();
    void setRadius(int radius);
    void paintEvent(QPaintEvent *event);
private:

};
#endif // IMAGEWIDGET_H
