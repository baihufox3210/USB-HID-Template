#ifndef USB_GAMEPAD_H
#define USB_GAMEPAD_H

#include <USB.h>
#include <USBHIDGamepad.h>

class USB_GamePad {
    private:
        USBHIDGamepad _gamepad;

    public:
        void begin();

        void start();
        void stop();

        bool isConnected();

        void press(int id);
        void release(int id);
};
#endif