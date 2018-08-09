#ifndef ARDUINOINTERFACER_H
#define ARDUINOINTERFACER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QtDebug>
#include <QDataStream>
#include <QList>

#include <math.h>

class ArduinoInterfacer : public QObject
{
    Q_OBJECT
    public:
        ArduinoInterfacer(QString port, qint32 rate = QSerialPort::Baud9600);
        virtual ~ArduinoInterfacer();

    public slots:
        bool sendCmd(const char cmd);
        void received();

    signals:
        void pushed(const QList<float> values); // Pushes a received float

    protected:

    private:
        /* Serial */
        QSerialPort m_serial;
        QByteArray m_buffer;
        QList<float> m_valuesBuffer;
};

#endif // ARDUINOINTERFACER_H
