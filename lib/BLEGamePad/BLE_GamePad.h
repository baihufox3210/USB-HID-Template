#ifndef Ble_GamePad_H
#define Ble_GamePad_H

#include <string>
#include <cstdint>
#include <BleGamepad.h>

class Ble_GamePad {
    private:
        BleGamepad _gamepad;

        std::string _deviceName;
        std::string _deviceManufacturer;

        int _batteryLevel;
        int _pinPassword;

    public:
        Ble_GamePad(const std::string& deviceName, const std::string& deviceManufacturer, int batteryLevel, int pinPassword);

        void begin();

        void startAdvertising();
        void stopAdvertising();

        bool isConnected();

        void press(int id);
        void release(int id);
};
#endif