#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include "control/scalesworker.h"

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QObject *parent = nullptr);
    ~Service();


signals:

public slots:

private:
    QThread scalesWorkerThread;
};

#endif // SERVICE_H
