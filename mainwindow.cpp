#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    curWin(NULL)
{
    setWindowTitle(tr("WBP"));//设置窗口标题
    setWindowIcon(QIcon(":/mamtool.ico"));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    setupUi();
    initBuf();
    readText();

}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    /****file****/
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);

    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    /****edit****/
    undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("撤销(Ctrl+Z)"));
    undoAct->setEnabled(false);
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(QIcon(":/images/redo.png"), tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("恢复(Ctrl+Y)"));
    redoAct->setEnabled(false);
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

    removeAct = new QAction(QIcon(":/images/remove.png"), tr("&Remove"), this);
    removeAct->setShortcuts(QKeySequence::Delete);
    removeAct->setStatusTip(tr("Remove the current selection"));
    connect(removeAct, SIGNAL(triggered()), this, SLOT(remove()));

    /****about****/
    aboutAct = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    /****build****/
    buildAct = new QAction(QIcon(":/images/build.png"), tr("&Build"), this);
    buildAct->setStatusTip(tr("Build"));
    connect(buildAct, SIGNAL(triggered()), this, SLOT(build()));

    downAct = new QAction(QIcon(":/images/download.png"), tr("&Download"), this);
    downAct->setStatusTip(tr("Download"));
    connect(downAct, SIGNAL(triggered()), this, SLOT(download()));


    /****widget****/
    QAction *act = new QAction(QIcon(":/images/widget/window.PNG"), tr("Window"), this);
    act->setStatusTip(tr("Window"));
    act->setShortcut(Qt::Key_F3);
    connect(act, SIGNAL(triggered()), this, SLOT(addWidget()));
    m_graphActList.append(act);

    act = new QAction(QIcon(":/images/widget/button.PNG"), tr("Button"), this);
    act->setStatusTip(tr("Button"));
    act->setShortcut(Qt::Key_F4);
    connect(act, SIGNAL(triggered()), this, SLOT(addWidget()));
    m_graphActList.append(act);

    act = new QAction(QIcon(":/images/widget/text.PNG"), tr("Text"), this);
    act->setStatusTip(tr("Text"));
    act->setShortcut(Qt::Key_F5);
    connect(act, SIGNAL(triggered()), this, SLOT(addWidget()));
    m_graphActList.append(act);

    act = new QAction(QIcon(":/images/widget/edit.PNG"), tr("Edit"), this);
    act->setStatusTip(tr("Edit"));
    act->setShortcut(Qt::Key_F6);
    connect(act, SIGNAL(triggered()), this, SLOT(addWidget()));
    m_graphActList.append(act);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(removeAct);

    buildMenu = menuBar()->addMenu(tr("&Build"));
    buildMenu->addAction(buildAct);
    buildMenu->addAction(downAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    editToolBar->addAction(removeAct);


    buildToolBar = addToolBar(tr("Build"));
    buildToolBar->addAction(buildAct);
    buildToolBar->addAction(downAct);

    addToolBarBreak(Qt::TopToolBarArea);

    graphToolBar = addToolBar(tr("Widget"));
    for(int i=0;i<m_graphActList.count();i++){
        graphToolBar->addAction(m_graphActList[i]);
    }
    graphToolBar->setIconSize(QSize(100,100));
    graphToolBar->setFixedHeight(100);

}

void MainWindow::createStatusBar()
{
    /*状态栏显示的信息分3种
        1. 一般信息，用QLabel 代表
        2.  永久信息，文本会一直显示在状态栏的最右边。
        3. 临时信息，指定信息现实的时间。时间到即信息消失
    */
    stateBar = statusBar();
    // 设置不显示label的边框
    stateBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    stateBar->setSizeGripEnabled(false); //设置是否显示右边的大小控制点

    QLabel *per1 = new QLabel("Ready", this);
    stateBar->addPermanentWidget(per1); //现实永久信息
    stateBar->showMessage("Init success...", 3000); // 显示临时信息，时间3秒钟.
}

void MainWindow::setupUi()
{
    resize(1200,800);
    m_mdiArea = new QScrollArea(this);
    setCentralWidget(m_mdiArea);

    m_leftW = new LeftWidget();
    QDockWidget *m_dockW = new QDockWidget(tr("window"), this);
    m_dockW->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);//可移动
    m_dockW->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_dockW->setWidget(m_leftW);
    this->addDockWidget(Qt::LeftDockWidgetArea, m_dockW);//初始位置

}

void MainWindow::initBuf()
{
    //先初始化buf
    memset(widgetBuf.buf, 0, 10240);
    widgetBuf.pos = 0;

    memset(stringBuf.buf, 0, 10240);
    stringBuf.pos = 0;

    memset(picBuf.buf, 0, 10240);
    picBuf.pos = 0;
}


/**
* 函数说明：创建xml文件
*
* @param
*
* @return
**/
bool MainWindow::docXmlCreate(QString &filename)
{
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    doc.clear();

    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QTextStream out(&file);
    doc.save(out,4);        //缩进4格

    file.close();
    return true;

}
/**
* 函数说明：写入xml文件
*
* @param
*
* @return
**/
bool MainWindow::docXmlWrite(QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return false;
    }
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}
/**
* 函数说明：读取xml文件
*
* @param
*
* @return
**/
bool MainWindow::docXmlRead(QString &filename)
{
    QString errorStr;
    int errorLine;
    int errorCol;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    //setContent是将指定的内容指定给QDomDocument解析，
    //第一参数可以是QByteArray或者是文件名等
    if(!doc.setContent(&file,true,&errorStr,&errorLine,&errorCol))
    {
        file.close();
        qDebug() << errorStr << "line: " << errorLine << "col: " << errorCol;
        return false;
    }

    file.close();
    return true;
}
QDomElement MainWindow::getWidgetDom(QWidget *w, int idx)
{
    QDomElement dom = doc.createElement(w->objectName());
    QDomAttr index = doc.createAttribute(QString("index"));
    index.setValue(QString::number(idx));
    dom.setAttributeNode(index);

    QDomAttr x0 = doc.createAttribute(QString("x0"));
    x0.setValue(QString::number(w->geometry().left()));
    dom.setAttributeNode(x0);
    QDomAttr y0 = doc.createAttribute(QString("y0"));
    y0.setValue(QString::number(w->geometry().top()));
    dom.setAttributeNode(y0);
    QDomAttr xSize = doc.createAttribute(QString("xSize"));
    xSize.setValue(QString::number(w->width()));
    dom.setAttributeNode(xSize);
    QDomAttr ySize = doc.createAttribute(QString("ySize"));
    ySize.setValue(QString::number(w->height()));
    dom.setAttributeNode(ySize);

    QDomAttr bkColor = doc.createAttribute(QString("bkColor"));
    bkColor.setValue(QString::number(w->height()));
    dom.setAttributeNode(bkColor);

    return dom;
}
bool MainWindow::saveProjectFile(QString &filename)
{
    // 1、先创建xml文件
    if (!docXmlCreate(filename))
    {
        return false;
    }
    //加入根节点
    QDateTime datetime = QDateTime::currentDateTime();
    QString currentDate = datetime.toString("yyyy-MM-dd dddd hh:mm");
    QDomElement root = doc.createElement(QString("PLT"));
    QDomAttr curDate = doc.createAttribute(QString("date"));
    curDate.setValue(currentDate);
    root.setAttributeNode(curDate);
    doc.appendChild(root);
    QWidgetList winList = EWindow::windowList();
    for(int i=0;i<winList.count();i++){
        QDomElement win = getWidgetDom(winList[i], i);
        root.appendChild(win);

        QWidgetList childList = ((EWindow *)winList[i])->childWidgets();
        for(int j=0;j<childList.count();j++){
            QDomElement child = getWidgetDom(childList[j], j);
            win.appendChild(child);
        }
    }
    // 2、写入到文件
    docXmlWrite(filename);
    return true;
}



void MainWindow::addWidget()
{

    int index = m_graphActList.indexOf((QAction *)sender());
    if (index < 0){
        return;
    }else if (index != 0){
        if (!curWin){
            QMessageBox::warning(NULL, "警告", "请先建父窗体！", QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }
    switch (index) {
    case 0:
    {
        curWin = new EWindow(m_mdiArea);
        curWin->resize(800,480);
        connect(curWin, SIGNAL(currentItemChanged(QWidget*)),
                m_leftW, SLOT(currentItemChanged(QWidget*)));
        curWin->propertyChanged(curWin);
        m_leftW->addWidget(curWin);
        break;
    }
    case 1:
    {
        EButton *btn = new EButton(curWin);
        QFont font = btn->font();
        font.setPixelSize(28);
        btn->setFont(font);
        btn->resize(80,50);
        curWin->addWidget(btn);
        connect(btn, SIGNAL(currentItemChanged(QWidget*)), curWin, SLOT(propertyChanged(QWidget*)));
        m_leftW->addWidget(btn);
        break;
    }
    case 2:
    {
        EText *text = new EText(curWin);
        QFont font = text->font();
        font.setPixelSize(28);
        text->setFont(font);
        text->resize(100,50);
        curWin->addWidget(text);
        connect(text, SIGNAL(currentItemChanged(QWidget*)), curWin, SLOT(propertyChanged(QWidget*)));
        m_leftW->addWidget(text);
        break;
    }
    case 3:
    {
        EEdit *edit = new EEdit(curWin);
        QFont font = edit->font();
        font.setPixelSize(28);
        edit->setFont(font);
        edit->resize(100,50);
        curWin->addWidget(edit);
        connect(edit, SIGNAL(currentItemChanged(QWidget*)), curWin, SLOT(propertyChanged(QWidget*)));
        m_leftW->addWidget(edit);
        break;
    }
    default:
        break;
    }
}

void MainWindow::ResProgress_slt(int pos, QString msg)
{
    if ((pos >= 100) && (msg == "done")){
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

char* MainWindow::QStringToMultBytes(QString str)
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

void MainWindow::newFile()
{

}

bool MainWindow::open()
{
    return true;
}

bool MainWindow::save()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("保存项目文件"),
                                                    "",
                                                    tr("保存为 (*.eprg)"));
    if(filename.isEmpty())
    {
        return false;              //如果关闭窗口或者点击取消，则返回-1，并退出
    }
    //1、先保存工程文件
    if (!saveProjectFile(filename))
    {
        qDebug()<<"保存工程文件失败！";

        return false;
    }
    return true;
}

bool MainWindow::saveAs()
{
    return true;
}

void MainWindow::about()
{

}

void MainWindow::redo()
{

}

void MainWindow::undo()
{

}

void MainWindow::copy()
{

}

void MainWindow::paste()
{

}

void MainWindow::cut()
{

}

void MainWindow::remove()
{
    curWin->remove(focusWidget());
}

void MainWindow::readText()
{
    QFile f1(":/char3000.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream input(&f1);
    m_charList = input.readAll();

    //1、初始化串口线程
    QThread *com_thread = new QThread;
    com = new ComDriver("COM1", "9600", "Even", "1");
    com->moveToThread(com_thread);
    com_thread->start();
    connect(this, SIGNAL(DownLoad_sig(int,int,QByteArray)),
            com, SLOT(DownLoad_slt(int,int,QByteArray)));
    connect(com, SIGNAL(ResProgress_sig(int,QString)),
            this, SLOT(ResProgress_slt(int,QString)));
}

void MainWindow::build()
{

    initBuf();

    //创建一个app_info
    struct list_head *head;
    struct list_head *childHead;

    WindowInfo *winInfo;
    ButtonInfo *btnInfo;
    TextInfo *textInfo;
    EditInfo *editInfo;

    QWidgetList winList = EWindow::windowList();
    for(int i=0;i<winList.count();i++){
        winInfo = (WindowInfo*)malloc(sizeof(WindowInfo));
        winInfo->firstChild = NULL;
        if (i == 0){
            //初始化链表头部
            head = &winInfo->base.node_info;
            init_list_head(head);
            set_base_info(&winInfo->base, winList[i]);
        }else{
            set_base_info(&winInfo->base, winList[i]);
            list_add_tail(&winInfo->base.node_info, head);
        }
        set_color_info(winInfo->BkColor, winList[i]);
        QWidgetList childList = ((EWindow *)winList[i])->childWidgets();

        BasePara *baseInfo;
        for(int j=0;j<childList.count();j++){
            if (childList[j]->objectName() == "Button"){
                btnInfo = (ButtonInfo*)malloc(sizeof(ButtonInfo));
                set_text_info(&btnInfo->text, childList[j]);
                set_color_info(btnInfo->BkColor, childList[j]);
                baseInfo = &btnInfo->base;
            }else if (childList[j]->objectName() == "Text"){
                textInfo = (TextInfo*)malloc(sizeof(TextInfo));
                set_text_info(&textInfo->text, childList[j]);
                set_color_info(textInfo->BkColor, childList[j]);
                baseInfo = &textInfo->base;
            }else if (childList[j]->objectName() == "Edit"){
                editInfo = (EditInfo*)malloc(sizeof(EditInfo));
                set_text_info(&editInfo->text, childList[j]);
                set_color_info(editInfo->BkColor, childList[j]);
                editInfo->maxLen = ((EEdit *)childList[j])->maxLen;
                baseInfo = &editInfo->base;
            }

            if (j == 0){
                //初始化链表头部
                childHead = &baseInfo->node_info;
                init_list_head(childHead);
                set_base_info(baseInfo, childList[j]);
                winInfo->firstChild = baseInfo;
            }else{
                set_base_info(baseInfo, childList[j]);
                list_add_tail(&baseInfo->node_info, childHead);
            }
        }
    }

    for_each_app(head);
}

void MainWindow::download()
{
    downloadStep = 0;
    ResProgress_slt(101, "done");
}
BasePara* MainWindow::set_base_info(BasePara *base, QWidget *w)
{
    if (base == NULL)
    {
        return NULL;
    }

    base->x0 = w->geometry().left();
    base->y0 = w->geometry().top();
    base->xsize = w->width();
    base->ysize = w->height();
    base->resv[0] = 0;
    base->resv[1] = 0;
    base->resv[2] = 0;

    if (w->objectName() == "Window"){
        base->type = 0;
    }else if (w->objectName() == "Button"){
        base->type = 1;
    }else if (w->objectName() == "Text"){
        base->type = 2;
    }else if (w->objectName() == "Edit"){
        base->type = 3;
    }
    return base;
}
void MainWindow::set_text_info(TextPara *text, QWidget *w)
{
    QColor bc;
    if (w->objectName() == "Button"){
        bc = ((EButton *)w)->palette().color(QPalette::ButtonText);
        text->color = QColorToEColor(bc);
        text->alignment = (2<<0) | (3<<2);

        text->string = QStringToMultBytes(((EButton *)w)->text());
    }else if (w->objectName() == "Text"){
        bc = ((EText *)w)->palette().color(QPalette::WindowText);
        text->color = QColorToEColor(bc);
        //text->alignment = (2<<0) | (3<<2);
        text->alignment = alignmentConvert(((EText *)w)->alignment());
        text->string = QStringToMultBytes(((EText *)w)->text());
    }else if (w->objectName() == "Edit"){
        bc = ((EEdit *)w)->palette().color(QPalette::Text);
        text->color = QColorToEColor(bc);
        //text->alignment = (2<<0) | (3<<2);
        text->alignment = alignmentConvert(((EEdit *)w)->alignment());
        text->string = QStringToMultBytes(((EEdit *)w)->text());
    }

}

int MainWindow::alignmentConvert(int align)
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
uint MainWindow::QColorToEColor(QColor color)
{
    uint rgb = color.rgb();
    qDebug()<<QString::number(rgb, 16);
    //互换rb颜色
    rgb = ((rgb & 0x000000ff) << 16) | (rgb & 0x0000ff00) | ((rgb & 0x00ff0000) >> 16);
    qDebug()<<QString::number(rgb, 16);
    return rgb;
}

int MainWindow::set_color_info(int *color, QWidget *w)
{
    QColor bc;
    if (w->objectName() == "Window"){
        bc = ((EWindow *)w)->palette().color(QPalette::Window);
        color[0] = QColorToEColor(bc);
    }else if (w->objectName() == "Button"){
        bc = ((EButton *)w)->palette().color(QPalette::Disabled ,QPalette::Button);
        color[0] = QColorToEColor(bc);
        color[0] = INVALID_COLOR;
        bc = ((EButton *)w)->palette().color(QPalette::Active ,QPalette::Button);
        color[1] = QColorToEColor(bc);
        color[1] = INVALID_COLOR;
        bc = ((EButton *)w)->palette().color(QPalette::Inactive ,QPalette::Button);
        color[2] = QColorToEColor(bc);
    }else if (w->objectName() == "Text"){
        bc = ((EText *)w)->palette().color(QPalette::Window);
        color[0] = QColorToEColor(bc);
    }else if (w->objectName() == "Edit"){
        bc = ((EEdit *)w)->palette().color(QPalette::Disabled, QPalette::Base);
        color[0] = QColorToEColor(bc);
        color[0] = INVALID_COLOR;
        bc = ((EEdit *)w)->palette().color(QPalette::Base);
        color[1] = QColorToEColor(bc);
    }

}
void MainWindow::for_each_app(const struct list_head *head)
{
    struct list_head *pos;
    BasePara *baseInfo;
    WindowInfo *winInfo, *dstWin;
    ButtonInfo *btnInfo, *dstBtn;
    TextInfo *textInfo, *dstText;
    EditInfo *editInfo, *dstEdit;
    //遍历链表
    if (!head) return;
    list_for_each(pos, head)
    {
        baseInfo = list_entry(pos, BasePara, node_info);
        qDebug()<<baseInfo->x0<<baseInfo->y0<<baseInfo->xsize<<baseInfo->ysize<<baseInfo->type;
        switch(baseInfo->type) {
        case Window:
            winInfo = (WindowInfo *)baseInfo;

            dstWin = (WindowInfo *)(widgetBuf.buf + widgetBuf.pos);
            memcpy(dstWin, winInfo, sizeof(WindowInfo));
            widgetBuf.pos += sizeof(WindowInfo);
            dstWin->firstChild = (BasePara *)(widgetBuf.pos + START_ADDR_SDRAM_WIDGET);
            if (!winInfo->firstChild){
                break;
            }
            for_each_app(&winInfo->firstChild->node_info);

            dstWin->base.node_info.prev = NULL;
            //是否结束
            if (pos != head){
                dstWin->base.node_info.next = (list_head *)(widgetBuf.pos + START_ADDR_SDRAM_WIDGET);
            }else{
                dstWin->base.node_info.next = NULL;
            }
            break;
        case Button:
            btnInfo = (ButtonInfo *)baseInfo;

            dstBtn = (ButtonInfo *)(widgetBuf.buf + widgetBuf.pos);
            memcpy(dstBtn, btnInfo, sizeof(ButtonInfo));
            widgetBuf.pos += sizeof(ButtonInfo);
            dstBtn->base.node_info.prev = NULL;
            dstBtn->text.string = (char *)(START_ADDR_SDRAM_STRING + (dstBtn->text.string - stringBuf.buf));
            //是否结束
            if (pos != head){
                dstBtn->base.node_info.next = (list_head *)(widgetBuf.pos + START_ADDR_SDRAM_WIDGET);
            }else{
                dstBtn->base.node_info.next = NULL;
            }
            break;
        case Text:
            textInfo = (TextInfo *)baseInfo;

            dstText = (TextInfo *)(widgetBuf.buf + widgetBuf.pos);
            memcpy(dstText, textInfo, sizeof(TextInfo));
            widgetBuf.pos += sizeof(TextInfo);
            dstText->base.node_info.prev = NULL;
            dstText->text.string = (char *)(START_ADDR_SDRAM_STRING + (dstText->text.string - stringBuf.buf));
            //是否结束
            if (pos != head){
                dstText->base.node_info.next = (list_head *)(widgetBuf.pos + START_ADDR_SDRAM_WIDGET);
            }else{
                dstText->base.node_info.next = NULL;
            }
            break;
        case Edit:
            editInfo = (EditInfo *)baseInfo;

            dstEdit = (EditInfo *)(widgetBuf.buf + widgetBuf.pos);
            memcpy(dstEdit, editInfo, sizeof(EditInfo));
            widgetBuf.pos += sizeof(EditInfo);
            dstEdit->base.node_info.prev = NULL;
            dstEdit->text.string = (char *)(START_ADDR_SDRAM_STRING + (dstEdit->text.string - stringBuf.buf));
            //是否结束
            if (pos != head){
                dstEdit->base.node_info.next = (list_head *)(widgetBuf.pos + START_ADDR_SDRAM_WIDGET);
            }else{
                dstEdit->base.node_info.next = NULL;
            }
            break;
        default:
            break;
        }
        if (pos == head) break;
    }
}


