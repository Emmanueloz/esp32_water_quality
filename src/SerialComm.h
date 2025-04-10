#include <Arduino.h>
#pragma once

class SerialComm
{
private:
    HardwareSerial *serial = nullptr;

public:
    SerialComm() = default;
    void begin(HardwareSerial &serialPort, unsigned long baudrate);
    void send(const String &message);
    String receive();
};
