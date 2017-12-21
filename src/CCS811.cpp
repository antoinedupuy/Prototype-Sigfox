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

//Acquisition des valeurs d'émission de CO2 (en ppm) et de TVOC (en ppb)
void displayDataCCS811(){
  if (mySensor.dataAvailable()) //Data capteur d'air dispo
  {
    mySensor.readAlgorithmResults();
    Serial.print("CO2 : ");
    Serial.print(mySensor.getCO2());
    Serial.println("ppm");
    Serial.print("tVOC : ");
    Serial.print(mySensor.getTVOC());
    Serial.println("ppb");
  }
delay(10);
}
