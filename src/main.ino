#include "sigfoxNetwork.h"
#include "CCS811.h"
#include "SI7006.h"
#include "VEML.h"
#include <ArduinoLowPower.h>
/*
SigfoxMessage msg;

void setup() {
  Serial.begin(9600);

  CCS811init();
  sigfoxInit(msg);
  }

void loop() {
  Serial.println("--------------Mesure de la qualité de l'air-------------- ");
  displayDataCCS811(&msg);
  //Serial.println("--------------Mesure de la température!--------------");
  //si7006Loop();
  sendDataSigfox(msg);
  Serial.println();
  //LowPower.sleep(1000);
  delay(6000);
  //LowPower.sleep(15 * 60 * 1000);   //Endormir le système 15 min
}*/

SigfoxMessage msg;

void setup() {
  uint8_t data[4] = {0x11,0xE5,0x72,0x8A}; //Reset key
  uint8_t value = 0;

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
  sigfoxInit(msg);
}

void loop() {
  readSI7006(&msg);
  delay(10);

  readVEML(&msg);
  delay(10);

  readCCS811(&msg);
  delay(10);

  sendDataSigfox(msg);
  delay(2000);
}
