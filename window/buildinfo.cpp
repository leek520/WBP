#include "buildinfo.h"


BuildInfo::BuildInfo()
{
    initBuild();
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

    memset(fontBuf.buf, 0, FontLen);
    fontBuf.pos = 0;

    memset(charBuf.buf, 0, CharLen);
    charBuf.pos = 0;

    memset(imageBuf.buf, 0, ImageLen);
    imageBuf.pos = 0;

    m_CharRecord = " !\"#$%&'()*+,-./"
                   "0123456789:;<=>?"
                   "@ABCDEFGHIJKLMNO"
                   "PQRSTUVWXYZ[\\]^_"
                   "`abcdefghijklmno"
                   "pqrstuvwxyz{|}~";
}


uint BuildInfo::QColorToEColor(QColor color)
{
    uint rgba = color.rgba();
    //qDebug()<<QString::number(rgba, 16);
    //r从FF->00
    rgba = ((color.red() << 0) |
            (color.green() << 8) |
            (color.blue() << 16) |
            ((0x000000FF - color.alpha()) << 24));
    //qDebug()<<QString::number(rgba, 16);
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
        //第一步：先转unicode
        if (1){   //全汉字字库的菜单
            qtmp = str.at(i);
            num = qtmp.unicode();
            if (num > 0x7f){  //如果为内置的字符，则直接用原始unicode
                //int charIdx = m_charList.indexOf(str.at(i));
                int charIdx = m_CharRecord.indexOf(str.at(i));
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
                if (1){   //全汉字字库的菜单
                    qtmp = str.at(i);
                    num = qtmp.unicode();
                    if (num > 0x7f){  //如果为内置的字符，则直接用原始unicode
                        //int charIdx = m_charList.indexOf(str.at(i));
                        int charIdx = m_CharRecord.indexOf(str.at(i));
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

void BuildInfo::QImageToEImage(QString filename, QPoint leftTop, int type, ImageInfo *imageinfo)
{
    //ImageMethods type = GUI_DRAW_BMP565;   //0:无压缩，1：压缩

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


void BuildInfo::RecordChar(QString &string)
{
    for(int i=0;i<string.count();i++){
        QChar ch = string.at(i);
        if (!m_CharRecord.contains(ch)){
            m_CharRecord.append(ch);
        }
    }
}
bool BuildInfo::compareUnicode(QChar &a, QChar &b)
{
    return (a.unicode() < b.unicode());
}

void BuildInfo::SortRecordChar()
{
    qSort(m_CharRecord.begin(), m_CharRecord.end(), compareUnicode);
}
int BuildInfo::GetFontHeadAddress(int index)
{
    int fontSize = 0;
    QStringList fontList = PV->getEnumProperty("TextFont");
    if (index < fontList.count()){
       fontSize =  fontList[index].toInt();
    }
    return m_fontList[fontSize];
}
void BuildInfo::FontToChar(int fontSize)
{

    //GUI_FONT结构体信息
    m_fontList.insert(fontSize, START_ADDR_SDRAM_CHAR + charBuf.pos);

    GUI_FONT *gui_font = (GUI_FONT *)(charBuf.buf + charBuf.pos);
    charBuf.pos += sizeof(GUI_FONT);
    gui_font->XMag = 1;
    gui_font->YMag = 1;
    gui_font->p.pFontData = (void *)(START_ADDR_SDRAM_CHAR + charBuf.pos);
    switch (fontSize) {
    case 16:
        gui_font->YSize = 16;
        gui_font->YDist = 16;
        gui_font->Baseline = 14;
        gui_font->LHeight = 8;
        gui_font->CHeight = 12;
        break;
    case 24:
        gui_font->YSize = 24;
        gui_font->YDist = 24;
        gui_font->Baseline = 21;
        gui_font->LHeight =11;
        gui_font->CHeight = 16;
        break;
    case 32:
        gui_font->YSize = 33;
        gui_font->YDist = 33;
        gui_font->Baseline = 27;
        gui_font->LHeight = 14;
        gui_font->CHeight = 22;
        break;
    default:
        break;
    }

    GUI_FONT_PROP *fontProp = (GUI_FONT_PROP *)(charBuf.buf + charBuf.pos);
    charBuf.pos += sizeof(GUI_FONT_PROP);
    fontProp->First = 0X0020;
    fontProp->Last = 0x007F;
    fontProp->paCharInfo = (GUI_CHARINFO *)(START_ADDR_SDRAM_CHAR + charBuf.pos + sizeof(GUI_FONT_PROP));
    fontProp->pNext = (GUI_FONT_PROP *)(START_ADDR_SDRAM_CHAR + charBuf.pos);


    fontProp = (GUI_FONT_PROP *)(charBuf.buf + charBuf.pos);
    charBuf.pos += sizeof(GUI_FONT_PROP);
    fontProp->First = CHAR_START_UNICODE + 96;
    fontProp->Last = CHAR_START_UNICODE + m_CharRecord.count();
    fontProp->paCharInfo = (GUI_CHARINFO *)(START_ADDR_SDRAM_CHAR + charBuf.pos + 96 * 8);
    fontProp->pNext = NULL;


    QFont font;
    font.setPixelSize(fontSize);
    QFontMetrics fm(font);
    int charWidth;
    int charHeight = fm.height();;
    GUI_CHARINFO *charInfo;
    for(int i=0;i<m_CharRecord.count();i++){
        charWidth = fm.width(m_CharRecord.at(i));
        //字体数组信息buf
        charInfo = (GUI_CHARINFO *)(charBuf.buf + charBuf.pos);
        charBuf.pos += sizeof(GUI_CHARINFO);
        charInfo->XSize = charWidth;
        charInfo->XDist = charWidth;
        charInfo->BytesPerLine = charWidth / 8;
        charInfo->pData = (uchar *)(START_ADDR_SDRAM_FONT + fontBuf.pos);


        charWidth = fm.width(m_CharRecord.at(i));
        //指定图片大小为字体的大小
        QSize size(charWidth, charHeight);
        //以ARGB32格式构造一个QImage
        QImage image(size, QImage::Format_ARGB32);
        //填充图片背景,120/250为透明度
        image.fill(qRgba(255, 255, 255, 0));

        //为这个QImage构造一个QPainter
        QPainter painter(&image);
        //设置画刷的组合模式CompositionMode_SourceOut这个模式为目标图像在上。
        //改变组合模式和上面的填充方式可以画出透明的图片。
        painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);

        //改变画笔和字体
        QPen pen = painter.pen();
        pen.setColor(qRgba(0, 0, 0, 255));

        painter.setPen(pen);
        painter.setFont(font);

        //防止锯齿
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        painter.drawText(image.rect(), Qt::AlignCenter, m_CharRecord.at(i));
        //image.save("123.bmp");

        QColor color;
        int value = 0;
        //qDebug()<<charWidth<<charHeight;
        for(int j=0;j<charHeight;j++){
            for(int t=0;t<charWidth-7;t=t+8){
                value = 0;
                for(int k=0;k<8;k++){
                    color = image.pixelColor(t+k, j);
                    if ((color.red()==0) && (color.blue()==0) && (color.green()==0)){
                        value = value | (1<<(7-k));
                    }
                }
                fontBuf.buf[fontBuf.pos++] = value & 0xff;
                //QString strings = QString::number(value & 0xff, 16);
            }
        }
    }


}

void BuildInfo::downLoadInfo()
{
    imageBuf.pos = 0;
    writeBufToTxt();
    if (com->OpenSerial()){
        downloadStep = 0;
        ResProgress_slt(101);
    }

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

    out << "charBuf:";
    writeBufToTxt(out, charBuf.buf, charBuf.pos);

    out << "fontBuf:";
    writeBufToTxt(out, fontBuf.buf, fontBuf.pos);

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
            }else if (buf == charBuf.buf){
                address = START_ADDR_SDRAM_CHAR + i;
            }else if (buf == fontBuf.buf){
                address = START_ADDR_SDRAM_FONT + i;
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
        case 5:
            //擦除20K，下载地址，下载文本数据包
            erase = 0x5c;
            address = START_ADDR_FLASH_CHAR;
            if (charBuf.pos > 0){
                byte.resize(charBuf.pos);
                for(int i=0;i<charBuf.pos;i++) {
                    byte[i] = charBuf.buf[i];
                }
                emit DownLoad_sig(erase, address, byte);
                break;
            }else{
                downloadStep++;
            }
        case 6:
            //擦除20K，下载地址，下载文本数据包
            erase = 0x5f;   //252K
            address = START_ADDR_FLASH_FONT;
            if (fontBuf.pos > 0){
                byte.resize(fontBuf.pos);
                for(int i=0;i<fontBuf.pos;i++) {
                    byte[i] = fontBuf.buf[i];
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


