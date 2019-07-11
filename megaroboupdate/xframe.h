#ifndef XFRAME_H
#define XFRAME_H

#include <QObject>

//! 数据是否进行压缩，默认使用qCompress进行压缩
enum FORMAT{
    NORMAL,
    QCOMPRESSED
};

enum ID{
    MRH_ENTITY,
    MRQ_ENTITY,
    MCT_ENTITY,
    PACKAGE
};

class XFrame : public QObject
{
    Q_OBJECT
public:
    explicit XFrame(QObject *parent = nullptr);

    virtual int loadFile();

    virtual void setDesc(QString &desc);
    virtual void setId( ID id );

signals:

public slots:

public:
    //! data
    int mDescLen;
    QString mDescription;       /* DESCRIPTION_SIZE */
    quint32 mId;                /* ID */
    quint32 mSize;              /* payload size */
    quint32 mCheck;             /* crc32Check */
    quint32 mFormat;            /* qCompress */
    quint32 mSections;          /* section num */
    QByteArray mPayload;        /* source data */
};

#endif // XFRAME_H
