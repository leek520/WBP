#ifndef PUBLICVAR_H
#define PUBLICVAR_H

#include <QObject>
#include "common.h"

#define PV (PublicVar::GetInstance())

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
signals:

public slots:

private:
    static PublicVar *m_instance;
    QMap<QString, QStringList> propertyEnum;
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
