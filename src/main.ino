#include "sigfoxNetwork.h"
#include "CCS811.h"
#include "SI7006.h"
#include <ArduinoLowPower.h>

SigfoxMessage msg;

void setup() {
  Serial.begin(9600);

  CCS811init();
  /*Wire.begin(); // Initialise I2C communication as MASTER
  si7006Init();*/
  sigfoxInit(msg);
  }

void loop() {
  Serial.println("--------------Mesure de la qualité de l'air-------------- ");
  displayDataCCS811(&msg);
  //Serial.println("--------------Mesure de la température--------------");
  //si7006Loop();
  sendDataSigfox(msg);
  Serial.println();
  //LowPower.sleep(1000);
  delay(6000);
  //LowPower.sleep(15 * 60 * 1000);   //Endormir le système 15 min
}
