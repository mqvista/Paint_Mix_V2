#ifndef LOGINFO_H
#define LOGINFO_H

#include <QObject>
#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDate>

class LogInfo
{
public:
    LogInfo();
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static void saveToFile(QString *logString);
private:
    QMutex mutex;
};

#endif // LOGINFO_H
