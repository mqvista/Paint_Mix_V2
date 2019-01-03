#ifndef MOTIONWORKER_H
#define MOTIONWORKER_H

#include <QObject>
#include <QMutex>
#include "motion.h"
#include "utils/filereadwrite.h"
#include "utils/errorhandle.h"

typedef QMap<quint16, QMap<QString, QString>> detailType;


class MotionWorker : public QThread
{
    Q_OBJECT
public:
    static MotionWorker *Instance();
    Q_INVOKABLE void openSerial485();
    Q_INVOKABLE void initDeviceMotor();
    Q_INVOKABLE void closeSerial485();
    Q_INVOKABLE void addWater(double weight, quint8 scalesNum);
    Q_INVOKABLE void initAsix(quint8 motorNum);
    Q_INVOKABLE void liquidOut(quint8 motorNum, double weight, quint8 scalesNum);
    Q_INVOKABLE void runFormula(const QString& formulaName, bool needRunningFlag = true);
    // 微调用单次运行
    void runFormula(const QMap<quint16, QMap<QString, QString>> singleFormula, quint8 length);
    // 滚动循环用
    Q_INVOKABLE void runLoopFormula(const QString& formulaName);

    // Q_ARG 不支持模板类型，只能使用typedefine 间接支持
    typedef  QMap<quint16, QMap<QString, QString>> FixedType;
    Q_INVOKABLE void runAndSaveNewFormula(QString formulaName, FixedType newFormula);

    // testUSE
    Q_INVOKABLE void moveAsix(quint8 num);
    // for user control open close
    Q_INVOKABLE void openMiddleTankPumpToOutside();
    Q_INVOKABLE void closeMiddleTankPumpToOutside();
    Q_INVOKABLE void openExtrenPump();
    Q_INVOKABLE void closeExtrenPump();
    Q_INVOKABLE void openTankMuxer();
    Q_INVOKABLE void closeTankMuxer();
    Q_INVOKABLE void openSmallScalePumpToOutSide();
    Q_INVOKABLE void closeSmallScalePumpToOutSide();
    Q_INVOKABLE void openBigScalePumpToOutSide();
    Q_INVOKABLE void closeBigScalePumpToOutSide();

private:
    explicit MotionWorker();
    FileReadWrite fileReadWrite;
    bool m_stopFlag = false;
    QTimer *m_MiddleTankTimer;


signals:
    //通知主界面关闭初始化界面
    void isIniting(bool status);
    // 通知 model 系统正在运动中
    void runningStatus(bool value);
    void resetGuidViewPoint();

public slots:
    // 接受来自UI的停止信号
    void getStopCurrentSignal();
    void getTimerReflushTank();
    // 控制刷新middle tank
    void getRunningStatus(bool value);
};

#endif // MOTIONWORKER_H
