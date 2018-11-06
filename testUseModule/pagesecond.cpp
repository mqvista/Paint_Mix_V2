#include "pagesecond.h"

PageSecond::PageSecond(QObject *parent) : QObject(parent)
{

}

void PageSecond::moveAsix(QString num)
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "moveAsix", Qt::QueuedConnection, Q_ARG(quint8,num.toInt()));
}

void PageSecond::getExternADCValue()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "getExternADCValue", Qt::QueuedConnection);
}

void PageSecond::openPump()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openExtrenPump", Qt::QueuedConnection);
}

void PageSecond::closePump()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeExtrenPump", Qt::QueuedConnection);
}
