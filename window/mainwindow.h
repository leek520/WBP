#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "leftwidget.h"
#include "propertywidget.h"
#include "widgetselection.h"
#include "widget.h"

#include "comobject.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void setupUi();

    bool docXmlRead(QString &filename);
    bool docXmlCreate(QString &filename);
    bool docXmlWrite(QString &filename);
    bool saveProjectFile(QString &filename);
    bool openProjectFile(QString &filename);

private slots:
    void newFile();
    bool open();
    bool save();
    bool saveAs();
    void about();

    void redo();
    void undo();
    void copy();
    void paste();
    void cut();
    void remove();

    void build();
    void download();

    void addWidget();
signals:
    void DownLoad_sig(const int cmd, const int addr, const QByteArray data);
private:
    QStatusBar *stateBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QMenu *buildMenu;
    QMenu *viewMenu;
    QMenu *windowMenu;


    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *viewToolBar;
    QToolBar *graphToolBar;
    QToolBar *buildToolBar;
    QToolBar *windowToolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;

    QAction *redoAct;
    QAction *undoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *removeAct;

    QAction *aboutAct;

    QAction *buildAct;
    QAction *downAct;

    QList <QAction *>m_graphActList;

    QScrollArea *m_mdiArea;
    LeftWidget *m_leftW;
    PropertyWidget *m_propW;
    QDomDocument doc;
};

#endif // MAINWINDOW_H
