#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Socket.h>
#include "SerialComm.h"
#include "BlueConnection.h"
#include "BlueCallback.h"

BlueCallback blueCallback(nullptr);

SerialComm comm(Serial2);

String ssid = "";
String password = "";
String apiKey = "";

const String SERVICE_UUID = "853540ca-6f63-4823-baf8-52dc3781b06a";
const String CHARACTERISTIC_UUID = "1a5c9524-128c-40b9-9b13-bf435190a3a6";

void setup()
{
  Serial.begin(9600);
  // comm.begin(9600, 134217756U, 16, 17); // Serial1, RX=16, TX=17
  comm.begin(9600, 134217756U);
  Socket::setSerialComm(&comm);
  blueCallback = BlueCallback(&comm);
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

  Serial.println("Connected to WiFi");
  comm.send("response=connectWifiSuccess");
  Socket::connectServer("api.aqua-minds.org", 443, apiKey);
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

void sendBluetooth(Keyvalue kv[], int count)
{
  Serial.println("Sending bluetooth");
  JsonDocument doc = JsonDocument();

  for (int i = 0; i < count; i++)
  {
    doc[kv[i].key] = kv[i].value;
  }

  BlueConnection::seen(doc.as<String>());
}

void loop()
{
  Keyvalue kv[MAX_PAIRS];
  int count = comm.receive(kv);
  Socket::socketLoop();

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
      Socket::disconnectServer();
    }
    else if (kv[0].value == "connectBluetooth")
    {
      Serial.println("Connecting to bluetooth");

      BlueConnection::initConnection(
          BlueInitConnection{
              "ESP32 Water Quality",
              SERVICE_UUID,
              CHARACTERISTIC_UUID,
              &blueCallback});
    }
    else if (kv[0].value == "sendBluetooth")
    {
      sendBluetooth(kv, count);
    }
    else
    {
      Serial.print("Unknown command: ");
      Serial.println(kv[0].key);
      comm.send("response=UnknownCommand");
    }
  }
  else if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    command.trim();
    Serial.println(command);
    comm.send(command);
  }
}