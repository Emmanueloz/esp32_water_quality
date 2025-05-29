#include "Socket.h"

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
