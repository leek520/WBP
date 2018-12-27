#include "widget.h"

Widget::Widget(WidgetType type, QWidget *parent) :
    QWidget(parent),
    m_type(type)
{
    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);    //可获得焦点
    setLayout(new QGridLayout);
    layout()->setMargin(0);
    layout()->setSpacing(0);

    QLabel *child = new QLabel(this);;
    switch (m_type) {
    case Window:
        break;
    case Button:
        child->setFrameShadow(QFrame::Raised);
        child->setFrameShape(QFrame::WinPanel);
        break;
    case Text:
        break;
    case Edit:
        child->setFrameShadow(QFrame::Sunken);
        child->setFrameShape(QFrame::Panel);
        break;
    default:
        break;
    }
    m_CentralWidget = static_cast<QWidget *>(child);
    m_CentralWidget->installEventFilter(this);
    m_CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->addWidget(WigetEntry(m_CentralWidget, m_type));
}

WidgetType Widget::getWidgetType()
{
    return m_type;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *me = (QMouseEvent *)event;
    if (me->type() == QEvent::MouseMove){
        me->ignore();
        if (me->buttons() & Qt::LeftButton){
           move(me->globalPos() - dragPosition);
        }
    }else if (me->type() == QEvent::MouseButtonPress){
        me->ignore();
        if (me->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
         {
            dragPosition = me->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
        }
    }else if (me->type() == QEvent::MouseButtonDblClick){
        emit MouseButtonDblClick(this);
    }
    QFocusEvent *fe = (QFocusEvent *)event;
    if ((watched == m_CentralWidget) && (fe->type() == QEvent::FocusIn)){
        setFocus();
    }

}
void Widget::paintEvent(QPaintEvent *event)
{
    //绘制边框
    QPainter painter(this);
    painter.setPen(QColor(139, 139, 139));
    painter.drawLine(0, 0, this->width() - 1, 0);
    painter.drawLine(0, 0, 0, this->height() - 1);
    painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
    painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
}
