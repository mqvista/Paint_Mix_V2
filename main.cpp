#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "utils/filereadwrite.h"

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    //qputenv("QT_VIRTUALKEYBOARD_STYLE", QByteArray("retro"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    FileReadWrite frw;
    frw.readProfileLists();

    return app.exec();
}
