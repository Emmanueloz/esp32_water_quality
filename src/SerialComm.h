#include <Arduino.h>
#pragma once

#define MAX_PAIRS 10
struct Keyvalue
{
    String key;
    String value;
};
class SerialComm
{
private:
    HardwareSerial *serial;
    String readline();

public:
    SerialComm();
    SerialComm(HardwareSerial &serialPort);
    void begin(long baudRate);
    void send(const String &message);
    int receive(Keyvalue *data);
};
