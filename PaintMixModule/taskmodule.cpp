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

void TaskModule::runLoopFormula(QString formulaName)
{
    QMetaObject::invokeMethod(MotionWorker::Instance(), "runLoopFormula",
                              Qt::QueuedConnection,
                              Q_ARG(QString, formulaName));
}

void TaskModule::systemReboot()
{

    m_systemControl.systemReboot();
}

void TaskModule::systemShutdown()
{
    m_systemControl.systemShutdown();
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

QString TaskModule::middleTankLevel()
{
    return m_middleTankLevel;
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

void TaskModule::setMiddleTankLevel(QString value)
{
    m_middleTankLevel = value;
    emit middleTankLevelChanged();
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

void TaskModule::getMiddleTankLevel(double fWeight)
{
    QString tmp = QString::number(fWeight, 'f', 2);
    setMiddleTankLevel(tmp);
}

void TaskModule::getResetGridViewPoint()
{
    emit resetGridViewPoint();
}
