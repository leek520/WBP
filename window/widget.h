﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPair>
#include <QDate>
#include <QRectF>
#include <QAction>
#include <QMessageBox>
#include "common.h"
#include "comobject.h"

#define WindowWidth     800
#define WindowHeight    480
#define WidgetWidth     120
#define WidgetHeight    50

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
         (type == Edit) ? QString("Edit") : \
         (type == Image) ? QString("Image") : \
         (type == Line) ? QString("Line") : \
         (type == Rect) ? QString("Rect") : \
         (type == Circle) ? QString("Circle") : QString("Unkown"))

#define StrToEnum(str) \
        ((str.toLower() == QString("Window").toLower()) ? Window :\
         (str.toLower() == QString("Button").toLower()) ? Button :\
         (str.toLower() == QString("Text").toLower()) ? Text :\
         (str.toLower() == QString("Edit").toLower()) ? Edit : \
         (str.toLower() == QString("Image").toLower()) ? Image : \
         (str.toLower() == QString("Line").toLower()) ? Line : \
         (str.toLower() == QString("Rect").toLower()) ? Rect : \
         (str.toLower() == QString("Circle").toLower()) ? Circle : Text)

#define ConvListAdd(addr, offset) ((struct list_head *)((int)addr + offset));

class Widget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int Id READ getId WRITE setId)
    Q_PROPERTY(int Type READ getType WRITE setType)
    Q_PROPERTY(QColor BkColor READ getBkColor WRITE setBkColor)
    Q_PROPERTY(QColor BkPressColor READ getBkPressColor WRITE setBkPressColor)
    Q_PROPERTY(QColor BkDisableColor READ getBkDisableColor WRITE setBkDisableColor)
    Q_PROPERTY(QString String READ getTextString WRITE setTextString)
    Q_PROPERTY(QColor TextColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(int AlignH READ getAlignH WRITE setAlignH)
    Q_PROPERTY(int AlignV READ getAlignV WRITE setAlignV)
    Q_PROPERTY(int TextType READ getTextType WRITE setTextType)
    Q_PROPERTY(int TextMaxLen READ getTextMaxLen WRITE setTextMaxLen)
    Q_PROPERTY(int TextRegAddress READ getTextRegAddress WRITE setTextRegAddress)
    Q_PROPERTY(int TextDotBef READ getTextDotBef WRITE setTextDotBef)
    Q_PROPERTY(int TextDotAft READ getTextDotAft WRITE setTextDotAft)
    Q_PROPERTY(QStringList TextStringList READ getTextStringList WRITE setTextStringList)


    Q_PROPERTY(QString BkImage READ getBkImage WRITE setBkImage)
    Q_PROPERTY(QPoint ImagePos READ getImagePos WRITE setImagePos)

    Q_PROPERTY(int LineType READ getLineType WRITE setLineType)
    Q_PROPERTY(QPoint LineStart READ getLineStart WRITE setLineStart)
    Q_PROPERTY(int LineLength READ getLineLength WRITE setLineLength)

    Q_PROPERTY(int LineWidth READ getLineWidth WRITE setLineWidth)
    Q_PROPERTY(QRectF Rectangle READ getRectangle WRITE setRectangle)
    Q_PROPERTY(QPoint Center READ getCenter WRITE setCenter)
    Q_PROPERTY(int Radius READ getRadius WRITE setRadius)
    Q_PROPERTY(bool FillEnable READ getFillEnable WRITE setFillEnable)
    Q_PROPERTY(QColor FillColor READ getFillColor WRITE setFillColor)
    Q_PROPERTY(QColor LineColor READ getLineColor WRITE setLineColor)

    Q_PROPERTY(QString LuaCmd READ getLuaCmd WRITE setLuaCmd)

    Q_PROPERTY(QVariant BkColor1 READ getBkColor1 WRITE setBkColor1)
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QList<QPair<QVariant::Type, QString> > getPropertyTable();
    void setPosProperty();
    void addContexMenuAction(QAction *action);
private:
    int assignId();

    void setImage();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void virtual paintEvent(QPaintEvent *event);
    void virtual initPropertyTable();
    void virtual initCenterWidget();
    void virtual initParament();
    void virtual createContexMenu();
signals:
    void MouseButtonDblClick(Widget *w);
    void currentItemChanged(Widget *w);

private:
    QPoint dragPosition;   //鼠标拖动的位置
    static QMap<int, int> m_IdPool;
protected:
    QList<QPair<QVariant::Type, QString> > m_propTable;
    QLabel *m_CentralWidget;
    QMenu *m_ContextMenu;

public:
    int getId();
    void setId(int Id);

    int getType();
    void setType(int Type);  

    int getLineType();
    void setLineType(int type);

    QPoint getLineStart();
    void setLineStart(QPoint pos);

    int getLineLength();
    void setLineLength(int length);

    QRectF getRectangle();
    void setRectangle(QRectF rect);

    QPoint getCenter();
    void setCenter(QPoint center);

    int getRadius();
    void virtual setRadius(int radius);

    QColor getFillColor();
    void setFillColor(QColor Color);

    QColor getLineColor();
    void setLineColor(QColor Color);

    int getLineWidth();
    void setLineWidth(int width);

    bool getFillEnable();
    void setFillEnable(bool enable);

    QString getLuaCmd();
    void setLuaCmd(QString LuaCmd);

    QString getBkImage();
    void setBkImage(QString BkImage);

    QPoint getImagePos();
    void setImagePos(QPoint pos);

    QColor getBkColor();
    void setBkColor(QColor BkColor);

    QColor getBkPressColor();
    void setBkPressColor(QColor BkColor);

    QColor getBkDisableColor();
    void setBkDisableColor(QColor BkColor);

    QString getTextString();
    void setTextString(QString String);

    QColor getTextColor();
    void setTextColor(QColor TextColor);

    int getAlignH();
    void setAlignH(int Align);

    int getAlignV();
    void setAlignV(int Align);

    int getTextType();
    void setTextType(int value);

    int getTextMaxLen();
    void setTextMaxLen(int value);

    int getTextRegAddress();
    void setTextRegAddress(int value);

    int getTextDotBef();
    void setTextDotBef(int value);

    int getTextDotAft();
    void setTextDotAft(int value);

    QStringList getTextStringList();
    void setTextStringList(QStringList String);

    QVariant getBkColor1();
    void virtual setBkColor1(QVariant bkColor);
protected:
    /*****属性表****/
    int m_Type;
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
    int m_TextType      ;
    int m_TextMaxLen    ;
    int m_TextRegAddress;
    int m_TextDotBef    ;
    int m_TextDotAft    ;
    QString m_TextString;
    QStringList m_TextStringList;

    QString m_LudCmd;

    int m_LineType;
    QPoint m_LineStart;
    int m_LineLength;
    QPoint m_Center;
    QRectF m_Rectangle;
    int m_Radius;
    QColor m_FillColor;
    bool m_FillEnable;
    int m_LineWidth;
    QColor m_LineColor;
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
    char *QStringListToMultBytes(QStringList strList, int maxLen);
    char *QStringToLuaChar(QString str);
    void QImageToEImage(QString filename, QPoint leftTop, ImageInfo *imageinfo);
    void GraphToEgraph(Widget *w, GraphInfo *graphinfo);

    void downLoadInfo();
    void cancel();
private slots:
    void readCharList();
    void ResProgress_slt(int pos, QString msg="");
    void writeBufToTxt();
    void writeBufToTxt(QTextStream &out, char *buf, int len);
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
