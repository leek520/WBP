#include "buttonwidget.h"

ButtonWidget::ButtonWidget(QWidget *parent) :
    Widget(parent)
{
    initPropertyTable();
    initCenterWidget();
    initParament();
    createContexMenu();
}

void ButtonWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));
    m_propTable << qMakePair(QVariant::Color, QString("BkPressColor"));
    m_propTable << qMakePair(QVariant::Color, QString("BkDisableColor"));
    m_propTable << qMakePair(QVariant::String, QString("LuaCmd"));

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

void ButtonWidget::initCenterWidget()
{
    m_CentralWidget = new QLabel(this);
    m_CentralWidget->setLineWidth(1);
    m_CentralWidget->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
    QFont font;
    font.setPixelSize(32);
    m_CentralWidget->setFont(font);
    m_CentralWidget->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_CentralWidget->installEventFilter(this);
    m_CentralWidget->setAutoFillBackground(true);
    m_CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->addWidget(m_CentralWidget);
}

void ButtonWidget::initParament()
{
    Widget::initParament();
    m_Type = Button;
    setTextString("button");
}


