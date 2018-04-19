#ifndef SCALESWORKER_H
#define SCALESWORKER_H

#include <QObject>
#include <QThread>
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
    //发送信号，通知别人去处理去更新数据
    void scalesSmallDataChangedSig(double value);
    void scalesBigDataChangedSig(double value);

    void scalesSmallOpenSig(QString name, quint32 baud);
    void scalesBigOpenSig(QString name, quint32 baud);
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
    QThread scalesBigThread;
    QThread scalesSmallThread;
    //秤数值的单位的保存
    double m_BigScalesValue = 0;
    double m_SmallScalesValue = 0;
    QString m_BigScalesUnit = "";
    QString m_SmallScalesUnit = "";
};

#endif // SCALESWORKER_H
