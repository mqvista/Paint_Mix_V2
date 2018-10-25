#include "indexmodule.h"

IndexModule::IndexModule(QObject *parent) : QObject(parent)
{
    connect(ErrorHandle::Instance(), &ErrorHandle::broadCastError, this, &IndexModule::getErrorBroadCast);
    m_Initialization = false;
    m_SystemError = false;

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

bool IndexModule::getSystemError()
{
    return m_SystemError;
}

void IndexModule::setSystemError(bool status)
{
    m_SystemError = status;
    emit systemErrorChanged();
}

QString IndexModule::getSystemErrorMessage()
{
    return m_SystemErrorMessage;
}

void IndexModule::setSystemErrorMessage(QString msg)
{
    m_SystemErrorMessage = msg;
    emit systemErrorMessageChanged();
}

void IndexModule::getErrorBroadCast(ErrorHandle::errorType type)
{
    // 反射获取枚举的key
    QMetaEnum me = QMetaEnum::fromType<ErrorHandle::errorType>();
    // 通知界面 显示错误讯息
    setSystemErrorMessage(me.key(type));
    setSystemError(true);
    return;
}
