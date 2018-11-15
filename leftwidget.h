#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include "common.h"
#include "basewidget.h"
#include "formwindow.h"


#define PropName(x)     (#x+14)
#define PropValue(x)    QString("%1").arg(x)
class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = 0);
    void initUi();
    QSize sizeHint() const {
        return QSize(250, 200);
    }
signals:
private:
    void setPropertyTable(int row, QString prop, QString value);
public slots:
    void currentChanged(QWidget *now);
private:
    QTreeWidget *m_objectTree;
    QTableWidget *m_propertyTable;

};

#endif // LEFTWIDGET_H
