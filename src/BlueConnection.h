#pragma once
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "SerialComm.h"

struct BlueInitConnection
{
  String name;
  String serviceUUID;
  String characteristicUUID;
  BLECharacteristicCallbacks *callbacks;
  SerialComm *serialComm;
};

class BlueConnection
{
private:
  static BLEServer *pServer;
  static BLEService *pService;
  static BLECharacteristic *pCharacteristic;
  static bool isInitialized;

public:
  static SerialComm *comm;
  static void initConnection(BlueInitConnection initConnection);
  static void deinitConnection();
  static void seen(String value);
};