#include <Arduino.h>

#include <FastLED.h>

#include <USB.h>
#include <USBHIDGamepad.h>

#include <BleGamepad.h>
#include <NimBLEDevice.h>

#define LED_PIN 48
#define NUM_LEDS 1

#define BLE_PIN_PASSWORD 123456

enum Mode {MODE_USB, MODE_BLE};
Mode currentMode = MODE_BLE;

USBHIDGamepad usbGamepad;

BleGamepad bleGamepad("ESP32 BLE Gamepad", "Espressif", 100);

CRGB leds[NUM_LEDS];

struct Button {
	int pin, hid;
	bool lastState;
};

Button buttons[] = {
};

void setButtonEvent(int buttonID, bool isPressed) {
	if(currentMode == MODE_USB) {
		if(isPressed) usbGamepad.pressButton(buttonID);
		else usbGamepad.releaseButton(buttonID);
	}
	else {
		if(isPressed) bleGamepad.press(buttonID);
		else bleGamepad.release(buttonID);
	}
}

void setup() {
	Serial.begin(115200);

	for(Button& button : buttons) {
		pinMode(button.pin, INPUT_PULLUP);
		button.lastState = digitalRead(button.pin);
	}

	FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(50);

	leds[0] = CRGB::Red;
	FastLED.show();

	if(currentMode == MODE_USB) {
		USB.begin();
		usbGamepad.begin();

		leds[0] = CRGB::Green;
		FastLED.show();
	}
	else {
		NimBLEDevice::init("ESP32 BLE Gamepad");

		NimBLEDevice::setSecurityAuth(true, true, true);

		NimBLEDevice::setSecurityIOCap(BLE_HS_IO_DISPLAY_ONLY);
		NimBLEDevice::setSecurityPasskey(BLE_PIN_PASSWORD);

		NimBLEDevice::setSecurityInitKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);
		NimBLEDevice::setSecurityRespKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);

		NimBLEDevice::deleteAllBonds();
		
		bleGamepad.begin();

		leds[0] = CRGB::Blue;
		FastLED.show();
	}
}

void loop() {
	if(currentMode == MODE_BLE) {
		if(!bleGamepad.isConnected()) {
			static unsigned long lastFlash = 0;
			static bool flashState = false;

			if(millis() - lastFlash > 500) {
				flashState = !flashState;
				leds[0] = flashState ? CRGB::Blue : CRGB::Black;
				
				FastLED.show();
				lastFlash = millis();
			}
		}
		else {
			leds[0] = CRGB::Blue;
			FastLED.show();
		}
	}

	for(Button& button : buttons) {
		bool currentState = digitalRead(button.pin);

		if(currentState != button.lastState) {
			setButtonEvent(button.hid, currentState == LOW);
			button.lastState = currentState;
		}
	}

	delay(10);
}