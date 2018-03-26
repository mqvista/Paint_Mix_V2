#ifndef FILEREADWRITE_H
#define FILEREADWRITE_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class FileReadWrite : public QObject
{
    Q_OBJECT
public:
    explicit FileReadWrite(QObject *parent = nullptr);
    void readProfileLists();

private:
    QString confPath = "";
    QString profilePath = "./profile.xml";
};

#endif // FILEREADWRITE_H
