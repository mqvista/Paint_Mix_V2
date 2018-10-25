#include "motionworker.h"
#include "utils/errorhandle.h"

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
    qDebug() << "Motion thread" << QThread::currentThreadId() << endl;
    Motion::Instance()->openSerial485("45VBMPWF");
    if (!Motion::Instance()->openSerial485("45VBMPWF"))
    {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_RS485_OPEN_FAILED);
    }
}


// 初始化板子和旋转轴
void MotionWorker::initDeviceMotor()
{
    if (!Motion::Instance()->initBoard())
    {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_BOARD_INIT_FAILED);
        return;
    }
    if (!Motion::Instance()->initAsixMotor(0))
    {
        ErrorHandle::Instance()->collectionError(ErrorHandle::ERROR_ROTARY_INIT_FAILED);
        return;
    }
    emit isIniting(false);
}

void MotionWorker::closeSerial485()
{
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

void MotionWorker::runFormula(const QString& formulaName)
{

    emit runningStatus(true);

    // 设置一个变量保存读取出来的数据
    QMap<quint16, QMap<QString, QString>> formula;
    qint16 length;
    // 读取方案文件
    fileReadWrite.readProfileDetail(formulaName, &formula, &length);


    // 循环qmap 找出每一个步骤，并执行
    for (quint8 i=1; i<=length; i++)
    {
        // 建立一个子 qmap， 存储循环出来的数据
        QMap<QString, QString> subFormula;
        subFormula = formula.value(i);

        // 判断是否有 Motor 注液流且 Motor 唯一
        if (subFormula.count("Motor") == 1)
        {
            quint8 motorNum = subFormula.value("Motor").toUInt();
            quint8 scaleNum = subFormula.value("Scales").toUInt();
            quint32 weight = subFormula.value("Weight").toUInt();
            // 运动到指定位置
            if(! Motion::Instance()->moveAsixToScales(Motion::Instance()->converyDegree(motorNum, scaleNum)))
            {
                break;
            }
            // 放水
            if(! Motion::Instance()->liquidOut(motorNum, weight, scaleNum))
            {
                break;
            }
            continue;
        }
        // 判断是放清水
        if (subFormula.count("Water") == 1)
        {
            quint8 scaleNum = subFormula.value("Scales").toUInt();
            quint32 weight = subFormula.value("Weight").toUInt();
            if (! Motion::Instance()->addWater(weight, scaleNum))
            {
                break;
            }
            continue;
        }
        // 判断是否是搬运水
        if (subFormula.count("Exchange") == 1)
        {
            if (! Motion::Instance()->pumpToScale(2))
            {
                break;
            }
            continue;
        }
    }
    emit runningStatus(false);
}

void MotionWorker::runUseDetail(const detailType formulaDetails)
{

    emit runningStatus(true);

    // 循环qmap 找出每一个步骤，并执行
    for (quint8 i=1; i<=formulaDetails.size(); i++)
    {
        // 建立一个子 qmap， 存储循环出来的数据
        QMap<QString, QString> subFormula;
        subFormula = formulaDetails.value(i);

        // 判断是否有 Motor 注液流且 Motor 唯一
        if (subFormula.count("Motor") == 1)
        {
            quint8 motorNum = subFormula.value("Motor").toUInt();
            quint8 scaleNum = subFormula.value("Scales").toUInt();
            quint32 weight = subFormula.value("Weight").toUInt();
            // 运动到指定位置
            qDebug() << Motion::Instance()->converyDegree(motorNum, scaleNum);
            Motion::Instance()->moveAsixToScales(Motion::Instance()->converyDegree(motorNum, scaleNum));
            // 放水
            Motion::Instance()->liquidOut(motorNum, weight, scaleNum);
            continue;
        }
        // 判断是放清水
        if (subFormula.count("Water") == 1)
        {
            quint8 scaleNum = subFormula.value("Scales").toUInt();
            quint32 weight = subFormula.value("Weight").toUInt();
            Motion::Instance()->addWater(weight, scaleNum);
            continue;
        }
        // 判断是否是搬运水
        if (subFormula.count("Exchange") == 1)
        {
            Motion::Instance()->pumpToScale(2);
            continue;
        }
    }

    emit runningStatus(false);
}

// extern board
void MotionWorker::pumpToOutside()
{
    emit runningStatus(true);
    Motion::Instance()->pumpToOutSide();
    emit runningStatus(false);
}

void MotionWorker::addWaterOutside(quint32 liter)
{
    emit runningStatus(true);
    Motion::Instance()->addWaterOutside(liter);
    emit runningStatus(false);
}

void MotionWorker::reflushLimData()
{
    Motion::Instance()->reflushOutSideSenser();
}

MotionWorker::MotionWorker(QObject *parent) : QObject(parent)
{

}

void MotionWorker::processError(ErrorHandle::errorType type)
{
    switch (type)
    {
    case ErrorHandle::ERROR_RS485_NOT_OPEN:
        openSerial485();
        break;
    case ErrorHandle::ERROR_BOARD_INIT_FAILED:
        initDeviceMotor();
        break;
    case ErrorHandle::ERROR_ROTARY_INIT_FAILED:
        initDeviceMotor();
        break;
    default:
        break;
    }
}
