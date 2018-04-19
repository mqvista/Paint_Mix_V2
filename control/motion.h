#ifndef MOTION_H
#define MOTION_H

#include "DriverGC.h"


class Motion : public QThread
{
public:
    Motion();
    // Open DriverGC Serial Port
    void openSerial485(QString port, quint32 baud);
    // Close DriverGc Serial Port
    void closeSerial485();

public slots:
    void serial485Error(QString msg1, QString msg2);
};

#endif // MOTION_H
