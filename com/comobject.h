#ifndef COMOBJECT_H
#define COMOBJECT_H

#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QtSerialPort/QtSerialPort>

#define ERROR_OPEN      -1
#define ERROR_ADDR      -2
#define ERROR_FILE      -3
#define ERROR_FONTSIZE  -4
#define ERROR_PICTYPE0  -5
#define ERROR_PICTYPE1  -6
#define ERROR_NOFINDCHAR -7


#define DECODE_OK       -10
#define DECODE_CRP2     -11
#define CANCEL_OK       -15
#define SERIAL_SET      -16

#define RECEIVE_MSG     -20
//0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz<>():,.;!+-*=
#define FONT_CHAR_LENGTH   10+26+26+14  //10个数字，26个大写字母，26个小写字母，15个窄符号

//÷≠℃△○●℉Φ的一是...
#define FONT_HZ_LENGTH     8 + 2995   //(宽的符号和汉字)

#define CHAR32_FIRST_ADD_SDRAM 0xa0200000
#define CHAR16_FIRST_ADD_SDRAM 0xa0270000

#define CHAR_START_UNICODE    0x4e00

enum{
    FLASH_DOWNLOAD,
    FLASH_DECODE,
};


class ComDriver : public QObject
{
    Q_OBJECT
public:
    ComDriver(QObject *parent = 0);
    ComDriver(QString name, QString baud, QString parity, QString stopbit, QObject *parent = 0);
    bool OpenSerial();
    bool OpenSerial(QString name, QString baud, QString parity, QString stopbit);
    void CancelCom();
private:
    //CRC-16校验
    unsigned int CRC16Check(uchar *pchMsg, ushort wDataLen);
    unsigned int CRC16Check_CCITT(uchar *pchMsg, uint wDataLen);
    bool SendMsgDownLoad(const int cmd, const int addr, const uchar *data, const int len, const int flag=0);
    bool FetchData(uchar *data, int *len, int stat_pos);
public:
    static QString name;
    static QString baud;
    static QString parity;
    static QString databit;
    static QString stopbit;
public slots:
    void SendMsg();
    void DownLoad_slt(const int cmd, const int addr, const QByteArray data);
    void ReceiveMsg();
signals:
    void ResProgress_sig(int pos, QString msg="");
private:
    int s_cmd;
    int m_cmd;
    int m_address;
    QStringList dataStr;
    int cur_pos;
    int com_status;
    int file_byte_count;
    int send_count;
    int receive_count;
    QSerialPort *m_com;
    QByteArray m_sendData;
    QByteArray m_dataAll;
    QByteArray m_ReceiveBuf;
    QTimer *m_sendTimer;
    bool cancel;
};

#endif // COMOBJECT_H
