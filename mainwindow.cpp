#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("WBP"));//设置窗口标题
    setWindowIcon(QIcon(":/mamtool.ico"));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    setupUi();

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
    m_mdiArea = new QMdiArea(this);
    setCentralWidget(m_mdiArea);

    m_leftW = new LeftWidget();
    QDockWidget *m_dockW = new QDockWidget(tr("window"), this);
    m_dockW->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);//可移动
    m_dockW->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_dockW->setWidget(m_leftW);
    this->addDockWidget(Qt::LeftDockWidgetArea, m_dockW);//初始位置


    FormWindow *win = new FormWindow(m_mdiArea);
    win->resize(800,480);
    connect(win, SIGNAL(currentChanged(QWidget*)),
            m_leftW, SLOT(currentChanged(QWidget*)));
    EPushButton *btn = new EPushButton(win);
    btn->resize(100,200);
    btn->setText("菜单");
    win->addWidget(btn);

    ELabel *lbl = new ELabel(win);
    lbl->resize(100,100);
    lbl->setText("abc1123");
    win->addWidget(lbl);


}

void MainWindow::QStringToMultBytes(QString str, char *array)
{
//    char* ptr;
//    QByteArray ba;
//    ba = str.toLocal8Bit();
//    ptr = ba.data();
//    memset(array, 0, 128);
//    strcpy(array, ptr);

    memset(array, 0, 128);

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
        array[i*3+0] = 0xe0 | ((num >> 12) & 0xf);
        array[i*3+1] = 0x80 | ((num >> 6) & 0x3f);
        array[i*3+2] = 0x80 | ((num >> 0) & 0x3f);
    }
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

}

void MainWindow::readText()
{
    memset(sendBuf.buf, 0, 1024);
    sendBuf.len = 0;


    QFile f1(":/char3000.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream input(&f1);
    m_charList = input.readAll();
}

void MainWindow::build()
{
    //创建一个app_info
    struct list_head *head;
    struct list_head *childHead;

    WindowInfo *winInfo;
    ButtonInfo *btnInfo;
    TextInfo *textInfo;
    EditInfo *editInfo;

    QWidgetList winList = FormWindow::windowList();
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

        QWidgetList childList = ((FormWindow *)winList[i])->childWidgets();
        childList.removeOne(winList[i]);

        BaseInfo *baseInfo;
        for(int j=0;j<childList.count();j++){
            if (childList[j]->objectName() == "Button"){
                btnInfo = (ButtonInfo*)malloc(sizeof(ButtonInfo));
                QStringToMultBytes(((QPushButton *)childList[j])->text(), btnInfo->text);
                baseInfo = &btnInfo->base;
            }else if (childList[j]->objectName() == "Text"){
                textInfo = (TextInfo*)malloc(sizeof(TextInfo));
                QStringToMultBytes(((QLabel *)childList[j])->text(), textInfo->text);
                baseInfo = &textInfo->base;
            }else if (childList[j]->objectName() == "Edit"){
                editInfo = (EditInfo*)malloc(sizeof(EditInfo));
                QStringToMultBytes(((QLineEdit *)childList[j])->text(), editInfo->text);
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
    //1、初始化串口线程
    QThread *com_thread = new QThread;
    com = new ComDriver("COM1", "9600", "Even", "1");
    com->moveToThread(com_thread);
    com_thread->start();
    connect(this, SIGNAL(DownLoad_sig(int,int,QByteArray)),
            com, SLOT(DownLoad_slt(int,int,QByteArray)));

    //擦除20K，下载地址，下载数据包
    int erase = 0x5c;
    int address = START_ADDR_FLASH;
    QByteArray byte;
    byte.resize(sendBuf.len);
    for(int i=0;i<sendBuf.len;i++) {
        byte[i] = sendBuf.buf[i];
    }
    emit DownLoad_sig(erase, address, byte);

}
BaseInfo* MainWindow::set_base_info(BaseInfo *base, QWidget *w)
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
void MainWindow::for_each_app(const struct list_head *head)
{
    struct list_head *pos;
    BaseInfo *baseInfo;
    WindowInfo *winInfo, *dstWin;
    ButtonInfo *btnInfo, *dstBtn;
    TextInfo *textInfo, *dstText;
    EditInfo *editInfo, *dstEdit;
    //遍历链表
    list_for_each(pos, head)
    {
        baseInfo = list_entry(pos, BaseInfo, node_info);
        qDebug()<<baseInfo->x0<<baseInfo->y0<<baseInfo->xsize<<baseInfo->ysize<<baseInfo->type;
        switch(baseInfo->type) {
        case Window:
            winInfo = (WindowInfo *)baseInfo;

            dstWin = (WindowInfo *)(sendBuf.buf + sendBuf.len);
            memcpy(dstWin, winInfo, sizeof(WindowInfo));
            sendBuf.len += sizeof(WindowInfo);
            dstWin->firstChild = (BaseInfo *)(sendBuf.len + START_ADDR_SDRAM);

            for_each_app(&winInfo->firstChild->node_info);

            dstWin->base.node_info.prev = NULL;
            //是否结束
            if (pos != head){
                dstWin->base.node_info.next = (list_head *)(sendBuf.len + START_ADDR_SDRAM);
            }else{
                dstWin->base.node_info.next = NULL;
            }
            break;
        case Button:
            btnInfo = (ButtonInfo *)baseInfo;

            dstBtn = (ButtonInfo *)(sendBuf.buf + sendBuf.len);
            memcpy(dstBtn, btnInfo, sizeof(ButtonInfo));
            sendBuf.len += sizeof(ButtonInfo);
            dstBtn->base.node_info.prev = NULL;
            //是否结束
            if (pos != head){
                dstBtn->base.node_info.next = (list_head *)(sendBuf.len + START_ADDR_SDRAM);
            }else{
                dstBtn->base.node_info.next = NULL;
            }
            qDebug()<<QString(btnInfo->text);
            break;
        case Text:
            textInfo = (TextInfo *)baseInfo;

            dstText = (TextInfo *)(sendBuf.buf + sendBuf.len);
            memcpy(dstText, textInfo, sizeof(TextInfo));
            sendBuf.len += sizeof(TextInfo);
            dstText->base.node_info.prev = NULL;
            //是否结束
            if (pos != head){
                dstText->base.node_info.next = (list_head *)(sendBuf.len + START_ADDR_SDRAM);
            }else{
                dstText->base.node_info.next = NULL;
            }
            qDebug()<<QString(textInfo->text);
            break;
        case Edit:
            editInfo = (EditInfo *)baseInfo;

            dstEdit = (EditInfo *)(sendBuf.buf + sendBuf.len);
            memcpy(dstEdit, editInfo, sizeof(EditInfo));
            sendBuf.len += sizeof(EditInfo);
            dstEdit->base.node_info.prev = NULL;
            //是否结束
            if (pos != head){
                dstEdit->base.node_info.next = (list_head *)(sendBuf.len + START_ADDR_SDRAM);
            }else{
                dstEdit->base.node_info.next = NULL;
            }
            qDebug()<<QString(editInfo->text);
            break;
        default:
            break;
        }
        if (pos == head) break;
    }
}

void MainWindow::destroy_app_list(struct list_head *head)
{
    struct list_head *pos = head->next;
    struct list_head *tmp = NULL;
    while (pos != head)
    {
        tmp = pos->next;
        list_del(pos);
        pos = tmp;
    }
}

