#include "../include/Arduino.h"

using namespace std;

Arduino::Arduino(QString port) :
    m_ardInterfacer(port)
{
    this->resize(750, 400);

    m_plotter = new QCustomPlot(this);
    m_dPlotter = new QCustomPlot(this);

    m_plotter->addGraph();
    m_dPlotter->addGraph();

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
    m_layout->addWidget(m_plotter);
    m_layout->addWidget(m_dPlotter);
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

    m_times.append(el);
    m_Y.append(values.at(0));

    if(m_Y.size() > 1000) {
        m_Y.erase(m_Y.begin());
        m_dY.erase(m_dY.begin());
        m_times.erase(m_times.begin());
    }

    m_plotter->graph(0)->setData(m_times, m_Y);
    m_plotter->yAxis->rescale();
    m_plotter->xAxis->setRange(el - 5, el);
    m_plotter->replot();

    /* Derivative calculations */
    if(m_Y.size() <= 1 || m_times.size() <= 1) {
        m_dY.append(0.0);
    } else {
        int i = m_times.size() - 1;

        m_dY.append( (m_Y.at(i) - m_Y.at(i - 1)) / (m_times.at(i) - m_times.at(i - 1)) );
    }

    m_dPlotter->graph(0)->setData(m_times, m_dY);
    m_dPlotter->yAxis->rescale();
    m_dPlotter->xAxis->setRange(el - 5, el);
    m_dPlotter->replot();
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
