#ifndef TASKMODULE_H
#define TASKMODULE_H

#include <QObject>
#include "control/motionworker.h"

class TaskModule : public QObject
{
    Q_OBJECT
public:
    explicit TaskModule(QObject *parent = nullptr);
    Q_INVOKABLE void test();
    Q_INVOKABLE void runFromula(QString formulaName);

signals:

public slots:
};

#endif // TASKMODULE_H
