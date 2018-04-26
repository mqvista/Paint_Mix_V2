#ifndef SCALESWORKER_H
#define SCALESWORKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include "scalesbig.h"
#include "scalessmall.h"

class ScalesWorker : public QObject
{
    Q_OBJECT
public:
    static ScalesWorker *Instance();
    ~ScalesWorker();
    Q_INVOKABLE void scalesSmallOpen(QString name, quint32 baud);
    Q_INVOKABLE void scalesBigOpen(QString name, quint32 baud);
    Q_INVOKABLE void scalesSmallClose();
    Q_INVOKABLE void scalesBigClose();

signals:
    // A signal to notice anyone can update the small scale value
    void scalesSmallDataChangedSig(double value);
    // A signal to notice anyone can update the big scale value
    void scalesBigDataChangedSig(double value);
    // A signal to notice the small scale calss to open the scale serial port
    void scalesSmallOpenSig(QString name, quint32 baud);
    // A signal to notice the big scale calss to open the scale serial port
    void scalesBigOpenSig(QString name, quint32 baud);
    // A signal to notice the small cales to close the port
    void scalesSmallCloseSig();
    void scalesBigCloseSig();


public slots:
    //接收秤信号发回的数据
    void getScalesBigDataSlot(double value, QString unit);
    void getScalesSmallDataSlot(double value, QString unit);

private:
    explicit ScalesWorker(QObject *parent = nullptr);
    ScalesBig m_scalesBig;
    ScalesSmall m_scalesSmall;
    QThread m_scalesBigThread;
    QThread m_scalesSmallThread;
    //秤数值的单位的保存
    double m_BigScalesValue = 0;
    double m_SmallScalesValue = 0;
    QString m_BigScalesUnit = "";
    QString m_SmallScalesUnit = "";
};

#endif // SCALESWORKER_H
