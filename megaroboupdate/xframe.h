#ifndef XFRAME_H
#define XFRAME_H

#include <QObject>
#include <QDebug>
#include "crc32check.h"

#define DESCRIPTION_SIZE    100

enum Format{
    QCompressed,
    InCompressed
};

enum ID{
    MCT_MRH,
    MCT_MRQ,
    MCT_TOOLSET,
    MCT_BLOCK,
    MCT_ENTITY,
    MCT_PACKAGE
};

class XFrame : public QObject
{
    Q_OBJECT
public:
    explicit XFrame(QObject *parent = nullptr);
    XFrame(const QString& strPath, const QString& outFileName, QObject *parent = nullptr);

    virtual int compressFile();
    virtual int uncompressFile();
    virtual int packetData();

    void setDescription( const QString &des );
    void setFormat( Format f ){ mFormat = f; }
    
    //! default MCT_MRQ
    void setID(ID id){ mId = id; }
    virtual int generateCheckCode(QByteArray &baSource, quint32 &out);

signals:

public slots:

public:
    QString filePath;           /* input */
    QString mOutFileName;       /* output */

    virtual int save();
    void setOutFilePath( const QString &str ){ mOutFileName = str; }
    void setFilePath( const QString &str ){ filePath = str; }
public:

    //! data
    int mDescLen;
    QString mDescription;   /* DESCRIPTION_SIZE */
    quint32 mId;            /* ID */
    quint32 mSize;          /* payload size */
    quint32 mCheck;         /* crc32Check */
    quint32 mFormat;        /* default Format::QCompressed */
    quint32 mSections;      /* section num */
    QByteArray mPayload;    /* source data */
    QByteArray mOutputData; /* packet data */

protected:
    virtual int loadIn(QByteArray &bA);


    virtual int iCalCrc32Check();   /* 生成校验码 */
    void setSections( quint64 i ){ mSections = i; }


};

#endif // XFRAME_H
