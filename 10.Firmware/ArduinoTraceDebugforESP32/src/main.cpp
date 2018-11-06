#include <Arduino.h>
#include <ArduinoTrace.h>

#define SerialMonitor Serial
#define __BAUDRATE__ 115200

void increaseTemp(float temp);

void setup() {
    SerialMonitor.begin(__BAUDRATE__);

    TRACE();

    float temp = 35.6;
    DUMP(temp);

    increaseTemp(temp);
}

void loop() {

}

void increaseTemp(float temp) {
    TRACE();
    temp = temp*2.0f;
    DUMP(temp);
}
