#include <Arduino.h>
#include "SerialComm.h"
#include <ArduinoJson.h>
#include <Socket.h>
#include <WiFi.h>

SerialComm comm(Serial1);

String ssid = "";
String password = "";
String apiKey = "";

void setup()
{
  Serial.begin(9600);
  comm.begin(9600, 134217756U, 16, 17); // Serial1, RX=16, TX=17
  Socket::setSerialComm(&comm);
  Serial.println("Setup");
}

void connectInit(Keyvalue kv[], int count)
{
  for (int i = 0; i < count; i++)
  {
    if (kv[i].key == "apiKey")
    {
      apiKey = kv[i].value;
    }
    else if (kv[i].key == "ssid")
    {
      ssid = kv[i].value;
    }
    else if (kv[i].key == "password")
    {
      password = kv[i].value;
    }
  }

  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  Serial.println(password);

  if (WiFi.status() == WL_CONNECT_FAILED)
  {
    Serial.println("Connection failed, check SSID and password");
    comm.send("response=connectFailed");
    return;
  }
  else if (WiFi.status() == WL_NO_SSID_AVAIL)
  {
    Serial.println("No SSID available, check SSID");
    comm.send("response=connectFailed");
    return;
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    comm.send("response=connecting");
  }

  Socket::connectServer("https://api.aqua-minds.org", 80, apiKey);
  Serial.println("Connected to WiFi");
  comm.send("response=connectSuccess");
}

void seenRecords(Keyvalue kv[], int count)
{
  JsonDocument doc = JsonDocument();
  doc["color"] = JsonObject();

  for (int i = 0; i < count; i++)
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
  Socket::send(doc);
  comm.send("response=seenSuccess");
}

void loop()
{
  Keyvalue kv[MAX_PAIRS];
  int count = comm.receive(kv);

  if (count > 0 && kv[0].key == "command")
  {
    if (kv[0].value == "connectInit")
    {
      connectInit(kv, count);
    }
    else if (kv[0].value == "seen")
    {
      seenRecords(kv, count);
    }
    else if (kv[0].value == "seenFinished")
    {
      Serial.println("Seen finished");
    }
    else
    {
      Serial.print("Unknown command: ");
      Serial.println(kv[0].key);
      comm.send("response=UnknownCommand");
    }
  }
}