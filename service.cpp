#include "service.h"

Service::Service(QObject *parent) : QObject(parent)
{
    ScalesWorker::Instance()->moveToThread(&scalesWorkerThread);
    scalesWorkerThread.start();

    /*
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesSmallOpen", Qt::QueuedConnection ,
                              Q_ARG(QString, "tty.usbserial"), Q_ARG(quint32, 115200));
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesBigOpen", Qt::QueuedConnection ,
                              Q_ARG(QString, "tty.usbserial3"), Q_ARG(quint32, 115200));
                              */
}

Service::~Service()
{
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesSmallClose", Qt::QueuedConnection);
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesBigClose", Qt::QueuedConnection);
    scalesWorkerThread.quit();
    scalesWorkerThread.wait();
}
