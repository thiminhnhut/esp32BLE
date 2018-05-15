#include <Arduino.h>
#include "SmartConfigESP32.h"
#include "EEPROMESP32.h"

#define __BAUD_RATE__ 115200
#define __SIZE_EEPROM__ 1024
#define __ADDRESS_NETWORK__ 0x00
#define __TIMEOUT_CONNECT_WIFI__ 5000

SmartConfigESP32 smartConfigESP32;
EEPROMESP32 eepromESP32;

void setup() {
    Serial.begin(__BAUD_RATE__);
    eepromESP32.begin(__SIZE_EEPROM__);
    Network _networkEEPROM = smartConfigESP32.getNetwork(eepromESP32, __ADDRESS_NETWORK__);
    if (smartConfigESP32.checkNetwork(_networkEEPROM)) {
        WiFi.begin(_networkEEPROM.ssid.c_str(), _networkEEPROM.password.c_str());
        if (!smartConfigESP32.isConnect()) {
            int end_time = millis() + __TIMEOUT_CONNECT_WIFI__;
            while (millis() < end_time) {
                Serial.print(".");
                if (smartConfigESP32.isConnect()) {
                    Serial.println();
                    break;
                }
                yield();
            }
        }

        if (!smartConfigESP32.isConnect()) {
            smartConfigESP32.connect();
            if (smartConfigESP32.isConnect()) {
                Network _network = smartConfigESP32.getNetwork();
                smartConfigESP32.saveNetwork(eepromESP32, __ADDRESS_NETWORK__, _network);
            }
        } else {
            Serial.println("WiFi Connected.");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
        }

    } else {
        smartConfigESP32.connect();
        if (smartConfigESP32.isConnect()) {
            Network _network = smartConfigESP32.getNetwork();
            smartConfigESP32.saveNetwork(eepromESP32, __ADDRESS_NETWORK__, _network);
        }
    }
}

void loop() {

}
