#include "sigfoxNetwork.h"

void reboot() {
  NVIC_SystemReset();
  while (1);
}

void sigfoxInit(SigfoxMessage msg){
  while (!Serial);
  if (!SigFox.begin()) {
    Serial.println("SigFox error, rebooting");
    reboot();
  }
  delay(100); // Wait at least 30ms after first configuration

  // Enable debug prints and LED indication
  SigFox.debug();
  // Read and convert the module temperature (PARTIE A SUPPRIMER PLUS TARD)
  /*msg.moduleTemperature = (int8_t) SigFox.internalTemperature();
  msg.temp2 = 35;
  Serial.print("Internal temp: ");
  Serial.print(msg.moduleTemperature, HEX); // display what we will send in Hexadecimal
  Serial.print(" (");
  Serial.print(msg.moduleTemperature); // display what we will send in Decimal
  Serial.println(" x100 deg C)");*/

  // Clears all pending interrupts
  SigFox.status();
  delay(1);
}

void sendDataSigfox(SigfoxMessage msg){
  SigFox.begin();
  delay(100);
  SigFox.beginPacket();
  /*Serial.println("Valeur avant envoi en hexa : ");
  Serial.println(msg.CO2, HEX);*/
  SigFox.write((uint8_t*)&msg, sizeof(SigfoxMessage));

  Serial.print("Status: ");

  SigFox.endPacket();
  SigFox.end();
}
