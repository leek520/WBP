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
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);
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
    QPalette palette(currentItem->palette());
    if (id == QLatin1String("geometry")) {
        currentItem->setGeometry(value.toRect());
    }else if (id == QLatin1String("backColor")) {
        if (currentItem->objectName() == "Window"){
            palette.setColor(QPalette::Window, value.value<QColor>());
            ((EWindow *)currentItem)->setPalette(palette);
        }else if (currentItem->objectName() == "Button"){
//            palette.setColor(QPalette::Active, QPalette::Button, value.value<QColor>());
//            ((EButton *)currentItem)->setPalette(palette);
            qDebug()<<QString::number(value.value<QColor>().rgba(), 16);
            currentItem->setStyleSheet(QString("background-color: #%1;")
                                       .arg(QString::number(value.value<QColor>().rgba(), 16)));
        }else if (currentItem->objectName() == "Text"){
            palette.setColor(QPalette::Window, value.value<QColor>());
            ((EText *)currentItem)->setPalette(palette);
        }else if (currentItem->objectName() == "Edit"){
            palette.setColor(QPalette::Base, value.value<QColor>());
            ((EEdit *)currentItem)->setPalette(palette);
        }
        currentItem->setAutoFillBackground(true);   //一定要有这句话，不然不更新窗口颜色
    }else if (id == QLatin1String("text")) {
        if (currentItem->objectName() == "Button"){
            ((EButton *)currentItem)->setText(value.toString());
        }else if (currentItem->objectName() == "Text"){
            ((EText *)currentItem)->setText(value.toString());
        }else if (currentItem->objectName() == "Edit"){
            ((EEdit *)currentItem)->setText(value.toString());
        }
    }else if (id == QLatin1String("textColor")) {
        if (currentItem->objectName() == "Button"){
            palette.setColor(QPalette::ButtonText, value.value<QColor>());
            ((EButton *)currentItem)->setPalette(palette);
        }else if (currentItem->objectName() == "Text"){
            palette.setColor(QPalette::WindowText, value.value<QColor>());
            ((EText *)currentItem)->setPalette(palette);
        }else if (currentItem->objectName() == "Edit"){
            palette.setColor(QPalette::Text, value.value<QColor>());
            ((EEdit *)currentItem)->setPalette(palette);
        }
    }else if ((id == QLatin1String("Horizontal")) || (id == QLatin1String("Vertical"))) {

        int hA = idToProperty[QLatin1String("Horizontal")]->value().toInt();
        int vA = idToProperty[QLatin1String("Vertical")]->value().toInt();
        Qt::Alignment align = Qt::Alignment((1<<hA) | (1<<(vA+5)));
        qDebug()<<hA<<vA<<align;
        if (currentItem->objectName() == "Text"){
            ((EText *)currentItem)->setAlignment(align);
        }else if (currentItem->objectName() == "Edit"){
            ((EEdit *)currentItem)->setAlignment(align);
        }
    }else if (id == QLatin1String("maxLen")){
        ((EEdit *)currentItem)->maxLen = value.toInt();
    }
}

void LeftWidget::currentItemChanged(QWidget *w)
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

    currentItem = w;
    if (!currentItem) {
        return;
    }

    QStringList propertyList;
    QString text;
    QColor color, textColor;
    //根据w类型获取对应需要显示的属性列表
    if (w->objectName() == "Window"){
        propertyList = ((EWindow *)w)->m_propertyList;
        color = ((EWindow *)w)->palette().color(QPalette::Window);
    }else if (w->objectName() == "Button"){
        propertyList = ((EButton *)w)->m_propertyList;
        text = ((EButton *)w)->text();
        color = ((EButton *)w)->palette().color(QPalette::Button);
        textColor = ((EButton *)w)->palette().color(QPalette::ButtonText);
    }else if (w->objectName() == "Text"){
        propertyList = ((EText *)w)->m_propertyList;
        text = ((EText *)w)->text();
        color = ((EText *)w)->palette().color(QPalette::Window);
        textColor = ((EText *)w)->palette().color(QPalette::WindowText);
    }else if (w->objectName() == "Edit"){
        propertyList = ((EEdit *)w)->m_propertyList;
        text = ((EEdit *)w)->text();
        color = ((EEdit *)w)->palette().color(QPalette::Base);
        textColor = ((EEdit *)w)->palette().color(QPalette::Text);
    }

    QtVariantProperty *property;
    //共有属性
    property = variantManager->addProperty(QVariant::Rect, tr("geometry"));
    property->setValue(w->geometry());
    addProperty(property, QLatin1String("geometry"));

    if (propertyList.contains("backColor")){
        property = variantManager->addProperty(QVariant::Color, tr("backColor"));
        property->setValue(color);
        addProperty(property, QLatin1String("backColor"));
    }

    if (propertyList.contains("maxLen")){
        property = variantManager->addProperty(QVariant::Int, tr("maxLen"));
        property->setAttribute(QLatin1String("minimum"), 0);
        property->setValue(((EEdit *)w)->maxLen);
        addProperty(property, QLatin1String("maxLen"));
    }
    if (propertyList.contains("text")){
        property = variantManager->addProperty(QVariant::String, tr("text"));
        property->setValue(text);
        addProperty(property, QLatin1String("text"));

        property = variantManager->addProperty(QVariant::Color, tr("textColor"));
        property->setValue(textColor);
        addProperty(property, QLatin1String("textColor"));

    }
    if (propertyList.contains("alignment")){
        QtVariantProperty *Gproperty = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), tr("alignment"));

        property = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), tr("Horizontal"));
        QStringList enumNames1;
        enumNames1 << "AlignLeft"  << "AlignRight" << "AlignHCenter";
        property->setAttribute(QLatin1String("enumNames"), enumNames1);
        property->setValue(0);
        addProperty(property, QLatin1String("Horizontal"));
        Gproperty->addSubProperty(property);

        property = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), tr("Vertical"));
        QStringList enumNames2;
        enumNames2 << "AlignTop" << "AlignBottom" << "AlignVCenter";
        property->setAttribute(QLatin1String("enumNames"), enumNames2);
        property->setValue(2);
        addProperty(property, QLatin1String("Vertical"));
        Gproperty->addSubProperty(property);

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


