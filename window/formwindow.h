#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include "widget.h"
#include "widgetselection.h"
#include "buttonwidget.h"
#include "editwidget.h"
#include "textwidget.h"
#include "imagewidget.h"
#include "scrollarea.h"
class WindowWidget : public Widget
{
    Q_OBJECT
public:
    explicit WindowWidget(QWidget *parent = 0);
    void addWidget(QWidget *w);
    void removeWidget(QWidget *w);
    static void refreshAll();
    QWidgetList getChildList(int type=0);
    static QList<WindowWidget *> getWindowList();
signals:
    void removeWidgetSgn(Widget *w);
    void addWidgetSgn(WidgetType type, QPoint pos);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    void initPropertyTable();
    void initParament();
public slots:
    void propertyChanged(QWidget *w);
private:
    void setCurrent(QWidget *w);
    void setWidgetProperty(QWidget *w);
    void resetCurrentWidget();
private slots:
    void focusChanged(QWidget *old, QWidget *now);

private:
    int m_dragMode;
    QWidgetList m_childList;
    QWidgetList m_graphList;
    QWidgetList m_imageList;
    static QList<WindowWidget *> m_windowList;
public:
    static WindowWidget *m_curWin;
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
