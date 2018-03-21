#include "VEML.h"

void initVEML(){
  Serial.println("Configure VEML6030");
  Wire.beginTransmission(VEML6030_ADDR);
  Wire.write(0x00);
  Wire.write(0xC0); // Low - ALS_IT : 800 ms ALS_SD = 0
  Wire.write(0x08); // High - ALS_GAIN : 01 (2x)
  if ( Wire.endTransmission() == 0 ) {
    Serial.println("... OK");
  } else {
    Serial.println("... KO");
  }
  delay(10);
  Wire.beginTransmission(VEML6030_ADDR);
  Wire.write(0x03);
  Wire.write(0x07); // power saving
  Wire.write(0x00);
  if ( Wire.endTransmission() == 0 ) {
    Serial.println("... OK");
  } else {
    Serial.println("... KO");
  }
}

void readVEML(SigfoxMessage * msg){
  byte high,low;
  unsigned int als = 0;
  Serial.println("Read VEML6030");
  Wire.beginTransmission(VEML6030_ADDR);
  Wire.write(0x04);
  if ( Wire.endTransmission(false) == 0 ) {
     Wire.requestFrom(VEML6030_ADDR,2,true);
     if (Wire.available() == 2)
     {
        low = Wire.read();
        high = Wire.read();
        als = word(high,low);
        Serial.print("Als :");Serial.println(als);
        msg->luminosite = als;
     } else {
       als = 0;
       Serial.println("VEML6030 - Transmission error(2)");
     }
  } else {
     Serial.println("VEML6030 - Transmission error(1)");
  }
  delay(10);
}
