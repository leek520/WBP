#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include "common.h"
#include "widget.h"
class ToolBar : public QToolBar
{
public:
    ToolBar(const QString &title, QWidget *parent = 0);
    void addAction(QAction *action);
protected:
    bool eventFilter(QObject *watched, QEvent *event);
public:
    static QAction *pressAct;
};

#endif // TOOLBAR_H
