#ifndef DRIVERGC_H
#define DRIVERGC_H

#include "Functions.h"
#include "Protocol.h"
#include "drivergc_global.h"
#include <QByteArray>
#include <QDebug>
#include <QMutex>
#include <QScopedPointer>
#include <iostream>
#include <qstring.h>

class DRIVERGCSHARED_EXPORT DriverGC : public Functions {
public:
    static DriverGC* Instance();

protected:
    DriverGC();
};

#endif // DRIVERGC_H
