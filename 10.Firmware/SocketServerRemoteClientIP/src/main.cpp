#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "TAM 7";
const char* password =  "21019400";

WiFiServer wifiServer(80);

void setup() {
    Serial.begin(115200);

    delay(1000);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());

    wifiServer.begin();
}

void loop() {
    WiFiClient client = wifiServer.available();

    if (client) {
        Serial.print("Client connected with IP:");
        Serial.println(client.remoteIP());
        String data = client.readString();
        Serial.println("Data= " + data + " Length = " + data.length());
        client.stop();
  }

  delay(100);
}
