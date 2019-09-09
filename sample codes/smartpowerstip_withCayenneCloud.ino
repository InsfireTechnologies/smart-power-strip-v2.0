/*
 *              Wemos D1 Mini pin configuration details
 *
 *                      ____________________
 *                    /                      \
 *                   |                        |
 *          (/RST) 1 | RST                 TX | 22 (/GPIO1)
 *          (ADC0) 2 | A0                  RX | 21  (GPIO3) 
 *        (GPIO16) 4 | D0                  D1 | 20  (GPIO5) <SCL>
 *  <SCk> (GPIO14) 5 | D5                  D2 | 19  (GPIO4) <SDA>
 * <MISO> (GPIO12) 6 | D6                  D3 | 18  (GPIO0)
 * <MOSI> (GPIO13) 7 | D7                  D4 | 17  (GPIO2)
 *  <SS>  (GPIO15)16 | D8                   G | 15    (GND)
 *          (3.3V) 8 | 3V3                 5V | USB    (5v)
 *                    \                       |
 *                    -| Reset  ______  D1mini|
 *                     |_______/\____/\_______|
 *              
 * 
 */

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "YourNetworkSSID";           //Add your home wifi network ssid 
char wifiPassword[] = "networkpassword";   //Add wifi password

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_username";   //Replace with your MQTT username
char password[] = "MQTT_password";   //Replace with your MQTT password
char clientID[] = "CLIENT_ID";       //Replace with your clientID

//GPIO pins used to drive relay
const int Relay4 = 14;        //ESP8266 GPIO14 pin D5(on Wemos)
const int Relay3 = 12;        //ESP8266 GPIO12 pin D6(on Wemos)
const int Relay2 = 13;        //ESP8266 GPIO13 pin D7(on Wemos)
const int Relay1 = 15;        //ESP8266 GPIO15 pin D8(on Wemos)


void setup() {
  //configure GPIO pins as output
  pinMode(Relay4, OUTPUT); 
  pinMode(Relay3, OUTPUT); 
  pinMode(Relay2, OUTPUT); 
  pinMode(Relay1, OUTPUT); 

  //Here Active Low Logic used so Relay(SwitchON when GPIO pins are low)
  //so to keep SwitchOFF initially issue HIGH command
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);

  pinMode(LED_BUILTIN, OUTPUT); // pin mode setup for onboard led
  
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  Serial.println("Ready..");
  digitalWrite(LED_BUILTIN, LOW); //active low so status ON
}

unsigned long previousmillis = 0; 
int setInterval = 5000;

void loop() {
  Cayenne.loop();
  
  unsigned long currentmillis = millis();
  if (currentmillis - previousmillis > setInterval) { // send data after every 5 seconds interval
   digitalWrite(LED_BUILTIN, LOW);        
   Cayenne.virtualWrite(6, WiFi.RSSI());  // sends wifi signal strength to cloud
   digitalWrite(LED_BUILTIN, HIGH); 
   previousmillis = currentmillis;
  }
  
}

// below functions are executed depending on action for Various Channel Number defined on cayenne cloud for widgets like button, led, etc.
CAYENNE_IN(0)  // action for channel 0
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
  if(getValue.asInt()) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);  
  } 
}

CAYENNE_IN(1)   // action for channel 1
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
  if(getValue.asInt()){
      Serial.println("SwitchON 1");
      digitalWrite(Relay1,0); //Device will be SwitchON 
    }
  else {
      Serial.println("SwitchOFF 1");
      digitalWrite(Relay1,1); //Device will be SwitchOFF 
    }
}

CAYENNE_IN(2)   // action for channel 2
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
  if(getValue.asInt()){
      Serial.println("SwitchON 2");
      digitalWrite(Relay2,0); //Device will be SwitchON 
    }
  else {
      Serial.println("SwitchOFF 2");
      digitalWrite(Relay2,1); //Device will be SwitchOFF 
    }
}

CAYENNE_IN(3)   // action for channel 3
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
  if(getValue.asInt()){
      Serial.println("SwitchON 3");
      digitalWrite(Relay3,0); //Device will be SwitchON 
    }
  else {
      Serial.println("SwitchOFF 3");
      digitalWrite(Relay3,1); //Device will be SwitchOFF 
    }
}

CAYENNE_IN(4)   // action for channel 4
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message"); 
  if(getValue.asInt()){
      Serial.println("SwitchON 4");
      digitalWrite(Relay4,0); //Device will be SwitchON 
    }
  else {
      Serial.println("SwitchOFF 4");
      digitalWrite(Relay4,1); //Device will be SwitchOFF 
    }
}
