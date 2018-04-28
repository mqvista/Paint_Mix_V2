#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "drivergc_global.h"
#include <QByteArray>
#include <QDateTime>
#include <QDebug>
#include <QIODevice>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QThread>

class DRIVERGCSHARED_EXPORT Communication : public QThread {
    Q_OBJECT
public:
    bool Open(const QString& port, const quint32& baud = 460800);
    bool OpenUseSN(const QString& serialNumber, const quint32& baud = 460800);
    bool Close();
    bool IsOpened();
signals:
    void DebugOut(QString msg, QDateTime curTime = QDateTime::currentDateTime());
    void ErrorOut(QString msg1, QString msg2);

protected:
    QSerialPort _com;

    ~Communication();
    virtual void ReceiveEvent() = 0;

public slots:
    void GetSerialError(QSerialPort::SerialPortError error);
};

#endif // COMMUNICATION_H
