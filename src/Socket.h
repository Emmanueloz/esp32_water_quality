#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "SerialComm.h"

class Socket
{
private:
    static SerialComm *_comm;

public:
    static void setSerialComm(SerialComm *serialComm);
    static bool connectServer(String host, int port, String apiKey);
    static void disconnectServer();
    static void send(JsonDocument &body);
};
