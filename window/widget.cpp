#include "widget.h"
int Widget::m_curLan = 0;
bool Widget::m_sim = false;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_ContextMenu(new QMenu())
{
    setObjectName("Widget");
    setMinimumSize(0, 0);
    setMouseTracking(true); //开启鼠标追踪
    setFocusPolicy(Qt::StrongFocus);    //可获得焦点
    setAutoFillBackground(true);
    setContextMenuPolicy(Qt::DefaultContextMenu);
    setLayout(new QGridLayout);
    layout()->setMargin(0);
    layout()->setSpacing(0);

}

Widget::~Widget()
{
    delete m_CentralWidget;
    delete m_ContextMenu;
}


QList<QPair<QVariant::Type, QString> > Widget::getPropertyTable()
{
    return m_propTable;
}

void Widget::setImage()
{
    QFileInfo file(m_BkImage);
    QString suffix = file.suffix().toLower();
    if (QFile::exists(m_BkImage) &&
        file.isFile() &&
        (suffix.contains("bmp") ||
         suffix.contains("png") ||
         suffix.contains("jpg"))){

        QImage image;
        image.load(m_BkImage);

        m_CentralWidget->setPixmap(QPixmap::fromImage(image));

        QSize size = image.size();
        setGeometry(m_ImagePos.x(),
                    m_ImagePos.y(),
                    size.width(),
                    size.height());
    }else{
        m_CentralWidget->setPixmap(QPixmap());
        move(m_ImagePos);
    }
}

void Widget::setPosProperty()
{
    QRect rect = this->frameGeometry();
    m_LineStart = QPoint(rect.left(), (rect.top()+rect.bottom())/2);
    if (0 == m_LineType){  //水平
        m_LineLength = rect.right() - rect.left() + 1;
    }else{
        m_LineLength = rect.bottom() - rect.top() + 1;
    }
    m_Rectangle = rect;

    m_Center = rect.center();
    //qDebug()<<rect<<m_Center;
    if (m_Type == Circle){
        if (width()<height()){
            m_Radius = rect.width()/2;
        }else{
            m_Radius = rect.height()/2;
        }
    }
    m_ImagePos = QPoint(rect.left(), rect.top());
}

void Widget::addContexMenuAction(QAction *action)
{
    m_ContextMenu->addAction(action);
}
QStringList Widget::getLanStringList(int lan)
{
    return m_TextStringList[lan];
}

void Widget::setLanStringList(int lan, QStringList list)
{
    m_TextStringList[lan] = list;
}
QString Widget::getLanString(int lan)
{
    return m_TextString[lan];
}

void Widget::setLanString(int lan, QString str)
{
    m_TextString[lan] = str;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (Widget::m_sim) return QWidget::eventFilter(watched, event);
    //处理鼠标事件
    QMouseEvent *me = (QMouseEvent *)event;
    switch (event->type()) {
    case QEvent::MouseMove:
        me->ignore();
        if (me->buttons() & Qt::LeftButton){
           move(me->globalPos() - dragPosition);
           setPosProperty();
           emit currentItemChanged(this);
           setCursor(Qt::SizeAllCursor);
        }
        break;
    case QEvent::MouseButtonRelease:
        setCursor(Qt::ArrowCursor);
        break;
    case QEvent::MouseButtonPress:
        me->ignore();
        if (me->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
         {
            dragPosition = me->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
        }
        emit checkContainWidget(this);
        break;
    case QEvent::MouseButtonDblClick:
        emit mouseButtonDblClick(this);
        break;
    case QEvent::FocusIn:
        //处理焦点事件
        if (watched != this){
             setFocus();
        }
        break;
    case QEvent::ContextMenu:
        m_ContextMenu->exec(QCursor::pos());
        break;
    default:
        return QWidget::eventFilter(watched, event);
        break;
    }

}
void Widget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    //绘制边框
//    painter.setPen(QColor(139, 139, 139));
//    painter.drawLine(0, 0, this->width() - 1, 0);
//    painter.drawLine(0, 0, 0, this->height() - 1);
//    painter.drawLine(this->width() - 1, 0, this->width() - 1, this->height() - 1);
//    painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
}

void Widget::initPropertyTable()
{

}

void Widget::initCenterWidget()
{
    m_CentralWidget = new QLabel();
    m_CentralWidget->setMouseTracking(true); //开启鼠标追踪
    QFont font;
    font.setPixelSize(32);
    font.setFamily("Times");
    font.setWeight(QFont::Thin);
    m_CentralWidget->setFont(font);
    m_CentralWidget->setMinimumSize(0,0);
    m_CentralWidget->installEventFilter(this);
    m_CentralWidget->setAutoFillBackground(true);
    m_CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->addWidget(m_CentralWidget);
}

void Widget::initParament()
{
    m_Id = 0;
    m_BkColor = m_CentralWidget->palette().color(QPalette::Window);
    m_BkPressColor = m_BkDisableColor = m_BkColor;

    m_TextColor = m_CentralWidget->palette().color(QPalette::WindowText);
    m_AlignH = (m_CentralWidget->alignment() & 0x0f) >> 1;
    m_AlignV = (m_CentralWidget->alignment() & 0xff) >> 6;

    m_TextType = String;
    m_TextFont = 2;
    m_TextRegAddress = 0;
    m_TextDotLen = 0;
    m_TextDotLen = 0;
    m_TextMaxLen = 128;

    for(int i=0;i<LAN_NUM;i++){
        m_TextString.append("");
        m_TextStringList.append(QStringList());
    }
    m_ImageCompress = 0;

    m_WriteRegAddress = 0;
    m_WriteBitAddress = 0;
    m_WriteRegType = 0;
    m_WriteValueType = 0;
    m_WriteValue = 0;
    m_IsBitReg = false;
    m_WriteEnable = false;
}

void Widget::createContexMenu()
{

}

void Widget::refresh()
{
    setTextString(m_TextString[Widget::m_curLan]);
    setBkColor(m_BkColor);
    setTextColor(m_TextColor);
    update();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    //处理按键事件
    QPoint m(0, 0);
    if (event->key() == Qt::Key_Up){
        m.setX(0);
        m.setY(1);
    }else if (event->key() == Qt::Key_Down){
        m.setX(0);
        m.setY(-1);
    }else if (event->key() == Qt::Key_Left){
        m.setX(1);
        m.setY(0);
    }else if (event->key() == Qt::Key_Right){
        m.setX(-1);
        m.setY(0);
    }
    //如果位置变化则通知属性窗体
    if ((m.x() != 0) || (m.y() != 0)){
        move(this->pos() - m);
        setPosProperty();
        emit currentItemChanged(this);
    }
}

int Widget::getId()
{
    return m_Id;
}

void Widget::setId(int Id)
{
    m_Id = Id;
}

int Widget::getType()
{
    return m_Type;
}

void Widget::setType(int Type)
{
    m_Type = Type;
}

QColor Widget::getBkColor()
{
    return m_BkColor;
}

void Widget::setBkColor(QColor BkColor)
{
    m_BkColor = BkColor;

    if (m_BkColor.alpha() == 0){
       setStyleSheet("QWidget#Widget{background: transparent;}");
    }

    QPalette palette(m_CentralWidget->palette());
    palette.setColor(QPalette::Window, BkColor);
    m_CentralWidget->setPalette(palette);

    //qDebug()<<m_CentralWidget->font().family();
    //repaint();
}

QString Widget::getBkImage()
{
    return m_BkImage;
}

void Widget::setBkImage(QString BkImage)
{
    m_BkImage = BkImage;

    setImage();
}

ushort Widget::getImageCompress()
{
    return m_ImageCompress;
}

void Widget::setImageCompress(ushort type)
{
    m_ImageCompress = type;
}

QPoint Widget::getImagePos()
{
    return m_ImagePos;
}

void Widget::setImagePos(QPoint pos)
{
    m_ImagePos = pos;

    setImage();
}
int Widget::getLineType()
{
    return m_LineType;
}
void Widget::setLineType(int type)
{
    m_LineType = type;

    if (0 == m_LineType){  //水平
        resize(m_LineLength, 3);
        move(m_LineStart - QPoint(0, 1));
    }else{
        resize(3, m_LineLength);
        move(m_LineStart - QPoint(1, 0));
    }

}
QPoint Widget::getLineStart()
{
    return m_LineStart;
}

void Widget::setLineStart(QPoint pos)
{
    m_LineStart = pos;

    if (0 == m_LineType){  //水平
        move(m_LineStart - QPoint(0, 1));
    }else{
        move(m_LineStart - QPoint(1, 0));
    }
}
int Widget::getLineLength()
{
    return m_LineLength;
}
void Widget::setLineLength(int length)
{
    m_LineLength = length;
    if (0 == m_LineType){  //水平
        resize(m_LineLength, 3);
    }else{
        resize(3, m_LineLength);
    }

}

QRectF Widget::getRectangle()
{
    return m_Rectangle;
}

void Widget::setRectangle(QRectF rect)
{
    m_Rectangle = rect;
    setGeometry(m_Rectangle.toRect());
}

QPoint Widget::getCenter()
{
    return m_Center;
}

void Widget::setCenter(QPoint center)
{
    move(pos()+center-m_Center);

    m_Center = center;
}

int Widget::getRadius()
{
    return m_Radius;
}

void Widget::setRadius(int radius)
{
    m_Radius = radius;
}
QColor Widget::getFillColor()
{
    return m_FillColor;
}
void Widget::setFillColor(QColor Color)
{
    m_FillColor = Color;
    update();
}
QColor Widget::getLineColor()
{
    return m_LineColor;
}
void Widget::setLineColor(QColor Color)
{
    m_LineColor = Color;
    update();
}
int Widget::getLineWidth()
{
    return m_LineWidth;
}
void Widget::setLineWidth(int width)
{
    m_LineWidth = width;
    update();
}

bool Widget::getFillEnable()
{
    return m_FillEnable;
}
void Widget::setFillEnable(bool enable)
{
    m_FillEnable = enable;
    update();
}

QColor Widget::getBkPressColor()
{
    return m_BkPressColor;
}

void Widget::setBkPressColor(QColor BkColor)
{
    m_BkPressColor = BkColor;
}

QColor Widget::getBkDisableColor()
{
    return m_BkDisableColor;
}

void Widget::setBkDisableColor(QColor BkColor)
{
    m_BkDisableColor = BkColor;
}

QString Widget::getTextString()
{
    return m_TextString[Widget::m_curLan];

}

void Widget::setTextString(QString String)
{
    switch (m_TextType) {
    case 0:
        m_TextString[Widget::m_curLan] = String;
        m_CentralWidget->setText(String);
        break;
    case 1:
        m_CentralWidget->setText("0000");
        break;
    case 2:
        if (m_TextStringList[Widget::m_curLan].count() == 0){
           m_CentralWidget->setText("");
        }else{
            m_CentralWidget->setText(m_TextStringList[Widget::m_curLan].first());
        }
        break;
    default:
        m_TextString[Widget::m_curLan] = String;
        m_CentralWidget->setText(String);
        break;
    }
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

    m_CentralWidget->setAlignment(Qt::Alignment((m_AlignV << 6) | (m_AlignH << 1)));
}

int Widget::getAlignV()
{
    return m_AlignV;
}

void Widget::setAlignV(int Align)
{
    m_AlignV = Align;

    m_CentralWidget->setAlignment(Qt::Alignment((m_AlignV << 6) | (m_AlignH << 1)));
}

int Widget::getTextType()
{
    return m_TextType;
}

void Widget::setTextType(int value)
{
    m_TextType = value;
    refresh();
}

int Widget::getTextFont()
{
    return m_TextFont;
}

void Widget::setTextFont(int value)
{
    m_TextFont = value;
    QFont font(m_CentralWidget->font());
    QStringList fontList = PV->getEnumProperty("TextFont");
    if (m_TextFont < fontList.count()){
        font.setPixelSize(fontList[m_TextFont].toInt());
    }else{
        font.setPixelSize(fontList.last().toInt());
    }
    m_CentralWidget->setFont(font);
}
int Widget::getTextMaxLen()
{
    return m_TextMaxLen;
}

void Widget::setTextMaxLen(int value)
{
    m_TextMaxLen = value;
}
int Widget::getTextRegAddress()
{
    return m_TextRegAddress;
}

void Widget::setTextRegAddress(int value)
{
    m_TextRegAddress = value;
}
int Widget::getTextTotLen()
{
    return m_TextTotLen;
}

void Widget::setTextTotLen(int value)
{
    m_TextTotLen = value;
}
int Widget::getTextDotLen()
{
    return m_TextDotLen;
}

void Widget::setTextDotLen(int value)
{
    m_TextDotLen = value;
}

QStringList Widget::getTextStringList()
{
    return m_TextStringList[Widget::m_curLan];
}

void Widget::setTextStringList(QStringList String)
{
    m_TextStringList[Widget::m_curLan] = String;
}

ushort Widget::getWriteRegAddress()
{
    return m_WriteRegAddress;
}

void Widget::setWriteRegAddress(ushort value)
{
    m_WriteRegAddress = value;
}

bool Widget::getIsBitReg()
{
    return m_IsBitReg;
}

void Widget::setIsBitReg(bool value)
{
    m_IsBitReg = value;
}

bool Widget::getWriteEnable()
{
    return m_WriteEnable;
}

void Widget::setWriteEnable(bool value)
{
    m_WriteEnable = value;
}
ushort Widget::getWriteBitAddress()
{
    return m_WriteBitAddress;
}

void Widget::setWriteBitAddress(ushort value)
{
    m_WriteBitAddress = value;
}
ushort Widget::getWriteRegType()
{
    return m_WriteRegType;
}

void Widget::setWriteRegType(ushort value)
{
    m_WriteRegType = value;
}

ushort Widget::getWriteValueType()
{
    return m_WriteValueType;
}

void Widget::setWriteValueType(ushort value)
{
    m_WriteValueType = value;
}

int Widget::getWriteValue()
{
    return m_WriteValue;
}

void Widget::setWriteValue(int value)
{
    m_WriteValue = value;
}

QVariant Widget::getBkColor1()
{
    return QVariant::fromValue<QList<QColor> >(m_BkColor1);
}

void Widget::setBkColor1(QVariant bkColor)
{
    m_BkColor1 = bkColor.value<QList<QColor> >();
}

