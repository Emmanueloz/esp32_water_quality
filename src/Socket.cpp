#include "Socket.h"

void Socket::setSerial(SerialComm *serialComm)
{
    comm = serialComm;
    Serial.println("Serial communication set for Socket.");
}

bool Socket::connectServer(String host, int port, String apiKey)
{
    return false;
}

void Socket::disconnectServer()
{
}

void Socket::send(JsonDocument &body)
{
    Serial.println("Sending data to server...");
    Serial.println(body.as<String>());
}
