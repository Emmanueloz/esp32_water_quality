#include "BlueConnection.h"

BLEServer *BlueConnection::pServer = nullptr;
BLEService *BlueConnection::pService = nullptr;
BLECharacteristic *BlueConnection::pCharacteristic = nullptr;

void BlueConnection::initConnection(BlueInitConnection initConnection)
{
    BLEDevice::init(initConnection.name.c_str());

    pServer = BLEDevice::createServer();

    pService = pServer->createService(initConnection.serviceUUID.c_str());

    pCharacteristic = pService->createCharacteristic(
        initConnection.characteristicUUID.c_str(),
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY);

    pCharacteristic->addDescriptor(new BLE2902());

    pCharacteristic->setCallbacks(initConnection.callbacks);

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->start();

    Serial.println("BLE server started");
}
