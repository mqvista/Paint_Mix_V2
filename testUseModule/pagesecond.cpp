#include "pagesecond.h"

PageSecond::PageSecond(QObject *parent) : QObject(parent)
{

}

void PageSecond::moveAsix(QString num)
{
    qDebug() << "MoveAsix";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "moveAsix", Qt::QueuedConnection, Q_ARG(quint8, num.toInt()));
    qDebug() << "finishStartMoveAsix";
}

void PageSecond::openMiddleTankToOutsidePump()
{
    qDebug() << "openMiddleTankToOutsidePump";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openMiddleTankPumpToOutside", Qt::QueuedConnection);
    qDebug() << "finishOpenMiddleTankToOutsidePump";
}

void PageSecond::closeMiddleTankToOutsidePump()
{
    qDebug() << "closeMiddleTankToOutsidePump";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeMiddleTankPumpToOutside", Qt::QueuedConnection);
    qDebug() << "FinishCloseMiddleTankToOutsidePump";
}

void PageSecond::openMiddleTankAddWaterPump()
{
    qDebug() << "openMiddleTankAddWaterPump";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openExtrenPump", Qt::QueuedConnection);
    qDebug() << "finishOpenMiddleTankAddWaterPump";
}

void PageSecond::closeMiddleTankAddWaterPump()
{
    qDebug() << "closeMiddleTankAddWaterPump";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeExtrenPump", Qt::QueuedConnection);
    qDebug() << "FinishcloseMiddleTankAddWaterPump";
}

void PageSecond::openMiddleTankMix()
{
    qDebug() << "openMiddleTankMix";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openTankMuxer", Qt::QueuedConnection);
    qDebug() << "FinishopenMiddleTankMix";
}

void PageSecond::closeMiddleTankMix()
{
    qDebug() << "closeMiddleTankMix";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeTankMuxer", Qt::QueuedConnection);
    qDebug() << "FinishcloseMiddleTankMix";
}

void PageSecond::openSmallScalePumpToOutSide()
{
    qDebug() << "openSmallScalePumpToOutSide";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openSmallScalePumpToOutSide", Qt::QueuedConnection);
    qDebug() << "FinishopenSmallScalePumpToOutSide";
}

void PageSecond::closeSmallScalePumpToOutSide()
{
    qDebug() << "closeSmallScalePumpToOutSide";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeSmallScalePumpToOutSide", Qt::QueuedConnection);
    qDebug() << "FinishcloseSmallScalePumpToOutSide";
}

void PageSecond::openBigScalePumpToOutSide()
{
    qDebug() << "closeSmallScalePumpToOutSide";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openBigScalePumpToOutSide", Qt::QueuedConnection);
    qDebug() << "FinishcloseSmallScalePumpToOutSide";
}

void PageSecond::closeBigScalePumpToOutSide()
{
    qDebug() << "closeBigScalePumpToOutSide";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeBigScalePumpToOutSide", Qt::QueuedConnection);
    qDebug() << "FinishcloseBigScalePumpToOutSide";
}
