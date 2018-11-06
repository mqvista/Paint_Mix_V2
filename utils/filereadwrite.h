#ifndef FILEREADWRITE_H
#define FILEREADWRITE_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomDocument>


class FileReadWrite : public QObject
{
    Q_OBJECT
public:
    explicit FileReadWrite(QObject *parent = nullptr);
    bool readProfileLists(QList<QString> *list);
    bool readProfileDetail(QString name, QMap<quint16, QMap<QString, QString>> *detail, qint16 *detailLength);
    bool deleteProfileDetail(QString name);
    bool insertProfileDetail(QString name, QMap<quint16, QMap<QString, QString>> detail, qint16 detailLength);
    bool replaceProfileDetail(QString name, QMap<quint16, QMap<QString, QString>> detail, qint16 detailLength);

private:
    QString confPath = "";
    QString profilePath = "profile.xml";
};

#endif // FILEREADWRITE_H
