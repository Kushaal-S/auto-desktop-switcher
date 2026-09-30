#ifndef CONFIG_H
#define CONFIG_H

// ---------- Pins ----------
#define BUTTON_PIN   12   // Arm/Disarm toggle button (to GND)
#define LED_ARMED    14   // Green LED (optional)
#define LED_DISARMED 27   // Red LED (optional)

// ---------- Sender (ESP8266) MAC address ----------
// Replace with the MAC address of YOUR ESP8266
uint8_t esp8266Address[] = { 0x08, 0xF9, 0xE0, 0x70, 0xFE, 0x35 };

// ---------- BLE keyboard identity ----------
#define BLE_NAME         "SpyDevice"
#define BLE_MANUFACTURER "SecretOps Inc"
#define BLE_BATTERY      100

// ---------- ESP-NOW message ----------
typedef struct struct_message {
  char msg[32];
} struct_message;

#endif
