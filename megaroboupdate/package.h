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
    //! compress func
    Package(const QString& strPath, const QString& outFileName, QObject *parent);
    //! uncompress func
    Package(const QString& strPath, QObject *parent = nullptr);

    virtual int compressFile();
    virtual int uncompressFile();

    void insertFile( const QString &fileName );
    void insertEntity(Entity *entity );

private:
    QStringList mFileList;

    /* 压缩时候的entity */
    QList<Entity *> mEntityList;

    /* 解压缩出来的entity */
    QList<Entity *> mOutEntityList;

    int _loadIn();

    int splitEntity();

    int _save();

    int unpackingToEntity(Package *pk);

protected:
    int loadIn(QByteArray &bA);
    int save();
};

#endif // PACKAGE_H
