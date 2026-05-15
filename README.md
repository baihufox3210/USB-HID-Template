# USB HID Template

A USB HID gamepad testing project based on the ESP32-S3.

## Hardware Requirements

- ESP32-S3-DevKitM-1 development board
- WS2812B LED strip (connected to GPIO 48)
- Push buttons (optional, connected to the specified GPIO pins)

## Button Configuration

Add button configurations to the `buttons` array in `src/main.cpp`:

```cpp
Button buttons[] = {
    {GPIO_PIN, HID_BUTTON_ID, false},
};
```

## Dependencies
- [FastLED](https://github.com/FastLED/FastLED)