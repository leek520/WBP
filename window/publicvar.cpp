#include "publicvar.h"
PublicVar *PublicVar::m_instance = NULL;
PublicVar::PublicVar(QObject *parent) : QObject(parent)
{
    QFile file(":/propertyEnumList");
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QDomDocument doc;
    doc.setContent(&file,true);
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode Node = root.firstChild();
    while (!Node.isNull())
    {
        QDomElement wDom = Node.toElement();
        QString type = wDom.tagName();
        propertyEnum.insert(type, QStringList());

        QDomNode childNode = Node.firstChild();
        while (!childNode.isNull())
        {
            QDomElement childDom = childNode.toElement();
            QString value = childDom.attribute("value");
            propertyEnum[type].append(value);

            childNode = childNode.nextSibling();
        }
        Node = Node.nextSibling();
    }
}

PublicVar::~PublicVar()
{
    delete m_instance;
}
QStringList PublicVar::getEnumProperty(QString prop)
{
    return propertyEnum.value(prop);
}

