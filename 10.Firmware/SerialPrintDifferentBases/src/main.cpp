#include <Arduino.h>

void setup() {
    Serial.begin(115200);

    int value = 10;

    Serial.print("Value = ");
    Serial.print(value, DEC);
    Serial.println(" (DEC)");

    Serial.print("Value = ");
    Serial.print(value, BIN);
    Serial.println(" (BIN)");

    Serial.print("Value = ");
    Serial.print(value, OCT);
    Serial.println(" (OCT)");

    Serial.print("Value = ");
    Serial.print(value, HEX);
    Serial.println(" (HEX)");
}

void loop() {

}
