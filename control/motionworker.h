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
    // 微调用单次运行
    void runFormula(const QMap<quint16, QMap<QString, QString>> singleFormula, quint8 length);

    // Q_ARG 不支持模板类型，只能使用typedefine 间接支持
    typedef  QMap<quint16, QMap<QString, QString>> FixedType;
    Q_INVOKABLE void runAndSaveNewFormula(QString formulaName, FixedType newFormula);

    // testUSE
    Q_INVOKABLE void moveAsix(quint8 num);
    Q_INVOKABLE void getExternADCValue();
    Q_INVOKABLE void openExtrenPump();
    Q_INVOKABLE void closeExtrenPump();



private:
    explicit MotionWorker(QObject *parent = nullptr);
    FileReadWrite fileReadWrite;


signals:
    //通知主界面关闭初始化界面
    void isIniting(bool status);
    // 通知 model 系统正在运动中
    void runningStatus(bool value);

public slots:
//    void processError(ErrorHandle::errorType type);
};

#endif // MOTIONWORKER_H
