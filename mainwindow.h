#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "widget.h"
#include "leftwidget.h"
#include "formwindow.h"
#include "basewidget.h"
#include "widgetselection.h"
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

    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *findAct;

    QAction *wstackAct;
    QAction *whsideAct;
    QAction *wvsideAct;

    QAction *aboutAct;

    QMdiArea *m_mdiArea;
    LeftWidget *m_leftW;
};

#endif // MAINWINDOW_H
