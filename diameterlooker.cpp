#include "diameterlooker.h"
#include "ui_diameterlooker.h"

diameterLooker::diameterLooker(QWidget *parent,int diam, int num) : Looker(parent,num), ui(new Ui::diameterLooker),m_diam(diam)
{
    ui->setupUi(this);

    m_centerViewer = new centerViewer(this,m_diam);
    diameterPlot = new QCustomPlot(this);
    diameterPlot->addGraph();
    diameterPlot->setMinimumHeight(200);
    ui->HLayout->insertWidget(1,m_centerViewer);
    ui->VLayout->addWidget(diameterPlot);

    setEnabled(false);
}

diameterLooker::~diameterLooker()
{
    delete ui;
    delete m_centerViewer;
    delete diameterPlot;
}

void diameterLooker::setModel(int diam){
    m_diam = diam;
    m_centerViewer->setScale(m_diam);
}

void diameterLooker::rePaint()
{
    QVector <double> m_data = data();
    ui->lcdNumber->display(m_data.at(0));//Основной диаметр
    ui->lcdNumber_2->display(m_data.at(1));//х Диаметр
    ui->lcdNumber_3->display(m_data.at(2));//y Диаметр
    ui->lcdNumber_4->display(m_data.at(3));//х Смещение
    ui->lcdNumber_5->display(m_data.at(4));//y Смещение
    m_centerViewer->setCoord(m_data.at(3),m_data.at(4));   //Размер и положение
    m_centerViewer->setRad(m_data.at(1)/2.0,m_data.at(2)/2.0);
    if(static_cast<int>(m_data.at(5)) == 0){//Только если не пришла ошибка, добавляем данные на график. Иначе, будет пустое место
        m_diameters.append(m_data.at(0));
        xDiameters.append(packetCounter++);
        if(m_diameters.size()>100){
            m_diameters.removeFirst();
            xDiameters.removeFirst();
        }
        setGraphData();
    }

    setError(m_data.at(5));

}

void diameterLooker::setError(int error){
     QString error_message;
     switch (error) {
               case 0: error_message = tr("-");break;
               case 1: error_message = tr("Перекрытие рабочей зоны по двум каналам."); break;
               case 2: error_message = tr("Перекрытие верхней границы рабочей зоны по двум каналам"); break;
               case 3:error_message = tr("Перекрытие нижней границы рабочей зоны по двум каналам");break;
               case 4: error_message = tr("Перекрытие нижней границы рабочей зоны по первому каналу");break;
               case 5: error_message = tr("Перекрытие верхней границы рабочей зоны по первому каналу");break;
               case 6: error_message = tr("Перекрытие рабочей зоны по первому каналу.");break;
               case 7: error_message = tr("Перекрытие верхней границы рабочей зоны по второму каналу");break;
               case 8:error_message = tr("Перекрытие нижней границы рабочей зоны по второму каналу");break;
               case 9: error_message = tr("Перекрытие рабочей зоны по второму каналу.");break;
               case 10: error_message = tr("Перекрытие рабочей зоны по первому каналу и перекрытие верхней границы рабочей зоны по второму каналу"); break;
               case 11: error_message = tr("Перекрытие рабочей зоны по первому каналу перекрытие нижней границы рабочей зоны по второму каналу.");break;
               case 12: error_message = tr("Перекрытие рабочей зоны по второму каналу и перекрытие верхней границы рабочей зоны по первому каналу."); break;
               case 13: error_message = tr("Перекрытие рабочей зоны по второму каналу и перекрытие нижней границы рабочей зоны по первому каналу."); break;
               case 14: error_message = tr("Перекрытие верхней границы рабочей зоны по первому каналу и перекрытие нижней границы рабочей зоны по второму каналу."); break;
               case 15:error_message = tr("Перекрытие нижней границы рабочей зоны по первому каналу и перекрытие верхней границы рабочей зоны по второму каналу.");break;
               case 16: error_message = tr("Наличие двух и более объектов в зоне измерения.");break;
               default: error_message = tr("Неизвестная ошибка"); break;
      }
     ui->label->setText(error_message);
     QPalette palette;
     if(error!=0){
         palette.setColor(QPalette::WindowText,Qt::red);
        ui->lcdNumber->display("-");
        ui->lcdNumber_2->display("-");
        ui->lcdNumber_3->display("-");
     }
     else
         palette.setColor(QPalette::WindowText,Qt::black);

     ui->lcdNumber->setPalette(palette);
     ui->lcdNumber_2->setPalette(palette);
     ui->lcdNumber_3->setPalette(palette);
}

void diameterLooker::setGraphData(){
    diameterPlot->graph()->setData(xDiameters,m_diameters);
    diameterPlot->xAxis->rescale();
    diameterPlot->yAxis->rescale();

    diameterPlot->xAxis->setRange(diameterPlot->xAxis->range().upper, 100, Qt::AlignRight);
    diameterPlot->yAxis->setRangeLower(0);
    //diameterPlot->yAxis->setRange(diameterPlot->yAxis->range().lower, 0, Qt::AlignRight);
    diameterPlot->replot();
}
