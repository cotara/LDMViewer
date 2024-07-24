#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("LDMViewer");
    w.setWindowIcon(QIcon("://res/target.png"));
    QFontDatabase::addApplicationFont(":/fonts/res/Fonts/Nunito/Nunito-Light.ttf");
    QFontDatabase::addApplicationFont(":/fonts/res/Fonts/GranaPadano.ttf");
    QFontDatabase::addApplicationFont(":/fonts/res/Fonts/SF/SFUIText-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/res/Fonts/SF/SF/SFUIText-Light.ttf");
    QFontDatabase::addApplicationFont(":/fonts/res/Fonts/SF/SF/SFUIText-Regular.ttf");
    QFile file(":/qss/style.css");
    if(file.open(QFile::ReadOnly)){
          QByteArray style = file.readAll();
          a.setStyleSheet(style);
          file.close();
    }

    w.showMaximized();
    return a.exec();
}
