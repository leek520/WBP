#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "widget.h"
#include "leftwidget.h"
#include "formwindow.h"
#include "basewidget.h"
#include "widgetselection.h"
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



    void set_text_info(TextPara *text, QWidget *w);

    uint QColorToEColor(QColor color);
    int set_color_info(int *color, QWidget *w);

    void QStringToMultBytes(QString str, char *array);
    BasePara* set_base_info(BasePara *base, QWidget *w);
    void for_each_app(const struct list_head *head);
    void destroy_app_list(struct list_head *head);
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

    void readText();
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

private:
    EWindow *curentWin;
    ComDriver *com;
    QString m_charList;
    struct SendBuf{
       int len;
       char buf[10240];
    }sendBuf;

};

#endif // MAINWINDOW_H
