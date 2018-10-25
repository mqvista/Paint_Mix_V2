#ifndef MOTIONWORKER_H
#define MOTIONWORKER_H

#include <QObject>
#include <QMutex>
#include "motion.h"
#include "utils/filereadwrite.h"
#include "utils/errorhandle.h"

typedef QMap<quint16, QMap<QString, QString>> detailType;


class MotionWorker : public QObject
{
    Q_OBJECT
public:
    static MotionWorker *Instance();
    Q_INVOKABLE void openSerial485();
    Q_INVOKABLE void initDeviceMotor();
    Q_INVOKABLE void closeSerial485();
    Q_INVOKABLE void addWater(quint32 weight, quint8 scalesNum);
    Q_INVOKABLE void initAsix(quint8 motorNum);
    Q_INVOKABLE void liquidOut(quint8 motorNum, quint32 weight, quint8 scalesNum);
    Q_INVOKABLE void runFormula(const QString& formulaName);
    Q_INVOKABLE void runUseDetail(const detailType formulaDetails);
    Q_INVOKABLE void pumpToOutside();
    Q_INVOKABLE void addWaterOutside(quint32 liter);
    Q_INVOKABLE void reflushLimData();

private:
    explicit MotionWorker(QObject *parent = nullptr);
    FileReadWrite fileReadWrite;


signals:
    //通知主界面关闭初始化界面
    void isIniting(bool status);
    // 通知 model 系统正在运动中
    void runningStatus(bool value);

public slots:
    void processError(ErrorHandle::errorType type);
};

#endif // MOTIONWORKER_H
