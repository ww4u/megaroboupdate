
#include "entity.h"
#include <QFile>
#include "crc32check.h"
#include <QDebug>

Entity::Entity(QObject *parent):
    XFrame( parent )
{

}

int Entity::init( QString path )
{
    QByteArray ba;
    if( loadFile( path, ba ) !=0 ){
        qDebug() << tr( "Error : Invalid File" );
        return -1;
    }

    pickUpData( ba );
}

void Entity::setId( ID id )
{
    this->mId = id;
}

int Entity::loadFile(QString path, QByteArray &baLoad)
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

void Entity::pickUpData(QByteArray &in)
{
    mDescLen = mDescription.length();
    mDescription;

    mId;    /*  */

    mSize = in.size();

    mFormat = NORMAL;

    mSections = 1;

    mPayload = in;

    mCheck = getCRC( (quint8*)( in.data() ), in.length() );

}
