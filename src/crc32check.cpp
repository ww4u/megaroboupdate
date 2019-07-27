
#include "crc32check.h"

quint32 getCRC(unsigned char* buf, int nLength)
{
    if (nLength < 1)
        return 0xffffffff;

    quint32 crc = 0;

    for (int i(0); i != nLength; ++i)
    {
        crc = table[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
    }

    crc = crc ^ 0xffffffff;

    return crc;
}
