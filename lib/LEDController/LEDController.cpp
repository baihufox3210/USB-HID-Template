#include <LEDController.h>

#define LED_PIN 48
#define NUM_LEDS 1

static CRGB leds[NUM_LEDS];

static CRGB getCRGBFromLEDColor(LEDColor color) {
    switch(color) {
        case LEDColor::OFF: return CRGB::Black;
        case LEDColor::RED: return CRGB::Red;
        case LEDColor::BLUE: return CRGB::Blue;
        case LEDColor::GREEN: return CRGB::Green;
        
        default: return CRGB::Black;
    }
}

LEDController::LEDController()
    : _lastFlash(0), _flashState(false) {}

void LEDController::begin(int brightness) {
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

void LEDController::setColor(LEDColor color) {
    leds[0] = getCRGBFromLEDColor(color);
    FastLED.show();
}

void LEDController::flash(LEDColor color, unsigned long interval) {
    unsigned long currentMillis = millis();

    if(currentMillis - _lastFlash >= interval) {
        _flashState = !_flashState;

        leds[0] = _flashState ? getCRGBFromLEDColor(color) : CRGB::Black;
        FastLED.show();
        
        _lastFlash = currentMillis;
    }
}