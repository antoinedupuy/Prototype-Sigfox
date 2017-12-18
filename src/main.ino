#include "sigfoxNetwork.h"
#include "CCS811.h"

void setup() {
  Serial.begin(9600);

  SigfoxMessage msg;
  //comment
  CCS811init();
  sigfoxInit(msg);
  sendDataSigfox(msg);
}

void loop() {
  Serial.println("Mesure de la qualité de l'air ");
  displayDataCCS811();
  delay(1000);
}
