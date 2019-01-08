#ifndef EDITOR_H
#define EDITOR_H

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QAction>
#include <QMenu>

#include "codeeditor.h"

class MdiChild : public CodeEditor
{
    Q_OBJECT
public:
    explicit MdiChild(QWidget *parent = 0);

    QString curFile;
    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString currentFile() { return curFile; }
private:
    void createActions();
public slots:
    void documentWasModified();
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *event);
    //void dragEnterEvent(QDragEnterEvent *e);
   // void dropEvent(QDropEvent *e);
signals:
    void fontChang();//字体设置信号
    void fontColor();//字体颜色信号
    void Del();//删除信号
private:
    bool isUntitled;
    bool maybeSave();
    void setCurrentFile(const QString &fileName);

    //自定义的右键菜单项目
    QAction *actRedo;
    QAction *actUndo;
    QAction *actCut;
    QAction *actCopy;
    QAction *actPaste;
    QAction *actDel;
    QAction *actSelectAll;
    QAction *actFontChang;
    QAction *actFontColor;
};

#endif // EDITOR_H
