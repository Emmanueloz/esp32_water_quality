#include <Arduino.h>
#include "SerialComm.h"

SerialComm comm(Serial2);

void setup()
{
  Serial.begin(115200);
  comm.begin(9600);
}

void loop()
{
  Keyvalue kv[MAX_PAIRS];
  int count = comm.receive(kv);

  for (int i = 0; i < count; i++)
  {
    Serial.println(kv[i].key + "=" + kv[i].value);
  }
  delay(1000);
}