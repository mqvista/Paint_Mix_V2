#include "indexmodule.h"

IndexModule::IndexModule(QObject *parent) : QObject(parent)
{
    m_Initialization = false;
}

bool IndexModule::getInitialization()
{
    return m_Initialization;
}

void IndexModule::setIsnitialization(bool status)
{
    //qDebug()<< "init status changed";
    m_Initialization = status;
    emit initializationChanged();
}
