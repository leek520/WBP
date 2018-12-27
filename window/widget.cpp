#include "widget.h"

Widget::Widget(WidgetType type, QWidget *parent) :
    QWidget(parent),
    m_Type(type)
{
    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);    //可获得焦点
    setAutoFillBackground(true);
    setLayout(new QGridLayout);
    layout()->setMargin(1);
    layout()->setSpacing(0);

    createProperyTable(type);
}

WidgetType Widget::getType()
{
    return m_Type;
}

QList<QPair<QVariant::Type, QString> > Widget::getPropertyTable()
{
    return m_propTable;
}

void Widget::createProperyTable(WidgetType type)
{
    m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));


    m_Id = 0;
    QLabel *child = new QLabel(this);
    m_CentralWidget = static_cast<QWidget *>(child);
    switch (type) {
    case Window:
        break;
    case Button:
        child->setFrameShadow(QFrame::Raised);
        child->setFrameShape(QFrame::WinPanel);
        addTextPropery();
        break;
    case Text:
        addTextPropery();
        break;
    case Edit:
        child->setFrameShadow(QFrame::Sunken);
        child->setFrameShape(QFrame::Panel);
        addTextPropery();
        break;
    default:
        break;
    }
    m_CentralWidget->installEventFilter(this);
    m_CentralWidget->setAutoFillBackground(true);
    m_CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->addWidget(WigetEntry(m_CentralWidget, m_Type));
}

void Widget::addTextPropery()
{
    m_propTable << qMakePair(QVariant::String, QString("String"));
    m_propTable << qMakePair(QVariant::Color, QString("TextColor"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignH"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignV"));

    QLabel *label = (QLabel *)m_CentralWidget;
    m_String = label->text();
    m_BkColor = m_CentralWidget->palette().color(QPalette::Window);
    m_TextColor = m_CentralWidget->palette().color(QPalette::WindowText);
    m_AlignH = ((int)label->alignment() & 0x0f) >> 1;
    m_AlignV = ((int)label->alignment() & 0xff) >> 6;
}

int Widget::assignId()
{

}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *me = (QMouseEvent *)event;
    if (me->type() == QEvent::MouseMove){
        me->ignore();
        if (me->buttons() & Qt::LeftButton){
           move(me->globalPos() - dragPosition);
           emit currentItemChanged(this);
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

int Widget::getId()
{
    return m_Id;
}

void Widget::setId(int Id)
{
    m_Id = Id;
}

QColor Widget::getBkColor()
{
    return m_BkColor;
}

void Widget::setBkColor(QColor BkColor)
{
    m_BkColor = BkColor;

    QPalette palette(m_CentralWidget->palette());
    palette.setColor(QPalette::Window, BkColor);
    m_CentralWidget->setPalette(palette);
}

QString Widget::getString()
{
    return m_String;
}

void Widget::setString(QString String)
{
    m_String = String;

    WigetEntry(m_CentralWidget, m_Type)->setText(String);
}

QColor Widget::getTextColor()
{
    return m_TextColor;
}

void Widget::setTextColor(QColor TextColor)
{
    m_TextColor = TextColor;

    QPalette palette(m_CentralWidget->palette());
    palette.setColor(QPalette::WindowText, TextColor);
    m_CentralWidget->setPalette(palette);
}

int Widget::getAlignH()
{
    return m_AlignH;
}

void Widget::setAlignH(int Align)
{
    m_AlignH = Align;

    WigetEntry(m_CentralWidget, m_Type)->setAlignment(Qt::Alignment((m_AlignV << 6) | (m_AlignH << 1)));
}

int Widget::getAlignV()
{
    return m_AlignV;
}

void Widget::setAlignV(int Align)
{
    m_AlignV = Align;

    WigetEntry(m_CentralWidget, m_Type)->setAlignment(Qt::Alignment((m_AlignV << 6) | (m_AlignH << 1)));
}

QVariant Widget::getBkColor1()
{
    return QVariant::fromValue<QList<QColor> >(m_BkColor1);
}

void Widget::setBkColor1(QVariant bkColor)
{
    m_BkColor1 = bkColor.value<QList<QColor> >();
}
