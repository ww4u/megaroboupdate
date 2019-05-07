
#include "block.h"
#include "xframe.h"
#include <QFile>

Block::Block(QObject *parent):
    XFrame( parent )
{

}
Block::Block(const QString& strPath, const QString& outFileName, QObject *parent):
    XFrame(strPath, outFileName, parent)
{

}
