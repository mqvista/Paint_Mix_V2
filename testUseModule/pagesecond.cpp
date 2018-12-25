#include "pagesecond.h"

PageSecond::PageSecond(QObject *parent) : QObject(parent)
{

}

void PageSecond::moveAsix(QString num)
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "moveAsix", Qt::QueuedConnection, Q_ARG(quint8, num.toInt()));
}

void PageSecond::openMiddleTankToOutsidePump()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openMiddleTankPumpToOutside", Qt::QueuedConnection);
}

void PageSecond::closeMiddleTankToOutsidePump()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeMiddleTankPumpToOutside", Qt::QueuedConnection);
}

void PageSecond::openMiddleTankAddWaterPump()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openExtrenPump", Qt::QueuedConnection);
}

void PageSecond::closeMiddleTankAddWaterPump()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeExtrenPump", Qt::QueuedConnection);
}
