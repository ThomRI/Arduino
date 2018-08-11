#include "../include/Arduino.h"

using namespace std;

Arduino::Arduino(QString port) :
    m_ardInterfacer(port)
{
    this->setMinimumSize(750, 600);

    m_3Daxis = new Axis3DPreview;
    m_3Daxis->setMinimumSize(300, 300);

    m_multiPlot = new MultiPlot(2, 5);

    m_Kp_Box = new QDoubleSpinBox;
    m_Kp_Box->setPrefix("Kp : ");
    m_Kp_Box->setRange(0.0, 100.0);

    m_Ki_Box = new QDoubleSpinBox;
    m_Ki_Box->setPrefix("Ki : ");
    m_Ki_Box->setRange(0.0, 100.0);

    m_Kd_Box = new QDoubleSpinBox;
    m_Kd_Box->setPrefix("Kd : ");
    m_Kd_Box->setRange(0.0, 100.0);

    m_point_Box = new QDoubleSpinBox;
    m_point_Box->setPrefix("Point : ");
    m_point_Box->setRange(-10.0, 10.0);

    m_connectButton = new QPushButton("Connect to Arduino");
    connect(m_connectButton, SIGNAL(clicked()), this, SLOT(connectClicked()));

    connect(m_Kp_Box, SIGNAL(valueChanged(double)), this, SLOT(update_Kp(double)));
    connect(m_Ki_Box, SIGNAL(valueChanged(double)), this, SLOT(update_Ki(double)));
    connect(m_Kd_Box, SIGNAL(valueChanged(double)), this, SLOT(update_Kd(double)));
    connect(m_point_Box, SIGNAL(valueChanged(double)), this, SLOT(update_Point(double)));

    m_timer.start();

    QVBoxLayout *boxLayout = new QVBoxLayout;
    boxLayout->addWidget(m_Kp_Box);
    boxLayout->addWidget(m_Ki_Box);
    boxLayout->addWidget(m_Kd_Box);
    boxLayout->addWidget(m_point_Box);
    boxLayout->addWidget(m_connectButton);

    m_hLayout = new QHBoxLayout;
    m_hLayout->addWidget(m_3Daxis);
    m_hLayout->addLayout(boxLayout);

    m_vLayout = new QVBoxLayout;
    m_vLayout->addWidget(m_multiPlot);
    m_vLayout->addLayout(m_hLayout);

    this->setLayout(m_vLayout);

    connect(&m_ardInterfacer, SIGNAL(pushed(const QList<float>)), this, SLOT(received(const QList<float>)));
}

void Arduino::received(const QList<float> values)
{
    double el = m_timer.elapsed() / 1000.0; // seconds

    m_3Daxis->setRotation(0.0, values[0], 0.0);
    m_multiPlot->add(el, values);
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

void Arduino::update_Point(double value)
{
    if(m_ardInterfacer.sendCmd((const char) 103)) {
        m_ardInterfacer.send((float) value);
    }
}

void Arduino::connectClicked()
{
    m_ardInterfacer.connectSerial();

    update_Kd(m_Kd_Box->value());
    update_Ki(m_Ki_Box->value());
    update_Kp(m_Kp_Box->value());
    update_Point(m_point_Box->value());
}

Arduino::~Arduino()
{
    //dtor
}
