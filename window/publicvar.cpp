#include "publicvar.h"
PublicVar *PublicVar::m_instance = NULL;
static QMap<int, int> m_IdPool;
PublicVar::PublicVar(QObject *parent) : QObject(parent)
{

}

PublicVar::~PublicVar()
{
    delete propertyEnum;
    delete m_instance;
}
void PublicVar::setEnumProperty(QMap<QString, QStringList> *enumMap)
{
    propertyEnum = enumMap;
}

QStringList PublicVar::getEnumProperty(QString prop)
{
    return propertyEnum->value(prop);
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
