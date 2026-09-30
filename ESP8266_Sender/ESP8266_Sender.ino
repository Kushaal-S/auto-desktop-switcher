/*
 * Auto Desktop Switch - ESP8266 Sender (Trigger Button)
 *
 * Sends a "trigger" message to the ESP32 over ESP-NOW
 * whenever the button is pressed.
 */

#include <ESP8266WiFi.h>
#include <espnow.h>
#include "config.h"

bool lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_add_peer(esp32Address, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // Detect falling edge
  if (lastButtonState == HIGH && buttonState == LOW) {
    struct_message message;
    strcpy(message.msg, "trigger");
    esp_now_send(esp32Address, (uint8_t *)&message, sizeof(message));
    Serial.println("[ESP8266] Button Pressed → Sent: trigger");
    delay(100); // Debounce
  }

  lastButtonState = buttonState;
  delay(10);
}
