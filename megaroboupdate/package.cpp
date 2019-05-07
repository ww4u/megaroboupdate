
#include "package.h"
#include <QFile>
#include "entity.h"
#include "block.h"
#include "common.h"

Package::Package(QObject *parent):
    XFrame( parent )
{
    mSections = 0;
    mFormat = Format::QCompressed;
    mSize = 0;
}

//! compress
Package::Package(const QString& strPath, const QString& outFileName, QObject *parent):
    XFrame(strPath, outFileName, parent)
{
}

//! uncompress
Package::Package(const QString& strPath, QObject *parent)
{
    filePath = strPath;
    mSections = 0;
    mFormat = Format::QCompressed;
    mSize = 0;
}

int Package::compressFile()
{
    qDebug() << "Enter Package Compress";
    QByteArray ba;
    if(loadIn(ba) != 0){
        qDebug() << "package loadin error";
        return -1;
    }

    if( mFormat == Format::QCompressed ){
        QByteArray t = qCompress( mPayload );
        mPayload.clear();
        mPayload = t;
        mSize = mPayload.size();
    }else if( mFormat == Format::InCompressed ){

    }

    //! output data
    this->packetData();

    if(save() != 0){
        qDebug() << "save fail";
        return -1;
    }
    qDebug() << "Package Compress Success";
    return 0;
}

int Package::uncompressFile()
{
    qDebug() << "Enter Package Uncompress";
    if(_loadIn() != 0){
        return -1;
    }

    if(unpackingToEntity(this) != 0){
        return -1;
    }

    _save();
    qDebug() << "Package Uncompress Success";
}

void Package::insertFile( const QString &fileName )
{
    mFileList.append( fileName );
}

void Package::insertEntity( Entity *entity )
{
    mEntityList .append( entity );
}
//！ 解压的时候调用改函数获得原始数据
int Package::_loadIn()
{
    QFile f(filePath);
    if( !f.exists() ){
        qDebug() << "File Not Exist";
        return -1;
    }
    if (!f.open(QIODevice::ReadOnly)){
        qDebug() << "Open error";
        return -1;
    }

    QByteArray ba = f.readAll();
    mDescription = QString::fromLocal8Bit(ba.mid( 0, DESCRIPTION_SIZE ));
    mId          = byteArrayToInt(ba.mid( DESCRIPTION_SIZE, 4 ));
    mSize        = byteArrayToInt(ba.mid( DESCRIPTION_SIZE+4, 4 ));
    mCheck       = byteArrayToInt(ba.mid( DESCRIPTION_SIZE+8, 4 ));
    mFormat      = byteArrayToInt(ba.mid( DESCRIPTION_SIZE+12, 4 ));
    mSections    = byteArrayToInt(ba.mid( DESCRIPTION_SIZE+16, 4 ));
    mPayload     = ba.mid( DESCRIPTION_SIZE+20, mSize );

    if(mFormat == QCompressed){
        mPayload = qUncompress(mPayload);
        mSize    = mPayload.size();
    }else{}

    //! check
    quint32 u32tmp = getCRC((unsigned char*)(mPayload.data()), mSize);
    if(u32tmp != mCheck){
        qDebug() << "_loadin check error";
        return -1;
    }

    f.close();
    return 0;
}

//!
int Package::splitEntity()
{
    return 0;
}

//! 压缩文件的时候需要获得entity的数据调用此函数
int Package::loadIn(QByteArray &bA)
{
    if(mEntityList.size() <= 0)
        return -1;

    foreach (Entity *e, mEntityList) {
        mPayload.append(e->mDescription.toLocal8Bit().data(), DESCRIPTION_SIZE);
        mPayload.append((char *)&(e->mId), 4);
        mPayload.append((char *)&(e->mSize), 4);
        mPayload.append((char *)&(e->mCheck), 4);
        mPayload.append((char *)&(e->mFormat), 4);
        mPayload.append((char *)&(e->mSections), 4);
        mPayload.append( e->mPayload );
        mSections += 1;
    }
    mId = MCT_PACKAGE;
    mSize = mPayload.size();
    if(generateCheckCode(mPayload, mCheck) != 0){
        return -1;
    }
    mFormat = QCompressed;

    return 0;
}
#include <QDir>
/* 压缩时调用 */
int Package::save()
{
    if(mOutFileName.isEmpty()){
        mOutFileName = QDir::currentPath() + "/package.package";
    }
    QFile f(mOutFileName);
    if (!f.open(QIODevice::WriteOnly)){
        return -1;
    }
    f.write( mOutputData );
    f.close();

    return 0;
}
/* 将package解包成entity--->mOutEntityList */
int Package::unpackingToEntity(Package *pk)
{
    for(int i = 0; i < pk->mSections; i++){
        Entity *e = new Entity;
        e->mDescription = QString::fromLocal8Bit(pk->mPayload.mid( 0, DESCRIPTION_SIZE ));
        e->mId = byteArrayToInt(pk->mPayload.mid( DESCRIPTION_SIZE, 4 ));
        e->mSize = byteArrayToInt(pk->mPayload.mid( DESCRIPTION_SIZE+4, 4 ));
        e->mCheck = byteArrayToInt(pk->mPayload.mid( DESCRIPTION_SIZE+8, 4 ));
        e->mFormat = byteArrayToInt(pk->mPayload.mid( DESCRIPTION_SIZE+12, 4 ));
        e->mSections = byteArrayToInt(pk->mPayload.mid( DESCRIPTION_SIZE+16, 4 ));
        e->mPayload = pk->mPayload.mid( DESCRIPTION_SIZE+20, e->mSize );
        mOutEntityList.append(e);
        pk->mPayload = pk->mPayload.mid(DESCRIPTION_SIZE+20+e->mSize);
    }
    return 0;
}

#include <QCoreApplication>
/* 将解析出来的各个entity提取出源码 */
/* 解压时调用 */
int Package::_save()
{
    for(int i = 0; i < mOutEntityList.size(); i++){
        if(mOutEntityList.at(i)->mId == MCT_MRQ){
            mOutEntityList.at(i)->mOutFileName = qApp->applicationDirPath() + QString("/entity_%1.upd").arg(i);
        }else if( mOutEntityList.at(i)->mId == MCT_MRH ){
            mOutEntityList.at(i)->mOutFileName = qApp->applicationDirPath() + QString("/entity_%1.mrh").arg(i);
        }
        mOutEntityList.at(i)->extractSource();
    }

    return 0;
}
