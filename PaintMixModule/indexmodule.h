#ifndef INDEXMODULE_H
#define INDEXMODULE_H

#include <QObject>
#include <QDebug>
#include <QMetaType>
#include <QMetaEnum>
#include "utils/errorhandle.h"

class IndexModule : public QObject
{
    Q_OBJECT
    // 设置属性， 通知qml 初始化已经完成或正在进行中
    Q_PROPERTY(bool initialization READ getInitialization WRITE setIsnitialization NOTIFY initializationChanged)
    // 设置属性， 通知 qml 需要弹出窗口处理错误
    Q_PROPERTY(bool systemError READ getSystemError WRITE setSystemError NOTIFY systemErrorChanged)
    // 设置属性， 通知 qml 错误处理的窗口显示的内容
    Q_PROPERTY(QString systemErrorMessage READ getSystemErrorMessage WRITE setSystemErrorMessage NOTIFY systemErrorMessageChanged)
public:
    explicit IndexModule(QObject *parent = nullptr);
    bool getInitialization();
    void setIsnitialization(bool status);

    bool getSystemError();
    void setSystemError(bool status);

    QString getSystemErrorMessage();
    void setSystemErrorMessage(QString msg);

signals:
    void initializationChanged();
    void systemErrorChanged();
    void systemErrorMessageChanged();

public slots:
    // 接受广播，然后做对应的动作
    void getErrorBroadCast(ErrorHandle::errorType type);

private:
    bool m_Initialization;
    bool m_SystemError;
    QString m_SystemErrorMessage;
};

#endif // INDEXMODULE_H
