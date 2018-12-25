#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "service.h"
#include "utils/loginfo.h"
#include "utils/filereadwrite.h"

int main(int argc, char *argv[])
{
    //LogInfo logInfo;
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Service service(&engine);
    qDebug() << "Main thread" << QThread::currentThreadId() << endl;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    service.needRunafterQmlLoaded();
    return app.exec();
}
