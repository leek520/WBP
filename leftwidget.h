#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include "common.h"
#include "basewidget.h"
#include "formwindow.h"

#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = 0);
    void initUi();
    QSize sizeHint() const {
        return QSize(250, 200);
    }
    void addWidget(QWidget *w);
    void removeWidget(QWidget *w);
signals:
private:
    void createPropertyTree();
    void updateExpandState();
    void addProperty(QtVariantProperty *property, const QString &id);
public slots:
    void valueChanged(QtProperty *property, const QVariant &value);
    void currentItemChanged(QWidget *w);
private:
    QtTreePropertyBrowser *propertyEditor;
    QtVariantPropertyManager *variantManager;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;
    QWidget *currentItem;

    QTreeWidget *m_objectTree;
};

#endif // LEFTWIDGET_H
