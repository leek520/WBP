#include "widget.h"

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

    m_Id = 0;
    m_BkColor = m_CentralWidget->palette().color(QPalette::Window);

    switch (m_Type) {
    case Window:
        break;
    case Button:
    case Text:
    case Edit:
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
        break;
    }
    default:
        break;
    }

}

int Widget::assignId()
{

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
    //    char* ptr;
    //    QByteArray ba;
    //    ba = str.toLocal8Bit();
    //    ptr = ba.data();
    //    memset(array, 0, 128);
    //    strcpy(array, ptr);


    char* textAddr = &stringBuf.buf[stringBuf.pos];

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
    return (char *)textAddr;
}

struct list_head *BuildInfo::headToBuildInfo(const list_head *head)
{
    struct list_head *ret = CalWidgetAdd(widgetBuf.pos);  //记录本次拷贝buf之前的位置
    BasePara *baseInfo;
    baseInfo = list_entry(head, BasePara, list);
    WindowInfo *winInfo = (WindowInfo *)baseInfo;
    WindowInfo *dstWin = (WindowInfo *)(widgetBuf.buf + widgetBuf.pos);
    memcpy(dstWin, winInfo, sizeof(WindowInfo));
    widgetBuf.pos += sizeof(WindowInfo);

    dstWin->base.list.next = CalWidgetAdd(widgetBuf.pos);

    return ret;
}

list_head *BuildInfo::widgetToBuildInfo(const list_head *head, list_head *prevHead, int *prevSize)
{
    //遍历链表生成buf
    struct list_head *ret = CalWidgetAdd(widgetBuf.pos);  //记录本次拷贝buf之前的位置
    struct list_head *pos;
    BasePara *baseInfo;
    list_for_each(pos, head){
        baseInfo = list_entry(pos, BasePara, list);
        switch (baseInfo->type) {
        case Window:
        {
            WindowInfo *winInfo = (WindowInfo *)baseInfo;
            WindowInfo *dstWin = (WindowInfo *)(widgetBuf.buf + widgetBuf.pos);
            memcpy(dstWin, winInfo, sizeof(WindowInfo));
            widgetBuf.pos += sizeof(WindowInfo);

            dstWin->base.list.prev = prevHead;
            //迭代计算child
            if (list_empty(&winInfo->childList)){
                dstWin->childList.next = CalWidgetAdd(widgetBuf.pos - 8);
                dstWin->childList.prev = dstWin->childList.next;
            }else{
                dstWin->childList.next = CalWidgetAdd(widgetBuf.pos);
                int lastSize;
                dstWin->childList.prev = widgetToBuildInfo(&winInfo->childList, CalWidgetAdd(widgetBuf.pos-8), &lastSize);
                // 重置子窗体的最后一个的next
                BasePara *lastChild = (BasePara *)(widgetBuf.buf + widgetBuf.pos - lastSize);
                lastChild->list.next = (struct list_head *)((int)dstWin->childList.next - 8);

            }

            if (pos == head->prev){ //是否为最后一个窗体
                dstWin->base.list.next = CalWidgetAdd(0);
                WindowInfo *headWin = (WindowInfo *)widgetBuf.buf;

                if (list_empty(&winInfo->childList)){
                    headWin->base.list.prev = CalWidgetAdd(widgetBuf.pos-sizeof(WindowInfo));
                }else{
                    headWin->base.list.prev = (struct list_head *)((int)dstWin->childList.next-sizeof(WindowInfo));
                }

            }else{
                dstWin->base.list.next = CalWidgetAdd(widgetBuf.pos);
            }

            break;
        }
        case Button:
        {
            ButtonInfo *btnInfo = (ButtonInfo *)baseInfo;

            ButtonInfo *dstBtn = (ButtonInfo *)(widgetBuf.buf + widgetBuf.pos);
            memcpy(dstBtn, btnInfo, sizeof(ButtonInfo));
            dstBtn->base.list.prev = prevHead;
            widgetBuf.pos += sizeof(ButtonInfo);

            dstBtn->text.string = (char *)(START_ADDR_SDRAM_STRING + (dstBtn->text.string - stringBuf.buf));

            dstBtn->base.list.next = CalWidgetAdd(widgetBuf.pos);
            *prevSize = sizeof(ButtonInfo);
            prevHead = &btnInfo->base.list;
            break;
        }
        case Text:
        {
            TextInfo *textInfo = (TextInfo *)baseInfo;

            TextInfo *dstText = (TextInfo *)(widgetBuf.buf + widgetBuf.pos);
            memcpy(dstText, textInfo, sizeof(TextInfo));
            widgetBuf.pos += sizeof(TextInfo);

            dstText->text.string = (char *)(START_ADDR_SDRAM_STRING + (dstText->text.string - stringBuf.buf));
            dstText->base.list.prev = prevHead;
            dstText->base.list.next = CalWidgetAdd(widgetBuf.pos);
            *prevSize = sizeof(TextInfo);
            prevHead = &textInfo->base.list;
            break;
        }
        case Edit:
        {
            EditInfo *editInfo = (EditInfo *)baseInfo;

            EditInfo *dstEdit = (EditInfo *)(widgetBuf.buf + widgetBuf.pos);
            memcpy(dstEdit, editInfo, sizeof(EditInfo));
            widgetBuf.pos += sizeof(EditInfo);

            dstEdit->text.string = (char *)(START_ADDR_SDRAM_STRING + (dstEdit->text.string - stringBuf.buf));
            dstEdit->base.list.prev = prevHead;
            dstEdit->base.list.next = CalWidgetAdd(widgetBuf.pos);
            *prevSize = sizeof(EditInfo);
            prevHead = &editInfo->base.list;
            break;
        }
        default:
            break;
        }
    }

    return ret;
}

void BuildInfo::widgetToBuildInfo(const list_head *head)
{
    struct list_head *pos;
    struct list_head *rootNode = ConvListAdd(START_ADDR_SDRAM_WIDGET);
    struct list_head *prevNode = rootNode;
    struct list_head *curNode;


    list_for_each(pos, head){
        //当前节点地址
        curNode = CalWidgetAdd(widgetBuf.pos);
        BasePara *wBaseInfo = list_entry(pos, BasePara, list);
        if (Window != wBaseInfo->type) break;

        WindowInfo *winInfo = (WindowInfo *)wBaseInfo;
        WindowInfo *dstWin = (WindowInfo *)(widgetBuf.buf + prevPos);
        memcpy(dstWin, winInfo, sizeof(WindowInfo));
        widgetBuf.pos += sizeof(WindowInfo);

        //第一个节点
        if (pos == head->next){
            dstWin->base.list.prev = rootNode;
        }else{
            dstWin->base.list.prev = prevNode;
        }

        //最后一个节点
        if (pos == head->prev){
            dstWin->base.list.next = rootNode;

            WindowInfo *firstWin = (WindowInfo *)(widgetBuf.buf);
            firstWin->base.list.prev = curNode;
        }else{
            dstWin->base.list.next = CalWidgetAdd(widgetBuf.pos);
        }
        prevNode = CalWidgetAdd(widgetBuf.pos);
        //计算child
        if (list_empty(&winInfo->childList)){
            dstWin->childList.next = CalWidgetAdd(widgetBuf.pos - 8);
            dstWin->childList.prev = CalWidgetAdd(widgetBuf.pos - 8);
        }else{

            struct list_head *rootChild = CalWidgetAdd(widgetBuf.pos-8);
            struct list_head *prevChild = rootChild;
            struct list_head *curChild = CalWidgetAdd(widgetBuf.pos-8);
            int rootChildPos = widgetBuf.pos - sizeof(WindowInfo);

            dstWin->childList.next = curChild;

            int childSize = 0;

            struct list_head *childPos;
            struct list_head *childHead = &winInfo->childList;
            list_for_each(childPos, childHead){
                BasePara *baseInfo = list_entry(childPos, BasePara, list);
                BasePara *dstBase;
                TextPara *dstString;
                switch (baseInfo->type) {
                case Button:
                {
                    ButtonInfo *btnInfo = (ButtonInfo *)baseInfo;
                    ButtonInfo *dstBtn = (ButtonInfo *)(widgetBuf.buf + widgetBuf.pos);
                    dstBase = (BasePara *)dstBtn;
                    dstString = (TextPara *)(&dstBtn->text);
                    memcpy(dstBtn, btnInfo, sizeof(ButtonInfo));
                    childSize = sizeof(ButtonInfo);
                    break;
                }
                case Text:
                {
                    TextInfo *textInfo = (TextInfo *)baseInfo;
                    TextInfo *dstText = (TextInfo *)(widgetBuf.buf + widgetBuf.pos);
                    dstBase = (BasePara *)dstText;
                    dstString = (TextPara *)(&dstText->text);
                    memcpy(dstText, textInfo, sizeof(TextInfo));
                    childSize = sizeof(TextInfo);
                    break;
                }
                case Edit:
                {
                    EditInfo *editInfo = (EditInfo *)baseInfo;
                    EditInfo *dstEdit = (EditInfo *)(widgetBuf.buf + widgetBuf.pos);
                    dstBase = (BasePara *)dstEdit;
                    dstString = (TextPara *)(&dstEdit->text);
                    memcpy(dstEdit, editInfo, sizeof(EditInfo));
                    childSize = sizeof(EditInfo);
                    break;
                }
                default:
                    break;
                }
                //第一个节点
                if (pos == childHead->next){
                    dstBase->list.prev = rootChild;
                }else{
                    dstBase->list.prev = prevChild;
                }

                widgetBuf.pos += childSize;

                dstString->string = (char *)(START_ADDR_SDRAM_STRING + (dstString->string - stringBuf.buf));

                //最后一个节点
                if (pos == childHead->prev){
                    dstBase->list.next = rootChild;
                }else{
                    dstBase->list.next = CalWidgetAdd(widgetBuf.pos);

                    WindowInfo *rootWin = (WindowInfo *)(widgetBuf.buf + rootChildPos);
                    rootWin->childList.prev = curNode;
                }
                //记录本次
                prevChild = CalWidgetAdd(widgetBuf.pos);
            }
        }
    }
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

