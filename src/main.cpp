#include <Arduino.h>
#include "SerialComm.h"

SerialComm comm;

void setup()
{
  Serial.begin(115200);
  comm.begin(Serial2, 9600);
}

void loop()
{
  String receivedMessage = comm.receive();
  if (receivedMessage != "")
  {
    Serial.println("Received: " + receivedMessage);
  }

  comm.send("Hello from ESP32!");
  delay(1000);
}