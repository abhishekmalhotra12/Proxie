#include <ESP8266WiFi.h>
#include <stdio.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Wire.h> 
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR1   0x3C
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 

Adafruit_SSD1306 display1(-1);
#define WIFI_SSID "pk"
#define WIFI_PASS "rimo6412"

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "prabhatkumar"
#define MQTT_PASS "efff9bbedfa14ed48db10e8570ad7a24"

int led = D7;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

Adafruit_MQTT_Subscribe message = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/message");
Adafruit_MQTT_Publish LightsStatus = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/LightsStatus");


void setup()
{
  Serial.begin(9600);
  display1.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR1);
  display1.clearDisplay();
  display1.setTextSize(2);
    display1.setTextColor(WHITE);
    display1.setCursor(30,0);
    display1.println("NANO");
    display1.display();
     display1.setTextSize(1);
    display1.setTextColor(WHITE);
    display1.setCursor(20,20);
    display1.println("Messenger");
    display1.display();
    delay(5000);
   display1.clearDisplay();
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("\n\nConnecting Wifi>");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  digitalWrite(LED_BUILTIN, LOW);

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

  
  if (mqtt.connected() && mqtt.ping())
  {
    
    return;
  }

  int8_t ret;

  mqtt.disconnect();

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) 
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  
    retries--;
    if (retries == 0)
    {
      ESP.reset();
    }
  }
  Serial.println("MQTT Connected!");
}
