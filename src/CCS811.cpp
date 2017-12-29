#include "CCS811.h"

#define CCS811_ADDR 0x5B //Adresse I2C

CCS811 mySensor(CCS811_ADDR);

//Initialisation du capteur de qualité d'air
void CCS811init(){
  Serial.begin(9600);

  CCS811Core::status returnCode = mySensor.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    Serial.println(".begin() returned with an error.");
    while (1);
  }
}

//Acquisition des valeurs d'émission de CO2 (en ppm) et de TVOC (en ppb) que l'on écrit dans le message Sigfox et qu'on affiche ds le Moniteur série
void displayDataCCS811(SigfoxMessage * msg){
  if (mySensor.dataAvailable()) //Data capteur d'air dispo
  {
    mySensor.readAlgorithmResults();
    Serial.print("CO2 : ");
    Serial.print(mySensor.getCO2());
    msg->CO2 = mySensor.getCO2(); // On écrit la valeur du CO2 dans la struct du message Sigfox
    Serial.println("ppm");
    Serial.print("tVOC : ");
    Serial.print(mySensor.getTVOC());
    msg->TVOC = mySensor.getTVOC();
    Serial.println("ppb");
  }
delay(10);
}
