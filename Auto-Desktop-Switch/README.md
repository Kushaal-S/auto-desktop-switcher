# Auto Desktop Switch

A two-board wireless "panic button" that instantly switches your Windows virtual desktop.

Press a button on an **ESP8266**; it sends an **ESP-NOW** message to an **ESP32**, which acts as a **Bluetooth (BLE) keyboard** and sends `Win + Ctrl + Left Arrow` to your PC. After one switch, the system **auto-disarms** until you re-arm it with the button on the ESP32.

## How it works

```
[ESP8266 + Button] --ESP-NOW "trigger"--> [ESP32] --BLE keyboard--> PC
                                              │
                                    Arm/Disarm button + LEDs
```

1. The ESP8266 detects a button press and sends `"trigger"` via ESP-NOW.
2. The ESP32 receives it. If **armed** and BLE is connected, it presses `Win + Ctrl + ←`.
3. The ESP32 then **auto-disarms** (red LED on).
4. Press the ESP32 button to toggle **armed** (green LED) / **disarmed** (red LED).

## Project structure

```
Auto-Desktop-Switch/
├── ESP32_Receiver/        # BLE keyboard + ESP-NOW receiver
│   ├── ESP32_Receiver.ino
│   └── config.h           # pins, MAC address, BLE name
├── ESP8266_Sender/        # ESP-NOW sender (trigger button)
│   ├── ESP8266_Sender.ino
│   └── config.h           # pin, MAC address
├── tools/                 # helper sketches to read each board's MAC
├── docs/wiring.md
├── LICENSE
└── README.md
```

## Hardware

- 1× ESP32 dev board
- 1× ESP8266 (e.g. NodeMCU / Wemos D1 Mini)
- 2× push buttons
- 2× LEDs (green, red) + resistors — optional

See [docs/wiring.md](docs/wiring.md).

## Libraries

- [ESP32 BLE Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) (`BleKeyboard`)
- ESP32 and ESP8266 board packages (Arduino IDE / Boards Manager)
- `WiFi`, `esp_now` / `espnow` come with the board packages

> **Note:** The code uses the ESP32 Arduino core **2.x** ESP-NOW callback signature. On core 3.x the receive callback signature changed and needs a small adjustment.

## Setup

1. Upload `tools/Get_MAC_ESP32` and `tools/Get_MAC_ESP8266` to get each board's MAC address.
2. Put the **ESP8266's** MAC in `ESP32_Receiver/config.h` (`esp8266Address`).
3. Put the **ESP32's** MAC in `ESP8266_Sender/config.h` (`esp32Address`).
4. Upload `ESP32_Receiver` to the ESP32 and `ESP8266_Sender` to the ESP8266.
5. Pair **"SpyDevice"** from your PC's Bluetooth settings.
6. Press the ESP8266 button to test.

## Notes

- Windows shortcut used: `Win + Ctrl + Left Arrow` (switch to previous virtual desktop). Edit the keys in `ESP32_Receiver.ino` for other shortcuts or OSes.
- The BLE name/manufacturer can be changed in `ESP32_Receiver/config.h`.
- Serial baud: ESP32 = 115200, ESP8266 = 9600.

## License

MIT — see [LICENSE](LICENSE).
