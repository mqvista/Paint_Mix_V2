#include "filereadwrite.h"

FileReadWrite::FileReadWrite(QObject *parent) : QObject(parent)
{

}

void FileReadWrite::readProfileLists()
{
    QFile *file = new QFile(profilePath);
    if (!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "File can't access!!";
    }
}
