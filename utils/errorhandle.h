#ifndef ERRORHANDLE_H
#define ERRORHANDLE_H

#include <QObject>
#include <QQueue>
#include <QDateTime>
#include <QTimer>

class ErrorHandle : public QObject
{
    Q_OBJECT
public:
    static ErrorHandle *Instance();
    ~ ErrorHandle();
    enum errorType{
        ERROR_RS485_NOT_FOUND,
        ERROR_RS485_NOT_OPEN,
        ERROR_RS485_OPEN_FAILED,
        ERROR_RS485_NOT_CONNECTED,
        ERROR_RS485_NO_RESPONSE,
        ERROR_RS485_LINK_LOST,

        ERROR_SMALL_SCALE_NOT_FOUND,
        ERROR_SMALL_SCALE_NOT_OPENED,
        ERROR_SMALL_SCALE_NOT_CONNECTED,
        ERROR_SMALL_SCALE_NO_RESPONSE,
        ERROR_SMALL_SCALE_LINK_LOST,

        ERROR_BIG_SCALE_NOT_FOUND,
        ERROR_BIG_SCALE_NOT_OPENED,
        ERROR_BIG_SCALE_NOT_CONNECTED,
        ERROR_BIG_SCALE_NO_RESPONSE,
        ERROR_BIG_SCALE_LINK_LOST,

        ERROR_ROTARY_AXIS_TIMEOUT,
        ERROR_ROTARY_ENCODER,
        ERROR_ROTARY_AXIS_LIMIT,
        ERROR_ROTARY_INIT_FAILED,
        ERROR_BOARD_INIT_FAILED,

        ERROR_SCALE_OPEN_FAILED,
        ERROR_SCALE_NOT_FOUND,
        ERROR_TANK_IS_EMPTY_OR_TANK_SENSER_ERROR,
        ERROR_TANK_WILL_OVER_LIMIT,
        ERROR_UNKNOWN
    };
    Q_ENUM(errorType)

    Q_INVOKABLE void init();
    // 收集错误信息
    Q_INVOKABLE void collectionError(errorType type);

private:
    explicit ErrorHandle(QObject *parent = nullptr);
    // 错误队列的类型
    struct errorQueueType
    {
        errorType type;
        QDateTime dataTime;
        bool isSloved;
        bool isBroadCasted;
    };
    // 声明一个错误队列
    QQueue<errorQueueType> errorQueue;
    void checkQueue();
    QTimer *m_loopTimer;

signals:
    // 广播错误信息到界面
    void broadCastError(errorType type);
    // 发送到worker去处理错误
    void sendError(errorType type);

public slots:
    void getErrorMessageRetry();

};

#endif // ERRORHANDLE_H
