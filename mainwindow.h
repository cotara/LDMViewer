#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectionpanel.h"
#include "console.h"
#include <QHBoxLayout>
#include "statusbar.h"
#include "ldmdevice.h"


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
    void connectionChanged(int numDev, int status,const QString &host);
    void connectionFailed(int ,const QString &msg);
    void connectionPushed(bool action);
    void modbusPacketPrint(int server ,const  QString &str);
    void clearConsole();
    void on_actionconsoleOn_toggled(bool arg1);
    void on_actionsettingsOn_toggled(bool arg1);
    void on_actiontcp_com_toggled(bool arg1);
    void on_actiondoubleMode_toggled(bool arg1);
    void connectNewDevice(LDMDevice* dev);
    void saveSettings();

private:
    Ui::MainWindow *ui;
    QHBoxLayout *HLayout,*devicesLayout;
    QVBoxLayout *VLayout;

    StatusBar *m_statusBar;
    QVector <LDMDevice*> devices;
    ConnectionPanel *m_connectionPanel;
    Console *m_console;
    int currentCountDev=1;
    int connectedDevices = 0;//Количество устройств, подключенных
    int connectingDevice = 0;//Количество устройств, находящихся в состоянии подключения/отключения
    QMap <int, int> connectionState;

};
#endif // MAINWINDOW_H
