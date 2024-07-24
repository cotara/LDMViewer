#include "connectionpanel.h"
#include "ui_connectionpanel.h"




ConnectionPanel::ConnectionPanel(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ConnectionPanel)
{
    setTitle("Настройки подключения");
    setObjectName("historysettings");
    ui->setupUi(this);


    interfaceSwitch(false);//С ком-портом
    //IP
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->ipAdd->setValidator(ipValidator);
    ui->ipAdd2->setValidator(ipValidator);
    ui->ipAdd->setText("127.0.0.1");
    ui->ipAdd2->setText("127.0.0.1");
    ui->port->setText("502");
    ui->port2->setText("502");
    ui->port->setEnabled(true);
    ui->port2->setEnabled(true);

    //Компорты
    on_updAvblPortsButt_clicked();
    ui->spdBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->spdBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->spdBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->spdBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->spdBox->addItem(QStringLiteral("230400"), 230400);
    ui->spdBox->addItem(QStringLiteral("460800"), 460800);
    ui->spdBox->addItem(QStringLiteral("921600"), 921600);

    ui->spdBox->setCurrentIndex(0);
    //Изменился сервер
    connect(ui->deviceNumLine,QOverload<int>::of(&QSpinBox::valueChanged),[=](int i){ emit serverChanged(0,i);});
    connect(ui->deviceNumLine2,QOverload<int>::of(&QSpinBox::valueChanged),[=](int i){ emit serverChanged(1,i);});
    //Изменилась модель
    connect(ui->diamBox1,&QComboBox::currentTextChanged,[=](const QString &text){ emit modelChanged(0,text.toInt());});
    connect(ui->diamBox2,&QComboBox::currentTextChanged,[=](const QString &text){ emit modelChanged(1,text.toInt());});
    //Изменился айпи или номер компорта
    connect(ui->ipAdd,&QLineEdit::textChanged,[=](const QString &ipAdd_comp){ emit ipAdd_compChanged(0,ipAdd_comp);});
    connect(ui->ipAdd2,&QLineEdit::textChanged,[=](const QString &ipAdd_comp){ emit ipAdd_compChanged(1,ipAdd_comp);});
    connect(ui->portsBox,&QComboBox::currentTextChanged,[=](const QString &comport){ emit ipAdd_compChanged(0,comport);});
    //Изменился порт или скорость
    connect(ui->port,&QLineEdit::textChanged,[=](const QString &port){ emit port_boudChanged(0,port.toInt());});
    connect(ui->port2,&QLineEdit::textChanged,[=](const QString &port){ emit port_boudChanged(1,port.toInt());});
    connect(ui->spdBox,&QComboBox::currentTextChanged,[=](const QString &baud){ emit port_boudChanged(0,baud.toInt());});

    ui->deviceNumLine->setValue(1);
    ui->deviceNumLine2->setValue(2);

    QList<QString> models{"20","40","50","120"};
    ui->diamBox1->addItems(models);
    ui->diamBox2->addItems(models);

    connect(ui->clearButton,&QPushButton::clicked,this,&ConnectionPanel::clearConsole);
    oneTwoChange(false);//Отображаем настройки для одного устройства
    setStatusLabel(ui->deviceNumLine->text().toInt(),false);    //Текущий статус первого
    setStatusLabel(ui->deviceNumLine2->text().toInt(),false);   //Текущий статус второго
    ui->clearButton->setVisible(false);
}

ConnectionPanel::~ConnectionPanel(){
    delete ui;
}

void ConnectionPanel::enableClearConsoleButton(bool state){
    ui->clearButton->setVisible(state);
}

QString ConnectionPanel::getIpAdd(int number){
    if(number==0)
        return ui->ipAdd->text();
    else if(number==1)
        return ui->ipAdd2->text();
    else
        return QString("Empty Num");
}

int ConnectionPanel::getPort(int number){
    if(number==0)
        return ui->port->text().toInt();
    else if(number==1)
        return ui->port2->text().toInt();
    else
        return -1;
}

int ConnectionPanel::getServer(int number){
    if(number==0)
        return ui->deviceNumLine->value();
    else if(number==1)
        return ui->deviceNumLine2->value();
    else
        return -1;
}

int ConnectionPanel::getModel(int number)
{
    if(number==0)
        return ui->diamBox1->currentText().toInt();
    else if(number==1)
        return ui->diamBox2->currentText().toInt();
    else
        return -1;
}

QString ConnectionPanel::getComport(){
    return ui->portsBox->currentText();
}

int ConnectionPanel::getBaud(){
    return ui->spdBox->currentText().toInt();
}

void ConnectionPanel::setIP(int numDev, const QString &ip){
    if(numDev==0)
        ui->ipAdd->setText(ip);
    else if(numDev==1)
        ui->ipAdd2->setText(ip);
}

void ConnectionPanel::setPort(int numDev, int port){
    if(numDev==0)
        ui->port->setText(QString::number(port));
    else if(numDev==1)
        ui->port2->setText(QString::number(port));
}

void ConnectionPanel::setComport(const QString &comport){
        ui->portsBox->setCurrentText(comport);
}

void ConnectionPanel::setBaudrate(int baudrate){
    ui->spdBox->setCurrentText(QString::number(baudrate));
}

void ConnectionPanel::setModel(int numDev, int model){
    if(numDev==0)
        ui->diamBox1->setCurrentText(QString::number(model));
    else if(numDev==1)
        ui->diamBox2->setCurrentText(QString::number(model));
}

void ConnectionPanel::setServer(int numDev, int server){
    if(numDev==0)
        ui->deviceNumLine->setValue(server);
    else if(numDev==1)
        ui->deviceNumLine2->setValue(server);
}
//Изменение состояния кнопки
void ConnectionPanel::connectionButtonChanged(bool enabled, int text)
{
    ui->connectButton->setEnabled(enabled);
    switch (text){
        case 0: ui->connectButton->setText("Подключиться"); break;
        case 1: ui->connectButton->setText("Отключиться"); break;
    }
}
//Изменение состояния панели
void ConnectionPanel::enablePanel(bool enabled){
    elementsEnable(enabled);
}


//Выбор ком-порта
void ConnectionPanel::on_portsBox_currentIndexChanged(int index){

    if (index != -1) {
        QSerialPortInfo serial_info;
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        int mun = ports.count();
        if (mun-1<index){
                QMessageBox::critical(this,"Внимание!","COM-порт отсутсвует");
                on_updAvblPortsButt_clicked();
                return;
        }
        serial_info=ports.takeAt(index);
        ui->dscrLabel->setText(serial_info.description());
    }
}


//Обновить доступные компорты
void ConnectionPanel::on_updAvblPortsButt_clicked(){

    ui->portsBox->clear();
    QStringList list;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    if (ports.isEmpty())
        QMessageBox::warning(this,"Внимание!","В системе нет ни одного COM-порта");
    for (QSerialPortInfo port : ports) {
        list << port.portName();
     }
     ui->portsBox->addItems(list);
}

//ПОДКЛЮЧИТЬСЯ!
void ConnectionPanel::on_connectButton_clicked(){
    if(ui->connectButton->text() == "Подключиться")
        emit connectionPushed(true);

    else if(ui->connectButton->text() == "Отключиться")
        emit connectionPushed(false);

}

//Переключение режима TCP - SERIAL
void ConnectionPanel::interfaceSwitch(bool type){
        ui->IPlabel->setVisible(type);
        ui->IPlabel2->setVisible(type);
        ui->ipAdd->setVisible(type);
        ui->ipAdd2->setVisible(type);
        ui->portLabel->setVisible(type);
        ui->portLabel2->setVisible(type);
        ui->port->setVisible(type);
        ui->port2->setVisible(type);

        ui->Portslabel->setVisible(!type);
        ui->portsBox->setVisible(!type);
        ui->updAvblPortsButt->setVisible(!type);
        ui->dscrLabel->setVisible(!type);
        ui->SpdLabel->setVisible(!type);
        ui->spdBox->setVisible(!type);

        oneTwoChange(m_doubleMode);//В случае переключения на TCP
}
//Переключение режимов 1-2 устройства
void ConnectionPanel::oneTwoChange(int arg1){
    if(m_interface){//Если текущий режим - tcp
        ui->IPlabel2->setVisible(arg1);
        ui->ipAdd2->setVisible(arg1);
        ui->portLabel2->setVisible(arg1);
        ui->port2->setVisible(arg1);
    }

    ui->settings2Box->setVisible(arg1);
}

void ConnectionPanel::setStatusLabel(int server, bool state){

    if(ui->deviceNumLine->text().toInt() == server){
        if(state){
            ui->statusLabel->setStyleSheet(lightgreen);
            ui->statusLabel->setText("On-line");
        }
        else {
            ui->statusLabel->setStyleSheet(red);
            ui->statusLabel->setText("Off-line");
        }
    }
    else if(ui->deviceNumLine2->text().toInt() == server){
        if(state){
            ui->statusLabel2->setStyleSheet(lightgreen);
            ui->statusLabel2->setText("On-line");
        }
        else {
            ui->statusLabel2->setStyleSheet(red);
            ui->statusLabel2->setText("Off-line");
        }
    }

}


void ConnectionPanel::elementsEnable(bool state){
    emit doubleButtonBlock(state);
    ui->portsBox->setEnabled(state);
    ui->updAvblPortsButt->setEnabled(state);
    ui->spdBox->setEnabled(state);
    ui->deviceNumLine->setEnabled(state);
    ui->deviceNumLine2->setEnabled(state);
    ui->ipAdd->setEnabled(state);
    ui->ipAdd2->setEnabled(state);
    ui->port->setEnabled(state);
    ui->port2->setEnabled(state);
}



