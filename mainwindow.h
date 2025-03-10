#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "console.h"
#include <QHBoxLayout>
#include "statusbar.h"
#include "redwilldevice.h"
#include "diameterlooker.h"
#include "serialsettings.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createRedwillDevice(ClientType type);
    void fillDevInfo();
    void newSettingsOk(QList<ConSettings> &settings);
    void setMessage(const QString &msg);
    void communicationFailed(int serv);
    void connectionChanged(const QString &host,int status);
    void deviceReceived(int server);
    void deviceAck(int server);
    void add6ToQueue(int server, const QVector<unsigned short> & par, int startAdd, int count);
    void sendTimeout();
    void freqCalcTimeout();
    void on_actionconnect_triggered(bool checked);      //Кнопка коннект
    void on_actionsettingsOn_triggered();               //Кнопка показать настройки
    void on_actionconsoleOn_toggled(bool arg1);         //Кнопка показать консоль

    void on_actionlogOn_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    QHBoxLayout *HLayout,*devicesLayout;
    QVBoxLayout *VLayout;
    QTimer *m_timerSend, *m_freqCalcTimer;
    SerialSettings *m_serialSetting;
    StatusBar *m_statusBar;
    Console *m_console;
    devInfo m_devInfo;
    ConSettings m_conSettings;
    diameterLooker *m_looker;
    RedwillDevice *m_dev = nullptr;
    QElapsedTimer startTime;
    int m_period=100;
    int packetCounter=0;


};
#endif // MAINWINDOW_H
