#include "sigfoxNetwork.h"
#include "CCS811.h"

void setup() {
  Serial.begin(115200);

  SigfoxMessage msg;
  sleep(15);
  CCS811init();
  sigfoxInit(msg);
  sendDataSigfox(msg);
}

void loop() {
  displayDataCCS811();
  delay(1000);
}
