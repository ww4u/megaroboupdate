#ifndef COMMON_H
#define COMMON_H

#include <QByteArray>

/*  */
enum Endian
{
    LittileEndian,
    BigEndian
};

int byteArrayToInt(QByteArray arr,  Endian endian = LittileEndian);

#endif // COMMON_H
