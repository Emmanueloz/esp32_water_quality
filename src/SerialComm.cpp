#include "SerialComm.h"

SerialComm::SerialComm(HardwareSerial &serialPort) : serial(&serialPort) {}

void SerialComm::begin(long baudrate)
{
    serial->begin(baudrate);
}

void SerialComm::send(const String &message)
{
    if (serial)
    {
        serial->println(message);
    }
}

int SerialComm::receive(Keyvalue *data)
{
    if (!serial->available())
        return 0;

    String line = readline();
    line.trim();

    int count = 0;
    int start = 0;

    while (start < line.length() && count < MAX_PAIRS)
    {
        int commaIndex = line.indexOf(',', start);
        String pair = (commaIndex == -1) ? line.substring(start) : line.substring(start, commaIndex);
        int equalIndex = pair.indexOf('=');

        if (equalIndex != -1)
        {
            data[count].key = pair.substring(0, equalIndex);
            data[count].value = pair.substring(equalIndex + 1);
            count++;
        }

        if (commaIndex == -1)
            break;
        start = commaIndex + 1;
    }

    return count;
}

String SerialComm::readline()
{
    if (serial)
    {
        return serial->readStringUntil('\n');
    }
    return "";
}