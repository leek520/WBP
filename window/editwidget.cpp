#include "editwidget.h"

EditWidget::EditWidget(QWidget *parent) :
    Widget(parent)
{
    initPropertyTable();
    initCenterWidget();
    initParament();
}


void EditWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));

    m_propTable << qMakePair(QVariant::Color, QString("BkDisableColor"));

    m_propTable << qMakePair(QVariant::String, QString("String"));
    m_propTable << qMakePair(QVariant::Color, QString("TextColor"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignH"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignV"));
}

void EditWidget::initCenterWidget()
{
    m_CentralWidget = new QLabel(this);
    m_CentralWidget->setLineWidth(1);
    m_CentralWidget->setLineWidth(2);
    m_CentralWidget->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    m_CentralWidget->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_CentralWidget->setFont(QFont("Times", 26, QFont::Normal));
    m_CentralWidget->installEventFilter(this);
    m_CentralWidget->setAutoFillBackground(true);
    m_CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->addWidget(m_CentralWidget);
}
void EditWidget::initParament()
{
    m_Type = Edit;
    m_TextString = "";
    Widget::initParament();
}
