
#include "xframe.h"
#include <QFile>
#include <QByteArray>
#include <common.h>

XFrame::XFrame(QObject *parent) :
    QObject(parent),
    mFormat(Format::QCompressed),
    mSize(0),
    mSections(0),
    mId(1)
{

}
XFrame::XFrame(const QString& strPath, const QString& outFileName, QObject *parent):
    filePath( strPath ),
    mOutFileName( outFileName ),
    mSections( 0 ),
    mFormat(Format::QCompressed),
    mSize(0),
    mId(1)
{

}

int XFrame::compressFile()
{
    return 0;
}

int XFrame::uncompressFile()
{
    return 0;
}

int XFrame::loadIn( QByteArray &bA )
{
    return 0;
}

void XFrame::setDescription( const QString &des )
{
    mDescription = des;
}

int XFrame::iCalCrc32Check()
{
    return 0;
}

int XFrame::packetData()
{
    mOutputData.clear();
    if( mDescription.size() > DESCRIPTION_SIZE ){
        qDebug() << "Error: Description Too Large";
        return -1;
    }
    mOutputData.append( mDescription.toLocal8Bit().data(), DESCRIPTION_SIZE );
    mOutputData.append((char *)&mId, 4);
    mOutputData.append((char *)&mSize, 4);
    mOutputData.append((char *)&mCheck, 4);
    mOutputData.append((char *)&mFormat, 4);
    mOutputData.append((char *)&mSections, 4);
    mOutputData.append( mPayload );

    return 0;
}
int XFrame::save()
{
    return 0;
}
int XFrame::generateCheckCode(QByteArray &baSource, quint32 &out)
{
    if( !baSource.isEmpty() ){
        unsigned char*buf = (unsigned char*)(baSource.data());
        out = getCRC(buf, baSource.size());
        return 0;
    }
    return -1;
}
