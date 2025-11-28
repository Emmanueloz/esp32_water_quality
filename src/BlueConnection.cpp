#include "BlueConnection.h"

BLEServer *BlueConnection::pServer = nullptr;
BLEService *BlueConnection::pService = nullptr;
BLECharacteristic *BlueConnection::pCharacteristic = nullptr;
bool BlueConnection::isInitialized = false;
SerialComm *BlueConnection::comm = nullptr;

class BlueServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        // Optional: Handle connection
        if (BlueConnection::comm)
        {
            BlueConnection::comm->send("response=bluetoothOn");
        }
    }

    void onDisconnect(BLEServer *pServer)
    {
        if (BlueConnection::comm)
        {
            BlueConnection::comm->send("response=bluetoothOff");
        }
        // Restart advertising
        BLEDevice::startAdvertising();
    }
    friend class BlueConnection;
};

void BlueConnection::deinitConnection()
{
    if (isInitialized)
    {
        // Stop advertising first
        BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
        if (pAdvertising)
        {
            pAdvertising->stop();
        }

        // Remove service and characteristics
        if (pService)
        {
            pService->stop();
            if (pCharacteristic)
            {
                pCharacteristic->setCallbacks(nullptr);
                pCharacteristic = nullptr;
            }
            pService = nullptr;
        }

        // Deinitialize the BLE device
        BLEDevice::deinit(false);

        // Free memory
        pServer = nullptr;

        isInitialized = false;
        Serial.println("BLE server stopped");
    }
}

void BlueConnection::seen(String value)
{
    if (isInitialized)
    {
        pCharacteristic->setValue(value.c_str());
        pCharacteristic->notify();
    }
}

void BlueConnection::initConnection(BlueInitConnection initConnection)
{
    // Clean up any existing connection
    deinitConnection();

    // Initialize BLE device
    BLEDevice::init(initConnection.name.c_str());

    comm = initConnection.serialComm;

    // Create BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new BlueServerCallbacks());

    // Create BLE Service
    pService = pServer->createService(initConnection.serviceUUID.c_str());

    // Create BLE Characteristic
    pCharacteristic = pService->createCharacteristic(
        initConnection.characteristicUUID.c_str(),
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY);

    pCharacteristic->addDescriptor(new BLE2902());

    if (initConnection.callbacks)
    {
        pCharacteristic->setCallbacks(initConnection.callbacks);
    }

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(initConnection.serviceUUID.c_str());
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();

    isInitialized = true;
    Serial.println("BLE server started");
}
