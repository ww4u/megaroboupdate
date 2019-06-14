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
    QCommandLineOption op7("u", "update.txt","file");

    QCommandLineOption op8("d","MCT_motion.mrp", "file");
    QCommandLineOption op9("i","debug.xml", "file");

    QCommandLineOption op10("j","MCT_motion.mrp", "file");
    QCommandLineOption op11("k","debug.xml", "file");

    QCommandLineOption op12("l","MCT_motion.mrp", "file");
    QCommandLineOption op13("m","debug.xml", "file");


    parser.addOption(op1);
    parser.addOption(op2);
    parser.addOption(op3);
    parser.addOption(op4);
    parser.addOption(op5);
    parser.addOption(op6);
    parser.addOption(op7);
    parser.addOption(op8);
    parser.addOption(op9);
    parser.addOption(op10);
    parser.addOption(op11);
    parser.addOption(op12);
    parser.addOption(op13);

    parser.process(a);

    QString packagePath, packName;
    if(parser.isSet(op1)){
        if(!parser.isSet(op3) || !parser.isSet(op4)|| !parser.isSet(op7)|| !parser.isSet(op8)
                || !parser.isSet(op9)|| !parser.isSet(op10)|| !parser.isSet(op11)
                || !parser.isSet(op12)|| !parser.isSet(op13)){
            qDebug() << "Error: Argument Error";
            return -1;
        }
        if(parser.isSet(op5)){
            packagePath = parser.value(op5);
        }
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

        //!
        Entity *e3 = new Entity;
        e3->setFilePath(parser.value(op8));
        e3->setID(DEMON0_MRP);
        if(e3->compressFile() != 0){
            return -1;
        }

        Entity *e4 = new Entity;
        e4->setFilePath(parser.value(op9));
        e4->setID(DEMON0_DEBUG_XML);
        if(e4->compressFile() != 0){
            return -1;
        }

        Entity *e5 = new Entity;
        e5->setFilePath(parser.value(op10));
        e5->setID(DEMON1_MRP);
        if(e5->compressFile() != 0){
            return -1;
        }

        Entity *e6 = new Entity;
        e6->setFilePath(parser.value(op11));
        e6->setID(DEMON1_DEBUG_XML);
        if(e6->compressFile() != 0){
            return -1;
        }

        Entity *e7 = new Entity;
        e7->setFilePath(parser.value(op12));
        e7->setID(DEMON2_MRP);
        if(e7->compressFile() != 0){
            return -1;
        }

        Entity *e8 = new Entity;
        e8->setFilePath(parser.value(op13));
        e8->setID(DEMON2_DEBUG_XML);
        if(e8->compressFile() != 0){
            return -1;
        }

        Entity *e9 = new Entity;
        e9->setFilePath(parser.value(op7));
        e9->setID(UPDATE_TXT);
        if(e9->compressFile() != 0){
            return -1;
        }
        //!

        Package *p = new Package;
        p->setOutFilePath(packagePath);
        p->insertEntity(e);
        p->insertEntity(e2);
        p->insertEntity(e3);
        p->insertEntity(e4);
        p->insertEntity(e5);
        p->insertEntity(e6);
        p->insertEntity(e7);
        p->insertEntity(e8);
        p->insertEntity(e9);
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

    return 0;
}
