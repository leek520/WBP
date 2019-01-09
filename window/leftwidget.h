#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QTreeWidgetItem>
#include "common.h"
#include "widget.h"
#include "widgetselection.h"
class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = 0);
    QSize sizeHint() const {
        return QSize(250, 200);
    }
    void setInit();
signals:
    void switchTabWindow(Widget *w);
private:
public slots:
    void addWidget(Widget *w);
    void setCurrentItem(QWidget *w);
    void removeWidget(QWidget *w);
    void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
private:
    QTreeWidget *m_objectTree;
    QTreeWidgetItem *m_curWinItem;
};

#endif // LEFTWIDGET_H
