#include "comobject.h"


const unsigned char gCrcHigh[256]=
{
    0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X01, 0XC0,
    0X80, 0X41, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41,
    0X00, 0XC1, 0X81, 0X40, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0,
    0X80, 0X41, 0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1, 0X81, 0X40,
    0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1,
    0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X01, 0XC0, 0X80, 0X41,
    0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1,
    0X81, 0X40, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41,
    0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X01, 0XC0,
    0X80, 0X41, 0X00, 0XC1, 0X81, 0X40, 0X00, 0XC1, 0X81, 0X40,
    0X01, 0XC0, 0X80, 0X41, 0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1,
    0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1, 0X81, 0X40,
    0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X01, 0XC0,
    0X80, 0X41, 0X00, 0XC1, 0X81, 0X40, 0X00, 0XC1, 0X81, 0X40,
    0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0,
    0X80, 0X41, 0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1, 0X81, 0X40,
    0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X01, 0XC0,
    0X80, 0X41, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41,
    0X00, 0XC1, 0X81, 0X40, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0,
    0X80, 0X41, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41,
    0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0,
    0X80, 0X41, 0X00, 0XC1, 0X81, 0X40, 0X00, 0XC1, 0X81, 0X40,
    0X01, 0XC0, 0X80, 0X41, 0X01, 0XC0, 0X80, 0X41, 0X00, 0XC1,
    0X81, 0X40, 0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41,
    0X00, 0XC1, 0X81, 0X40, 0X01, 0XC0, 0X80, 0X41, 0X01, 0XC0,
    0X80, 0X41, 0X00, 0XC1, 0X81, 0X40
};

const unsigned char gCrcLow[256]=
{
    0X00, 0XC0, 0XC1, 0X01, 0XC3, 0X03, 0X02, 0XC2, 0XC6, 0X06,
    0X07, 0XC7, 0X05, 0XC5, 0XC4, 0X04, 0XCC, 0X0C, 0X0D, 0XCD,
    0X0F, 0XCF, 0XCE, 0X0E, 0X0A, 0XCA, 0XCB, 0X0B, 0XC9, 0X09,
    0X08, 0XC8, 0XD8, 0X18, 0X19, 0XD9, 0X1B, 0XDB, 0XDA, 0X1A,
    0X1E, 0XDE, 0XDF, 0X1F, 0XDD, 0X1D, 0X1C, 0XDC, 0X14, 0XD4,
    0XD5, 0X15, 0XD7, 0X17, 0X16, 0XD6, 0XD2, 0X12, 0X13, 0XD3,
    0X11, 0XD1, 0XD0, 0X10, 0XF0, 0X30, 0X31, 0XF1, 0X33, 0XF3,
    0XF2, 0X32, 0X36, 0XF6, 0XF7, 0X37, 0XF5, 0X35, 0X34, 0XF4,
    0X3C, 0XFC, 0XFD, 0X3D, 0XFF, 0X3F, 0X3E, 0XFE, 0XFA, 0X3A,
    0X3B, 0XFB, 0X39, 0XF9, 0XF8, 0X38, 0X28, 0XE8, 0XE9, 0X29,
    0XEB, 0X2B, 0X2A, 0XEA, 0XEE, 0X2E, 0X2F, 0XEF, 0X2D, 0XED,
    0XEC, 0X2C, 0XE4, 0X24, 0X25, 0XE5, 0X27, 0XE7, 0XE6, 0X26,
    0X22, 0XE2, 0XE3, 0X23, 0XE1, 0X21, 0X20, 0XE0, 0XA0, 0X60,
    0X61, 0XA1, 0X63, 0XA3, 0XA2, 0X62, 0X66, 0XA6, 0XA7, 0X67,
    0XA5, 0X65, 0X64, 0XA4, 0X6C, 0XAC, 0XAD, 0X6D, 0XAF, 0X6F,
    0X6E, 0XAE, 0XAA, 0X6A, 0X6B, 0XAB, 0X69, 0XA9, 0XA8, 0X68,
    0X78, 0XB8, 0XB9, 0X79, 0XBB, 0X7B, 0X7A, 0XBA, 0XBE, 0X7E,
    0X7F, 0XBF, 0X7D, 0XBD, 0XBC, 0X7C, 0XB4, 0X74, 0X75, 0XB5,
    0X77, 0XB7, 0XB6, 0X76, 0X72, 0XB2, 0XB3, 0X73, 0XB1, 0X71,
    0X70, 0XB0, 0X50, 0X90, 0X91, 0X51, 0X93, 0X53, 0X52, 0X92,
    0X96, 0X56, 0X57, 0X97, 0X55, 0X95, 0X94, 0X54, 0X9C, 0X5C,
    0X5D, 0X9D, 0X5F, 0X9F, 0X9E, 0X5E, 0X5A, 0X9A, 0X9B, 0X5B,
    0X99, 0X59, 0X58, 0X98, 0X88, 0X48, 0X49, 0X89, 0X4B, 0X8B,
    0X8A, 0X4A, 0X4E, 0X8E, 0X8F, 0X4F, 0X8D, 0X4D, 0X4C, 0X8C,
    0X44, 0X84, 0X85, 0X45, 0X87, 0X47, 0X46, 0X86, 0X82, 0X42,
    0X43, 0X83, 0X41, 0X81, 0X80, 0X40
};



ComDriver::ComDriver(QString name, QString baud, QString parity, QString stopbit, QObject *parent) :
    QObject(parent)
{

    //打开窗口
    m_com = new QSerialPort();
    SetSerialPara(name, baud, parity, stopbit);
    connect(m_com,SIGNAL(readyRead()),this,SLOT(ReceiveMsg()));
    qDebug()<<"SerialPort is open";


    m_sendTimer = new QTimer(this);
    connect(m_sendTimer, SIGNAL(timeout()), this, SLOT(SendMsg()));
}

void ComDriver::SetSerialPara(QString name, QString baud, QString parity, QString stopbit)
{
    if (m_com->isOpen()){
        m_com->close();
    }
    m_com->setPortName(name);
    if (!m_com->open(QIODevice::ReadWrite)){
        return;
    }
    if (baud == "9600")
        m_com->setBaudRate(QSerialPort::Baud9600);
    else
        m_com->setBaudRate(QSerialPort::Baud115200);
    m_com->setDataBits(QSerialPort::Data8);
    if (parity == "None")
        m_com->setParity(QSerialPort::NoParity);
    else if (parity == "Even")
        m_com->setParity(QSerialPort::EvenParity);
    else if (parity == "Odd")
        m_com->setParity(QSerialPort::OddParity);
    if (stopbit == "1")
        m_com->setStopBits(QSerialPort::OneStop);
    else if (stopbit == "1.5")
        m_com->setStopBits(QSerialPort::OneAndHalfStop);
    else if (stopbit == "2")
        m_com->setStopBits(QSerialPort::TwoStop);

    m_com->setFlowControl(QSerialPort::NoFlowControl);

    qDebug()<<"parity:"<<m_com->parity();
}
/**
* 函数说明：CRC校验
*
* @param:需要校验的数据，长度
*
* @return:校验码
**/
unsigned int ComDriver::CRC16Check(uchar *pchMsg, ushort wDataLen)
{
    unsigned int aTemp,   aNum;

    uchar gCrcH = 0xff;
    uchar gCrcL = 0xff;
    for (aNum=0; aNum<wDataLen;aNum++)
    {
       aTemp =  gCrcH ^ pchMsg[aNum];
       gCrcH = gCrcL ^ gCrcHigh[aTemp];
       gCrcL = gCrcLow[aTemp];
    }
    return (gCrcH<<8)|gCrcL;
}
/**
* 函数说明：CRC校验
*
* @param:需要校验的数据，长度
*
* @return:校验码
**/
unsigned int ComDriver::CRC16Check_CCITT(uchar *pchMsg, uint wDataLen)
{
    /*这里注意len一定要定义为uint，要不然长度不够*/
    int crc = 0xFFFF;
    for (uint j = 0; j < wDataLen; j++) {
        crc = ((crc >> 8) | (crc << 8)) & 0xffff;
        crc ^= (pchMsg[j] & 0xff);// byte to int, trunc sign
        crc ^= ((crc & 0xff) >> 4);
        crc ^= (crc << 12) & 0xffff;
        crc ^= ((crc & 0xFF) << 5) & 0xffff;
    }
    crc &= 0xffff;
    return crc;

}
bool ComDriver::SendMsgDownLoad(const int cmd, const int addr, const uchar *data, const int len, const int flag)
{
    int i=0, send_len=0, data_len=0;
    QByteArray send_buf;
    send_buf.resize(len+6);
    send_buf[0] = 0x01;
    send_buf[1] = 0xa0;
    send_buf[2] = cmd;
    send_buf[3] = (addr >> 16) & 0xff;
    send_buf[4] = (addr >> 8) & 0xff;
    send_buf[5] = (addr >> 0) & 0xff;
    if (data != NULL && flag == 0){
        data_len = 256;
    }else{
        data_len = len;
    }

    for(i=0;i<data_len;i++) {
        send_buf[i+6] = data[i];
    }
    //添加CRC
    unsigned short CRC = CRC16Check((unsigned char *)send_buf.data(), send_buf.count());

    send_buf.append((CRC >> 8) & 0xff);
    send_buf.append((CRC >> 0) & 0xff);

    send_len = m_com->write(send_buf);
    if (send_len>0){
        send_count += send_len;
        cur_pos = cur_pos + send_len - 6 - 2;
        for(i=0;i<data_len;i++) {
            m_dataAll.append(data[i]);
        }
        qDebug()<<"Send success!";
        return true;
    }else{
        qDebug()<<"Send failed!";
        return false;
    }

}

bool ComDriver::FetchData(uchar *data, int *len, int start_pos)
{
    int value = 0;
    bool ok = false;
    int i = 0, pos = 0;
    //判断是否已经取完txt数据
    if (start_pos >= file_byte_count){
        return false;
    }
    while (1){  
        pos = start_pos + i;
        if (pos >= m_sendData.count())
            break;
        data[i++] = m_sendData[pos];
        if (i>=256)
            break;
    }
    *len = i;
    if (i > 256){
        qDebug()<<"123";
    }
    return true;
}

void ComDriver::SendMsg()
{
    s_cmd = 0x5d;
    SendMsgDownLoad(s_cmd, m_address, NULL, 0);

}



void ComDriver::DownLoad_slt(const int cmd, const int addr, const QByteArray data)
{
    //清理历史变量
    cur_pos = 0;
    send_count = 0;
    receive_count = 0;
    dataStr = QStringList();
    m_dataAll.clear();

    //检查串口是否打开
    if (!m_com->isOpen()){

    }

    //定位
    m_cmd = cmd;
    m_address = addr;
    m_sendData = data;
    file_byte_count = m_sendData.count();
    SendMsg();
    m_sendTimer->start(500);
}

void ComDriver::ReceiveMsg()
{
    m_sendTimer->stop();
    //1、读取并处理串口缓冲区数据
    bool status = false;
    uchar data[512];

    int len = 0;
    bool f_status = false;

    QByteArray seial_buff = m_com->readAll();
    if(!seial_buff.isEmpty())
    {
        //这里一定要做包的完整性校验，否则会因为硬件差异，一个包分两次传输
        m_ReceiveBuf.append(seial_buff);

        int r_cnt = m_ReceiveBuf.count();
        qDebug()<<"Recive:"<<m_ReceiveBuf.toHex().data();
        if (r_cnt < 8){
            return;
        }
        //CRC校验，如果不通过----
        receive_count += 8;
        unsigned char r_cmd = (unsigned char)m_ReceiveBuf[1];
        //删除本次处理完的包
        m_ReceiveBuf.remove(0, 8);

        switch (r_cmd) {
        case 0x18:
            qDebug()<<"CRC error!";
            break;
        case 0x19:
            status = true;
            qDebug()<<"Store error!";
            break;
        case 0x20:
            qDebug()<<"Length error!";
            break;
        case 0x21:
            qDebug()<<"CRC Length error!";
            break;
        case 0x22:
            qDebug()<<"Address error!";
            break;
        case 0xa0:
            status = true;
            qDebug()<<"Receive sucess!";
            break;
        default:

            qDebug()<<r_cmd<<"Noknow error!";
            break;
        }

        switch (s_cmd) {
        case 0x5d:  //定位
            if (status){
                qDebug()<<"Set start address success!";
                if (m_cmd == 0x0){  //如果输入的擦除大小为0，则直接跳过擦除
                    s_cmd = 0x5b;
                    SendMsgDownLoad(s_cmd, m_address, NULL, 0);
                }else{
                    s_cmd = m_cmd;
                    SendMsgDownLoad(s_cmd, m_address, NULL, 0);
                }

            }else{
                m_sendTimer->start(500);
                s_cmd = 0x5d;
                SendMsgDownLoad(s_cmd, m_address, NULL, 0);
            }
            break;
        case 0x57:      //4k
        case 0x58:      //8k
        case 0x59:      //16k
        case 0x5c:      //20k
        case 0x5a:      //1M
        case 0x5f:      //252k
            if (status){
                qDebug()<<"Erase success!";
                f_status = FetchData(data, &len, cur_pos);
                if (!f_status){
                    return;
                }
                if (s_cmd == 0) return;
                s_cmd = 0x5b;
                SendMsgDownLoad(s_cmd, m_address, data, len);
            }else{
                s_cmd = 0x5d;   //如果擦除失败，则重新定位擦除
                SendMsgDownLoad(s_cmd, m_address, NULL, 0);
            }

            break;
        case 0x5b:
            if (status){
                int percent = (cur_pos*100)/file_byte_count;
                emit ResProgress_sig(percent);

                qDebug()<<cur_pos<<"Down part success!";
                f_status = FetchData(data, &len, cur_pos);
                if (f_status){
                    s_cmd = 0x5b;
                    SendMsgDownLoad(s_cmd, m_address, data, len);
                }else{
                    uchar *strAll = NULL;
                    strAll = (uchar *)m_dataAll.data();
                    uint CRC_CCITT = CRC16Check_CCITT(strAll, m_dataAll.count());
                    qDebug()<<cur_pos<<send_count<<receive_count<<CRC_CCITT;
                    data[0] = (cur_pos >> 0) & 0xff;
                    data[1] = (CRC_CCITT >> 8) & 0xff;
                    data[2] = (CRC_CCITT >> 0) & 0xff;
                    s_cmd = 0x60;
                    SendMsgDownLoad(s_cmd, (cur_pos>>8), data, 3, 1);
                }

            }else{
                f_status = FetchData(data, &len, cur_pos);
                s_cmd = 0x5b;
                SendMsgDownLoad(s_cmd, m_address, data, len);
            }
            break;
        case 0x60:
            if (status){
                qDebug()<<"Download finshed!";
            }else{

            }
            break;
        default:
            break;
        }
    }
}


