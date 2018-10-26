#ifndef MOTION_H
#define MOTION_H

#include <QMutex>
#include <QTimer>
#include <QDateTime>
#include "DriverGC.h"
#include "scalesworker.h"

//////////////////////////////////////////////////////////
/// \brief The Motion class
/// This Class is used to control the machine by DriverGC
/// You can use a worker to inherit it, and the worker
/// must run in the different thread
///
///
/////////////////////////////////////////////////////////

class Motion : public QThread
{
    Q_OBJECT
public:
    static Motion *Instance();
    // Open DriverGC Serial Port
    bool openSerial485(QString portSN);
    // Close DriverGc Serial Port
    bool closeSerial485();
    // Init the board
    bool initBoard();
    // Init the Motor
    bool initAsixMotor(quint8 motorNum);
    // Move asix
    bool moveAsixToScales(quint16 degree);
    // detect is the motion with encoder area
    bool detectEncoder();
    // Take the liquid to bottole
    bool liquidOut(quint8 motorNum, quint32 weight, quint8 scalesNum);
    // Stop the motor motion
    bool stopDrop(quint8 motorNum);
    // Add water to scales small or big
    bool addWater(quint32 weight, quint8 scalesNum);

    // punmp water from one scale to other scale (废弃)
    bool pumpToScale(quint8 targetScalesNum);
    // Convery motorNum and scale Num to degree
    quint16 converyDegree(quint8 motorNum, quint8 scaleNum);
    // 新机构设计, 所有的液体移除到外部的桶, 使用蠕动泵, 参数秤的编号 1和2
    bool pumpToOutSide(quint8 scaleNum);

    // extren board pump
    bool pumpToOutSide();
    bool addWaterOutside(quint32 liter);
    void reflushOutSideSenser();

    // 给大容量补充原液
    bool topUpTank();


    // Scales 1 , enum type
    enum scales1Motor :quint16 {
        scales1Motor01 = 288,
        scales1Motor02 = 252,
        scales1Motor03 = 216,
        scales1Motor04 = 180,
        scales1Motor05 = 144,
        scales1Motor06 = 108,
        scales1Motor07 = 72,
        scales1Motor08 = 36,
        scales1Motor09 = 0,
        scales1Motor10 = 324
    };

    // Scales 2 , enum type
    enum scales2Motor :quint16 {
        scales2Motor01 = 108,
        scales2Motor02 = 72,
        scales2Motor03 = 37,
        scales2Motor04 = 0,
        scales2Motor05 = 324,
        scales2Motor06 = 188,
        scales2Motor07 = 252,
        scales2Motor08 = 216,
        scales2Motor09 = 180,
        scales2Motor10 = 144
    };

public slots:
    // Get Serial 485 error message from DriverGC signal
    void serial485Error(QString msg1, QString msg2);
    // Get DriverGC debug message
    void driverGCDebugInfo(QString msg, QDateTime curTime);
    // Get the small scales senser data
    void getSmallScalesValue(double value);
    // Get the big scales senser data
    void getBigScalesValue(double value);
    // 接受来自UI的停止信号
    void getStopCurrentSignal();

signals:
    void finishWeight(double fWeight);
    void pumpToOutsideWeight(double fWeight);


private:
    Motion();
    // Save the current machine local
    //quint8 m_CurrentMotor;
    // Save the current machine degree
    quint16 m_CurrentDegree;
    // Save the asix A, curret encoder value
    qint32 m_EncoderData;
    // Block thread untils the motor is free
    void waitWhileFree(quint16 motor);
    // Save the big scales value from scalesWorker
    double m_BigScalesValue;
    // Save the small scales value from scalesWorker
    double m_SmallScalesValue;
    //
    QTimer *m_timers;
    bool m_stopFlag = false;
};

#endif // MOTION_H
