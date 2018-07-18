#include "SmartConfigESP32.h"

SmartConfigESP32::SmartConfigESP32() {

}

void SmartConfigESP32::connect() {
    WiFi.mode(WIFI_AP_STA);
    WiFi.beginSmartConfig();

    Serial.println("Waiting for SmartConfig.");
    while (!WiFi.smartConfigDone()) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("SmartConfig done.");

    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi Connected.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

Network SmartConfigESP32::getNetwork() {
    Network _network;
    _network.ssid = WiFi.SSID();
    _network.password = WiFi.psk();
    return _network;
}

void SmartConfigESP32::saveNetwork(EEPROMESP32 eepromESP32, unsigned char address, Network _network) {
    unsigned char lengthSSID = _network.ssid.length();
    unsigned char lengthPassword = _network.password.length();

    unsigned char addressSSID = address + 2;
    unsigned char addressPassword = (addressSSID + 1) + lengthSSID;

    eepromESP32.write(address, lengthSSID);
    eepromESP32.write(address + 1, lengthPassword);
    eepromESP32.writeString(addressSSID, _network.ssid);
    eepromESP32.writeString(addressPassword, _network.password);
    eepromESP32.commit();
}

Network SmartConfigESP32::getNetwork(EEPROMESP32 eepromESP32, unsigned char address) {
    unsigned char lengthSSID = eepromESP32.read(address);
    unsigned char lengthPassword = eepromESP32.read(address + 1);
    unsigned char addressSSID = address + 2;
    unsigned char addressPassword = (addressSSID + 1) + lengthSSID;

    Network _network;
    _network.ssid = eepromESP32.readString(addressSSID);
    _network.password = eepromESP32.readString(addressPassword);

    return _network;
}

bool SmartConfigESP32::checkNetwork(Network network) {
    return network.ssid.length() > 0 && network.password.length() >= _minLengthPassword;
}

bool SmartConfigESP32::isConnect() {
    return WiFi.status() == WL_CONNECTED;
}
