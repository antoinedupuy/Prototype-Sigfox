#include "sigfoxNetwork.h"
#include "CCS811.h"
#include "SI7006.h"
void setup() {
  Serial.begin(9600);

  SigfoxMessage msg;
  CCS811init();
  /*Wire.begin(); // Initialise I2C communication as MASTER
  si7006Init();*/
  sigfoxInit(msg);
  sendDataSigfox(msg);
  }

void loop() {
  Serial.println("--------------Mesure de la qualité de l'air-------------- ");
  displayDataCCS811();
  //Serial.println("--------------Mesure de la température--------------");
  //si7006Loop();
  Serial.println();
  delay(1000);
}
