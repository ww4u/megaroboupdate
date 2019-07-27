#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QXmlStreamReader>
#include <QFile>
#include <QString>
#include "entity.h"
#include "package.h"

#define mqdbg() qDebug()

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
        case QtDebugMsg:
            fprintf(stdout, "%s\n", localMsg.constData());
            break;
        case QtInfoMsg:
            fprintf(stdout, "%s\n", localMsg.constData());
            break;
        case QtWarningMsg:
            fprintf(stdout, "%s\n", localMsg.constData());
            break;
        case QtCriticalMsg:
            fprintf(stdout, "%s\n", localMsg.constData());
            break;
        case QtFatalMsg:
            fprintf(stdout, "%s\n", localMsg.constData());
            break;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInstallMessageHandler(myMessageOutput);

    QCoreApplication::setApplicationName( QObject::tr( "Packet And Unpacket Tool" ) );
    QCoreApplication::setApplicationVersion( QObject::tr("v0.0.1.0") );

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption packetOption("c", QCoreApplication::translate("main", "Packet The File"));
    parser.addOption(packetOption);
    //<< "Source-File"
    QCommandLineOption unpacketOption("x", "Source File", "File");
    parser.addOption(unpacketOption);
    parser.process(a);

    QString desc, mrq_path, mrh_path, output_file_name, mrq_ver, mrh_ver, mct_ver;

    QString xmlPath = qApp->applicationDirPath() + "/config.xml";
    //xmlPath = "C:/Users/lwq/Desktop/pt/config.xml";

    QFile qFile( xmlPath );
    if( qFile.open( QIODevice::ReadOnly | QIODevice::Text) ){

    }else{ qDebug() << "Error: Invalid Config File"; return -1; }

    QXmlStreamReader reader( &qFile );
    while( reader.readNextStartElement() ){
        if( reader.name() == "config" ){
            while( reader.readNextStartElement() ){
                if( reader.name() == "desc" ){
                    desc = reader.readElementText();
                }else if( reader.name() == "block" ){
                    while( reader.readNextStartElement() ){
                        if( reader.name() == "mrq_path" ){
                            mrq_path = reader.readElementText();
                        }else if( reader.name() == "mrh_path" ){
                            mrh_path = reader.readElementText();
                        }else{
                            reader.skipCurrentElement();
                        }
                    }
                }else if( reader.name() == "output_file_name" ){
                    output_file_name = reader.readElementText();
                }else if( reader.name() == "mrq_version" ){
                    mrq_ver = reader.readElementText();
                }else if( reader.name() == "mrh_version" ){
                    mrh_ver = reader.readElementText();
                }else if( reader.name() == "mct_version" ){
                    mct_ver = reader.readElementText();
                }else if( reader.name() == "t4_version" ){

                }else{
                    reader.skipCurrentElement();
                }
            }
        }
        else
            { reader.skipCurrentElement(); }
    }

    if( parser.isSet( packetOption ) ){
        Entity *e1 = new Entity;
        e1->setDesc( mrh_ver );
        e1->setId( MRH_ENTITY );
        e1->init( mrh_path );

        Entity *e2 = new Entity;
        e2->setDesc( mrq_ver );
        e2->setId( MRQ_ENTITY );
        e2->init( mrq_path );

        Package *p = new Package;
        p->insertEntity( e1 );
        p->insertEntity( e2 );
        p->setDesc( desc );
        p->init();
        p->packet( output_file_name );
    }else if( parser.isSet( unpacketOption ) ){
        Package *p1 = new Package;
        QByteArray ba;
        p1->loadFile( parser.value( unpacketOption ), ba );
        p1->_init( ba );
        p1->unpacket();
    }else{}

    qFile.close();
    return 0;
}
