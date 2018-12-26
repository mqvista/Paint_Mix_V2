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
    process.start("sudo shutdown -t 0");
    process.waitForFinished();
    process.close();
}
