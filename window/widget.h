#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPair>
#include <QDate>
#include "common.h"
#include "comobject.h"

#define WigetEntry(ptr, type) \
        ((type == Window) ? (QLabel *)ptr :\
         (type == Button) ? (QLabel *)ptr :\
         (type == Text) ? (QLabel *)ptr :\
         (type == Edit) ? (QLabel *)ptr :\
         (QLabel *)ptr)

#define EnumToStr(type) \
        ((type == Window) ? QString("Window") :\
         (type == Button) ? QString("Button") :\
         (type == Text) ? QString("Text") :\
         (type == Edit) ? QString("Edit") : QString(""))

#define StrToEnum(str) \
        ((str == QString("Window")) ? Window :\
         (str == QString("Button")) ? Button :\
         (str == QString("Text")) ? Text :\
         (str == QString("Edit")) ? Edit : Edit)

#define ConvListAdd(addr, offset) ((struct list_head *)((int)addr + offset));

class Widget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int Id READ getId WRITE setId)
    Q_PROPERTY(QColor BkColor READ getBkColor WRITE setBkColor)
    Q_PROPERTY(QString String READ getString WRITE setString)
    Q_PROPERTY(QColor TextColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(int AlignH READ getAlignH WRITE setAlignH)
    Q_PROPERTY(int AlignV READ getAlignV WRITE setAlignV)

    Q_PROPERTY(QString LuaCmd READ getLuaCmd WRITE setLuaCmd)

    Q_PROPERTY(QVariant BkColor1 READ getBkColor1 WRITE setBkColor1)
public:
    explicit Widget(WidgetType type= Window, QWidget *parent = 0);
    WidgetType getType();
    QList<QPair<QVariant::Type, QString> > getPropertyTable();
private:
    void createCenterWidget();
    void createPropertyTable();

    void setTextParaProp();
    int assignId();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
signals:
    void MouseButtonDblClick(QWidget *w);
    void currentItemChanged(Widget *w);
private:
    QPoint dragPosition;   //鼠标拖动的位置
    QWidget *m_CentralWidget;

    QList<QPair<QVariant::Type, QString> > m_propTable;
public:
    int getId();
    void setId(int Id);

    QColor getBkColor();
    void setBkColor(QColor BkColor);

    QString getString();
    void setString(QString String);

    QColor getTextColor();
    void setTextColor(QColor TextColor);

    int getAlignH();
    void setAlignH(int Align);

    int getAlignV();
    void setAlignV(int Align);

    QString getLuaCmd();
    void setLuaCmd(QString LuaCmd);

    QVariant getBkColor1();
    void setBkColor1(QVariant bkColor);
private:
    static QMap<WidgetType, int> m_IdPool;
    /*****属性表****/
    WidgetType m_Type;
    int m_Id;
    QColor m_BkColor;
    QList<QColor> m_BkColor1;

    int m_AlignH;
    int m_AlignV;
    QColor m_TextColor;
    QString m_String;
    QString m_LudCmd;
};

class BuildInfo : public QObject
{
    Q_OBJECT
public:
    struct WidgetBuf{
       int pos;
       char buf[10240];
    };
    struct StringBuf{
       int pos;
       char buf[10240];
    };
    struct LuaBuf{
       int pos;
       char buf[10240];
    };
    struct PicBuf{
       int pos;
       char buf[10240];
    };
public:
    explicit BuildInfo();
    void initBuild();
    WidgetBuf *getWidgetBuf();
    uint QColorToEColor(QColor color);
    int QAlignToEAlign(int align);
    char *QStringToMultBytes(QString str);
    char *QStringToChar(QString str);

    void downLoadInfo();
private slots:
    void readCharList();
    void ResProgress_slt(int pos, QString msg="");
signals:
    void DownLoad_sig(const int cmd, const int addr, const QByteArray data);
private:
    ComDriver *com;
    QString m_charList;

    struct WidgetBuf widgetBuf;
    struct StringBuf stringBuf;
    struct LuaBuf luaBuf;
    struct PicBuf picBuf;
    int downloadStep;
};

#endif // WIDGET_H
