#ifndef BLOCK_H
#define BLOCK_H

#include "xframe.h"

class Block : public XFrame
{
    Q_OBJECT
public:
    explicit Block(QObject *parent = nullptr);
    Block(const QString& strPath, const QString& outFileName, QObject *parent = nullptr);

public:

};

#endif // BLOCK_H
