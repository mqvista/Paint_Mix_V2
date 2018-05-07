#include "service.h"

Service::Service(QQmlApplicationEngine *appEng, QObject *parent) : QObject(parent)
{
    qDebug() << "Service thread" << QThread::currentThreadId() << endl;
    // 把engine 指针传入
    m_engine = appEng;
    // 把scalesWorker 丢入线程
    ScalesWorker::Instance()->moveToThread(&scalesWorkerThread);
    scalesWorkerThread.start();
    // 把scalesWorker 丢入线程
    MotionWorker::Instance()->moveToThread(&motionWorkerThread);
    motionWorkerThread.start();

    // 初始化qml 上下文对象
    initContext();
    // 开启 loading 画面
    //m_IndexModule.setIsnitialization(true);

    // 初始化信号连接
    initSignalSlotConnect();
    // 开启相应的硬件端口，并初始化硬件
    //initSystem();


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
    m_engine->rootContext()->setContextProperty("indexModule", &m_IndexModule);
    m_engine->rootContext()->setContextProperty("formulaList", &m_FormulaListView);
    m_engine->rootContext()->setContextProperty("formulaGrid", &m_FormulaGridView);
    m_engine->rootContext()->setContextProperty("formulaAddNew", &m_FormulaAddNew);
}

void Service::initSignalSlotConnect()
{
    // Connect the scales value signal, and get the small scales value
    connect(ScalesWorker::Instance(), &ScalesWorker::scalesSmallDataChangedSig, Motion::Instance(), &Motion::getSmallScalesValue);
    // Connect the scales value signal, and get the big scales value
    connect(ScalesWorker::Instance(), &ScalesWorker::scalesBigDataChangedSig, Motion::Instance(), &Motion::getBigScalesValue);
    // 连接从运动worker出发出的初始化完成信号,并隐藏等待画面
    connect(MotionWorker::Instance(), &MotionWorker::isIniting, &m_IndexModule, &IndexModule::setIsnitialization);
}

void Service::initSystem()
{
    // 开启设备串口
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
    // 开启秤的串口
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesSmallOpen", Qt::QueuedConnection,
                              Q_ARG(QString, "tty.usbserial"), Q_ARG(quint32, 2400));
}
