#include <QApplication>
#include "include/Arduino.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Arduino ard("COM3");
    ard.show();

    return app.exec();
}
