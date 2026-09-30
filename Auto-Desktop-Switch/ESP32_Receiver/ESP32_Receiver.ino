/*
 * Auto Desktop Switch - ESP32 Receiver (BLE Keyboard)
 *
 * Receives a "trigger" message from the ESP8266 over ESP-NOW and, if armed,
 * sends Win + Ctrl + Left Arrow over Bluetooth to switch virtual desktops.
 * Auto-disarms after one successful switch. A button toggles arm/disarm.
 */

#include <WiFi.h>
#include <esp_now.h>
#include <BleKeyboard.h>
#include "config.h"

BleKeyboard bleKeyboard(BLE_NAME, BLE_MANUFACTURER, BLE_BATTERY);

bool armed = true;
bool lastButtonState = HIGH;

void onReceiveESPNow(const uint8_t *mac, const uint8_t *incomingData, int len) {
  struct_message message;
  memcpy(&message, incomingData, sizeof(message));

  Serial.print("[ESP32] Received: ");
  Serial.println(message.msg);

  if (strcmp(message.msg, "trigger") == 0 && armed) {
    if (bleKeyboard.isConnected()) {
      Serial.println("[ESP32] Sending desktop switch...");
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_ARROW);
      delay(100);
      bleKeyboard.releaseAll();

      // Auto-disarm after switch
      armed = false;
      updateLEDs();
      Serial.println("[ESP32] Auto-disarmed after trigger");
    } else {
      Serial.println("[ESP32] BLE not connected");
    }
  } else {
    Serial.println("[ESP32] Ignored (Disarmed)");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_ARMED, OUTPUT);
  pinMode(LED_DISARMED, OUTPUT);

  bleKeyboard.begin();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onReceiveESPNow);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, esp8266Address, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);

  updateLEDs();
}

void updateLEDs() {
  digitalWrite(LED_ARMED, armed ? HIGH : LOW);
  digitalWrite(LED_DISARMED, armed ? LOW : HIGH);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // Toggle arm/disarm on button press
  if (lastButtonState == HIGH && buttonState == LOW) {
    armed = !armed;
    updateLEDs();
    Serial.print("[ESP32] System ");
    Serial.println(armed ? "ARMED (manual)" : "DISARMED (manual)");
    delay(300); // Debounce
  }

  lastButtonState = buttonState;
  delay(10);
}
