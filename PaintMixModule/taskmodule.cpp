#include "taskmodule.h"

TaskModule::TaskModule(QObject *parent) : QObject(parent)
{
    setBusy(false);
    setPumpOutSideWeight("0");
}

void TaskModule::test()
{
    qDebug()<< "Do somethings";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "pumpToOutside",
                              Qt::AutoConnection);
}

void TaskModule::runFromula(QString formulaName)
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "runFormula",
                              Qt::QueuedConnection,
                              Q_ARG(QString, formulaName));
}

void TaskModule::getSenserData()
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "reflushLimData",
                              Qt::QueuedConnection);
}

void TaskModule::addWaterOutside(QString liter)
{
    quint32 value = liter.toInt();
    QMetaObject::invokeMethod(MotionWorker::Instance(), "addWaterOutside",
                              Qt::QueuedConnection,
                              Q_ARG(quint32, value));
}

void TaskModule::stopCurrentJob()
{
    emit stopCurrentJobSignal();
}


QString TaskModule::scaleSmall()
{
    return m_scaleSmall;
}

QString TaskModule::scaleBig()
{
    return m_scaleBig;
}

QString TaskModule::pumpOutSideWeight()
{
    return m_pumpOutSideWeight;
}

void TaskModule::setPumpOutSideWeight(QString value)
{
    m_pumpOutSideWeight = value;
    pumpOutSideWeightChanged();
}

void TaskModule::setScaleSmall(QString value)
{
    m_scaleSmall = value;
    emit scaleSmallChanged();
}

void TaskModule::setScaleBig(QString value)
{
    m_scaleBig = value;
    emit scaleBigChanged();
}

bool TaskModule::getBusy()
{
    return m_busy;
}

void TaskModule::setBusy(bool value)
{
    m_busy = value;
    emit busyChanged();
}

void TaskModule::getScaleSmallSlot(double value)
{
    setScaleSmall(QString::number(value, 'f', 2));
}

void TaskModule::getScaleBigSlot(double value)
{
    setScaleBig(QString::number(value, 'f', 2));
}

void TaskModule::getFinishWeight(double fWeight)
{
    emit taskFinishWeight(QString::number(fWeight, 'f', 2));
}

void TaskModule::getRunningStatus(bool value)
{
    m_busy = value;
    emit busyChanged();
}

void TaskModule::getPumpOutSideWeightFromMotion(double value)
{
    qDebug()<< value;
    QString tmp = QString::number(value, 'f', 1);
    setPumpOutSideWeight(tmp);
}
