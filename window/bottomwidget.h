#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include "common.h"
#include "widget.h"

class BottomWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit BottomWidget(QWidget *parent = 0);
    QSize sizeHint() const {
        return QSize(250, 50);
    }
    void insertMessage(QString msg);
signals:

private:
signals:

public slots:
};

#endif // BOTTOMWIDGET_H
