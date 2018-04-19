#ifndef CONVERT_H
#define CONVERT_H

#include <QBitArray>
#include <QByteArray>
#include <QDataStream>

class Convert {
public:
    static QByteArray from(const quint8& data);
    static QByteArray from(const quint16& data);
    static QByteArray from(const quint32& data);

    static QByteArray from(const qint8& data);
    static QByteArray from(const qint16& data);
    static QByteArray from(const qint32& data);

    static QByteArray from(const QBitArray& data);

    static quint8 toquint8(const QByteArray& data);
    static quint16 toquint16(const QByteArray& data);
    static quint32 toquint32(const QByteArray& data);

    static qint8 toqint8(const QByteArray& data);
    static qint16 toqint16(const QByteArray& data);
    static qint32 toqint32(const QByteArray& data);

    static QBitArray tobool(const QByteArray& data);

private:
    Convert();
};

#endif // CONVERT_H
