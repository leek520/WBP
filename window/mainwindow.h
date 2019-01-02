#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "leftwidget.h"
#include "propertywidget.h"
#include "widgetselection.h"
#include "widget.h"
#include "formwindow.h"
#include "comobject.h"
#include "propertydialog.h"
#include "comdialog.h"
#include "toolbar.h"
#include "scrollarea.h"
#include "bottomwidget.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void mouseMoveEvent(QMouseEvent * event);
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
    QDomElement widgetToDom(Widget *w, QDomElement root);
    void DomToWidget(QDomElement root, Widget *w);

    char *QStringToMultBytes(QString str);

    WindowInfo *setWidgetInfo(Widget *w, struct list_head *head, int *pos, int start);
    void setBaseInfo(Widget *w, BasePara *base);
    void setTextInfo(Widget *w, TextPara *text);

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

    void setCom();

    void ResProgress_slt(int step, int pos, QString msg="");
    void MouseButtonDblClick(Widget *w);
    void addWidget();
    void addWidgetSlt(WidgetType type, QPoint pos);
    Widget* addWidget(WidgetType type);
signals:

private:
    QStatusBar *stateBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QMenu *buildMenu;
    QMenu *viewMenu;
    QMenu *setMenu;
    QMenu *windowMenu;


    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *viewToolBar;
    QToolBar *buildToolBar;
    QToolBar *windowToolBar;

    ToolBar *graphToolBar;
    ToolBar *widgetToolBar;


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

    QAction *setComAct;

    QAction *buildAct;
    QAction *downAct;

    QPoint dragPosition;

    QList <QAction *>m_widgetActList;
    QList <QAction *>m_graphActList;

    Selection *m_sel;
    ScrollArea *m_mdiArea;
    QDomDocument doc;
    LeftWidget *m_leftW;
    PropertyWidget *m_propW;
    PropertyDialog *m_propD;
    BottomWidget *m_bottomW;
    ComDialog *m_comD;
    ProgressBar *m_progressBar;
    QDockWidget *m_dockBottom;

    BuildInfo *buildInfo;
};

#endif // MAINWINDOW_H
