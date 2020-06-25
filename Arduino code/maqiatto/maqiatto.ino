#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#include "MQTTConnector.h"
#include "Credentials.h"

#define WIFI_TIMEOUT 1000
#define LOOP_TIMEOUT 50

TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device


float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;

void WiFiBegin(const char* ssid, const char* pass)
{
  WiFi.begin(ssid, pass);
  Serial.printf("Waiting for AP connection ...\n");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(WIFI_TIMEOUT);
    Serial.printf(".");
  }
  IPAddress ip = WiFi.localIP();
  Serial.printf("\nConnected to AP. IP : %d.%d.%d.%d\n",
                ip[0], ip[1], ip[2], ip[3]);
}

void setup()
{
  ss.begin(9600);
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  WiFiBegin(STA_SSID, STA_PASS);
  MQTTBegin();
}

void loop()
{

  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
      }
    }

  delay(100);

  String str = lat_str + "," + lng_str ;
  
  // Length (with one extra character for the null terminator)
  int str_len = str.length() + 1;

  // Prepare the character array (the buffer)
  char char_array[str_len];

  // Copy it over
  str.toCharArray(char_array, str_len);
    
  Serial.print(char_array);

 

 
  MQTTLoop();
  if (MQTTPublish(TOPIC, char_array))
  {
    Serial.printf("MQTTPublish was succeeded.\n");
  }
  delay(LOOP_TIMEOUT);


  
}
