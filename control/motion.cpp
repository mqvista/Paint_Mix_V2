#include "motion.h"

Motion::Motion()
{

}

// Open DriverGC Serial Port
// Param1: Target Serial port url
// Param2: Target Serial port baud
void Motion::openSerial485(QString port, quint32 baud)
{
    DriverGC::Instance()->Open(port, baud);
    connect(DriverGC::Instance(), &DriverGC::ErrorOut, this, &Motion::serial485Error);
}

// Close DriverGc Serial Port
// No Params
void Motion::closeSerial485()
{
    DriverGC::Instance()->Close();
}

// Get Serial 485 error message from DriverGC signal
// Param1: Error message main
// Param2: Error message sub
void Motion::serial485Error(QString msg1, QString msg2)
{
    qDebug() << msg1;
    qDebug() << msg2;
}
