#include "sigfoxNetwork.h"
#include "CCS811.h"
#include "SI7006.h"
#include "VEML.h"
#include <ArduinoLowPower.h>
#include "dust.h"

SigfoxMessage msg;

void setup() {
  uint8_t data[4] = {0x11,0xE5,0x72,0x8A}; //Reset key
  uint8_t value = 0;

  pinMode(DUST_IN,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(CC811_nWake_PIN, OUTPUT);
  digitalWrite(CC811_nWake_PIN, LOW); // wake up CC811

  Serial.begin(9600);
  while (!Serial);

  Wire.begin();
  while ( Wire.available() ) {
     Wire.read();
  }

  initVEML();

  initCCS811(data,value);
  delay(10);
  digitalWrite(CC811_nWake_PIN, HIGH); // sleep CC811

  Serial.println("Go ...");
  Serial.println("---------------------");
}

void loop() {
  //Clignotement Led pour signaler début de loop()
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  sigfoxInit(msg);
  digitalWrite(CC811_nWake_PIN, LOW); // wake up CC811
  Serial.println("- - - - - - - - - - - - - -");
  readSI7006(&msg);
  readVEML(&msg);
  readCCS811(&msg);
  readDust(&msg);
  sendDataSigfox(msg);
  delay(1000);
  SigFox.end(); //sleep sigfox
  digitalWrite(CC811_nWake_PIN, HIGH); // sleep CC811

 // LowPower.sleep(7000);

  //delay(1000);
}


void dummy() {
  // This function will be called once on device wakeup
  // You can do some little operations here (like changing variables which will be used in the loop)
  // Remember to avoid calling delay() and long running functions since this functions executes in interrupt context
}
