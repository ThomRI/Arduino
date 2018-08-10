#ifndef ARDUINO_H
#define ARDUINO_H

#include "ArduinoInterfacer.h"
#include "DerivatorWidget.h"
#include "Axis3DPreview.h"

#include <QApplication>
#include <QString>
#include <QtDebug>
#include <QTime>
#include <QVBoxLayout>
#include <QList>
#include <QVector>
#include <QDoubleSpinBox>
#include <QPushButton>

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

        void update_Kp(double value);
        void update_Ki(double value);
        void update_Kd(double value);


    protected:

    private:
        ArduinoInterfacer m_ardInterfacer;

        /* 3D Axis */
            Axis3DPreview *m_3Daxis;
        /* Plot */
            DerivatorWidget *m_derivator;

        /* Sliders */
        QDoubleSpinBox  *m_Kp_Box,
                        *m_Ki_Box,
                        *m_Kd_Box;

        QTime m_timer;

        /* Widget */
        QVBoxLayout *m_vLayout;
        QHBoxLayout *m_hLayout;
};

#endif // ARDUINO_H
