#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "control/scalesworker.h"
#include "control/motionworker.h"

//module
#include "PaintMixModule/taskmodule.h"

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QQmlApplicationEngine *appEng, QObject *parent = nullptr);
    ~Service();
    void initContext();


signals:

public slots:

private:
    QQmlApplicationEngine *m_engine;
    QThread scalesWorkerThread;
    QThread motionWorkerThread;

    //module
    TaskModule m_TaskModule;

};

#endif // SERVICE_H
