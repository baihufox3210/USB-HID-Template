#include "BLE_GamePad.h"
#include <NimBLEDevice.h>

Ble_GamePad::Ble_GamePad(const std::string& deviceName, const std::string& deviceManufacturer, int batteryLevel, int pinPassword)
    : _gamepad(deviceName, deviceManufacturer, batteryLevel), _deviceName(deviceName), _pinPassword(pinPassword) {}

void Ble_GamePad::begin() {
    if(!NimBLEDevice::isInitialized()) {
        NimBLEDevice::init(_deviceName.c_str());

        NimBLEDevice::setSecurityAuth(true, true, true);

        NimBLEDevice::setSecurityIOCap(BLE_HS_IO_DISPLAY_ONLY);
        NimBLEDevice::setSecurityPasskey(_pinPassword);

        NimBLEDevice::setSecurityInitKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);
        NimBLEDevice::setSecurityRespKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);        
    }

    _gamepad.begin();
}

void Ble_GamePad::startAdvertising() {
    if(NimBLEDevice::isInitialized()) {
        NimBLEDevice::getAdvertising() -> start();
    }
}

void Ble_GamePad::stopAdvertising() {
    NimBLEDevice::getAdvertising() -> stop();
}

bool Ble_GamePad::isConnected() {
    return _gamepad.isConnected();
}

void Ble_GamePad::press(int id) {
    _gamepad.press(id);
}

void Ble_GamePad::release(int id) {
    _gamepad.release(id);
}