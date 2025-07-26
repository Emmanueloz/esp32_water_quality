#pragma once
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

struct BlueInitConnection
{
  String name;
  String serviceUUID;
  String characteristicUUID;
  BLECharacteristicCallbacks *callbacks;
};

class BlueConnection
{
private:
  static BLEServer *pServer;
  static BLEService *pService;
  static BLECharacteristic *pCharacteristic;

public:
  static void initConnection(BlueInitConnection initConnection);
};