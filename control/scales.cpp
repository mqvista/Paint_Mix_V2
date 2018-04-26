#include "scales.h"


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
        m_serialPort.setBaudRate(baud);
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
        qDebug() << "Open Failed" << m_serialPort.errorString();
        return false;
    }
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

//QString Scales::getSerialPortBySerialNumber()
//{
//    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
//        qDebug()<< info.portName();
//        qDebug()<< info.serialNumber();
//        qDebug()<< info.description();
//        qDebug()<< info.manufacturer();
//        qDebug()<< info.systemLocation();

//    }
//    return "1";
//}


void Scales::rawSerialReceiveSlot()
{
    QByteArray readAllData = m_serialPort.readAll();     //读取收到的数据one Byte
    receivedata.append(readAllData.data());             //将QByteArray转为QString，并保存

    if (QString(readAllData.data()) == "\n") {
        m_receivedata = receivedata;
        receivedata.clear();
        serialStrConver2Data(m_receivedata);
        emit receiveDataPush(m_scalesValue, m_scalesUnit);
    }
}

void Scales::scalesOpenSlot(QString port, quint32 baud)
{
    open(port, baud);
}

void Scales::scalesCloseSlot()
{
    close();
}
