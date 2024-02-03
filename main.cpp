#include "viewer.h"
#include "./ui_viewer.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGuiApplication::setApplicationDisplayName(Viewer::tr("Alpaca Image Viewer"));
    Viewer w;

    // when call program from command line
    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(Viewer::tr("[file]"), Viewer::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());

    if (!commandLineParser.positionalArguments().isEmpty()
        && !w.loadFile(commandLineParser.positionalArguments().constFirst()))
    {
        return -1 ;
    }
    w.show();
    return a.exec();
}
