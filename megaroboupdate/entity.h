#ifndef ENTITY_H
#define ENTITY_H

#include "xframe.h"

class Entity : public XFrame
{
    Q_OBJECT
public:
    explicit Entity(QObject *parent = nullptr);
    Entity(const QString& strPath, const QString& outFileName, QObject *parent = nullptr);

    virtual int compressFile();
    virtual int save();

    /* 提取源码 */
    int extractSource();



protected:
    int loadIn( QByteArray &bA );


};

#endif // ENTITY_H
