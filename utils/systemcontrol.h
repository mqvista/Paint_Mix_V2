#ifndef SYSTEMCONTROL_H
#define SYSTEMCONTROL_H

#include <QObject>
#include <QProcess>

class SystemControl : public QObject
{
    Q_OBJECT
public:
    explicit SystemControl(QObject *parent = nullptr);
    Q_INVOKABLE void systemReboot();
    Q_INVOKABLE void systemShutdown();

signals:

public slots:

private:
    QProcess process;
};

#endif // SYSTEMCONTROL_H
