# Wiring

## ESP8266 (Sender)

| Component      | Pin          |
|----------------|--------------|
| Trigger button | D4 (GPIO2) → GND |

The button uses the internal pull-up, so no resistor is needed.

## ESP32 (Receiver)

| Component            | Pin              |
|----------------------|------------------|
| Arm/Disarm button    | GPIO 12 → GND    |
| Green LED (armed)    | GPIO 14 → resistor (~220Ω) → GND |
| Red LED (disarmed)   | GPIO 27 → resistor (~220Ω) → GND |

LEDs are optional. The button uses the internal pull-up.

## Diagram

```
 [Button] ── D4        [Button] ── GPIO12
    │                     │
   GND                   GND
 ESP8266  ── ESP-NOW ──►  ESP32 ── BLE ──► PC
                          ├─ GPIO14 → Green LED
                          └─ GPIO27 → Red LED
```
