#include "service.h"

Service::Service(QQmlApplicationEngine *appEng, QObject *parent) : QObject(parent)
{
    qDebug() << "Service thread" << QThread::currentThreadId() << endl;
    // 把engine 指针传入
    m_engine = appEng;
    // 初始化qml 上下文对象
    initContext();

    // 把scalesWorker 丢入线程
    ScalesWorker::Instance()->moveToThread(&scalesWorkerThread);
    scalesWorkerThread.start();
    // 把scalesWorker 丢入线程
    MotionWorker::Instance()->moveToThread(&motionWorkerThread);
    motionWorkerThread.start();

    // 开启设备串口
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
    // 初始化a轴
    //QMetaObject::invokeMethod(MotionWorker::Instance(), "initAsix", Qt::QueuedConnection, Q_ARG(quint8, 0));

    // 开启秤的串口
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesSmallOpen", Qt::QueuedConnection,
                              Q_ARG(QString, "tty.usbserial"), Q_ARG(quint32, 2400));
//    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesBigOpen", Qt::QueuedConnection,
//                              Q_ARG(QString, "tty.usbserial"), Q_ARG(quint32, 9600));
}

Service::~Service()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "closeSerial485", Qt::QueuedConnection);
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesSmallClose", Qt::QueuedConnection);
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesBigClose", Qt::QueuedConnection);
    scalesWorkerThread.quit();
    scalesWorkerThread.wait();
    motionWorkerThread.quit();
    motionWorkerThread.wait();
}

void Service::initContext()
{
    m_engine->rootContext()->setContextProperty("taskModule", &m_TaskModule);
}
