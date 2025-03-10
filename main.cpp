#include "mainwindow.h"

#include <QApplication>
// Функция для обработки сообщений
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile logFile("log.txt");
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&logFile);
    QString logMessage;

    // Форматируем сообщение
    switch (type) {
    case QtDebugMsg:
        logMessage = QString("Debug: %1").arg(msg);
        break;
    case QtInfoMsg:
        logMessage = QString("Info: %1").arg(msg);
        break;
    case QtWarningMsg:
        logMessage = QString("Warning: %1").arg(msg);
        break;
    case QtCriticalMsg:
        logMessage = QString("Critical: %1").arg(msg);
        break;
    case QtFatalMsg:
        logMessage = QString("Fatal: %1").arg(msg);
        break;
    }

    // Добавляем время и само сообщение
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") << " " << logMessage << "\n";
    logFile.close();
}

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
    QFile file(":/qss/res/style.css");
    if(file.open(QFile::ReadOnly)){
          QByteArray style = file.readAll();
          a.setStyleSheet(style);
          file.close();
    }

    qInstallMessageHandler(messageHandler);
    qDebug() << "Файл лога от " + QDateTime::currentDateTime().toString();
    w.showMaximized();
    return a.exec();
}
