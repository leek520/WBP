#ifndef WIDGET_H
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
#include "publicvar.h"

#define DefaultWindowWidth      800
#define DefaultWindowHeight     480
#define DefaultWidgetWidth      120
#define DefaultWidgetHeight     50

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
    Q_PROPERTY(QString TextString READ getTextString WRITE setTextString)
    Q_PROPERTY(QColor TextColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(int AlignH READ getAlignH WRITE setAlignH)
    Q_PROPERTY(int AlignV READ getAlignV WRITE setAlignV)
    Q_PROPERTY(int TextFont READ getTextFont WRITE setTextFont)
    Q_PROPERTY(int TextType READ getTextType WRITE setTextType)
    Q_PROPERTY(int TextMaxLen READ getTextMaxLen WRITE setTextMaxLen)
    Q_PROPERTY(int TextRegAddress READ getTextRegAddress WRITE setTextRegAddress)
    Q_PROPERTY(int TextTotLen READ getTextTotLen WRITE setTextTotLen)
    Q_PROPERTY(int TextDotLen READ getTextDotLen WRITE setTextDotLen)
    Q_PROPERTY(QStringList TextStringList READ getTextStringList WRITE setTextStringList)


    Q_PROPERTY(QString BkImage READ getBkImage WRITE setBkImage)
    Q_PROPERTY(QPoint ImagePos READ getImagePos WRITE setImagePos)
    Q_PROPERTY(ushort ImageCompress READ getImageCompress WRITE setImageCompress)

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

    Q_PROPERTY(ushort WriteRegAddress READ getWriteRegAddress WRITE setWriteRegAddress)
    Q_PROPERTY(ushort WriteBitAddress READ getWriteBitAddress WRITE setWriteBitAddress)
    Q_PROPERTY(ushort WriteRegType READ getWriteRegType WRITE setWriteRegType)
    Q_PROPERTY(ushort WriteValueType READ getWriteValueType WRITE setWriteValueType)
    Q_PROPERTY(int WriteValue READ getWriteValue WRITE setWriteValue)

    Q_PROPERTY(QVariant BkColor1 READ getBkColor1 WRITE setBkColor1)
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QList<QPair<QVariant::Type, QString> > getPropertyTable();
    void setPosProperty();
    void addContexMenuAction(QAction *action);
    QString getLanString(int lan);
    void setLanString(int lan, QString str);
    QStringList getLanStringList(int lan);
    void setLanStringList(int lan, QStringList list);
    void refresh();
private:
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
    void mouseButtonDblClick(Widget *w);
    void currentItemChanged(Widget *w);
    void checkContainWidget(Widget *w);
private:
    QPoint dragPosition;   //鼠标拖动的位置  
protected:
    QList<QPair<QVariant::Type, QString> > m_propTable;
    QLabel *m_CentralWidget;
    QMenu *m_ContextMenu;
public:
    static int m_curLan;
    static bool m_sim;
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

    QString getBkImage();
    void setBkImage(QString BkImage);

    ushort getImageCompress();
    void setImageCompress(ushort type);

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

    int getTextFont();
    void setTextFont(int value);

    int getTextMaxLen();
    void setTextMaxLen(int value);

    int getTextRegAddress();
    void setTextRegAddress(int value);

    int getTextTotLen();
    void setTextTotLen(int value);

    int getTextDotLen();
    void setTextDotLen(int value);

    QStringList getTextStringList();
    void setTextStringList(QStringList String);

    ushort getWriteRegAddress();
    void setWriteRegAddress(ushort value);

    ushort getWriteBitAddress();
    void setWriteBitAddress(ushort value);

    ushort getWriteRegType();
    void setWriteRegType(ushort value);

    ushort getWriteValueType();
    void setWriteValueType(ushort value);

    int getWriteValue();
    void setWriteValue(int value);

    QVariant getBkColor1();
    void virtual setBkColor1(QVariant bkColor);
protected:
    /*****属性表****/
    int m_Type;
    int m_Id;
    QColor m_BkColor;
    QString m_BkImage;
    QPoint m_ImagePos;
    ushort m_ImageCompress;
    QColor m_BkPressColor;
    QColor m_BkDisableColor;

    QList<QColor> m_BkColor1;

    int m_AlignH;
    int m_AlignV;
    QColor m_TextColor;
    int m_TextType      ;
    int m_TextFont      ;
    int m_TextMaxLen    ;
    int m_TextRegAddress;
    int m_TextTotLen    ;
    int m_TextDotLen    ;
    QStringList m_TextString;
    QList<QStringList> m_TextStringList;

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

    ushort m_WriteRegAddress;
    ushort m_WriteBitAddress;
    ushort m_WriteRegType;
    ushort m_WriteValueType;
    int m_WriteValue;
};

#endif // WIDGET_H

