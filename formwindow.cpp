#include "formwindow.h"
QWidgetList EWindow::winList;
EWindow::EWindow(QWidget *parent) :
    QFrame(parent),
    sel(new Selection(parent)),
    Id(0)
{
    m_propertyList<<"Id"<<"geometry"<<"backColor";
    winList.append(this);
    addWidget(this);

    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);
    setObjectName("Window");

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor(0xDCDCDC));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    connect(sel, SIGNAL(sizeChanged(QWidget*,QRect,QRect)),
            this, SLOT(propertyChanged(QWidget*)));
}

EWindow::~EWindow()
{
    delete sel;
}

void EWindow::addWidget(QWidget *w)
{
    if (w != this){
        childs.append(w);
    }
    sel->addWidget(w);
    setCurrent(w);
}

void EWindow::setCurrent(QWidget *w)
{
    QWidget *curWidget = sel->current();
    if (curWidget){
        sel->hide(curWidget);
    }
    sel->setCurrent(w);
    sel->show(w);
    w->show();
    propertyChanged(w);
}

void EWindow::remove(QWidget *w)
{
    if (w->objectName() == "Window"){
        winList.removeOne(w);
        delete ((EWindow *)w);
    }else if (w->objectName() == "Button"){
        childs.removeOne(w);
        ((EWindow *)w->parentWidget())->sel->removeWidget(w);
        delete ((EButton *)w);
    }else if (w->objectName() == "Text"){
        childs.removeOne(w);
        ((EWindow *)w->parentWidget())->sel->removeWidget(w);
        delete ((EText *)w);
    }else if (w->objectName() == "Edit"){
        childs.removeOne(w);
        ((EWindow *)w->parentWidget())->sel->removeWidget(w);
        delete ((EEdit *)w);
    }

}

QWidgetList EWindow::childWidgets() const
{
    return childs;
}

QWidgetList EWindow::windowList()
{
    return winList;
}

void EWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (this->focusWidget() != this) return;
    event->ignore();
    if (event->buttons() & Qt::LeftButton){
       move(event->globalPos() - dragPosition);
       emit currentItemChanged(this);
    }
}

void EWindow::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    if (event->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
     {
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}




void EWindow::focusChanged(QWidget *old, QWidget *now)
{
    if (sel->isContainWidget(old)){
        //old->setStyleSheet("border: none;");
    }

    if (sel->isContainWidget(now)){
        setCurrent(now);
    }
}

void EWindow::propertyChanged(QWidget *now)
{
    emit currentItemChanged(now);
}



QString getWidgetProperty(QWidget *w, QString property)
{
    QColor color, textColor;
    QString text;
    //根据w类型获取对应需要显示的属性列表
    if (w->objectName() == "Window"){
        color = ((EWindow *)w)->palette().color(QPalette::Window);
    }else if (w->objectName() == "Button"){
        color = ((EButton *)w)->palette().color(QPalette::Button);
        textColor = ((EButton *)w)->palette().color(QPalette::ButtonText);
        text = ((EButton *)w)->text();
    }else if (w->objectName() == "Text"){
        color = ((EText *)w)->palette().color(QPalette::Window);
        textColor = ((EText *)w)->palette().color(QPalette::WindowText);
        text = ((EText *)w)->text();
    }else if (w->objectName() == "Edit"){
        color = ((EEdit *)w)->palette().color(QPalette::Base);
        textColor = ((EEdit *)w)->palette().color(QPalette::Text);
        text = ((EEdit *)w)->text();
    }

    if (property == "backColor"){
        return QString::number(color.rgb(), 16);
    }else if(property == "textColor"){
        return QString::number(textColor.rgb(), 16);
    }else if(property == "text"){
        return text;
    }
}
void setWidgetProperty(QWidget *w, QString property, QString value)
{
    QColor color("#"+value);
    QPalette palette(w->palette());

    //根据w类型获取对应需要显示的属性列表
    if (w->objectName() == "Window"){
        if (property == "backColor"){
            palette.setColor(QPalette::Window, color);
            ((EWindow *)w)->setPalette(palette);
        }

    }else if (w->objectName() == "Button"){
        if (property == "backColor"){
            w->setStyleSheet(QString("background-color: #%1;").arg(value));
        }else if (property == "textColor"){
            palette.setColor(QPalette::ButtonText, color);
            ((EButton *)w)->setPalette(palette);
        }else if (property == "text"){
            ((EButton *)w)->setText(value);
        }
    }else if (w->objectName() == "Text"){
        if (property == "backColor"){
            palette.setColor(QPalette::Window, color);
            ((EText *)w)->setPalette(palette);
        }else if (property == "textColor"){
            palette.setColor(QPalette::WindowText, color);
            ((EText *)w)->setPalette(palette);
        }else if (property == "text"){
            ((EText *)w)->setText(value);
        }
    }else if (w->objectName() == "Edit"){
        if (property == "backColor"){
            palette.setColor(QPalette::Base, color);
            ((EEdit *)w)->setPalette(palette);
        }else if (property == "textColor"){
            palette.setColor(QPalette::Text, color);
            ((EEdit *)w)->setPalette(palette);
        }else if (property == "text"){
            ((EEdit *)w)->setText(value);
        }
    }
    w->setAutoFillBackground(true);
}
uint QColorToEColor(QColor color)
{
    uint rgb = color.rgb();
    qDebug()<<QString::number(rgb, 16);
    //互换rb颜色
    rgb = ((rgb & 0x000000ff) << 16) | (rgb & 0x0000ff00) | ((rgb & 0x00ff0000) >> 16);
    qDebug()<<QString::number(rgb, 16);
    return rgb;
}
int alignmentConvert(int align)
{
    int aH = align & 0xf;
    int aV = (align >> 4) & 0xf;
    aH = aH >> 1;
    aV = aV >> 2;
    if (aV == 2){
        aV = 3;
    }
    return ((aH<<0) | (aV<<2));
}
