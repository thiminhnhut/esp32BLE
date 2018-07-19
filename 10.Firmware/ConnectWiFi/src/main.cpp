#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "cdttech.vn";
const char* password =  "cdt12345";

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address = "); Serial.println(WiFi.localIP());
    WiFi.printDiag(Serial);
}

void loop() {

}
