#include "taskmodule.h"

TaskModule::TaskModule(QObject *parent) : QObject(parent)
{

}

void TaskModule::test()
{
    qDebug()<< "Do somethings";
    QMetaObject::invokeMethod(MotionWorker::Instance(), "addWater",
                              Qt::AutoConnection,
                              Q_ARG(quint32, 10),
                              Q_ARG(quint8, 1));
}
