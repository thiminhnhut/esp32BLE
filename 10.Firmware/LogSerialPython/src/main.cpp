#include <Arduino.h>

#define SerialMonitor Serial
#define __BAUD_RATE__ 115200

unsigned long i = 0;

void setup() {
    SerialMonitor.begin(__BAUD_RATE__);
}

void loop() {
    SerialMonitor.println(i++);
    delay(2000);
}
