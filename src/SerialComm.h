#pragma once
#include <Arduino.h>

#define MAX_PAIRS 10 // Máximo de pares clave=valor por mensaje

struct Keyvalue
{
    String key;
    String value;
};

class SerialComm
{
public:
    SerialComm(HardwareSerial &serialPort);
    void begin(long baudRate, uint32_t config = -1, int8_t rxPin = -1, int8_t txPin = -1);
    void send(const String &message);
    int receive(Keyvalue *data);

private:
    HardwareSerial &serialPort;
    String readLine();
};
