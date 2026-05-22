#include "USBGamePad.h"

void USB_GamePad::begin() {
    USB.begin();
}

void USB_GamePad::start() {
    _gamepad.begin();
}

void USB_GamePad::stop() {
    _gamepad.end();
}

bool USB_GamePad::isConnected() {
    return (bool)USB;
}

void USB_GamePad::press(int id) {
    _gamepad.pressButton(id);
}

void USB_GamePad::release(int id) {
    _gamepad.releaseButton(id);
}   