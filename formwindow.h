#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include "common.h"
#include "widgetselection.h"

class FormWindow : public QFrame
{
    Q_OBJECT
public:
    explicit FormWindow(QWidget *parent = 0);
    ~FormWindow();
    void addWidget(QWidget *w);
    void setCurrent(QWidget *w);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    void propteryChanged();
signals:
    void currentChanged(QWidget *now);
public slots:
    void focusChanged(QWidget *old, QWidget *now);
private:
    Selection *sel;
    QPoint dragPosition;   //鼠标拖动的位置
public:

    WindowPorp prop;
    typedef QHash<QString, QString> PropteryHash;
    PropteryHash m_prop;
};

#endif // FORMWINDOW_H
