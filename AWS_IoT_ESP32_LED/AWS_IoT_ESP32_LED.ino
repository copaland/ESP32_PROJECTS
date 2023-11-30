/*********
AWS_IOT_ESP32_LED: Control LEDs 
#define in1_Pin    16             // Define the Input pin
#define in2_Pin    17             // Define the Input pin
#define in3_Pin    18             // Define the Input pin
#define in4_Pin    19             // Define the Input pin

#define out1_Pin    26             // Define the Relay Control pin
#define out2_Pin    27             // Define the Relay Control pin
#define out3_Pin    32             // Define the Relay Control pin
#define out4_Pin    33             // Define the Relay Control pin
*********/
#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
 
#define AWS_IOT_SUBSCRIBE_TOPIC1 "esp32/lamp1"
#define AWS_IOT_SUBSCRIBE_TOPIC2 "esp32/lamp2"
#define AWS_IOT_SUBSCRIBE_TOPIC3 "esp32/lamp3"
#define AWS_IOT_SUBSCRIBE_TOPIC4 "esp32/lamp4"
 
#define lamp1 26
#define lamp2 27
#define lamp3 32
#define lamp4 33
 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
 
void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC1);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC2);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC3);
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC4);
 
  Serial.println("AWS IoT Connected!");
  Serial.println(WiFi.localIP()); //
} 

void messageHandler(char* topic, byte* payload, unsigned int length)
{
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
/*
    for (int i = 0; i < length; i++) 
    {
      Serial.print((char)payload[i]); // Pring payload content
    }
*/
/*##################### Lamp 1 #####################*/
  if ( strstr(topic, "esp32/lamp1") )
  {
    String Relay1 = doc["state"];
    int r1 = Relay1.toInt();
    Serial.print(r1);
    if(r1==1)
    {
      digitalWrite(lamp1, HIGH);
      Serial.print("Lamp1 is ON");
    }
    else if(r1==0)
    {
      digitalWrite(lamp1, LOW);
      Serial.print("Lamp1 is OFF");
    }
  }
 
/*##################### Lamp 2 #####################*/
  if ( strstr(topic, "esp32/lamp2") )
  {
    String Relay2 = doc["state"];
    int r2 = Relay2.toInt();
    Serial.print(r2);
    if(r2==1)
    {
      digitalWrite(lamp2, HIGH);
      Serial.print("Lamp2 is ON");
    }
    else if(r2==0)
    {
      digitalWrite(lamp2, LOW);
      Serial.print("Lamp2 is OFF");
    }
  }
 
/*##################### Lamp 3 #####################*/
  if ( strstr(topic, "esp32/lamp3") )
  {
    String Relay3 = doc["state"];
    int r3 = Relay3.toInt();
    Serial.print(r3);
    if(r3==1)
    {
      digitalWrite(lamp3, HIGH);
      Serial.print("Lamp3 is ON");
    }
    else if(r3==0)
    {
      digitalWrite(lamp3, LOW);
      Serial.print("Lamp3 is OFF");
    }
  }
 
/*##################### Lamp 4 #####################*/
  if ( strstr(topic, "esp32/lamp4") )
  {
    String Relay4 = doc["state"];
    int r4 = Relay4.toInt();
    Serial.print(r4);
    if(r4==1)
    {
      digitalWrite(lamp4, HIGH);
      Serial.print("Lamp4 is ON");
    }
    else if(r4==0)
    {
      digitalWrite(lamp4, LOW);
      Serial.print("Lamp4 is OFF");
    }
  }
  Serial.println();
} 
 
void setup()
{
  Serial.begin(115200);
  
  pinMode (lamp1, OUTPUT);
  pinMode (lamp2, OUTPUT);
  pinMode (lamp3, OUTPUT);
  pinMode (lamp4, OUTPUT);
 
  digitalWrite(lamp1, LOW);
  digitalWrite(lamp2, LOW);
  digitalWrite(lamp3, LOW);
  digitalWrite(lamp4, LOW);
  
  connectAWS();
}
 
void loop()
{
  client.loop();
  delay(1000);
}
