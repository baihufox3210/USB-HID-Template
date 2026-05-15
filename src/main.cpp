#include <Arduino.h>
#include <FastLED.h>
#include <USB.h>
#include <USBHIDGamepad.h>

#define LED_PIN 48
#define LED_NUMS 1

USBHIDGamepad GamePad;
CRGB leds[LED_NUMS];

struct Button {
    int pin, hid;
    bool lastState;
};

Button buttons[] = {};

void setup() {
    Serial.begin(115200);

    for(Button& button : buttons) {
        pinMode(button.pin, INPUT_PULLUP);
    }

    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_NUMS);
    FastLED.setBrightness(50);

    leds[0] = CRGB::Blue;
    FastLED.show();

    USB.begin();
    GamePad.begin();
}

void loop() {
    for(Button& button : buttons) {
        bool currentState = digitalRead(button.pin);

        if (currentState != button.lastState) {
            if (currentState == LOW) {
                GamePad.pressButton(button.hid);
                leds[0] = CRGB::Green;
            } 
            else {
                GamePad.releaseButton(button.hid);
                leds[0] = CRGB::Red;
            }

            FastLED.show();
            button.lastState = currentState;
        }
    }

    delay(10); 
}