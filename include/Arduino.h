#ifndef ARDUINO_H
#define ARDUINO_H

#include "ArduinoInterfacer.h"
#include "MultiPlot.h"
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
        void update_Point(double value);

        void connectClicked();

    protected:

    private:
        ArduinoInterfacer m_ardInterfacer;

        /* 3D Axis */
            Axis3DPreview *m_3Daxis;
        /* Plot */
            MultiPlot *m_multiPlot;

        /* Widgets */
        QDoubleSpinBox  *m_Kp_Box,
                        *m_Ki_Box,
                        *m_Kd_Box,
                        *m_point_Box;
        QPushButton     *m_connectButton;

        QTime m_timer;

        /* Widget */
        QVBoxLayout *m_vLayout;
        QHBoxLayout *m_hLayout;
};

#endif // ARDUINO_H
