#ifndef ENTITY_H
#define ENTITY_H

#include "xframe.h"

class Entity : public XFrame
{
    Q_OBJECT
public:
    explicit Entity(QObject *parent = nullptr);

    int init(QString path);

    void setId( ID id );

protected:

    int loadFile(QString path, QByteArray &baLoad);

    void pickUpData( QByteArray &in );

};

#endif // ENTITY_H
