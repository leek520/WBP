#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QTreeWidgetItem>
#include "common.h"
#include "widget.h"

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = 0);
    QSize sizeHint() const {
        return QSize(250, 200);
    }
signals:

private:
public slots:
    void addWidget(Widget *w);
    void currentItemChanged(Widget *w);
    void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void removeWidgetSlt(Widget *w);
private:
    QTreeWidget *m_objectTree;
    QTreeWidgetItem *m_curWinItem;
};

#endif // LEFTWIDGET_H
