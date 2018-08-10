#include "../include/Arduino.h"

using namespace std;

Arduino::Arduino(QString port) :
    m_ardInterfacer(port)
{
    this->resize(750, 400);

    m_derivator = new DerivatorWidget(5);

    m_Kp_Slider = new QSlider(Qt::Horizontal, this);
    m_Kp_Slider->setRange(0.0, 10.0);

    m_Ki_Slider = new QSlider(Qt::Horizontal, this);
    m_Ki_Slider->setRange(0.0, 10.0);

    m_Kd_Slider = new QSlider(Qt::Horizontal, this);
    m_Kd_Slider->setRange(0.0, 10.0);

    connect(m_Kp_Slider, SIGNAL(valueChanged(int)), this, SLOT(update_Kp(int)));
    connect(m_Ki_Slider, SIGNAL(valueChanged(int)), this, SLOT(update_Ki(int)));
    connect(m_Kd_Slider, SIGNAL(valueChanged(int)), this, SLOT(update_Kd(int)));

    m_timer.start();

    m_layout = new QVBoxLayout;
    m_layout->addWidget(m_derivator);
    m_layout->addWidget(m_Kp_Slider);
    m_layout->addWidget(m_Ki_Slider);
    m_layout->addWidget(m_Kd_Slider);
    setLayout(m_layout);

    connect(&m_ardInterfacer, SIGNAL(pushed(const QList<float>)), this, SLOT(received(const QList<float>)));
}

void Arduino::received(const QList<float> values)
{
    double el = m_timer.elapsed() / 1000.0; // seconds
    if(el < 1) return; // Avoids noise

    m_derivator->add(el, values[0]);
}

void Arduino::update_Kp(int value)
{
    if(m_ardInterfacer.sendCmd((const char) 100)) {
        m_ardInterfacer.send((float)value);
    }
}

void Arduino::update_Ki(int value)
{
    if(m_ardInterfacer.sendCmd((const char) 101)) {
        m_ardInterfacer.send((float)value);
    }
}

void Arduino::update_Kd(int value)
{
    if(m_ardInterfacer.sendCmd((const char) 102)) {
        m_ardInterfacer.send((float)value);
    }

}

Arduino::~Arduino()
{
    //dtor
}
