#ifndef WIDGET_H
#define WIDGET_H
#include "common.h"

#define min(a,b) ((a)<(b)? (a) :(b))
#define max(a,b) ((a)>(b)? (a) :(b))

class Widget : public QMdiSubWindow
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QPoint dragPosition;   //鼠标拖动的位置
    int    edgeMargin;     //鼠标检测的边缘距离
    enum {nodir,
          top = 0x01,
          bottom = 0x02,
          left = 0x04,
          right = 0x08,
          topLeft = 0x01 | 0x04,
          topRight = 0x01 | 0x08,
          bottomLeft = 0x02 | 0x04,
          bottomRight = 0x02 | 0x08
    }resizeDir; //更改尺寸的方向

private:
    void detectEdge();  //检测鼠标是否接近窗口边缘
protected:
    void mousePressEvent(QMouseEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);


};


#endif // WIDGET_H
