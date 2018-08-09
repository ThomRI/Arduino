#include "../include/ArduinoInterfacer.h"

ArduinoInterfacer::ArduinoInterfacer(QString port, qint32 rate)
{
    m_serial.setPort(QSerialPortInfo(port));
    m_serial.setBaudRate(rate);
    m_serial.setDataBits(QSerialPort::Data8);
    //m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);
    //m_serial.setFlowControl(QSerialPort::NoFlowControl);

    m_buffer.clear();

    if(m_serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Device opened !";
    } else {
        qDebug() << "Error opening the device.";
    }

    connect(&m_serial, SIGNAL(readyRead()), this, SLOT(received()));
}

void ArduinoInterfacer::received()
{
    QByteArray buf = m_serial.readAll();

    for(QByteArray::iterator it = buf.begin();it != buf.end();it++) {
        char c = (*it); // Each char contained in the buffer

        if(c == ' ' || c == '\n') {
            m_valuesBuffer.append(QString(m_buffer).toFloat());
            m_buffer.clear();
        }
        if(c == ' ') continue; // Already treated
        else if(c == '\n') {
            emit pushed(m_valuesBuffer);

            m_valuesBuffer.clear();
            continue;
        }
        else if(c == '\r') continue; // Ignore \r

        // Not an end of line nor space
        m_buffer.append(c);
    }

    /*while(!in.atEnd()) {
        float value;
        in >> value;
        qDebug() << value;

        emit pushed(value);
    }*/


    /* FOR Serial.Write()
    for(QByteArray::iterator it = buf.begin();it != buf.end();it++) {
        unsigned char c = (*it); // Byte received
        if(c == 0xFF) { // New transmission
            union_float uf;
            uf.b[3] = (m_buffer[3] & 0xff);
            uf.b[2] = (m_buffer[2] & 0xff);
            uf.b[1] = (m_buffer[1] & 0xff);
            uf.b[0] = m_buffer[0];
            //qDebug() << bin << (unsigned char)m_buffer[3] << bin << (unsigned char)m_buffer[2] << bin << (unsigned char)m_buffer[1] << bin << (unsigned char)m_buffer[0] << "|" << uf.f;


            if(abs(uf.f) > 1.0e-10) emit pushed(uf.f);
            m_buffer.clear();
            break;
        }

        m_buffer.append(c);
    }
    CORRESPONDING ARDUINO CODE

    #define EOV (unsigned char)255
    void sendVar(const float &value)
    {
      byte *b = (byte*) &value;
      Serial.write(b, 4);

      Serial.write(EOV);
    }



    */
}

bool ArduinoInterfacer::sendCmd(const char cmd)
{
    return (m_serial.write(&cmd, 1) != -1);
}

ArduinoInterfacer::~ArduinoInterfacer()
{
    //dtor
}
