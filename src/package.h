#ifndef PACKAGE_H
#define PACKAGE_H

#include "xframe.h"
#include <QList>
#include <entity.h>

class Package : public XFrame
{
    Q_OBJECT
public:
    explicit Package(QObject *parent = nullptr);

    /* 获取entity的值，初始化package */
    void insertEntity(Entity *entity );
    void init();
    int packet(QString path);

    /* unpacket */
    int loadFile(QString path, QByteArray &baLoad);
    void _init( QByteArray &baLoad );
    int unpacket();
    void getEntity( QByteArray &in );
    int saveEntityFile();

private:
    QStringList mFileList;

    /* 压缩时候的entity */
    QList<Entity *> mEntityList;

    /* 解压缩出来的entity */
    QList<Entity *> mOutEntityList;

protected:

};

#endif // PACKAGE_H
