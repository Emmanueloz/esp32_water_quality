#include "Socket.h"

SerialComm *Socket::_comm = nullptr;

void Socket::setSerialComm(SerialComm *serialComm)
{
    _comm = serialComm;
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
