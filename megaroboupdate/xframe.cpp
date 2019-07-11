#include "xframe.h"

XFrame::XFrame(QObject *parent) : QObject(parent)
{

}

int XFrame::loadFile()
{
    return 0;
}

void XFrame::setDesc(QString &desc)
{
    this->mDescription = desc;
}

void XFrame::setId(ID id)
{
    this->mId = id;
}
