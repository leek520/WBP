#include "textwidget.h"


TextWidget::TextWidget(QWidget *parent) :
    Widget(parent)
{
    m_Type = Text;
    initPropertyTable();
    initCenterWidget();
    initParament();
}
void TextWidget::initPropertyTable()
{
    //m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));

    m_propTable << qMakePair(QVariant::TextFormat, QString("TextType"));
    m_propTable << qMakePair(QVariant::Int, QString("TextRegAddress"));
    m_propTable << qMakePair(QVariant::Int, QString("TextTotLen"));
    m_propTable << qMakePair(QVariant::Int, QString("TextDotLen"));
    m_propTable << qMakePair(QVariant::String, QString("TextString"));
    m_propTable << qMakePair(QVariant::Color, QString("TextColor"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignH"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignV"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("TextFont"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("TextMaxLen"));
}

void TextWidget::initParament()
{
    Widget::initParament();
    setBkColor(QColor(255, 255, 255, 0));
    setTextString("text");
}

