#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// put function declarations here:
int myFunction(int, int);

void setup()
{

  Serial.begin(115200);
  int result = myFunction(2, 3);
  JsonDocument doc;

  doc["x"] = result;
  doc["y"] = "z";
  doc["z"] = "y";

  String json;

  serializeJson(doc, json);
  Serial.println(json);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}