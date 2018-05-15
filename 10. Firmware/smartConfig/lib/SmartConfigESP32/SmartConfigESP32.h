#ifndef SmartConfigESP32_h
#define SmartConfigESP32_h
#include <Arduino.h>
#include <WiFi.h>
#include "EEPROMESP32.h"

struct Network {
    String ssid;
    String password;
};

class SmartConfigESP32 {
private:
    unsigned char _minLengthPassword = 8;
public:
    SmartConfigESP32();
    void connect();
    Network getNetwork();
    void saveNetwork(EEPROMESP32 eepromESP32, unsigned char address, Network _network);
    Network getNetwork(EEPROMESP32 eepromESP32, unsigned char address);
    bool checkNetwork(Network network);
    bool isConnect();
};
#endif
