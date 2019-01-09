#include "publicvar.h"
PublicVar *PublicVar::m_instance = NULL;
static QMap<int, int> m_IdPool;
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

int PublicVar::assignId(int type)
{
    if (!m_IdPool.contains(type)){
        m_IdPool.insert(type, 0);
    }
    int id = m_IdPool.value(type);
    m_IdPool[type] = id + 1;
    switch (type) {
    case Window:
        id += GUI_ID_WINDOW;
        break;
    case Button:
        id += GUI_ID_BUTTON;
        break;
    case Text:
        id += GUI_ID_TEXT;
        break;
    case Edit:
        id += GUI_ID_EDIT;
        break;
    default:
        id = 0;
        break;
    }
    return id;
}
