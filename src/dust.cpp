#include "dust.h"

void readDust(SigfoxMessage * msg){
  int samplingTime = 280;
  int deltaTime = 40;
  int sleepTime = 9680;

  float voMeasured = 0;
  float calcVoltage = 0;
  float dustDensity = 0;
  
  digitalWrite(DUST_IN,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(DUST_OUT); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(DUST_IN,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured * (3.3 / 1024);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  dustDensity = (0.172 * calcVoltage - 0.090) * 1000; //Dust density in µg/m3

  Serial.print("Dust density [µg/m3]: "); Serial.println(dustDensity);
  msg->dust = dustDensity;

  delay(10);

}
