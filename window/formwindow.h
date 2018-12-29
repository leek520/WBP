#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include "widget.h"
#include "widgetselection.h"

class FormWindow : public Widget
{
    Q_OBJECT
public:
    explicit FormWindow(QWidget *parent = 0);
    void addWidget(QWidget *w);
    void removeWidget(QWidget *w);
    QWidgetList getChildList();
    static QList<FormWindow *> getWindowList();
signals:

public slots:
    void propertyChanged(QWidget *w);
private:
    void setCurrent(QWidget *w);
private slots:
    void focusChanged(QWidget *old, QWidget *now);

private:
    QWidgetList m_childList;
    static QList<FormWindow *> m_windowList;
public:
    static FormWindow *m_curWin;
};


class ProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressBar(QWidget *parent = 0);
    void setMaxStep(int max);
    void setValue(int step, int pos);
public slots:
    void cancel_slt();
signals:
    void cancel_sig(int step, int pos);
private:
    QProgressBar *m_progress;
    QLabel *m_progresstext;
    int m_maxStep;
};

#endif // FORMWINDOW_H
