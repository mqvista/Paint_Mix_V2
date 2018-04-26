#include "motionworker.h"

MotionWorker *MotionWorker::Instance()
{
    static QMutex mutex;
        static QScopedPointer<MotionWorker> instance;
        if (Q_UNLIKELY(!instance)) {
            mutex.lock();
            if (!instance) {
                instance.reset(new MotionWorker);
            }
            mutex.unlock();
        }
        return instance.data();
}

void MotionWorker::openSerial485()
{
    qDebug() << "MOtion thread" << QThread::currentThreadId() << endl;
//    DriverGC::Instance()->Open("tty.SLAB_USBtoUART");
    Motion::Instance()->openSerial485("tty.SLAB_USBtoUART");
    Motion::Instance()->initBoard();
    Motion::Instance()->initAsixMotor(0);
}

void MotionWorker::closeSerial485()
{
//    DriverGC::Instance()->Close();
    Motion::Instance()->closeSerial485();
}

void MotionWorker::addWater(quint32 weight, quint8 scalesNum)
{
    Motion::Instance()->addWater(weight, scalesNum);
}

void MotionWorker::initAsix(quint8 motorNum)
{
    Motion::Instance()->initAsixMotor(motorNum);
}

void MotionWorker::liquidOut(quint8 motorNum, quint32 weight, quint8 scalesNum)
{
    Motion::Instance()->liquidOut(motorNum, weight, scalesNum);
}

MotionWorker::MotionWorker(QObject *parent) : QObject(parent)
{

}
