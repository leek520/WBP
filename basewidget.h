#ifndef EPUSHBUTTON_H
#define EPUSHBUTTON_H
#include "common.h"

class EButton : public QPushButton
{
    Q_OBJECT
public:
    EButton(QWidget *parent=0);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void currentItemChanged(QWidget *now);
public:
    QStringList m_propertyList;
private:
    QPoint dragPosition;   //鼠标拖动的位置
};
class EText : public QLabel
{
    Q_OBJECT
public:
    EText(QWidget *parent=0);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void currentItemChanged(QWidget *now);
public:
    QStringList m_propertyList;
private:
    QPoint dragPosition;   //鼠标拖动的位置
};
class EEdit : public QLineEdit
{
    Q_OBJECT
public:
    EEdit(QWidget *parent=0);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void currentItemChanged(QWidget *now);
public:
    int maxLen;
    QStringList m_propertyList;
private:
    QPoint dragPosition;   //鼠标拖动的位置
};
#endif // EPUSHBUTTON_H
