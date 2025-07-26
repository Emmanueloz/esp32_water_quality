#pragma once
#include <BLEDevice.h>
#include <Arduino.h>
#include "SerialComm.h"

class BlueCallback : public BLECharacteristicCallbacks
{
    SerialComm *comm;

public:
    BlueCallback(SerialComm *serialComm);
    void onWrite(BLECharacteristic *pCharacteristic);
};
