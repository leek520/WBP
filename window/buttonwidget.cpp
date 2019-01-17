#include "buttonwidget.h"

ButtonWidget::ButtonWidget(QWidget *parent) :
    Widget(parent)
{
    m_Type = Button;
    initPropertyTable();
    initCenterWidget();
    initParament();
    createContexMenu();
}

void ButtonWidget::initPropertyTable()
{
    //m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));
    m_propTable << qMakePair(QVariant::Color, QString("BkPressColor"));
    m_propTable << qMakePair(QVariant::Color, QString("BkDisableColor"));

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

    m_propTable << qMakePair(QVariant::Bool, QString("WriteEnable"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteRegType"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteRegAddress"));
    m_propTable << qMakePair(QVariant::Bool, QString("IsBitReg"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteBitAddress"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteValueType"));
    m_propTable << qMakePair(QVariant::Int, QString("WriteValue"));
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
    setTextString("button");
}


