#include <ESP8266WiFi.h>
#include <stdio.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


Adafruit_SSD1306 display1(-1);
#define WIFI_SSID "pk"
#define WIFI_PASS "rimo6412"

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "prabhatkumar"
#define MQTT_PASS "efff9bbedfa14ed48db10e8570ad7a24"

int led = D7;

WiFiClient client;


void setup()
{
  Serial.begin(9600);
  display1.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR1);
  display1.clearDisplay();
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(">");
    delay(50);
  }

  Serial.println("OK!");
  mqtt.subscribe(&message);

  pinMode(led, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(led, LOW);

}

void loop()
{
 
  MQTT_connect();

  
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &message)
    {
     
      Serial.print("onoff: ");
     char* a = (char*) message.lastread;
     int b = atoi(a);
     int k,d;
     d=b;
     for(k=b; k>=0; k--)
    {
       display1.setTextSize(2);
    display1.setTextColor(WHITE);
    display1.setCursor(45,16);
      display1.println(d);
      Serial.println(d);
    display1.display(); 
    d--;
    delay(1000);
     display1.clearDisplay();
    }
     
    }
    else
    {
    
    }
  }
 
}


void MQTT_connect()
{

  
}
