#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    buildInfo(new BuildInfo()),
    m_progressBar(new ProgressBar())
{
    setWindowTitle(tr("WBP"));//设置窗口标题
    setWindowIcon(QIcon(":/mamtool.ico"));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    setupUi();

    connect(buildInfo, SIGNAL(ResProgress_sig(int,int,QString)),
            this, SLOT(ResProgress_slt(int,int,QString)));
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

    /****set****/
    setComAct = new QAction(QIcon(":/images/about.png"), tr("&SetCom"), this);
    setComAct->setStatusTip(tr(""));
    connect(setComAct, SIGNAL(triggered()), this, SLOT(setCom()));

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

    setMenu = menuBar()->addMenu(tr("&Set"));
    setMenu->addAction(setComAct);

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
    stateBar = new QStatusBar(this);
    setStatusBar(stateBar);
    // 设置不显示label的边框
    stateBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    stateBar->setSizeGripEnabled(false); //设置是否显示右边的大小控制点

    QLabel *per1 = new QLabel("Ready", this);
    stateBar->addPermanentWidget(per1); //现实永久信息
    stateBar->showMessage("Init success...", 3000); // 显示临时信息，时间3秒钟.
}

void MainWindow::setupUi()
{
    setWindowState(Qt::WindowMaximized);
    m_mdiArea = new QScrollArea(this);
    m_mdiArea->setObjectName("m_mdiArea");
    m_mdiArea->setStyleSheet("QScrollArea#m_mdiArea{background-color:gray;}");
    setCentralWidget(m_mdiArea);
    new Selection(m_mdiArea);

    m_leftW = new LeftWidget();
    QDockWidget *m_dockLeft = new QDockWidget(tr("window"), this);
    m_dockLeft->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);//可移动
    m_dockLeft->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_dockLeft->setWidget(m_leftW);
    this->addDockWidget(Qt::LeftDockWidgetArea, m_dockLeft);//初始位置

    m_propW = new PropertyWidget();
    QDockWidget *m_dockRight = new QDockWidget(tr("Property"), this);
    m_dockRight->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);//可移动
    m_dockRight->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_dockRight->setWidget(m_propW);
    this->addDockWidget(Qt::RightDockWidgetArea, m_dockRight);//初始位置
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

    QList<FormWindow *> winList = FormWindow::getWindowList();
    for(int i=0;i<winList.count();i++){
        QDomElement winDom = widgetToDom(winList[i], root);

        QWidgetList childList = winList[i]->getChildList();
        for(int j=0;j<childList.count();j++){
            widgetToDom((Widget *)childList[j], winDom);
        }
    }
    // 2、写入到文件
    docXmlWrite(filename);
    return true;
}

bool MainWindow::openProjectFile(QString &filename)
{
    // 先读取xml文件
    if (!docXmlRead(filename))
    {
        return false;
    }

    QDomElement root = doc.documentElement();
    QString title = root.tagName();
    QString date = root.attribute(tr("date"));

    QDomNode winNode = root.firstChild();
    while (!winNode.isNull())
    {
        QDomElement wDom = winNode.toElement();
        QString type = wDom.tagName();

        Widget *win = addWidget(Window);
        DomToWidget(wDom, win);
        QDomNode childNode = winNode.firstChild();
        while (!childNode.isNull()){
            wDom = childNode.toElement();
            type = wDom.tagName();
            Widget *child = addWidget(StrToEnum(type));
            DomToWidget(wDom, child);

            childNode = childNode.nextSibling();
        }

        winNode = winNode.nextSibling();
    }
    return true;
}

QDomElement MainWindow::widgetToDom(Widget *w, QDomElement root)
{
    QList<QPair<QVariant::Type, QString> > propTable;
    propTable = w->getPropertyTable();

    QDomElement childDom = doc.createElement(EnumToStr(w->getType()));
    for(int k=0;k<propTable.count();k++){
        QDomAttr propNode = doc.createAttribute(propTable[k].second);
        QVariant value = w->property(propTable[k].second.toLocal8Bit());
        if (propTable[k].second == "geometry"){
            QRect rect = value.toRect();
            propNode.setValue(QString("[(%1,%2)],%3×%4")
                             .arg(rect.left())
                             .arg(rect.top())
                             .arg(rect.width())
                             .arg(rect.height()));
        }else{
            propNode.setValue(value.toString());
        }

        childDom.setAttributeNode(propNode);
    }
    root.appendChild(childDom);
    return childDom;
}

void MainWindow::DomToWidget(QDomElement root, Widget *w)
{
    QList<QPair<QVariant::Type, QString> > propTable;
    propTable = w->getPropertyTable();
    for(int i=0;i<propTable.count();i++){
        QString attrVaue = root.attribute(propTable[i].second);
        QVariant value;
        switch (propTable[i].first){
        case QVariant::Int:
            w->setProperty(propTable[i].second.toLocal8Bit(), attrVaue.toInt());
            break;
        case QVariant::String:
            w->setProperty(propTable[i].second.toLocal8Bit(), attrVaue);
            break;
        case QVariant::Color:
            w->setProperty(propTable[i].second.toLocal8Bit(), QColor(attrVaue));
            break;
        case QVariant::Rect:
        {
            QRegExp rx("(\\d+)");
            QStringList list;
            int pos = 0;
            while ((pos = rx.indexIn(attrVaue, pos)) != -1) {
                list << rx.cap(1);
                pos += rx.matchedLength();
            }
            if (list.count() == 4){
                QRect rect(list[0].toInt(), list[1].toInt(), list[2].toInt(), list[3].toInt());
                w->setProperty(propTable[i].second.toLocal8Bit(), rect);
            }
            break;
        }
        default:
            value = QVariant::fromValue<QString>(attrVaue);
            break;
        }

    }

}


void MainWindow::newFile()
{

}

bool MainWindow::open()
{
    //弹出打开对话框
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("打开工程文件"),
                                                    "",
                                                    tr("工程文件(*.eprg);;All files(*.*)"));
    if(filename.isEmpty())
    {
        return false;              //如果关闭窗口或者点击取消，则返回-1，并退出
    }
    //1、先保存工程文件
    if (!openProjectFile(filename))
    {
        qDebug()<<"打开工程文件失败！";

        return false;
    }
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
//    buildInfo->QImageToEImage(FormWindow::m_curWin->getBkImage(), FormWindow::m_curWin->getImagePos());
}

void MainWindow::remove()
{
    FormWindow::m_curWin->removeWidget(focusWidget());
}

struct list_head *MainWindow::setWidgetInfo(Widget *w, struct list_head *head, int *pos, int start)
{
    int curPos = (*pos);
    struct list_head *child = NULL;
    BasePara *base;
    switch (w->getType()) {
    case Window:
    {
        WindowInfo *winInfo = (WindowInfo*)(start + curPos);
        child = &winInfo->childList;
        init_list_head(child);
        winInfo->BkColor[0] = buildInfo->QColorToEColor(w->getBkColor());
        winInfo->Image = buildInfo->QImageToEImage(w->getBkImage(), w->getImagePos());
        base = &winInfo->base;
        *pos = curPos + sizeof(WindowInfo);
        break;
    }
    case Button:
    {
        ButtonInfo *btnInfo = (ButtonInfo*)(start + curPos);
        btnInfo->BkColor[0] = buildInfo->QColorToEColor(w->getBkColor());
        btnInfo->BkColor[1] = buildInfo->QColorToEColor(w->getBkPressColor());
        btnInfo->BkColor[2] = buildInfo->QColorToEColor(w->getBkDisableColor());
        btnInfo->cmd = buildInfo->QStringToChar(w->getLuaCmd());
        setTextInfo(w, &btnInfo->text);
        base = &btnInfo->base;
        *pos = curPos + sizeof(ButtonInfo);
        break;
    }
    case Text:
    {
        TextInfo *textInfo = (TextInfo*)(start + curPos);
        textInfo->BkColor[0] = buildInfo->QColorToEColor(w->getBkColor());
        setTextInfo(w, &textInfo->text);
        base = &textInfo->base;
        *pos = curPos + sizeof(TextInfo);
        break;
    }
    case Edit:
    {
        EditInfo *editInfo = (EditInfo*)(start + curPos);
        editInfo->BkColor[0] = buildInfo->QColorToEColor(w->getBkColor());
        editInfo->BkColor[1] = buildInfo->QColorToEColor(w->getBkDisableColor());
        setTextInfo(w, &editInfo->text);
        base = &editInfo->base;
        *pos = curPos + sizeof(EditInfo);
        break;
    }
    default:
        break;
    }

    setBaseInfo(w, base);

    list_add_tail(&base->list, head);

    return child;
}

void MainWindow::setBaseInfo(Widget *w, BasePara *base)
{
    //设置base信息
    base->Id = w->getId();
    base->x0 = w->geometry().left();
    base->y0 = w->geometry().top();
    base->xsize = w->width();
    base->ysize = w->height();

    base->resv = 0;
    base->type = int(w->getType());
}

void MainWindow::setTextInfo(Widget *w, TextPara *text)
{
    text->color = buildInfo->QColorToEColor(w->getTextColor());
    text->alignment = buildInfo->QAlignToEAlign((w->getAlignH() << 1) | (w->getAlignV() << 6));
    text->string = buildInfo->QStringToMultBytes(w->getString());

}

void MainWindow::build()
{

    buildInfo->initBuild();

    BuildInfo::WidgetBuf *widgetBuf = buildInfo->getWidgetBuf();
    int startAddress = (int)(&widgetBuf->buf);
    WindowInfo *headInfo = (WindowInfo *)(startAddress);
    struct list_head *winHead = &headInfo->base.list;

    init_list_head(winHead);
    init_list_head(&headInfo->childList);

    widgetBuf->pos += sizeof(WindowInfo);

    QList<FormWindow *> winList = FormWindow::getWindowList();
    for(int i=0;i<winList.count();i++){
        FormWindow *win = winList[i];

        struct list_head* childHead = setWidgetInfo(win, winHead, &widgetBuf->pos, startAddress);

        QWidgetList childList = win->getChildList();
        for(int j=0;j<childList.count();j++){
            Widget *child = (Widget *)childList[j];
            setWidgetInfo(child, childHead, &widgetBuf->pos, startAddress);
        }
    }
    //处理地址
    int offset = START_ADDR_SDRAM_WIDGET - startAddress;
    struct list_head *win;

    list_for_each(win, winHead){
        win->prev->next = ConvListAdd(win->prev->next, offset);
        win->prev = ConvListAdd(win->prev, offset);

        struct list_head *child;
        struct list_head *childHead = &((WindowInfo *)win)->childList;
        list_for_each(child, childHead){
            child->prev->next = ConvListAdd(child->prev->next, offset);
            child->prev = ConvListAdd(child->prev, offset);
        }
        childHead->prev->next = ConvListAdd(childHead->prev->next, offset);
        childHead->prev = ConvListAdd(childHead->prev, offset);
    }
    winHead->prev->next = ConvListAdd(winHead->prev->next, offset);
    winHead->prev = ConvListAdd(winHead->prev, offset);

    stateBar->showMessage("编译完成！", 3000); // 显示临时信息，时间3秒钟.
}

void MainWindow::download()
{
    buildInfo->downLoadInfo();
}

void MainWindow::setCom()
{
    m_comD = new ComDialog(this);
    m_comD->show();
}

void MainWindow::ResProgress_slt(int step, int pos, QString msg)
{
    if (step == 0){
        connect(m_progressBar, SIGNAL(cancel_sig(int,int)),
                this, SLOT(ResProgress_slt(int,int)));
        m_progressBar->setMaxStep(4);
        m_progressBar->setValue(0, 0);
        stateBar->addWidget(m_progressBar);
    }else{
        m_progressBar->setValue(step, pos);
        if (step > 4){
            stateBar->removeWidget(m_progressBar);
            disconnect(m_progressBar, SIGNAL(cancel_sig(int,int)),
                    this, SLOT(ResProgress_slt(int,int)));
            if ((pos >= 100) && (step < 6)){
                QMessageBox::information(this, tr("提示"), tr("下载完成！"));
            }else{
                buildInfo->cancel();
            }
        }
    }
}

void MainWindow::MouseButtonDblClick(QWidget *w)
{
    m_propD = new PropertyDialog(this);
    m_propD->show();
}

void MainWindow::addWidget()
{
    WidgetType type = (WidgetType)m_graphActList.indexOf((QAction *)sender());
    addWidget(type);
}

Widget* MainWindow::addWidget(WidgetType type)
{
    if (type == Window){
        FormWindow *win = new FormWindow(m_mdiArea);
        connect(win, SIGNAL(currentItemChanged(Widget*)),
                m_propW, SLOT(currentItemChanged(Widget*)));
        connect(win, SIGNAL(MouseButtonDblClick(QWidget*)),
                this, SLOT(MouseButtonDblClick(QWidget*)));
        win->resize(800, 480);
        win->propertyChanged(win);
        FormWindow::m_curWin = win;
        return win;
    }else{
        if (!FormWindow::m_curWin){
            QMessageBox::warning(NULL, "警告", "请先创建窗体！", QMessageBox::Yes, QMessageBox::Yes);
            return NULL;
        }
        Widget *w = new Widget(type, FormWindow::m_curWin);
        connect(w, SIGNAL(currentItemChanged(Widget*)),
                m_propW, SLOT(currentItemChanged(Widget*)));
        connect(w, SIGNAL(MouseButtonDblClick(QWidget*)),
                this, SLOT(MouseButtonDblClick(QWidget*)));
        w->resize(50, 30);
        FormWindow::m_curWin->addWidget(w);
        return w;
    }

}


