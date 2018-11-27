#include "leftwidget.h"

LeftWidget::LeftWidget(QWidget *parent) :
    QWidget(parent)
{
    QSplitter *splitter = new QSplitter(Qt::Vertical, this); //新建主分割窗口，水平分割
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    m_objectTree = new QTreeWidget(this);
    m_objectTree->setHeaderLabel("");
    splitter->addWidget(m_objectTree);

    createPropertyTree();
    splitter->addWidget(propertyEditor);

    initUi();
}

void LeftWidget::initUi()
{

}

void LeftWidget::addWidget(QWidget *w)
{
    m_objectTree->clear();
    QWidgetList winList = EWindow::windowList();
    for(int i=0;i<winList.count();i++){
        QTreeWidgetItem* pItem = new QTreeWidgetItem();
        pItem->setText(0, winList[i]->objectName());
        m_objectTree->addTopLevelItem(pItem);
        QWidgetList childList = ((EWindow *)winList[i])->childWidgets();
        for(int j=0;j<childList.count();j++){
            QTreeWidgetItem* pChild = new QTreeWidgetItem();
            pChild->setText(0, childList[j]->objectName());
            pItem->addChild(pChild);
        }
    }
    m_objectTree->expandAll();
}

void LeftWidget::removeWidget(QWidget *w)
{

}

void LeftWidget::createPropertyTree()
{
    variantManager = new QtVariantPropertyManager(this);

    connect(variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(valueChanged(QtProperty *, const QVariant &)));
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    propertyEditor = new QtTreePropertyBrowser();
    propertyEditor->setFactoryForManager(variantManager, variantFactory);
}

void LeftWidget::updateExpandState()
{
    QList<QtBrowserItem *> list = propertyEditor->topLevelItems();
    QListIterator<QtBrowserItem *> it(list);
    while (it.hasNext()) {
        QtBrowserItem *item = it.next();
        QtProperty *prop = item->property();
        idToExpanded[propertyToId[prop]] = propertyEditor->isExpanded(item);
    }
}

void LeftWidget::valueChanged(QtProperty *property, const QVariant &value)
{
    if (!propertyToId.contains(property))
        return;

    if (!currentItem)
        return;

    QString id = propertyToId[property];
    if (id == QLatin1String("geometry")) {
        currentItem->setGeometry(value.toRect());
    }else if (id == QLatin1String("text")) {
        if (currentItem->objectName() == "Button"){
            ((EButton *)currentItem)->setText(value.toString());
        }else if (currentItem->objectName() == "Text"){
            ((EText *)currentItem)->setText(value.toString());
        }else if (currentItem->objectName() == "Edit"){
            ((EEdit *)currentItem)->setText(value.toString());
        }
    }
}

void LeftWidget::currentItemChanged(QWidget *w)
{
    qDebug()<<w;
    updateExpandState();
    //删除原有属性map
    QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
    while (itProp != propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }
    propertyToId.clear();
    idToProperty.clear();

    currentItem = w;
    if (!currentItem) {
        return;
    }

    QStringList propertyList;
    QString text;
    //根据w类型获取对应需要显示的属性列表
    if (w->objectName() == "Window"){
        propertyList = ((EWindow *)w)->m_propertyList;
    }else if (w->objectName() == "Button"){
        propertyList = ((EButton *)w)->m_propertyList;
        text = ((EButton *)w)->text();
    }else if (w->objectName() == "Text"){
        propertyList = ((EText *)w)->m_propertyList;
        text = ((EText *)w)->text();
    }else if (w->objectName() == "Edit"){
        propertyList = ((EEdit *)w)->m_propertyList;
        text = ((EEdit *)w)->text();
    }

    QtVariantProperty *property;
    //共有属性
    property = variantManager->addProperty(QVariant::Rect, tr("geometry"));
    property->setValue(w->geometry());
    addProperty(property, QLatin1String("geometry"));

    if (propertyList.contains("text")){
        property = variantManager->addProperty(QVariant::String, tr("text"));
        property->setValue(text);
        addProperty(property, QLatin1String("text"));
    }

}
void LeftWidget::addProperty(QtVariantProperty *property, const QString &id)
{
    propertyToId[property] = id;
    idToProperty[id] = property;
    QtBrowserItem *item = propertyEditor->addProperty(property);
    if (idToExpanded.contains(id))
        propertyEditor->setExpanded(item, idToExpanded[id]);
}
