#include "widget.h"
QMap<int, int> Widget::m_IdPool;
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
    layout()->setMargin(1);
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
        id = 0;
        break;
    }
    return id;
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
    repaint();
}

void Widget::setPosProperty()
{
    this->setFocus();
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

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    //处理鼠标事件
    QMouseEvent *me = (QMouseEvent *)event;
    switch (event->type()) {
    case QEvent::MouseMove:
        me->ignore();
        if (me->buttons() & Qt::LeftButton){
           move(me->globalPos() - dragPosition);
           setPosProperty();
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
    m_CentralWidget->setFont(QFont("Times", 26, QFont::Normal));
    m_CentralWidget->setMinimumSize(0,0);
    m_CentralWidget->installEventFilter(this);
    m_CentralWidget->setAutoFillBackground(true);
    m_CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout()->addWidget(m_CentralWidget);
}

void Widget::initParament()
{
    m_Id = assignId();
    m_BkColor = m_CentralWidget->palette().color(QPalette::Window);
    m_BkPressColor = m_BkDisableColor = m_BkColor;
    m_TextString = m_CentralWidget->text();
    m_TextColor = m_CentralWidget->palette().color(QPalette::WindowText);
    m_AlignH = (m_CentralWidget->alignment() & 0x0f) >> 1;
    m_AlignV = (m_CentralWidget->alignment() & 0xff) >> 6;

}

void Widget::createContexMenu()
{

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

    repaint();
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
    return m_TextString;

}

void Widget::setTextString(QString String)
{
    m_TextString = String;

    m_CentralWidget->setText(m_TextString);
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
int Widget::getTextDotBef()
{
    return m_TextDotBef;
}

void Widget::setTextDotBef(int value)
{
    m_TextDotBef = value;
}
int Widget::getTextDotAft()
{
    return m_TextDotAft;
}

void Widget::setTextDotAft(int value)
{
    m_TextDotAft = value;
}

QStringList Widget::getTextStringList()
{
    return m_TextStringList;
}

void Widget::setTextStringList(QStringList String)
{
    m_TextStringList = String;
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
    memset(widgetBuf.buf, 0, WidgetLen);
    widgetBuf.pos = 0;

    memset(stringBuf.buf, 0, StringLen);
    stringBuf.pos = 0;

    memset(luaBuf.buf, 0, LuaLen);
    luaBuf.pos = 0;

    memset(imageBuf.buf, 0, ImageLen);
    imageBuf.pos = 0;

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
    uint rgba = color.rgba();
    qDebug()<<QString::number(rgba, 16);
    //r从FF->00
    rgba = ((color.red() << 0) |
            (color.green() << 8) |
            (color.blue() << 16) |
            ((0x000000FF - color.alpha()) << 24));
    qDebug()<<QString::number(rgba, 16);
    return rgba;
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
                int charIdx = m_charList.indexOf(str.at(i));
                if (charIdx > -1){
                    num = CHAR_START_UNICODE + charIdx;
                }else{
                    QMessageBox::critical(0, tr("错误"), QString("字库不包含字符:%1.").arg(str.at(i)), QMessageBox::Yes, QMessageBox::Yes);
                    return NULL;
                }

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

char *BuildInfo::QStringListToMultBytes(QStringList strList, int maxLen)
{
    int address = START_ADDR_SDRAM_STRING + stringBuf.pos;

    int i = 0;
    QByteArray data;
    const QChar *q = NULL;
    QChar qtmp;
    int num;
    for(int k=0;k<strList.count();k++){
        QString str = strList[k];
        q = str.unicode();
        int len = str.count();
        if (len > 42){      //128/3
            len = 42;
        }
        for(i=0;i<maxLen;i++)
        {
            if (i < len){
                //第一步：先转unicode
                QString Dstr = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                if (1){   //全汉字字库的菜单
                    if (Dstr.indexOf(str.at(i)) >= 0){  //如果为数字或者字母，则用原始的unicode码
                        qtmp = str.at(i);
                        num = qtmp.unicode();
                    }else{
                        int charIdx = m_charList.indexOf(str.at(i));
                        if (charIdx > -1){
                            num = CHAR_START_UNICODE + charIdx;
                        }else{
                            QMessageBox::critical(0, tr("错误"), QString("字库不包含字符:%1.").arg(str.at(i)), QMessageBox::Yes, QMessageBox::Yes);
                            return NULL;
                        }

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
            }else{
                //添加字符串结束标识符
                stringBuf.buf[stringBuf.pos++] = 0x00;
                stringBuf.buf[stringBuf.pos++] = 0x00;
                stringBuf.buf[stringBuf.pos++] = 0x00;
            }
        }
        //添加字符串结束标识符
        stringBuf.buf[stringBuf.pos++] = 0x00;
        stringBuf.buf[stringBuf.pos++] = 0x00;
        stringBuf.buf[stringBuf.pos++] = 0x00;
    }
    return (char *)address;
}

char *BuildInfo::QStringToLuaChar(QString str)
{
    int address = 0;
    int RealLen = str.toLocal8Bit().length();
    if (RealLen > 0){
        address = START_ADDR_SDRAM_LUA + luaBuf.pos;
        memcpy(&luaBuf.buf[luaBuf.pos], str.toLocal8Bit().data(), RealLen);
        luaBuf.pos += RealLen;
        luaBuf.buf[luaBuf.pos++] = '\n';
        luaBuf.buf[luaBuf.pos++] = '\0';
    }
    return (char *)address;
}

void BuildInfo::QImageToEImage(QString filename, QPoint leftTop, ImageInfo *imageinfo)
{
    ImageMethods type = GUI_DRAW_BMP565;   //0:无压缩，1：压缩

    int address = START_ADDR_SDRAM_IMAGE + imageBuf.pos;
    if (!QFile::exists(filename)){
        return;
    }
    //1.获取文件size信息
    QSize size = QPixmap(filename).size();
    imageinfo->x = leftTop.x();
    imageinfo->y = leftTop.y();
    imageinfo->GUI_Image = (GUI_BITMAP *)address;

    GUI_BITMAP GUI_Image;
    GUI_Image.XSize = size.width();
    GUI_Image.YSize = size.height();
    GUI_Image.BytesPerLine = 2 * GUI_Image.XSize;
    GUI_Image.BitsPerPixel = 16;
    GUI_Image.pPal = 0;
    GUI_Image.pMethods = type;
    GUI_Image.pData = (uchar *)(address + sizeof(GUI_BITMAP));

    memcpy(&imageBuf.buf[imageBuf.pos], &GUI_Image, sizeof(GUI_BITMAP));
    imageBuf.pos += sizeof(GUI_BITMAP);

    //2.先调用BmpToC转换为data
    QString outname = "123";
    QString EXE_PATH = QDir::currentPath() + "/BmpCvt.exe";
    int format = (type == GUI_DRAW_BMP565 ? 8:12); //8:565无压缩，12：565压缩
    QString build_cmd = QString("start \"\" /min \"%1\" \"%2\" -saveas%3,1,%4 -exit")
            .arg(EXE_PATH)
            .arg(filename)
            .arg(outname)
            .arg(format);
    system(build_cmd.toLocal8Bit());
    outname = filename.left(filename.lastIndexOf("\\")+1) + outname + ".c";
    //qDebug()<<outname;
    //3.将图片data写入picBuf中，并返回首地址
    /*3.1：打开生成的.c文件*/
    QFile file(outname);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream input(&file);
    QString tmpStr = input.readAll();
    file.close();
    /*3.2：取出有效部分*/
    QRegExp rx1("static GUI_CONST_STORAGE.+\n([.\n]+)GUI_CONST_STORAGE");
    rx1.setMinimal(true);
    int pos = 0;

    QString datatmpStr;
    while ((pos = rx1.indexIn(tmpStr, pos)) != -1){
        datatmpStr.push_back(rx1.capturedTexts().at(0));
        pos += rx1.matchedLength();
    }
    /*3.3：根据压缩方式填写buf*/

    int idx = datatmpStr.indexOf("0x");
    if (type == GUI_DRAW_BMP565){ //下载无压缩，文本中没有注释
        if ((datatmpStr[idx+6] != ',') || (datatmpStr[idx+4] == ',')){
            return;
        }
    }else{  //下载压缩图片，文本中有注释，需要去掉注释
        if ((datatmpStr[idx+6] == ',') || (datatmpStr[idx+4] != ',')){
            return;
        }
        QStringList strList;
        strList = datatmpStr.split("\n");
        for (int i=0;i<strList.count();i++){
            strList[i] = strList[i].mid(strList[i].indexOf("*/")+2);
        }
        datatmpStr = strList.join("\n");
    }
    pos = 0;
    bool ok;
    int value;
    QString tmp;
    QRegExp rx(tr("((0[xX])?[0-9a-fA-F]{1,4},)"));
    while ((pos = rx.indexIn(datatmpStr, pos)) != -1){
        tmp = rx.capturedTexts().at(0);
        tmp.replace(",","");
        if (type == GUI_DRAW_BMP565){   //无压缩
            if (tmp.indexOf("0x")>-1 || tmp.indexOf("0X")>-1){
                value = tmp.toInt(&ok, 16);
            }else{
                value = tmp.toInt(&ok, 10);
            }
            imageBuf.buf[imageBuf.pos++] =(uchar)((value >> 0) & 0xff);
            imageBuf.buf[imageBuf.pos++] = (uchar)((value >> 8) & 0xff);
        }else{
            if (tmp.indexOf("0x")>-1 || tmp.indexOf("0X")>-1){
                value = tmp.toInt(&ok, 16);
            }else{
                value = tmp.toInt(&ok, 10);
            }
            imageBuf.buf[imageBuf.pos++] =(uchar)((value >> 0) & 0xff);
        }
        pos += rx.matchedLength();
        if (imageBuf.pos >= ImageLen) break;
    }
}

void BuildInfo::GraphToEgraph(Widget *w, GraphInfo *graphinfo)
{
    switch (w->getType()) {
    case Line:
        graphinfo->x = w->getLineStart().x();
        graphinfo->y = w->getLineStart().y();
        if (w->getLineType() == 0){ //水平线
            graphinfo->width = w->getLineLength();
            graphinfo->height = 0;
        }else{
            graphinfo->width = 0;
            graphinfo->height = w->getLineLength();
        }
        graphinfo->radius = w->getLineLength();
        break;
    case Rect:
        graphinfo->x = w->getRectangle().left();
        graphinfo->y = w->getRectangle().top();
        graphinfo->width = w->getRectangle().width();
        graphinfo->height = w->getRectangle().height();
        graphinfo->radius = w->getRadius();
        graphinfo->isFill = w->getFillEnable();
        break;
    case Circle:
        graphinfo->x = w->getCenter().x();
        graphinfo->y = w->getCenter().y();
        graphinfo->width = w->getRadius();
        graphinfo->height = w->getRadius();
        graphinfo->radius = w->getRadius();
        graphinfo->isFill = w->getFillEnable();
        break;
    default:
        break;
    }
    graphinfo->lineType = w->getType();
    graphinfo->lineWidth = w->getLineWidth();
    graphinfo->lineColor = QColorToEColor(w->getLineColor());
    graphinfo->fillColor = QColorToEColor(w->getFillColor());
}


void BuildInfo::downLoadInfo()
{
    imageBuf.pos = 0;
    if (com->OpenSerial()){
        downloadStep = 0;
        ResProgress_slt(101);
    }
    writeBufToTxt();
}

void BuildInfo::cancel()
{
    downloadStep = 10;
}

void BuildInfo::writeBufToTxt()
{
    QString filename = "buf.txt";

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }

    QTextStream out(&file);

    out << "widgetBuf:";
    writeBufToTxt(out, widgetBuf.buf, widgetBuf.pos);

    out << "stringBuf:";
    writeBufToTxt(out, stringBuf.buf, stringBuf.pos);

    out << "luaBuf:";
    writeBufToTxt(out, luaBuf.buf, luaBuf.pos);

    out << "imageBuf:";
    writeBufToTxt(out, imageBuf.buf, imageBuf.pos);  

    file.close();
}

void BuildInfo::writeBufToTxt(QTextStream &out, char *buf, int len)
{
    QByteArray byte;
    QString strHex;

    byte.resize(len);
    for(int i=0;i<len;i++) {
        if (i%16 == 0){
            out << "\n";
            //打印地址
            int address = 0;
            if (buf == widgetBuf.buf){
                address = START_ADDR_SDRAM_WIDGET + i;
            }else if (buf == stringBuf.buf){
                address = START_ADDR_SDRAM_STRING + i;
            }else if (buf == luaBuf.buf){
                address = START_ADDR_SDRAM_LUA + i;
            }else if (buf == imageBuf.buf){
                address = START_ADDR_SDRAM_IMAGE + i;
            }
            out << QString("0x%1: ").arg(QString::number(address, 16).right(8));
        }
        byte[i] = buf[i];
        strHex = QString::number(byte.at(i), 16);
        int cnt = strHex.count();
        if (cnt == 1){
            strHex.prepend("0");
        }else if (cnt == 2){

        }else{
            strHex = strHex.right(2);
        }
        out << strHex << " ";
    }
    out << "\n";

}

void BuildInfo::ResProgress_slt(int pos, QString msg)
{
    emit ResProgress_sig(downloadStep, pos, msg);
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
            if (widgetBuf.pos > 0){
                byte.resize(widgetBuf.pos);
                for(int i=0;i<widgetBuf.pos;i++) {
                    byte[i] = widgetBuf.buf[i];
                }
                emit DownLoad_sig(erase, address, byte);
                break;
            }else{
                downloadStep++;
            }
        case 2:
            //擦除20K，下载地址，下载文本数据包
            erase = 0x5c;
            address = START_ADDR_FLASH_STRING;
            if (stringBuf.pos > 0){
                byte.resize(stringBuf.pos+100);
                for(int i=0;i<byte.count();i++) {
                    byte[i] = stringBuf.buf[i];
                }
                emit DownLoad_sig(erase, address, byte);
                break;
            }else{
                downloadStep++;
            }
        case 3:
            //擦除20K，下载地址，下载文本数据包
            erase = 0x5c;
            address = START_ADDR_FLASH_LUA;
            if (luaBuf.pos > 0){
                byte.resize(luaBuf.pos);
                for(int i=0;i<luaBuf.pos;i++) {
                    byte[i] = luaBuf.buf[i];
                }
                emit DownLoad_sig(erase, address, byte);
                break;
            }else{
                downloadStep++;
            }
        case 4:
            //擦除20K，下载地址，下载文本数据包
            erase = 0x5f;   //252K
            address = START_ADDR_FLASH_IMAGE;
            if (imageBuf.pos > 0){
                byte.resize(imageBuf.pos);
                for(int i=0;i<imageBuf.pos;i++) {
                    byte[i] = imageBuf.buf[i];
                }
                emit DownLoad_sig(erase, address, byte);
                break;
            }else{
                downloadStep++;
            }
        default:
            break;
        }
    }
}


