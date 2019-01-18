#include "iconviewwidget.h"

IconviewWidget::IconviewWidget(QWidget *parent) : Widget(parent)
{
    m_Type = Iconview;
    initPropertyTable();
    //initParament();
}

void IconviewWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    //m_propTable << qMakePair(QVariant::Color, QString("BkColor"));
    //m_propTable << qMakePair(QVariant::Color, QString("BkPressColor"));

    m_propTable << qMakePair(QVariant::TextFormat, QString("TextType"));
    m_propTable << qMakePair(QVariant::Int, QString("TextRegAddress"));
    m_propTable << qMakePair(QVariant::Int, QString("TextTotLen"));
    m_propTable << qMakePair(QVariant::Int, QString("TextDotLen"));
    //m_propTable << qMakePair(QVariant::String, QString("TextString"));
    m_propTable << qMakePair(QVariant::Color, QString("TextColor"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignH"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignV"));
    //m_propTable << qMakePair(QVariant::TextFormat, QString("TextFont"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("TextMaxLen"));

    m_propTable << qMakePair(QVariant::Bool, QString("WriteEnable"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteRegType"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteRegAddress"));
    m_propTable << qMakePair(QVariant::Bool, QString("IsBitReg"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteBitAddress"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteValueType"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteValue"));
}


void IconviewWidget::initParament()
{
    Widget::initParament();
}

void IconviewWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制边框
    painter.setPen(QColor(139, 139, 139));
    painter.drawLine(0, 0, this->width() - 1, 0);
    painter.drawLine(0, 0, 0, this->height() - 1);
    painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
    painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);

    painter.drawPixmap(10, 20, 140, 30, QPixmap::fromImage(QImage(":/copy")));
    painter.drawText(100,100,40,20, Qt::AlignCenter, QString("哈哈"));
}
