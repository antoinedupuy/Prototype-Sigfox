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

  // Clears all pending interrupts
  SigFox.status();
  delay(1);
}

void sendDataSigfox(SigfoxMessage msg){
  SigFox.begin();
  delay(100);
  SigFox.beginPacket();
  Serial.println("Valeur CO2 avant envoi en hexa : ");
  Serial.println(msg.CO2, HEX);
  Serial.println("Valeur tVOC avant envoi en hexa : ");
  Serial.println(msg.TVOC, HEX);
  SigFox.write((uint8_t*)&msg, sizeof(SigfoxMessage));

  Serial.print("Status: ");

  SigFox.endPacket();
  SigFox.end();
}
