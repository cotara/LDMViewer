#include "looker.h"

Looker::Looker(QWidget *parent, int num) : QGroupBox(parent), m_devNum(num){

    setTitle("Прибор №" + QString::number(m_devNum));

}
Looker::~Looker()
{

}
void Looker::setData(const QVector<double> &data)
{
    m_data = data;
    rePaint();

}
void Looker::setName(int name){
    m_devNum = name;
    setTitle("Прибор №" + QString::number(name));
}

void Looker::setModel(int)
{

}

void Looker::rePaint()
{

}

QVector<double> &Looker::data(){
    return m_data;
}
