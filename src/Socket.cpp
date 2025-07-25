#include "Socket.h"

WebSocketsClient Socket::_webSocket;
String Socket::_currenToken;
SerialComm *Socket::_comm = nullptr;

void Socket::setSerialComm(SerialComm *serialComm)
{
    _comm = serialComm;
}

void Socket::connectServer(String host, int port, String token)
{
    Serial.println("Connecting to websocket server...");
    _currenToken = token;
    String url = "/socket.io/?access_token=" + token + "&EIO=4&transport=websocket";
    _webSocket.onEvent(Socket::onEvent);
    _webSocket.beginSSL(host, port, url);
}

void Socket::disconnectServer()
{
}

void Socket::socketLoop()
{
    _webSocket.loop();
}

void Socket::onEvent(WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_CONNECTED:
        Serial.println("✅ WebSocket connected.");
        _webSocket.sendTXT("40/receive/?access_token=" + _currenToken);
        if (_comm)
            _comm->send("socket_connected=true");
        break;

    case WStype_DISCONNECTED:
        Serial.println("❌ WebSocket disconnected.");
        if (_comm)
            _comm->send("socket_disconnected=true");
        break;

    case WStype_TEXT:
        Serial.print("📨 Received: ");
        Serial.println((char *)payload);
        break;

    case WStype_ERROR:
        Serial.println("❌ WebSocket error.");
        if (_comm)
            _comm->send("socket_error=1");
        break;

    default:
        Serial.println("Unknown WebSocket event.");
        Serial.println(type);
        break;
    }
}

void Socket::send(JsonDocument &body)
{
    Serial.println("Sending data to server...");
    Serial.println(body.as<String>());
}
