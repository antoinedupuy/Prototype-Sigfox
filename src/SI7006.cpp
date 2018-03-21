#include "SI7006.h"

void readSI7006(SigfoxMessage * msg){
  byte high,low;
  float temp_f, hygro_f;
  unsigned int temp, hygro = 0;

  Serial.println("Read SI7006");
  //Lecture température
  Wire.beginTransmission(SI7006_ADDR);
  Wire.write(0xE3);
  if ( Wire.endTransmission() == 0 ) {
     Wire.requestFrom(SI7006_ADDR,2,true);
     if (Wire.available() == 2)
     {
        high = Wire.read();
        low = Wire.read();
        temp = word(high,low);
     } else {
       temp = 0;
     }
  }
  if ( temp & 0xFFFC ) {
     temp_f = (175.72 * (float)temp)/65536 - 46.85;
  }
  Serial.print("Temp :");Serial.println(temp_f);
    msg->temperature = temp_f * 100;
  delay(10);

  //Lecture hygrométrie
  Wire.beginTransmission(SI7006_ADDR);
  Wire.write(0xE5);
  if ( Wire.endTransmission() == 0 ) {
     Wire.requestFrom(SI7006_ADDR,2,true);
     if (Wire.available() == 2)
     {
        high = Wire.read();
        low = Wire.read();
        hygro = word(high,low);
     } else {
       hygro = 0;
     }
  }
  if ( hygro & 0xFFFC ) {
     hygro_f = (125 * (float)hygro)/65536 - 6;
  }
  Serial.print("Hygro :");Serial.println(hygro_f);
  msg->hygrometrie = hygro_f;
  delay(10);
}
