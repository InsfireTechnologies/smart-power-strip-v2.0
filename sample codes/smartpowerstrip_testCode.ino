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

//GPIO pins used to drive relay
const int Relay4 = 14;             //ESP8266 GPIO14 pin D5(on Wemos)
const int Relay3 = 12;             //ESP8266 GPIO12 pin D6(on Wemos)
const int Relay2 = 13;             //ESP8266 GPIO13 pin D7(on Wemos)
const int Relay1 = 15;             //ESP8266 GPIO15 pin D8(on Wemos)

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
}

void loop() {
  // This code just SwitchON relay for few seconds and than SwitchOFF, process keeps on repeating
  digitalWrite(LED_BUILTIN, LOW);    // Onboard SwitchON status to show process started
  digitalWrite(Relay1, LOW);         // Relay1 SwitchON command
  delay(1000);                       // wait for 1 second
  digitalWrite(Relay1, HIGH);        // Relay1 SwitchOFF command
  delay(1000);                       // wait for 1 second
  digitalWrite(Relay2, LOW);         // Relay2 SwitchON command
  delay(1000);                       // wait for 1 second
  digitalWrite(Relay2, HIGH);        // Relay2 SwitchOFF command
  delay(1000);
  digitalWrite(Relay3, LOW);         // Relay3 SwitchON command
  delay(1000);                       // wait for 1 second
  digitalWrite(Relay3, HIGH);        // Relay3 SwitchOFF command
  delay(1000);                       // wait for 1 second
  digitalWrite(Relay4, LOW);         // Relay4 SwitchON command
  delay(1000);                       // wait for 1 second
  digitalWrite(Relay4, HIGH);        // Relay4 SwitchOFF command
  digitalWrite(LED_BUILTIN, HIGH);   // Onboard SwitchOFF 
  delay(5000);                       // wait for 3 second
}
