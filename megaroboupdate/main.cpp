#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include "xframe.h"
#include "block.h"
#include "entity.h"
#include "package.h"


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
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInstallMessageHandler(myMessageOutput);

    QCoreApplication::setApplicationName("Pack and Unpacking tool");
    QCoreApplication::setApplicationVersion("V0.0.1.0");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption op1("c","Compress the files to package");
    QCommandLineOption op2("x","Uncompress the file to updating files");
    QCommandLineOption op3("q", "mrq-file-path", "file");
    QCommandLineOption op4("r", "mrh-file-path", "file");
    QCommandLineOption op5("o", "output-file-path", "file");
    QCommandLineOption op6("p", "package-file-path", "file");

    parser.addOption(op1);
    parser.addOption(op2);
    parser.addOption(op3);
    parser.addOption(op4);
    parser.addOption(op5);
    parser.addOption(op6);

    parser.process(a);

    QString packagePath, packName;
    if(parser.isSet(op1)){
        if(!parser.isSet(op3) || !parser.isSet(op4)){
            qDebug() << "Argument error";
            return -1;
        }
        if(parser.isSet(op5)){
            packagePath = parser.value(op5);
        }
//        qDebug() << parser.value(op3) << parser.value(op4) << packagePath;
        Entity *e = new Entity;
        e->setFilePath(parser.value(op3));
        e->setID(MCT_MRQ);
        if(e->compressFile() != 0){
            return -1;
        }

        Entity *e2 = new Entity;
        e2->setFilePath(parser.value(op4));
        e2->setID(MCT_MRH);
        if(e2->compressFile() != 0){
            return -1;
        }

        Package *p = new Package;
        p->setOutFilePath(packagePath);
        p->insertEntity(e);
        p->insertEntity(e2);
        if(p->compressFile() != 0){
            return -1;
        }

        return 0;
    }

    if(parser.isSet(op2)){
        if(!parser.isSet(op6)){
            qDebug() << "uncompress arguments error";
            return -1;
        }
        packName = parser.value(op6);

        Package *pt = new Package;
        pt->setFilePath(packName);
        pt->uncompressFile();
    }

#if 0
    Entity *e = new Entity();
    e->setFilePath("C:\\Users\\lwq\\Documents\\build-untitled5-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\debug\\testfile\\SinanjuProject(SOFT)_1.0.3.0.2(Beta).upd");
    e->setID(MCT_MRQ);
    e->compressFile();

    Entity *e1 = new Entity();
    e1->setFilePath("C:\\Users\\lwq\\Documents\\build-untitled5-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\debug\\testfile\\GreatShot_1.20_Beta1.mrh");
    e1->setID(MCT_MRH);
    e1->compressFile();

    Package *p = new Package;
    p->setOutFilePath("C:\\Users\\lwq\\Documents\\build-untitled5-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\debug\\testfile\\ppp.package");
    p->insertEntity(e);
    p->insertEntity(e1);
    p->compressFile();

#endif
#if 0
    Package *p = new Package;
    p->setFilePath("C:\\Users\\lwq\\Documents\\build-untitled5-Desktop_Qt_5_10_1_MinGW_32bit-Debug\\debug\\testfile\\ppp.package");
    p->uncompressFile();
#endif

    return 0;
}
