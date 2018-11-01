#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include "common.h"

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = 0);
    QSize sizeHint() const {
        return QSize(200, 200);
    }
signals:

public slots:
private:
    QTreeWidget *m_tree;
    QTableWidget *m_table;

};

#endif // LEFTWIDGET_H
