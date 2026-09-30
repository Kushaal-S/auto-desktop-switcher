// Prints the ESP8266's MAC address to Serial (9600 baud)
#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  delay(500);
  Serial.print("ESP8266 MAC: ");
  Serial.println(WiFi.macAddress());
}

void loop() {}
