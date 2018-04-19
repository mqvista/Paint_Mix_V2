#ifndef SCALES_H
#define SCALES_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

class Scales : public QObject
{
    Q_OBJECT
public:
    explicit Scales(QObject *parent = nullptr);
    ~Scales();
    bool open(QString port, quint32 baud);
    void close(void);
    bool isScalesOpen();
    void goToThread(QThread *thread);
//    QString getSerialPortBySerialNumber();

protected:
    QString m_receivedata;
    double m_scalesValue;
    QString m_scalesStatus;
    QString m_scalesUnit;
    virtual void serialStrConver2Data(QString msg) = 0;     //must rewrite


signals:
    void receiveDataPush(double value, QString unit);

public slots:
    void serialErrorSlot(QSerialPort::SerialPortError error);
    void rawSerialReceiveSlot();
    void scalesOpenSlot(QString port, quint32 baud);
    void scalesCloseSlot();

private:
    QSerialPort m_serialPort;
    QString receivedata;
};

#endif // SCALES_H
