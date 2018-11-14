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
    Q_INVOKABLE void getExternADCValue();
    Q_INVOKABLE void openPump();
    Q_INVOKABLE void closePump();

signals:

public slots:
};

#endif // PAGESECOND_H