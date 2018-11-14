#include "scales.h"
#include "utils/errorhandle.h"


Scales::Scales(QObject *parent) : QObject(parent)
{

}

Scales::~Scales()
{
    close();
}

bool Scales::open(QString port, quint32 baud)
{
    m_serialPort.setPortName(port);
    if (m_serialPort.open(QIODevice::ReadWrite))         //打开端口
    {
        qDebug() << "scale Serial is opened " << endl;
        m_serialPort.setBaudRate(qint32(baud));
        m_serialPort.setDataBits(QSerialPort::Data8);
        m_serialPort.setParity(QSerialPort::NoParity);
        m_serialPort.setStopBits(QSerialPort::OneStop);
        m_serialPort.setFlowControl(QSerialPort::NoFlowControl);
        m_serialPort.clearError();
        m_serialPort.clear();

        //链接串口接受信号和串口错误信号
        connect(&m_serialPort, &QSerialPort::readyRead, this, &Scales::rawSerialReceiveSlot);
        connect(&m_serialPort, &QSerialPort::errorOccurred, this, &Scales::serialErrorSlot);
        return true;
    }
    else
    {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_SCALE_OPEN_FAILED);
        qDebug() << "Open Failed" << m_serialPort.errorString();
        return false;
    }
}

bool Scales::openUseSN(const QString &serialNumber, const quint32 &baud)
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << info.serialNumber();
        if (info.serialNumber() == serialNumber)
        {
            if (open(info.portName(), baud))
            {
                return true;
            }
            return false;
        }
    }
    ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_SCALE_NOT_FOUND);
    return false;
}

void Scales::close()
{
    m_serialPort.close();
    qDebug()<< "Serial is closed";
//    if (m_serialPort.isOpen())
//    {
//        m_serialPort.close();
//        qDebug()<< "Serial is closed";
//    }
}

bool Scales::isScalesOpen()
{
    return m_serialPort.isOpen();
}

//接受串口错误信息
void Scales::serialErrorSlot(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        qDebug()<< m_serialPort.errorString();
    }
}


void Scales::goToThread(QThread *thread)
{
    m_serialPort.moveToThread(thread);
    this->moveToThread(thread);
    thread->start();
}

bool Scales::getSerialPortBySerialNumber(QString serialNumber, QString* portName)
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if (info.serialNumber() == serialNumber)
        {
            *portName = info.portName();
            return true;
        }
    }
    return false;
}


void Scales::rawSerialReceiveSlot()
{
    //qDebug()<< "Raws";
    QByteArray readData = m_serialPort.readAll();     //读取收到的数据one Byte
    //m_receivedata.append(readAllData.data());             //将QByteArray转为QString，并保存
    /////
    p_allData.append(readData);           // 数据直接附加到 private 的 QByteArray
    serialStrConver2Data();
    /////


    /*if (QString(readAllData.data()) == "\n") {
        p_receivedata = receivedata;
        m_receivedata.clear();
        serialStrConver2Data(p_receivedata);
        qDebug()<< "rdata"<< p_receivedata;
        emit receiveDataPush(p_scalesValue, p_scalesUnit);
    }*/
}

void Scales::scalesOpenSlot(QString port, quint32 baud)
{
    open(port, baud);
}

void Scales::scalesCloseSlot()
{
    close();
}

void Scales::scalesOpenUseSNSlot(QString serialNumber, quint32 baud)
{
    openUseSN(serialNumber, baud);
}
