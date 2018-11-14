#include "errorhandle.h"
#include "control/motionworker.h"

ErrorHandle::ErrorHandle(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<errorType>("errorType");
}

// 定时检查是否有未广播的错误
void ErrorHandle::checkQueue()
{
    if (!errorQueue.isEmpty())
    {
        // 如果头一个错误没有广播过，就广播通知界面显示
        if (!errorQueue.head().isBroadCasted)
        {
            errorQueue.head().isBroadCasted = true;
            emit broadCastError(errorQueue.head().type);
        }
    }
}

void ErrorHandle::getErrorMessageRetry()
{

    switch (errorQueue.head().type) {
    case ERROR_RS485_NOT_FOUND:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
        break;
    case ERROR_RS485_NOT_OPEN:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
        break;
    case ERROR_RS485_OPEN_FAILED:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
        break;
    case ERROR_RS485_NOT_CONNECTED:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
        break;
    case ERROR_RS485_NO_RESPONSE:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
        break;
    case ERROR_RS485_LINK_LOST:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "openSerial485", Qt::QueuedConnection);
        break;
    case ERROR_SMALL_SCALE_NOT_FOUND:
        break;
    case ERROR_SMALL_SCALE_NOT_OPENED:
        break;
    case ERROR_SMALL_SCALE_NOT_CONNECTED:
        break;
    case ERROR_SMALL_SCALE_NO_RESPONSE:
        break;
    case ERROR_SMALL_SCALE_LINK_LOST:
        break;
    case ERROR_BIG_SCALE_NOT_FOUND:
        break;
    case ERROR_BIG_SCALE_NOT_OPENED:
        break;
    case ERROR_BIG_SCALE_NOT_CONNECTED:
        break;
    case ERROR_BIG_SCALE_NO_RESPONSE:
        break;
    case ERROR_BIG_SCALE_LINK_LOST:
        break;
    case ERROR_ROTARY_AXIS_TIMEOUT:
        break;
    case ERROR_ROTARY_ENCODER:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "initDeviceMotor", Qt::QueuedConnection);
        break;
    case ERROR_ROTARY_AXIS_LIMIT:
        break;
    case ERROR_ROTARY_INIT_FAILED:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "initDeviceMotor", Qt::QueuedConnection);
        break;
    case ERROR_BOARD_INIT_FAILED:
        QMetaObject::invokeMethod(MotionWorker::Instance(), "initDeviceMotor", Qt::QueuedConnection);
        break;
    case ERROR_SCALE_OPEN_FAILED:
        break;
    case ERROR_SCALE_NOT_FOUND:
        break;
    case ERROR_TANK_IS_EMPTY_OR_TANK_SENSER_ERROR:
        break;
    case ERROR_TANK_WILL_OVER_LIMIT:
        break;
    case ERROR_UNKNOWN:
        break;
    }

    errorQueue.dequeue();
    return;
}

ErrorHandle *ErrorHandle::Instance()
{
    static QMutex mutex;
    static QScopedPointer<ErrorHandle> instance;
    if (Q_UNLIKELY(!instance)) {
        mutex.lock();
        if (!instance) {
            instance.reset(new ErrorHandle);
        }
        mutex.unlock();
    }
    return instance.data();
}

ErrorHandle::~ErrorHandle()
{
    m_loopTimer->stop();
}

void ErrorHandle::init()
{
    m_loopTimer = new QTimer(this);
    connect(m_loopTimer, &QTimer::timeout, this, &ErrorHandle::checkQueue);
    m_loopTimer->start(5000);
}

// 收集错误讯息
void ErrorHandle::collectionError(ErrorHandle::errorType type)
{
    // 先收集错误信息
    errorQueueType tempStruct;
    tempStruct.type = type;
    tempStruct.dataTime = QDateTime::currentDateTime();
    tempStruct.isSloved = false;
    tempStruct.isBroadCasted = false;

    // 插入错误队列
    errorQueue.enqueue(tempStruct);
}
