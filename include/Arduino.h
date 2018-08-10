#ifndef ARDUINO_H
#define ARDUINO_H

#include "ArduinoInterfacer.h"
#include "DerivatorWidget.h"

#include <QString>
#include <QtDebug>
#include <QTime>
#include <QVBoxLayout>
#include <QList>
#include <QVector>
#include <QSlider>

#include <iostream>

typedef QVector<double> ValuesArray;

class Arduino : public QWidget
{
    Q_OBJECT
    public:
        Arduino(QString port);
        virtual ~Arduino();

    public slots:
        void received(const QList<float> values);

        void update_Kp(int value);
        void update_Ki(int value);
        void update_Kd(int value);


    protected:

    private:
        ArduinoInterfacer m_ardInterfacer;

        /* Interface */

        /* Plot */
            DerivatorWidget *m_derivator;

        /* Sliders */
        QSlider *m_Kp_Slider,
                *m_Ki_Slider,
                *m_Kd_Slider;

        QTime m_timer;

        /* Widget */
        QVBoxLayout *m_layout;
};

#endif // ARDUINO_H
