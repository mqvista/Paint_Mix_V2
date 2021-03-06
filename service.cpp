#include "service.h"

Service::Service(QQmlApplicationEngine *appEng, QObject *parent) : QObject(parent)
{
    qDebug() << "Service thread" << QThread::currentThreadId() << endl;
    // 把engine 指针传入
    m_engine = appEng;
    // 错误处理的线程
    ErrorHandle::Instance()->moveToThread(&errorHandalThread);
    errorHandalThread.start();
    QMetaObject::invokeMethod(ErrorHandle::Instance(), "init", Qt::QueuedConnection);

    // 把scalesWorker 丢入线程
    ScalesWorker::Instance()->moveToThread(&scalesWorkerThread);
    scalesWorkerThread.start();
    // 把motionWorker 丢入线程
    MotionWorker::Instance()->moveToThread(&motionWorkerThread);
    motionWorkerThread.start();
    // 初始化qml 上下文对象
    initContext();
    // 初始化信号连接
    initSignalSlotConnect();
    // 开启 loading 画面
    m_IndexModule.setIsnitialization(true);
    // 开启相应的硬件端口，并初始化硬件
    initSystem();
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
    errorHandalThread.quit();
    errorHandalThread.wait();
}

// 暴露c++ 对象到qml
void Service::initContext()
{
    m_engine->rootContext()->setContextProperty("taskModule", &m_TaskModule);
    m_engine->rootContext()->setContextProperty("indexModule", &m_IndexModule);
    m_engine->rootContext()->setContextProperty("formulaList", &m_FormulaListView);
    m_engine->rootContext()->setContextProperty("formulaGrid", &m_FormulaGridView);
    m_engine->rootContext()->setContextProperty("formulaAddNew", &m_FormulaAddNew);
    m_engine->rootContext()->setContextProperty("formulaAddition", &m_FormulaAddition);
    m_engine->rootContext()->setContextProperty("pageSecond", &m_pageSecond);
}

void Service::initSignalSlotConnect()
{
    // Connect the scales value signal, and get the small scales value
    connect(ScalesWorker::Instance(), &ScalesWorker::scalesSmallDataChangedSig, Motion::Instance(), &Motion::getSmallScalesValue);
    // Connect the scales value signal, and get the big scales value
    connect(ScalesWorker::Instance(), &ScalesWorker::scalesBigDataChangedSig, Motion::Instance(), &Motion::getBigScalesValue);

    connect(ScalesWorker::Instance(), &ScalesWorker::scalesSmallDataChangedSig, &m_TaskModule, &TaskModule::getScaleSmallSlot);

    connect(ScalesWorker::Instance(), &ScalesWorker::scalesBigDataChangedSig, &m_TaskModule, &TaskModule::getScaleBigSlot);
    // 连接从运动worker出发出的初始化完成信号,并隐藏等待画面
    connect(MotionWorker::Instance(), &MotionWorker::isIniting, &m_IndexModule, &IndexModule::setIsnitialization);
    // qml 取得实际注液量
    connect(Motion::Instance(), &Motion::finishWeight, &m_TaskModule, &TaskModule::getFinishWeight);
    // 刷新gridview界面的光标
    connect(MotionWorker::Instance(), &MotionWorker::resetGuidViewPoint, &m_TaskModule, &TaskModule::getResetGridViewPoint);

    connect(MotionWorker::Instance(), &MotionWorker::runningStatus, &m_TaskModule, &TaskModule::getRunningStatus);

    connect(Motion::Instance(), &Motion::pumpToOutsideWeight, &m_TaskModule, &TaskModule::getPumpOutSideWeightFromMotion);
    // 停止当前工作
    connect(&m_TaskModule, &TaskModule::stopCurrentJobSignal, Motion::Instance(), &Motion::getStopCurrentSignal);
    connect(&m_TaskModule, &TaskModule::stopCurrentJobSignal, MotionWorker::Instance(), &MotionWorker::getStopCurrentSignal);
    // 连接广播的中桶液位
    connect(Motion::Instance(), &Motion::broadCaseMiddleTankLevel, &m_TaskModule, &TaskModule::getMiddleTankLevel);
}

void Service::initSystem()
{
    // 开启设备串口
    QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
    // 初始化控制板和电机
    QMetaObject::invokeMethod(MotionWorker::Instance(), "initDeviceMotor", Qt::QueuedConnection);
    // 开启秤的串口
    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesSmallOpenUseSN", Qt::QueuedConnection,
                              Q_ARG(QString, "AH06DLKH"), Q_ARG(quint32, 2400));

    QMetaObject::invokeMethod(ScalesWorker::Instance(), "scalesBigOpenUseSN", Qt::QueuedConnection,
                              Q_ARG(QString, "AH06DLKF"), Q_ARG(quint32, 9600));
}

void Service::needRunafterQmlLoaded()
{
    // 连接
    QObject *dialogItem;
    dialogItem = m_engine->rootObjects().first()->findChild<QObject*>("errorDialogObject");
    connect(dialogItem, SIGNAL(accepted()), ErrorHandle::Instance(), SLOT(getErrorMessageRetry()));
}
