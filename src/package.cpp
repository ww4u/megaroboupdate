
#include "package.h"
#include <QFile>
#include "entity.h"
#include "common.h"
#include "crc32check.h"
#include <QDebug>
#include <QDir>

Package::Package(QObject *parent):
    XFrame( parent )
{
    mSections = 0;
    mSize = 0;
}

void Package::insertEntity( Entity *entity )
{
    mEntityList .append( entity );
}

void Package::init()
{
    mDescription;
    mDescLen = mDescription.length();

    mId = PACKAGE;

    mFormat = QCOMPRESSED;
    mSections = mEntityList.size();

    mPayload.clear();
    QByteArray t;
    //! \todo
    foreach (Entity *e, mEntityList) {
        t.append( (char *)&( e->mDescLen ), 4);
        t.append(e->mDescription.toLocal8Bit().data(), e->mDescLen);
        t.append((char *)&(e->mId), 4);
        t.append((char *)&(e->mSize), 4);
        t.append((char *)&(e->mCheck), 4);
        t.append((char *)&(e->mFormat), 4);
        t.append((char *)&(e->mSections), 4);
        t.append( e->mPayload );
    }
    mCheck = getCRC( (quint8*)( t.data() ), t.size() );
    mPayload = qCompress(t);
    mSize = mPayload.size();
}
int Package::packet( QString path )
{
    qDebug() << tr( "Notify: Start Packet" );
    QByteArray t;
    t.append( (char *)&mDescLen, 4 );
    t.append( mDescription.toLocal8Bit().data(), mDescLen );
    t.append((char *)&mId, 4);
    t.append((char *)&mSize, 4);
    t.append((char *)&mCheck, 4);
    t.append((char *)&mFormat, 4);
    t.append((char *)&mSections, 4);
    t.append( mPayload );

    QFile f( path );
    if( f.open( QIODevice::ReadWrite ) ){

    }else{
        qDebug() << f.errorString();
        return -1;
    }

    f.write( t );
    f.close();

    qDebug() << tr( "Notify: Packet Complete" );

    return 0;
}
int Package::loadFile(QString path, QByteArray &baLoad)
{
    QFile file( path );
    if( file.open( QIODevice::ReadOnly ) ){

    }else{
        return -1;
    }

    QByteArray ba = file.readAll();
    if(ba.isEmpty())
        return -1;
    baLoad = ba;

    return 0;
}
void Package::_init(QByteArray &baLoad)
{
    mDescLen =  byteArrayToInt( baLoad.mid( 0, 4 ) );
    mDescription = QString::fromLocal8Bit( baLoad.mid( 4, mDescLen ) );
    mId = byteArrayToInt( baLoad.mid( 4+mDescLen, 4 ) );
    mSize = byteArrayToInt( baLoad.mid( 4+mDescLen+4, 4 ) );
    mCheck = byteArrayToInt( baLoad.mid( 4+mDescLen+4+4, 4 ) );
    mFormat = byteArrayToInt( baLoad.mid( 4+mDescLen+4+4+4, 4 ));
    mSections = byteArrayToInt( baLoad.mid( 4+mDescLen+4+4+4+4, 4 ));
    mPayload = baLoad.mid( 4+mDescLen+4+4+4+4+4, mSize );
}
int Package::unpacket()
{
    qDebug() << tr("Notify: Start Unpacket");

    if( mId != PACKAGE ){
        qDebug() << tr( "Notify: Invalid File" );
        return -1;
    }

    QByteArray tPayload = qUncompress( mPayload );

    quint32 iTmp = getCRC( (quint8*)(tPayload.data()), tPayload.size() );
    if( iTmp != mCheck ){
        qDebug()<< tr("Error: Check Fail");
        return -1;
    }

    getEntity( tPayload );

    if( saveEntityFile() < 0 ){
        qDebug() << tr("Error: Unpacket Fail");
        return -1;
    }

    qDebug() << tr("Notify: Unpacket Completed");
    return 0;
}
void Package::getEntity(QByteArray &in)
{
    for( quint32 i=0; i< mSections; i++ )
    {
        Entity *e = new Entity(this);
        e->mDescLen = byteArrayToInt( in.mid(0, 4) );
        e->mDescription = QString::fromLocal8Bit( in.mid( 4, e->mDescLen ) );
        e->mId = byteArrayToInt(in.mid( 4+e->mDescLen, 4 ));
        e->mSize = byteArrayToInt(in.mid( 4+e->mDescLen+4, 4 ));
        e->mCheck = byteArrayToInt(in.mid( 4+e->mDescLen+4+4, 4 ));
        e->mFormat = byteArrayToInt(in.mid( 4+e->mDescLen+4+4+4, 4 ));
        e->mSections = byteArrayToInt(in.mid( 4+e->mDescLen+4+4+4+4, 4 ));
        e->mPayload = in.mid( 4+e->mDescLen+4+4+4+4+4, e->mSize );
        mOutEntityList.append( e );
        in = in.mid( 4+e->mDescLen+4+4+4+4+4+e->mSize );
    }
}
int Package::saveEntityFile()
{
    if( mOutEntityList.size()<1 ){
        return -1;
    }
    foreach ( Entity *e, mOutEntityList) {
        QByteArray t;
        t.append( (char *)(&(e->mDescLen)), 4 );
        t.append( e->mDescription.toLocal8Bit().data(), e->mDescLen );
        t.append( (char *)(&(e->mId)), 4 );
        t.append((char *)&(e->mSize), 4);
        t.append((char *)&(e->mCheck), 4);
        t.append((char *)&(e->mFormat), 4);
        t.append((char *)&(e->mSections), 4);
        t.append( e->mPayload );

        QDir dir;
        QString fileName;
        bool b = dir.mkpath( QDir::tempPath() + "/output" );
        if( !b ){
            return -1;
        }

        if( e->mId == MRH_ENTITY ){
            fileName = "mrh.dat";
        }else if( e->mId == MRQ_ENTITY ){
            fileName = "mrq.dat";
        }else if( e->mId == MCT_ENTITY ){
            fileName = "mct.dat";
        }else if( e->mId == PACKAGE ){

        }else{}

        QFile f( QDir::tempPath() + "/output/" + fileName );
        if( !f.open( QIODevice::WriteOnly ) ){
            return -1;
        }
        f.write( t );
        f.close();
    }

    return 0;
}
