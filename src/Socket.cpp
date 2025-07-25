#include "Socket.h"

WebSocketsClient Socket::_webSocket;
String Socket::_currenToken;
SerialComm *Socket::_comm = nullptr;
bool Socket::_shouldDisconnect = false; // NEW

void Socket::setSerialComm(SerialComm *serialComm)
{
    _comm = serialComm;
}

void Socket::connectServer(String host, int port, String token)
{
    Serial.println("Connecting to websocket server...");
    if (_comm)
    {
        _comm->send("response=connectingSocket");
    }

    _currenToken = token;
    _shouldDisconnect = false;
    String url = "/socket.io/?access_token=" + token + "&EIO=4&transport=websocket";
    _webSocket.onEvent(Socket::onEvent);

    _webSocket.beginSSL(host, port, url);
    //_webSocket.setReconnectInterval(5000); // Reconectar si se pierde
    //_webSocket.enableHeartbeat(15000, 3000, 2);
}

void Socket::disconnectServer()
{
    Serial.println("🔌 Disconnecting from websocket server...");

    // CRÍTICO: Marcar que queremos desconectar
    _shouldDisconnect = true;

    // Enviar desconexión Socket.IO si está conectado
    if (_webSocket.isConnected())
    {
        _webSocket.sendTXT("41");
        delay(100); // Dar tiempo para enviar
    }

    // Deshabilitar heartbeat si existe
    _webSocket.disableHeartbeat();

    // Desconectar WebSocket
    _webSocket.disconnect();

    Serial.println("✅ Desconectado FORZADAMENTE - Reconexión BLOQUEADA");
}

void Socket::socketLoop()
{
    // CRÍTICO: Solo hacer loop si NO queremos desconectar
    if (!_shouldDisconnect)
    {
        _webSocket.loop();
    }
}

void Socket::onEvent(WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_CONNECTED:
        Serial.println("✅ WebSocket connected.");
        _webSocket.sendTXT("40/receive/?access_token=" + _currenToken);
        if (_comm)
            _comm->send("response=socketConnected");
        break;

    case WStype_DISCONNECTED:
        Serial.println("❌ WebSocket disconnected.");
        if (_comm)
            _comm->send("response=socketDisconnected");
        break;

    case WStype_TEXT:
        Serial.print("📨 Received: ");
        Serial.println((char *)payload);
        handleSocketIOMessage(String((char *)payload));
        break;

    case WStype_PING:
        Serial.println("🏓 WebSocket ping.");
        break;
    case WStype_PONG:
        Serial.println("🏓 WebSocket pong.");

    case WStype_ERROR:
        Serial.println("❌ WebSocket error.");
        Serial.println((char *)payload);
        if (_comm)
            _comm->send("socket_error=1");
        break;

    default:
        Serial.println("Unknown WebSocket event.");
        Serial.println(type);
        break;
    }
}

void Socket::handleSocketIOMessage(String message)
{
    if (message.length() == 0)
        return;

    char engineCode = message.charAt(0);

    switch (engineCode)
    {
    case '0': // Engine.IO OPEN
        Serial.println("Engine.IO Open received");
        break;

    case '2': // Engine.IO PING
        Serial.println("Engine.IO Ping received");
        _webSocket.sendTXT("3"); // Responder con Engine.IO PONG
        Serial.println("Engine.IO Pong sent");
        break;

    case '3': // Engine.IO PONG
        Serial.println("Engine.IO Pong received");
        break;

    case '4': // Socket.IO message
        handleSocketIOPacket(message);
        break;

    default:
        break;
    }
}

void Socket::handleSocketIOPacket(String message)
{
    if (message.length() < 2)
        return;

    char socketCode = message.charAt(1);

    switch (socketCode)
    {
    case '0': // CONNECT
        Serial.println("Socket.IO Connect confirmed");
        break;

    case '2': // EVENT
        Serial.println("Socket.IO Event: " + message);
        break;

    case '3': // ACK
        Serial.println("Socket.IO ACK: " + message);
        break;

    default:
        break;
    }
}

void Socket::send(JsonDocument &body)
{
    Serial.println("Sending data to server...");

    String message = body.as<String>();
    Serial.println(message);
    // 42/receive/,["message",{"color":{"r":131,"g":39,"b":101},"conductivity":2208.683122590,"ph":2.773825,"temperature":24.564110,"tds":279.3078,"turbidity":49}]
    _webSocket.sendTXT("42/receive/,[\"message\"," + message + "]");
}
