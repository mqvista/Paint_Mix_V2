#ifndef TASKMODULE_H
#define TASKMODULE_H

#include <QObject>
#include "control/motionworker.h"


class TaskModule : public QObject
{
    Q_OBJECT
    // 两个秤的属性到界面显示
    Q_PROPERTY(QString scaleSmall READ scaleSmall WRITE setScaleSmall NOTIFY scaleSmallChanged)
    Q_PROPERTY(QString scaleBig READ scaleBig WRITE setScaleBig NOTIFY scaleBigChanged)
    Q_PROPERTY(bool busy READ getBusy WRITE setBusy NOTIFY busyChanged)

public:
    explicit TaskModule(QObject *parent = nullptr);
    Q_INVOKABLE void test();
    Q_INVOKABLE void runFromula(QString formulaName);

    QString scaleSmall();
    QString scaleBig();
    void setScaleSmall(QString value);
    void setScaleBig(QString value);

    bool getBusy();
    void setBusy(bool value);

signals:
    void scaleSmallChanged();
    void scaleBigChanged();
    void taskFinishWeight(QString value);
    void busyChanged();

public slots:
    void getScaleSmallSlot(double value);
    void getScaleBigSlot(double value);
    void getFinishWeight(double fWeight);
    // 从motion 中获取系统繁忙状态
    void getRunningStatus(bool value);

private:
    QString m_scaleSmall;
    QString m_scaleBig;
    bool m_busy;
};

#endif // TASKMODULE_H
