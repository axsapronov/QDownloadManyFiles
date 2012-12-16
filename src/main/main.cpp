
#include <QtGui/QApplication>
#include "mainwindow.h"

#include <QTextCodec>
#include <QTranslator>
//#include <QLocale>


int main(int argc, char **argv)
{
//    QCoreApplication app(argc, argv);

    QApplication a(argc, argv);

    QTextCodec * codec = QTextCodec::codecForName("UTF-8"); // set encoding for progs
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

//    QTranslator translator;
//    translator.load(""+QLocale::system().name(),"lang");
//    a.installTranslator(&translator);


//    QStringList arguments = app.arguments();
//    arguments.takeFirst();      // remove the first argument, which is the program's name

//    if (arguments.isEmpty()) {
//        printf("Qt Download example\n"
//               "Usage: downloadmanager url1 [url2... urlN]\n"
//               "\n"
//               "Downloads the URLs passed in the command-line to the local directory\n"
//               "If the target file already exists, a .0, .1, .2, etc. is appended to\n"
//               "differentiate.\n");
//        return 0;
//    }

//    qDebug() << arguments;
//    DownloadManager manager;
//    manager.append(arguments);

//    QObject::connect(&manager, SIGNAL(finished()), &app, SLOT(quit()));

    MainWindow w;
    w.show();

    return a.exec();
}


