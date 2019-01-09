#ifndef PUBLICVAR_H
#define PUBLICVAR_H

#include <QObject>
#include "common.h"

#define PV (PublicVar::GetInstance())

#define GUI_ID_WINDOW   0000  //4096个
#define GUI_ID_BUTTON   1000
#define GUI_ID_TEXT     2000
#define GUI_ID_EDIT     3000


class PublicVar : public QObject
{
    Q_OBJECT
public:
    explicit PublicVar(QObject *parent = 0);
    ~PublicVar();
    //GetInstance是获得此类实例的唯一全局访问点
    static PublicVar* GetInstance() {
        if (m_instance == NULL) {
            m_instance = new PublicVar();
        }
        return m_instance;
    }
    QStringList getEnumProperty(QString prop);
    int assignId(int type);
signals:

public slots:

private:
    static PublicVar *m_instance;
    QMap<QString, QStringList> propertyEnum;
    QMap<int, int> m_IdPool;
};

/*************加载qss文件的函数*************/
class CommonHelper
{
public:
    static void setStyle(const QString &style)
    {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};
#endif // PUBLICVAR_H
