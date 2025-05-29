#include <Arduino.h>
#include "SerialComm.h"
#include <ArduinoJson.h>
#include <Socket.h>

SerialComm comm(Serial1);
String state = "repose";

void setup()
{
  Serial.begin(9600);
  comm.begin(9600, 134217756U, 16, 17);
  Serial.println("Setup");
}

void loop()
{
  Keyvalue kv[MAX_PAIRS];
  int count = comm.receive(kv);
  JsonDocument doc = JsonDocument();
  doc["color"] = JsonObject();

  for (int i = 0; i < count; i++)
  {

    if (kv[i].key == "state")
    {
      state = kv[i].value;
      doc["state"] = kv[i].value;
    }

    if (state == "reading")
    {
      if (kv[i].key == "colorR")
      {
        doc["color"]["r"] = kv[i].value;
      }
      else if (kv[i].key == "colorG")
      {
        doc["color"]["g"] = kv[i].value;
      }
      else if (kv[i].key == "colorB")
      {
        doc["color"]["b"] = kv[i].value;
      }
      else
      {
        doc[kv[i].key] = kv[i].value;
      }
    }
  }

  // Si el hay valores en el kv
  if (count > 0 && state == "reading")
  {
    Socket::send(doc);
    comm.send("ok");
  }

  delay(1000);
}