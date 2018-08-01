#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

const char *ssid = "MyESP32AP";
const char *password = "esp32ble";

void printStations();

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);

    Serial.println();
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
}

void loop() {
    printStations();
    delay(5000);
}

void printStations() {
    wifi_sta_list_t stationList;
    esp_wifi_ap_get_sta_list(&stationList);

    Serial.print("N of connected stations: ");
    Serial.println(stationList.num);

    for (unsigned int i = 0; i < stationList.num; i++) {
        wifi_sta_info_t station = stationList.sta[i];

        for (unsigned int j = 0; j < 6; j++){
            char str[3];
            sprintf(str, "%02x", (int)station.mac[j]);
            Serial.print(str);
            if (j < 5) {
                Serial.print(":");
            }
        }
        Serial.println();
    }
    Serial.println("-----------------");
}
