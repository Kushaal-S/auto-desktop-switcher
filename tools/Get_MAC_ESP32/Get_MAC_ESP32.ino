// Prints the ESP32's MAC address to Serial (115200 baud)
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(500);
  Serial.print("ESP32 MAC: ");
  Serial.println(WiFi.macAddress());
}

void loop() {}
