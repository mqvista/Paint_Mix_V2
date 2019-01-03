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

void PageSecond::openMiddleTankMix()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openTankMuxer", Qt::QueuedConnection);
}

void PageSecond::closeMiddleTankMix()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeTankMuxer", Qt::QueuedConnection);
}

void PageSecond::openSmallScalePumpToOutSide()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openSmallScalePumpToOutSide", Qt::QueuedConnection);
}

void PageSecond::closeSmallScalePumpToOutSide()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeSmallScalePumpToOutSide", Qt::QueuedConnection);
}

void PageSecond::openBigScalePumpToOutSide()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openBigScalePumpToOutSide", Qt::QueuedConnection);
}

void PageSecond::closeBigScalePumpToOutSide()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeBigScalePumpToOutSide", Qt::QueuedConnection);
}
