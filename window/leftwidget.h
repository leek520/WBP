#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include "common.h"

#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = 0);
    void initUi();
    QSize sizeHint() const {
        return QSize(150, 200);
    }

signals:
private:


public slots:

private:
    QTreeWidget *m_objectTree;
};

#endif // LEFTWIDGET_H
