#include "systemcontrol.h"

SystemControl::SystemControl(QObject *parent) : QObject(parent)
{

}

void SystemControl::systemReboot()
{
    process.start("sudo reboot");
    process.waitForFinished();
    process.close();
}

void SystemControl::systemShutdown()
{
    process.start("sudo poweroff");
    process.waitForFinished();
    process.close();
}
