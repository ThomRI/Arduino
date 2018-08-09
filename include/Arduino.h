#ifndef ARDUINO_H
#define ARDUINO_H

#include "ArduinoInterfacer.h"
#include <QString>
#include <QtDebug>
#include <QTime>
#include <QVBoxLayout>
#include <QList>
#include <QVector>

#include "qcustomplot.h"

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

    protected:

    private:
        ArduinoInterfacer m_ardInterfacer;

        /* Plot */
        QCustomPlot *m_plotter;
        QCustomPlot *m_dPlotter;

        ValuesArray m_times;
        ValuesArray m_Y;
        ValuesArray m_dY;

        QTime m_timer;

        /* Widget */
        QVBoxLayout *m_layout;
};

#endif // ARDUINO_H
