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
    resize(1000,600);
    m_mdiArea = new QScrollArea(this);
    setCentralWidget(m_mdiArea);

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

}

void MainWindow::remove()
{

}



void MainWindow::build()
{


}

void MainWindow::download()
{

}

void MainWindow::addWidget()
{
    Widget *w = new Widget(m_mdiArea);

    Selection *sel = new Selection(m_mdiArea);
    sel->addWidget(w);
    sel->setCurrent(w);
    w->setGeometry(20,20,200,100);
    w->show();
}


