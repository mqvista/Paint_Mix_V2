#ifndef MOTIONWORKER_H
#define MOTIONWORKER_H

#include <QObject>
#include <QMutex>
#include "motion.h"

class MotionWorker : public QObject
{
    Q_OBJECT
public:
    static MotionWorker *Instance();
    Q_INVOKABLE void openSerial485();
    Q_INVOKABLE void closeSerial485();
    Q_INVOKABLE void addWater(quint32 weight, quint8 scalesNum);
    Q_INVOKABLE void initAsix(quint8 motorNum);
    Q_INVOKABLE void liquidOut(quint8 motorNum, quint32 weight, quint8 scalesNum);

private:
    explicit MotionWorker(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MOTIONWORKER_H
