#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
    Widget(parent)
{
    m_Type = Image;
    initPropertyTable();
    initCenterWidget();
    initParament();
    layout()->setMargin(1);
}

void ImageWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::String, QString("BkImage"));
    m_propTable << qMakePair(QVariant::Point, QString("ImagePos"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("ImageCompress"));
}

void ImageWidget::initParament()
{
    Widget::initParament();
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QFileInfo file(m_BkImage);
    QString suffix = file.suffix().toLower();
    if (QFile::exists(m_BkImage) &&
        file.isFile() &&
        (suffix.contains("bmp") ||
         suffix.contains("png") ||
         suffix.contains("jpg"))){
    }else{
        QPainter painter(this);
        //绘制边框
        painter.setPen(QColor(139, 139, 139));
        painter.drawLine(0, 0, this->width() - 1, 0);
        painter.drawLine(0, 0, 0, this->height() - 1);
        painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
        painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);

    }
}

LineWidget::LineWidget(QWidget *parent) :
    Widget(parent)
{
    m_Type = Line;
    initPropertyTable();
    initCenterWidget();
    initParament();

    setStyleSheet("background: transparent");
}

void LineWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Line, QString("LineType"));
    m_propTable << qMakePair(QVariant::Point, QString("LineStart"));
    m_propTable << qMakePair(QVariant::Int, QString("LineLength"));
    m_propTable << qMakePair(QVariant::Int, QString("LineWidth"));
    m_propTable << qMakePair(QVariant::Color, QString("LineColor"));
}


void LineWidget::initParament()
{
    Widget::initParament();

    m_LineType = 0;
    QRect rect = this->frameGeometry();
    m_LineStart = QPoint(rect.left(), (rect.top()+rect.bottom())/2);
    m_LineLength = rect.right() - rect.left() + 1;
    m_LineWidth = 1;
    m_LineColor = Qt::black;
}
void LineWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(m_LineColor, m_LineWidth));
    if (0 == m_LineType){
        painter.drawLine(QPoint(0, height()/2), QPoint(width(), height()/2));
    }else{
        painter.drawLine(QPoint(width()/2, 0), QPoint(width()/2, height()));
    }

}
RectWidget::RectWidget(QWidget *parent) :
    Widget(parent)
{
    m_Type = Rect;
    initPropertyTable();
    initCenterWidget();
    initParament();

    setStyleSheet("background: transparent");
}

void RectWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Rect, QString("Rectangle"));
    m_propTable << qMakePair(QVariant::Int, QString("Radius"));
    m_propTable << qMakePair(QVariant::Bool, QString("FillEnable"));
    m_propTable << qMakePair(QVariant::Color, QString("FillColor"));
    m_propTable << qMakePair(QVariant::Int, QString("LineWidth"));
    m_propTable << qMakePair(QVariant::Color, QString("LineColor"));
}

void RectWidget::initParament()
{
    Widget::initParament();

    m_Rectangle = this->frameGeometry();
    m_Radius = 0;
    m_FillEnable = false;
    m_FillColor = Qt::white;
    m_LineWidth = 1;
    m_LineColor = Qt::black;
}

void RectWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(m_LineColor, m_LineWidth));
    if (m_FillEnable){
        painter.setBrush(m_FillColor);
    }
    //绘制边框
    QRect rect = QRect(0, 0, width()-1, height()-1);
    painter.drawRoundedRect(rect, m_Radius, m_Radius);
}
CircleWidget::CircleWidget(QWidget *parent) :
    Widget(parent)
{
    m_Type = Circle;
    initPropertyTable();
    initCenterWidget();
    initParament();

    setStyleSheet("background: transparent");
}

void CircleWidget::initPropertyTable()
{
    m_propTable << qMakePair(QVariant::Point, QString("Center"));
    m_propTable << qMakePair(QVariant::Int, QString("Radius"));
    m_propTable << qMakePair(QVariant::Bool, QString("FillEnable"));
    m_propTable << qMakePair(QVariant::Color, QString("FillColor"));
    m_propTable << qMakePair(QVariant::Int, QString("LineWidth"));
    m_propTable << qMakePair(QVariant::Color, QString("LineColor"));
}

void CircleWidget::initParament()
{
    Widget::initParament();

    QRect rect = this->frameGeometry();
    m_Center = rect.center();
    if (width()<height()){
        m_Radius = rect.width()/2;
    }else{
        m_Radius = rect.height()/2;
    }
    m_FillEnable = false;
    m_FillColor = Qt::white;
    m_LineWidth = 1;
    m_LineColor = Qt::black;

}

void CircleWidget::setRadius(int radius)
{
    resize(2*radius+1, 2*radius+1);
    move(pos() - QPoint(radius-m_Radius, radius-m_Radius));

    m_Radius = radius;
}
void CircleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(m_LineColor, m_LineWidth));
    if (m_FillEnable){
        painter.setBrush(m_FillColor);
    }
    QPoint center(width()/2, height()/2);
    painter.drawEllipse(center, m_Radius-1, m_Radius-1);
}
