//BlynkESP32_BT_WF library

#define BLYNK_TEMPLATE_ID ""//Need Blynk Template ID
#define BLYNK_TEMPLATE_NAME "" //Need Blynk Device Name
#define BLYNK_AUTH_TOKEN //"********************"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

#define button1_pin 18
//#define button2_pin 19

#define relay1_pin 32
//#define relay2_pin 33

bool relay1_state = LOW;
//bool relay2_state = LOW;
//int relay2_state = 0;

//Change the virtual pins according the rooms
#define button1_vpin    V0
//#define button2_vpin    V1

//------------------------------------------------------------------------------
// This function is called every time the device is connected to the Blynk.Cloud
// Request the latest state from the server
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
  //Blynk.syncVirtual(button2_vpin);
}

//--------------------------------------------------------------------------
// This function is called every time the Virtual Pin state change
//i.e when web push switch from Blynk App or Web Dashboard
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
  //digitalWrite(relay1_pin, !relay1_state);
}
/*--------------------------------------------------------------------------
BLYNK_WRITE(button2_vpin) {
  relay2_state = param.asInt();
  digitalWrite(relay2_pin, relay2_state);
}
*/
void setup()
{
  // Debug console
  Serial.begin(115200);
  //Serial.println("Hello, ESP32!");
  //--------------------------------------------------------------------
  pinMode(button1_pin, INPUT);//High active
  //pinMode(button2_pin, INPUT);

  //--------------------------------------------------------------------
  pinMode(relay1_pin, OUTPUT);
  //pinMode(relay2_pin, OUTPUT);

  //--------------------------------------------------------------------
  //During Starting all Relays should TURN OFF
  digitalWrite(relay1_pin, LOW); //off
  //digitalWrite(relay2_pin, LOW);

  //--------------------------------------------------------------------
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  //--------------------------------------------------------------------
  //Blynk.virtualWrite(button1_vpin, relay1_state);
  //Blynk.virtualWrite(button2_vpin, relay2_state);
  //Blynk.virtualWrite(button3_vpin, relay3_state);
  //Blynk.virtualWrite(button4_vpin, relay4_state);
  //--------------------------------------------------------------------
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  
  listen_push_buttons();
}

void listen_push_buttons(){
  //--------------------------------------------------------------------------
  if(digitalRead(button1_pin) == HIGH){ //High active
    delay(200);
    control_relay(1);
    Blynk.virtualWrite(button1_vpin, relay1_state); //update button state
  }
  /*--------------------------------------------------------------------------
  else if (digitalRead(button2_pin) == HIGH){
    delay(200);
    control_relay(2);
    Blynk.virtualWrite(button2_vpin, relay2_state); //update button state
  }
*/
}

void control_relay(int relay){
  //------------------------------------------------
  if(relay == 1){
    relay1_state = !relay1_state;
    digitalWrite(relay1_pin, relay1_state);
    Serial.print("Relay1 State = ");
    Serial.println(relay1_state);
    delay(50);
  }
  /*------------------------------------------------
  else if(relay == 2){
    relay2_state = !relay2_state;
    digitalWrite(relay2_pin, relay2_state);
    Serial.print("Relay1 State = ");
    Serial.println(relay2_state);    
    delay(50);
  }
  */
}
