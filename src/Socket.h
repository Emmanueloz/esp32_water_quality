#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include "SerialComm.h"

class Socket
{
private:
    static WebSocketsClient _webSocket;
    static SerialComm *_comm;
    static String _currenToken;
    static bool _shouldDisconnect;

public:
    static void setSerialComm(SerialComm *serialComm);
    static void connectServer(String host, int port, String token);
    static void handleSocketIOMessage(String message);
    static void handleSocketIOPacket(String message);
    static void disconnectServer();
    static void socketLoop();
    static void onEvent(WStype_t type, uint8_t *payload, size_t length);
    static void send(JsonDocument &body);
};
