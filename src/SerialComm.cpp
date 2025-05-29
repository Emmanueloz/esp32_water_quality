#include "SerialComm.h"

SerialComm::SerialComm(HardwareSerial &serial) : serialPort(serial) {}

void SerialComm::begin(long baudRate, uint32_t config, int8_t rxPin, int8_t txPin)
{
    if (config != -1, rxPin != -1, txPin != -1)
    {
        Serial.println("Initializing serial port with custom configuration...");
        serialPort.begin(baudRate, config, rxPin, txPin);
        return;
    }

    serialPort.begin(baudRate);
}

void SerialComm::send(const String &message)
{
    serialPort.println(message);
}

int SerialComm::receive(Keyvalue *data)
{
    if (!serialPort.available())
        return 0;

    String line = readLine();
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

String SerialComm::readLine()
{
    if (serialPort)
    {
        return serialPort.readStringUntil('\n');
    }
    return "";
}
