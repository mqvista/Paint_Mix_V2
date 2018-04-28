#ifndef INDEXMODULE_H
#define INDEXMODULE_H

#include <QObject>
#include <QDebug>

class IndexModule : public QObject
{
    Q_OBJECT
    // 设置属性， 通知qml 初始化已经完成或正在进行中
    Q_PROPERTY(bool initialization READ getInitialization WRITE setIsnitialization NOTIFY initializationChanged)
public:
    explicit IndexModule(QObject *parent = nullptr);
    bool getInitialization();
    void setIsnitialization(bool status);

signals:
    void initializationChanged();

public slots:

private:
    bool m_Initialization;
};

#endif // INDEXMODULE_H
