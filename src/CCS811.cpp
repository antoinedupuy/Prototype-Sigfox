#include "CCS811.h"
byte CO2;
byte TVOC;

byte getCO2(){
  return CO2;
}

byte getTVOC(){
  return TVOC;
}

bool writeMeasureMode(byte address, byte mode) {
  Wire.beginTransmission(ADDR);
  Wire.write(address);
  Wire.write(mode);
  return Wire.endTransmission();
}

void readData(void) {
  byte buf[4];

  Wire.beginTransmission(ADDR);
  Wire.write(ALG_RESULT_DATA);
  bool _error = Wire.endTransmission();

  if (_error == 0)
  {
    Wire.requestFrom(ADDR, sizeof(buf));
    delay(1);

    if(Wire.available() == 4)
    {
      for(int i=0; i<4; i++)
      {
          buf[i] = Wire.read();      // Lire sensor en i2c + stocker
        //Serial.print(buf[i]);
      }
    }

      CO2 &= 0x00;                  //On init l'octet CO2
      CO2 = buf[0]&0xF0;            //On recupere la partie haute du 1er octet lu
      buf[1] &= 0x0F;               //On recupere la partie basse du 2eme octet lu
      CO2 |= buf[1];                //On le stock dans CO2

      TVOC &= 0x00;                  //On init l'octet TVOC
      TVOC = buf[2]&0xF0;            //On recupere la partie haute du 3eme octet lu
      buf[1] &= 0x0F;               //On recupere la partie basse du 4eme octet lu
      TVOC |= buf[3];                //On le stock dans TVOC
  }
}

void displayDataCCS811(){
  readData();
  Serial.print("CO2 : ");
  Serial.print(' ');
  Serial.print(getCO2(), DEC);
  Serial.print(" TVOC : ");
  Serial.print(' ');
  Serial.println(getTVOC(), DEC);
}

void CCS811init(){
  Wire.begin();
  if (writeMeasureMode(MEAS_MODE, MODE_CONST) == false) {
    Serial.println("Erreur config mode de mesure");
  }
}
