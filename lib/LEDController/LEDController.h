#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <FastLED.h>

enum class LEDColor {
    OFF,
    RED,
    GREEN,
    BLUE
};

class LEDController {
    private:        
        unsigned long _lastFlash;
        bool _flashState;

    public:
        LEDController();

        void begin(int brightness);
        void setColor(LEDColor color);
        void flash(LEDColor color, unsigned long interval);
};
#endif