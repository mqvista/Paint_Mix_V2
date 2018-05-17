#ifndef MOTION_H
#define MOTION_H

#include "DriverGC.h"
#include "scalesworker.h"
#include <QDateTime>
#include <QMutex>
#include <QTimer>

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
    void openSerial485(QString portSN);
    // Close DriverGc Serial Port
    void closeSerial485();
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
    // punmp water from one scale to other scale
    bool pumpToScale(quint8 targetScalesNum);
    // Convery motorNum and scale Num to degree
    quint16 converyDegree(quint8 motorNum, quint8 scaleNum);

    // extren board pump
    bool pumpToOutSide();
    void reflushOutSideSenser();

    // Scales 1 , enum type
    enum scales1Motor :quint16 {
        scales1Motor01 = 344,
        scales1Motor02 = 308,
        scales1Motor03 = 272,
        scales1Motor04 = 236,
        scales1Motor05 = 200,
        scales1Motor06 = 164,
        scales1Motor07 = 128,
        scales1Motor08 = 92,
        scales1Motor09 = 56,
        scales1Motor10 = 20
    };

    // Scales 2 , enum type
    enum scales2Motor :quint16 {
        scales2Motor01 = 128,
        scales2Motor02 = 92,
        scales2Motor03 = 56,
        scales2Motor04 = 20,
        scales2Motor05 = 344,
        scales2Motor06 = 308,
        scales2Motor07 = 272,
        scales2Motor08 = 236,
        scales2Motor09 = 200,
        scales2Motor10 = 164
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

signals:
    void finishWeight(double fWeight);


private:
    Motion();
    // Save the current machine local
    quint8 m_CurrentMotor;
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
};

#endif // MOTION_H
