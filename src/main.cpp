#include <Arduino.h>

#include "LEDController.h"

#include "USB_GamePad.h"
#include "BLE_GamePad.h"

#define DEVICE_NAME "BLE GamePad"
#define DEVICE_MANUFACTURER "Espressif"
#define BETTERY_LEVEL 100

#define BLE_PIN_PASSWORD 123456

enum Mode {USB_MODE, BLE_MODE, None};

volatile Mode currentMode;
Mode lastMode = None;

LEDController ledController;

USB_GamePad usbGamePad;
Ble_GamePad bleGamepad(DEVICE_NAME, DEVICE_MANUFACTURER, BETTERY_LEVEL, BLE_PIN_PASSWORD);

struct Button {
	int pinID, hidID;
	bool lastState;
};

Button buttons[] = {
};

void switchToUSBMode() {
	bleGamepad.stopAdvertising();
	usbGamePad.start();
}

void switchToBleMode() {
	bleGamepad.startAdvertising();
	usbGamePad.stop();
}

void setButtonEvent(int hidID, bool isPressed) {
	if(isPressed) currentMode == USB_MODE ? usbGamePad.press(hidID - 1) : bleGamepad.press(hidID);
	else currentMode == USB_MODE ? usbGamePad.release(hidID - 1) : bleGamepad.release(hidID);
}

void setup() {
	Serial.begin(115200);

	for(Button& button : buttons) {
		pinMode(button.pinID, INPUT_PULLUP);
		button.lastState = digitalRead(button.pinID);
	}

	ledController.begin(50);

	usbGamePad.begin();
	bleGamepad.begin();

	ledController.setColor(LEDColor::RED);

	delay(100);
}

void loop() {
	if(usbGamePad.isConnected()) currentMode = USB_MODE;
	else currentMode = BLE_MODE;

	if(currentMode != lastMode) {
		if(currentMode == USB_MODE) switchToUSBMode();
		else switchToBleMode();

		lastMode = currentMode;
	}

	if(currentMode == BLE_MODE) {
		if(!bleGamepad.isConnected()) ledController.flash(LEDColor::BLUE, 500);
		else ledController.setColor(LEDColor::BLUE);
	}
	else {
		ledController.setColor(LEDColor::GREEN);
	}

	for(Button& button : buttons) {
		bool currentState = digitalRead(button.pinID);

		if(currentState != button.lastState) {
			setButtonEvent(button.hidID, currentState == LOW);
			button.lastState = currentState;
		}
	}

	delay(10);
}