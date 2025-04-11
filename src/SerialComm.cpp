#include "SerialComm.h"

void SerialComm::begin(HardwareSerial &serialPort, unsigned long baudrate)
{
    serial = &serialPort;
    serial->begin(baudrate);
}

void SerialComm::send(const String &message)
{
    if (serial)
    {
        serial->println(message);
    }
}

String SerialComm::receive(Keyvalue *data)
{
    if (serial)
    {
        return serial->readStringUntil('\n');
    }
    return "";
}

String SerialComm::readline()
{
    if (serial)
    {
        return serial->readStringUntil('\n');
    }
    return "";
}