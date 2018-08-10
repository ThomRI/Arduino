#include "../include/Arduino.h"

using namespace std;

Arduino::Arduino(QString port) :
    m_ardInterfacer(port)
{
    this->setMinimumSize(750, 600);

    m_3Daxis = new Axis3DPreview;
    m_3Daxis->setMinimumSize(300, 300);
    m_derivator = new DerivatorWidget(5);

    m_Kp_Box = new QDoubleSpinBox;
    m_Kp_Box->setPrefix("Kp : ");
    m_Kp_Box->setRange(0.0, 100.0);

    m_Ki_Box = new QDoubleSpinBox;
    m_Ki_Box->setPrefix("Ki : ");
    m_Ki_Box->setRange(0.0, 100.0);

    m_Kd_Box = new QDoubleSpinBox;
    m_Kd_Box->setPrefix("Kd : ");
    m_Kd_Box->setRange(0.0, 100.0);

    connect(m_Kp_Box, SIGNAL(valueChanged(double)), this, SLOT(update_Kp(double)));
    connect(m_Ki_Box, SIGNAL(valueChanged(double)), this, SLOT(update_Ki(double)));
    connect(m_Kd_Box, SIGNAL(valueChanged(double)), this, SLOT(update_Kd(double)));

    m_timer.start();

    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(m_Kp_Box);
    boxLayout->addWidget(m_Ki_Box);
    boxLayout->addWidget(m_Kd_Box);

    m_hLayout = new QHBoxLayout;
    m_hLayout->addWidget(m_3Daxis);
    m_hLayout->addLayout(boxLayout);

    m_vLayout = new QVBoxLayout;
    m_vLayout->addWidget(m_derivator);
    m_vLayout->addLayout(m_hLayout);

    this->setLayout(m_vLayout);

    connect(&m_ardInterfacer, SIGNAL(pushed(const QList<float>)), this, SLOT(received(const QList<float>)));
}

void Arduino::received(const QList<float> values)
{
    double el = m_timer.elapsed() / 1000.0; // seconds

    m_derivator->add(el, values[0]);
}

void Arduino::update_Kp(double value)
{
    if(m_ardInterfacer.sendCmd((const char) 100)) {
        m_ardInterfacer.send((float)value);
    }
}

void Arduino::update_Ki(double value)
{
    if(m_ardInterfacer.sendCmd((const char) 101)) {
        m_ardInterfacer.send((float)value);
    }
}

void Arduino::update_Kd(double value)
{
    if(m_ardInterfacer.sendCmd((const char) 102)) {
        m_ardInterfacer.send((float)value);
    }

}

Arduino::~Arduino()
{
    //dtor
}
