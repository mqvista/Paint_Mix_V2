#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "utils/filereadwrite.h"

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    FileReadWrite frw;

//    frw.deleteProfileDetail("CCCC");

    QMap<QString, QString> aaa;
    aaa.insert("water", "100");
    aaa.insert("wwwww", "100");
    aaa.insert("tttt", "100");
    QMap<quint16, QMap<QString, QString>> asdf;
    asdf.insert(1, aaa);
    asdf.insert(2, aaa);

    qDebug() << frw.insertProfileDetail("testU2se", asdf, 2);

    return app.exec();
}