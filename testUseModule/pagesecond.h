#ifndef PAGESECOND_H
#define PAGESECOND_H

#include <QObject>
#include <QMetaObject>
#include "control/motionworker.h"

class PageSecond : public QObject
{
    Q_OBJECT
public:
    explicit PageSecond(QObject *parent = nullptr);
    Q_INVOKABLE void moveAsix(QString num);
    Q_INVOKABLE void openMiddleTankToOutsidePump();
    Q_INVOKABLE void closeMiddleTankToOutsidePump();
    Q_INVOKABLE void openMiddleTankAddWaterPump();
    Q_INVOKABLE void closeMiddleTankAddWaterPump();
    Q_INVOKABLE void openMiddleTankMix();
    Q_INVOKABLE void closeMiddleTankMix();

signals:

public slots:
};

#endif // PAGESECOND_H
