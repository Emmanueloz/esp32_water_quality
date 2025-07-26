#include "BlueCallback.h"

BlueCallback::BlueCallback(SerialComm *serialComm)
{
    comm = serialComm;
}

void BlueCallback::onWrite(BLECharacteristic *pCharacteristic)
{
    std::string value = pCharacteristic->getValue();
    String valueStr = value.c_str();
    if (value.length() == 0)
        return;

    Serial.print("BLE Characteristic wrote: ");
    Serial.println(value.c_str());

    comm->send(valueStr);

    pCharacteristic->setValue("ACK");
    pCharacteristic->notify();
}