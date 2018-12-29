#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPair>
#include <QDate>
#include "common.h"
#include "comobject.h"

#define WidgetLen   10240
#define StringLen   10240
#define LuaLen      10240
#define ImageLen    512000  //500k
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
    Q_PROPERTY(QColor BkPressColor READ getBkPressColor WRITE setBkPressColor)
    Q_PROPERTY(QColor BkDisableColor READ getBkDisableColor WRITE setBkDisableColor)
    Q_PROPERTY(QString String READ getString WRITE setString)
    Q_PROPERTY(QColor TextColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(int AlignH READ getAlignH WRITE setAlignH)
    Q_PROPERTY(int AlignV READ getAlignV WRITE setAlignV)

    Q_PROPERTY(QString BkImage READ getBkImage WRITE setBkImage)
    Q_PROPERTY(QPoint ImagePos READ getImagePos WRITE setImagePos)

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
    void setImage();
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
    static QMap<WidgetType, int> m_IdPool;
    QString m_styleSheet;
    QLabel *m_imageW;

public:
    int getId();
    void setId(int Id);

    QColor getBkColor();
    void setBkColor(QColor BkColor);

    QString getBkImage();
    void setBkImage(QString BkImage);

    QPoint getImagePos();
    void setImagePos(QPoint pos);

    QColor getBkPressColor();
    void setBkPressColor(QColor BkColor);

    QColor getBkDisableColor();
    void setBkDisableColor(QColor BkColor);

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


    /*****属性表****/
    WidgetType m_Type;
    int m_Id;
    QColor m_BkColor;
    QString m_BkImage;
    QPoint m_ImagePos;
    QColor m_BkPressColor;
    QColor m_BkDisableColor;

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
       char buf[WidgetLen];
    };
    struct StringBuf{
       int pos;
       char buf[StringLen];
    };
    struct LuaBuf{
       int pos;
       char buf[LuaLen];
    };
    struct ImageBuf{
       int pos;
       char buf[ImageLen];
    };
public:
    explicit BuildInfo();
    void initBuild();
    WidgetBuf *getWidgetBuf();
    uint QColorToEColor(QColor color);
    int QAlignToEAlign(int align);
    char *QStringToMultBytes(QString str);
    char *QStringToChar(QString str);
    GUI_Image *QImageToEImage(QString filename, QPoint leftTop);


    void downLoadInfo();
    void cancel();
private slots:
    void readCharList();
    void ResProgress_slt(int pos, QString msg="");
signals:
    void DownLoad_sig(const int cmd, const int addr, const QByteArray data);
    void ResProgress_sig(int step, int pos, QString msg="");
private:
    ComDriver *com;
    QString m_charList;

    struct WidgetBuf widgetBuf;
    struct StringBuf stringBuf;
    struct LuaBuf luaBuf;
    struct ImageBuf imageBuf;
    int downloadStep;
};

#endif // WIDGET_H
/*
    QString EXE_PATH = QDir::currentPath() + "/BmpCvt.exe";
    int type = (m_picType->currentIndex()==0)?8:12;
    QString build_cmd = QString("start \"\" /min \"%1\" \"%2\" -saveas%3,1,%4 -exit")
            .arg(EXE_PATH)
            .arg(filename)
            .arg(outname)
            .arg(type);
    system(build_cmd.toLocal8Bit());
    qDebug()<<build_cmd;
*/
