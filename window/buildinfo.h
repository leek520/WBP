#ifndef BUILDINFO_H
#define BUILDINFO_H

#include <QObject>
#include "widget.h"

#define WidgetLen   10240
#define StringLen   10240
#define LuaLen      10240
#define CharLen     10240
#define FontLen      512000
#define ImageLen    512000  //500k

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
    struct FontBuf{
       int pos;
       char buf[FontLen];
    };
    struct CharBuf{
       int pos;
       char buf[CharLen];
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

    int GetFontHeadAddress(int index);
    void FontToChar(int fontSize);
    void RecordChar(QString &string);
    static bool compareUnicode(QChar &a, QChar &b);
    void SortRecordChar();
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
    QString m_CharRecord;
    QMap<int, int> m_fontList;

    struct WidgetBuf widgetBuf;
    struct StringBuf stringBuf;
    struct LuaBuf luaBuf;
    struct FontBuf fontBuf;
    struct CharBuf charBuf;
    struct ImageBuf imageBuf;
    int downloadStep;
};

#endif // BUILDINFO_H
