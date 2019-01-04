#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "common.h"
#include "widget.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(QWidget *parent = 0);
    QSize sizeHint() const {
        return QSize(250, 200);
    }
    void setEnumProperty(QMap<QString, QStringList> *enumMap);
private:
    void updateExpandState();
    void addProperty(QtVariantProperty *property, const QString &id);
signals:

public slots:
    void currentItemChanged(Widget *w);
    void valueChanged(QtProperty *property, const QVariant &value);
private:
    QMap<QString, QStringList> *propertyEnum;
    QtTreePropertyBrowser *propertyEditor;
    QtVariantPropertyManager *variantManager;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;

    Widget *m_curW;
};

#endif // PROPERTYWIDGET_H
