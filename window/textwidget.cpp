#include "textwidget.h"


TextWidget::TextWidget(QWidget *parent) :
    Widget(parent)
{
    initPropertyTable();
    initCenterWidget();
    initParament();
}
void TextWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));

    m_propTable << qMakePair(QVariant::TextFormat, QString("TextType"));
    m_propTable << qMakePair(QVariant::Int, QString("TextRegAddress"));
    m_propTable << qMakePair(QVariant::Int, QString("TextDotBef"));
    m_propTable << qMakePair(QVariant::Int, QString("TextDotAft"));
    m_propTable << qMakePair(QVariant::String, QString("TextString"));
    m_propTable << qMakePair(QVariant::Color, QString("TextColor"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignH"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignV"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("TextFont"));
}

void TextWidget::initParament()
{
    m_Type = Text;
    setTextString("text");
    Widget::initParament();
}

