#include <Arduino.h>
#pragma once

struct Keyvalue
{
    String key;
    String value;
};
class SerialComm
{
private:
    HardwareSerial *serial = nullptr;
    String readline();

public:
    SerialComm() = default;
    void begin(HardwareSerial &serialPort, unsigned long baudrate);
    void send(const String &message);
    String receive(Keyvalue *data);
};
