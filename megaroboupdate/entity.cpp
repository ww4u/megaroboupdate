
#include "entity.h"
#include <QFile>

Entity::Entity(QObject *parent):
    XFrame( parent )
{

}
Entity::Entity(const QString& strPath, const QString& outFileName, QObject *parent):
    XFrame(strPath, outFileName, parent)
{

}

int Entity::compressFile()
{
    QByteArray bAPayload;
    if( this->loadIn(bAPayload) !=0 ){
        qDebug() << "Error: loadIn error";
        return -1;
    }

    mSize = bAPayload.size();
    mPayload = bAPayload;

    //! 生成校验码
    if( generateCheckCode( mPayload, mCheck ) != 0 ){
        qDebug() << "Error: generate code error";
        return -1;
    }

    mFormat = Format::InCompressed;
    mSections = 1;

    //! packet data
    if (packetData() != 0){
        return -1;
    }

    //! save
    if(save() != 0)
        return -1;

    return 0;
}

int Entity::save()
{
    return 0;
}

int Entity::loadIn( QByteArray &bA )
{
    //!
    QFile f( filePath );
    if( !f.exists() ){
        qDebug() << "Error: File not exist";
        return -1;
    }

    if (!f.open(QIODevice::ReadOnly)){
        qDebug() << QString("Error: %1 open error").arg(filePath);
        return -1;
    }

    bA = f.readAll();
    if( bA.isEmpty() )
        return -1;
    f.close();

    return 0;
}
#include <QFileInfo>
#include <QDir>
/* 解压时提取出源代码 */
int Entity::extractSource()
{
    QFile f(mOutFileName);
    QFileInfo info(mOutFileName);
    //qDebug() << info.absolutePath() << info.absoluteFilePath();
    QDir dir;
    dir.mkpath(info.absolutePath());

    if(!f.open(QIODevice::WriteOnly)){
        return -1;
    }
    f.write(mPayload);
    f.close();

    return 0;
}
