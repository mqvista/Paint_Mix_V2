#ifndef TASKMODULE_H
#define TASKMODULE_H

#include <QObject>
#include "control/motionworker.h"
#include "utils/systemcontrol.h"


class TaskModule : public QObject
{
    Q_OBJECT
    // 两个秤的属性到界面显示
    Q_PROPERTY(QString scaleSmall READ scaleSmall WRITE setScaleSmall NOTIFY scaleSmallChanged)
    Q_PROPERTY(QString scaleBig READ scaleBig WRITE setScaleBig NOTIFY scaleBigChanged)
    Q_PROPERTY(QString pumpOutSideWeight READ pumpOutSideWeight WRITE setPumpOutSideWeight NOTIFY pumpOutSideWeightChanged)
    Q_PROPERTY(bool busy READ getBusy WRITE setBusy NOTIFY busyChanged)
    Q_PROPERTY(QString middleTankLevel READ middleTankLevel WRITE setMiddleTankLevel NOTIFY middleTankLevelChanged)

public:
    explicit TaskModule(QObject *parent = nullptr);
    Q_INVOKABLE void test();
    Q_INVOKABLE void runFromula(QString formulaName);
    Q_INVOKABLE void getSenserData();
    Q_INVOKABLE void addWaterOutside(QString liter);
    Q_INVOKABLE void stopCurrentJob();
    Q_INVOKABLE void runLoopFormula(QString formulaName);
    Q_INVOKABLE void systemReboot();
    Q_INVOKABLE void systemShutdown();


    QString scaleSmall();
    QString scaleBig();
    QString pumpOutSideWeight();
    QString middleTankLevel();
    void setPumpOutSideWeight(QString value);
    void setScaleSmall(QString value);
    void setScaleBig(QString value);
    void setMiddleTankLevel(QString value);

    bool getBusy();
    void setBusy(bool value);

signals:
    void scaleSmallChanged();
    void scaleBigChanged();
    void taskFinishWeight(QString value);
    void busyChanged();
    void pumpOutSideWeightChanged();
    void middleTankLevelChanged();
    void stopCurrentJobSignal();
    void resetGridViewPoint();

public slots:
    void getScaleSmallSlot(double value);
    void getScaleBigSlot(double value);
    void getFinishWeight(double fWeight);
    // 从motion 中获取系统繁忙状态
    void getRunningStatus(bool value);
    // 从motion 总获取总的移出重量
    void getPumpOutSideWeightFromMotion(double value);
    // 获取中桶
    void getMiddleTankLevel(double fWeight);
    // 从 worker 获取gridview光标复位信号
    void getResetGridViewPoint();

private:
    QString m_scaleSmall;
    QString m_scaleBig;
    QString m_pumpOutSideWeight;
    bool m_busy;
    QString m_middleTankLevel;
    SystemControl m_systemControl;
};

#endif // TASKMODULE_H
