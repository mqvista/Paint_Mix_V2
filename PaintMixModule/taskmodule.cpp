#include "taskmodule.h"

TaskModule::TaskModule(QObject *parent) : QObject(parent)
{

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

QString TaskModule::scaleSmall()
{
    return m_scaleSmall;
}

QString TaskModule::scaleBig()
{
    return m_scaleBig;
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
