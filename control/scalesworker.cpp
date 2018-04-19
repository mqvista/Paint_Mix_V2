#include "scalesworker.h"

ScalesWorker *ScalesWorker::Instance()
{
    static QMutex mutex;
    static QScopedPointer<ScalesWorker> instance;
    if (Q_UNLIKELY(!instance)) {
        mutex.lock();
        if (!instance) {
            instance.reset(new ScalesWorker);
        }
        mutex.unlock();
    }
    return instance.data();
}

ScalesWorker::~ScalesWorker()
{
    scalesBigThread.quit();
    scalesBigThread.wait();
    scalesSmallThread.quit();
    scalesSmallThread.wait();
}

ScalesWorker::ScalesWorker(QObject *parent) : QObject(parent)
{
    m_scalesBig.goToThread(&scalesBigThread);
    m_scalesSmall.goToThread(&scalesSmallThread);

    //秤开启和关闭信号
    connect(this, &ScalesWorker::scalesBigOpenSig, &m_scalesBig, &ScalesBig::scalesOpenSlot);
    connect(this, &ScalesWorker::scalesBigCloseSig, &m_scalesBig, &ScalesBig::scalesCloseSlot);
    connect(this, &ScalesWorker::scalesSmallOpenSig, &m_scalesSmall, &ScalesSmall::scalesOpenSlot);
    connect(this, &ScalesWorker::scalesSmallCloseSig, &m_scalesSmall, &ScalesSmall::scalesCloseSlot);
    //秤接收数据信号
    connect(&m_scalesBig, &ScalesBig::receiveDataPush, this, &ScalesWorker::getScalesBigDataSlot);
    connect(&m_scalesSmall, &ScalesSmall::receiveDataPush, this, &ScalesWorker::getScalesSmallDataSlot);
}

//开启小秤
void ScalesWorker::scalesSmallOpen(QString name, quint32 baud)
{
    emit scalesSmallOpenSig(name, baud);
}

//开启大秤
void ScalesWorker::scalesBigOpen(QString name, quint32 baud)
{
    emit scalesBigOpenSig(name, baud);
}

void ScalesWorker::scalesSmallClose()
{
    emit scalesSmallCloseSig();
}

void ScalesWorker::scalesBigClose()
{
    emit scalesBigCloseSig();
}

void ScalesWorker::getScalesBigDataSlot(double value, QString unit)
{
    m_BigScalesValue = value;
    m_BigScalesUnit = unit;
    emit scalesBigDataChangedSig(m_BigScalesValue);
}

void ScalesWorker::getScalesSmallDataSlot(double value, QString unit)
{
    m_SmallScalesValue = value;
    m_SmallScalesUnit = unit;
    emit scalesSmallDataChangedSig(m_SmallScalesValue);
}



