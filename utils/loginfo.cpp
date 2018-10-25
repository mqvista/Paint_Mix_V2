#include "loginfo.h"

LogInfo::LogInfo()
{
    qInstallMessageHandler(myMessageOutput);
}

void LogInfo::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    //mutex.lock();
    QByteArray localMsg = msg.toLocal8Bit();
    QString logString = QTime::currentTime().toString();
    switch (type) {
    case QtDebugMsg:
        logString.append(QString(" Debug:%2").arg(msg));
        break;
    case QtInfoMsg:
        logString.append(QString(" Info: %1  %2  %3  %4").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        break;
    case QtWarningMsg:
        logString.append(QString(" Warning: %1  %2  %3  %4").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        break;
    case QtCriticalMsg:
        logString.append(QString(" Critical: %1  %2  %3  %4").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        break;
    case QtFatalMsg:
        logString.append(QString(" Fatal: %1  %2  %3  %4").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function));
        break;
    }
    saveToFile(&logString);
    //mutex.unlock();
}

void LogInfo::saveToFile(QString *logString)
{
    QString filename = QString("log%1.txt").arg(QDate::currentDate().toString("yyyy-MM-dd"));
    QFile logFile(filename);
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return;
    }
    QTextStream out(&logFile);
    out << *logString << "\r\n";
    //out.flush();
    logFile.close();
}
