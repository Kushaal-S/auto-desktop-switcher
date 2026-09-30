#ifndef CONFIG_H
#define CONFIG_H

// ---------- Pins ----------
#define BUTTON_PIN D4  // GPIO2 (trigger button to GND)

// ---------- Receiver (ESP32) MAC address ----------
// Replace with the MAC address of YOUR ESP32
uint8_t esp32Address[] = { 0x24, 0x62, 0xAB, 0xDD, 0x80, 0xE8 };

// ---------- ESP-NOW message ----------
typedef struct struct_message {
  char msg[32];
} struct_message;

#endif
