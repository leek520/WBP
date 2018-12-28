#include "widget.h"
QMap<WidgetType, int> Widget::m_IdPool;
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

    createCenterWidget();
    createPropertyTable();
}

WidgetType Widget::getType()
{
    return m_Type;
}

QList<QPair<QVariant::Type, QString> > Widget::getPropertyTable()
{
    return m_propTable;
}

void Widget::createCenterWidget()
{
    QLabel *child = new QLabel(this);
    child->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_CentralWidget = static_cast<QWidget *>(child);
    switch (m_Type) {
    case Window:
        break;
    case Button:
        child->setLineWidth(1);
        child->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
        break;
    case Text:
        break;
    case Edit:
        child->setLineWidth(2);
        child->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        break;
    default:
        break;
    }
    m_CentralWidget->installEventFilter(this);
    m_CentralWidget->setAutoFillBackground(true);
    m_CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->addWidget(WigetEntry(m_CentralWidget, m_Type));
}

void Widget::createPropertyTable()
{
    m_propTable << qMakePair(QVariant::Int, QString("Id"));
    m_propTable << qMakePair(QVariant::Rect, QString("geometry"));
    m_propTable << qMakePair(QVariant::Color, QString("BkColor"));

    m_Id = assignId();
    m_BkColor = m_CentralWidget->palette().color(QPalette::Window);

    switch (m_Type) {
    case Window:
        break;
    case Button:
        m_propTable << qMakePair(QVariant::String, QString("LuaCmd"));
        setTextParaProp();
        break;
    case Text:
        setTextParaProp();
        break;
    case Edit:

        setTextParaProp();
        break;
    default:
        break;
    }

}

void Widget::setTextParaProp()
{
    m_propTable << qMakePair(QVariant::String, QString("String"));
    m_propTable << qMakePair(QVariant::Color, QString("TextColor"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignH"));
    m_propTable << qMakePair(QVariant::TextFormat, QString("AlignV"));

    QLabel *label = (QLabel *)m_CentralWidget;
    m_String = label->text();
    m_TextColor = m_CentralWidget->palette().color(QPalette::WindowText);
    m_AlignH = ((int)label->alignment() & 0x0f) >> 1;
    m_AlignV = ((int)label->alignment() & 0xff) >> 6;
}

int Widget::assignId()
{
    if (!m_IdPool.contains(m_Type)){
        m_IdPool.insert(m_Type, 0);
    }
    int id = m_IdPool.value(m_Type);
    m_IdPool[m_Type] = id + 1;
    switch (m_Type) {
    case Window:
        id += GUI_ID_WINDOW;
        break;
    case Button:
        id += GUI_ID_BUTTON;
        break;
    case Text:
        id += GUI_ID_TEXT;
        break;
    case Edit:
        id += GUI_ID_EDIT;
        break;
    default:
        break;
    }
    return id;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    //处理鼠标事件
    QMouseEvent *me = (QMouseEvent *)event;
    switch (event->type()) {
    case QEvent::MouseMove:
        me->ignore();
        if (me->buttons() & Qt::LeftButton){
           move(me->globalPos() - dragPosition);
           emit currentItemChanged(this);
        }
        break;
    case QEvent::MouseButtonPress:
        me->ignore();
        if (me->button() == Qt::LeftButton)  //每当按下鼠标左键就记录一下位置
         {
            dragPosition = me->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
        }
        break;
    case QEvent::MouseButtonDblClick:
        emit MouseButtonDblClick(this);
        break;
    case QEvent::FocusIn:
        //处理焦点事件
        if (watched == m_CentralWidget){
             setFocus();
        }
        break;
    default:
        return QWidget::eventFilter(watched, event);
        break;
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

QString Widget::getLuaCmd()
{
    return m_LudCmd;
}

void Widget::setLuaCmd(QString LuaCmd)
{
    m_LudCmd = LuaCmd;
}

QVariant Widget::getBkColor1()
{
    return QVariant::fromValue<QList<QColor> >(m_BkColor1);
}

void Widget::setBkColor1(QVariant bkColor)
{
    m_BkColor1 = bkColor.value<QList<QColor> >();
}


BuildInfo::BuildInfo()
{
    initBuild();
    readCharList();

    //1、初始化串口线程
    QThread *com_thread = new QThread;
    com = new ComDriver();
    com->moveToThread(com_thread);
    com_thread->start();
    connect(this, SIGNAL(DownLoad_sig(int,int,QByteArray)),
            com, SLOT(DownLoad_slt(int,int,QByteArray)));
    connect(com, SIGNAL(ResProgress_sig(int,QString)),
            this, SLOT(ResProgress_slt(int,QString)));
}
void BuildInfo::initBuild()
{
    //先初始化buf
    memset(widgetBuf.buf, 0, 10240);
    widgetBuf.pos = 0;

    memset(stringBuf.buf, 0, 10240);
    stringBuf.pos = 0;

    memset(picBuf.buf, 0, 10240);
    picBuf.pos = 0;

}

BuildInfo::WidgetBuf *BuildInfo::getWidgetBuf()
{
    return (&widgetBuf);
}

void BuildInfo::readCharList()
{
    QFile file(":/char3000.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream input(&file);
    m_charList = input.readAll();
    file.close();
}
uint BuildInfo::QColorToEColor(QColor color)
{
    uint rgb = color.rgb();
    //qDebug()<<QString::number(rgb, 16);
    //互换rb颜色
    rgb = ((rgb & 0x000000ff) << 16) | (rgb & 0x0000ff00) | ((rgb & 0x00ff0000) >> 16);
    //qDebug()<<QString::number(rgb, 16);
    return rgb;
}
int BuildInfo::QAlignToEAlign(int align)
{
    int aH = align & 0xf;
    int aV = (align >> 4) & 0xf;
    aH = aH >> 1;
    aV = aV >> 2;
    if (aV == 2){
        aV = 3;
    }
    return ((aH<<0) | (aV<<2));
}
char *BuildInfo::QStringToMultBytes(QString str)
{

    int address = START_ADDR_SDRAM_STRING + stringBuf.pos;

    int i = 0;
    QByteArray data;
    const QChar *q = NULL;
    QChar qtmp;
    int num;
    q = str.unicode();

    int len = str.count();
    if (len > 42){      //128/3
        len = 42;
    }
    for(i=0;i<len;i++)
    {
        //https://blog.csdn.net/chary8088/article/details/21226375
        //第一步：先转unicode
        QString Dstr = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        if (1){   //全汉字字库的菜单
            if (Dstr.indexOf(str.at(i)) >= 0){  //如果为数字或者字母，则用原始的unicode码
                qtmp = str.at(i);
                num = qtmp.unicode();
            }else{
                num = CHAR_START_UNICODE + m_charList.indexOf(str.at(i));
            }
        }else{
            qtmp =(QChar)*q++;
            num= qtmp.unicode();
        }
        quint8 hi = (quint8)(num >> 8);
        quint8 lo = (quint8)(num);
        data.append (hi);

        data.append (lo);
        //第二步：unicode转3字节码
        stringBuf.buf[stringBuf.pos++] = 0xe0 | ((num >> 12) & 0xf);
        stringBuf.buf[stringBuf.pos++] = 0x80 | ((num >> 6) & 0x3f);
        stringBuf.buf[stringBuf.pos++] = 0x80 | ((num >> 0) & 0x3f);
    }
    //添加字符串结束标识符
    stringBuf.buf[stringBuf.pos++] = 0x00;
    stringBuf.buf[stringBuf.pos++] = 0x00;
    stringBuf.buf[stringBuf.pos++] = 0x00;

    return (char *)address;
}

char *BuildInfo::QStringToChar(QString str)
{
    int address = START_ADDR_SDRAM_LUA + luaBuf.pos;

    int RealLen = str.toLocal8Bit().length();
    if (RealLen>0)
    {
        memcpy(&luaBuf.buf[luaBuf.pos], str.toLocal8Bit().data(), RealLen);
    }
    luaBuf.pos += RealLen;
    return (char *)address;
}


void BuildInfo::downLoadInfo()
{
    if (com->OpenSerial()){
        downloadStep = 0;
        ResProgress_slt(101);
    }
}


void BuildInfo::ResProgress_slt(int pos, QString msg)
{
    if (pos >= 100){
        downloadStep++;
        int erase;
        int address;
        QByteArray byte;
        switch (downloadStep) {
        case 1:
            //擦除20K，下载地址，下载窗体数据包
            erase = 0x5c;
            address = START_ADDR_FLASH_WIDGET;
            byte.resize(widgetBuf.pos);
            for(int i=0;i<widgetBuf.pos;i++) {
                byte[i] = widgetBuf.buf[i];
            }
            emit DownLoad_sig(erase, address, byte);
            break;
        case 2:
            //擦除20K，下载地址，下载文本数据包
            erase = 0x5c;
            address = START_ADDR_FLASH_STRING;
            byte.resize(stringBuf.pos);
            for(int i=0;i<stringBuf.pos;i++) {
                byte[i] = stringBuf.buf[i];
            }
            emit DownLoad_sig(erase, address, byte);
            break;
        default:
            break;
        }
    }
}

