#include "propertywidget.h"
PropertyWidget::PropertyWidget(QWidget *parent) : QWidget(parent)
{
    setLayout(new QVBoxLayout(this));
    variantManager = new QtVariantPropertyManager(this);
    connect(variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(valueChanged(QtProperty *, const QVariant &)));
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    propertyEditor = new QtTreePropertyBrowser();
    propertyEditor->setFactoryForManager(variantManager, variantFactory);
    layout()->addWidget(propertyEditor);
}

void PropertyWidget::currentItemChanged(Widget *w)
{
    updateExpandState();
    //删除原有属性map
    QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
    while (itProp != propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }
    propertyToId.clear();
    idToProperty.clear();

    m_curW = w;
    if (!m_curW) {
        return;
    }

    QtVariantProperty *property;
    QList<QPair<QVariant::Type, QString> > propTable = w->getPropertyTable();
    for(int i=0;i<propTable.count();i++){
        QVariant value = w->property(propTable[i].second.toLocal8Bit());
        switch (propTable[i].first) {
        case QVariant::TextFormat:
        {
            if (propTable[i].second == QString("TextMaxLen")){
                continue;
            }else{
                property = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), propTable[i].second);
                QStringList enumNames = PV->getEnumProperty(propTable[i].second);
                property->setAttribute(QLatin1String("enumNames"), enumNames);
                property->setValue(value);
                break;
            }
        }
        case QVariant::Line:
        {
            property = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), propTable[i].second);
            QStringList enumNames;
            if (propTable[i].second == "LineType"){
                enumNames << "Horizontal" << "Vertical";
                property->setAttribute(QLatin1String("enumNames"), enumNames);
                property->setValue(value);
            }
            break;
        }
        default:
            property = variantManager->addProperty(propTable[i].first, propTable[i].second);
            property->setValue(value);
            break;
        }
        addProperty(property, propTable[i].second);
    }
}

void PropertyWidget::updateExpandState()
{
    QList<QtBrowserItem *> list = propertyEditor->topLevelItems();
    QListIterator<QtBrowserItem *> it(list);
    while (it.hasNext()) {
        QtBrowserItem *item = it.next();
        QtProperty *prop = item->property();
        idToExpanded[propertyToId[prop]] = propertyEditor->isExpanded(item);
    }
}
void PropertyWidget::addProperty(QtVariantProperty *property, const QString &id)
{
    propertyToId[property] = id;
    idToProperty[id] = property;
    QtBrowserItem *item = propertyEditor->addProperty(property);
    if (idToExpanded.contains(id)){
        propertyEditor->setExpanded(item, idToExpanded[id]);
    }else{
//        idToExpanded[id] = false;
//        propertyEditor->setExpanded(item, idToExpanded[id]);
    }
}
void PropertyWidget::valueChanged(QtProperty *property, const QVariant &value)
{
    QVariant pvalue = value;
    if (!propertyToId.contains(property))
        return;

    if (!m_curW)
        return;

    QString id = propertyToId[property];
    m_curW->setProperty(id.toLocal8Bit(), pvalue);
}
