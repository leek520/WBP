#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>

class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(QWidget *parent = 0);
    QSize sizeHint() const {
        return QSize(250, 200);
    }
signals:

public slots:
};

#endif // PROPERTYWIDGET_H
