#include "SI7006.h"

void si7006Init(void)
{
  //while(!Serial) {};

  uint16_t reading;
  // Start I2C transmission
  Wire.beginTransmission(0X40);
  Wire.write(0xE0);
  // Stop I2C transmission
  Wire.endTransmission();
  Wire.requestFrom(0X40, 2);
  while(Wire.available() < 2); // if two bytes were received
  reading = Wire.read();  // receive high byte (overwrites previous reading)
  reading = reading << 8;    // shift high byte to be high 8 bits
  reading |= Wire.read(); // receive low byte as lower 8 bits
  Serial.println(reading);   // print the reading
  delay(300);
}

void si7006Loop(void)
{
    unsigned int data[2];
    byte test[2];
    word test2 = 0x0000;

    // Start I2C transmission
    Wire.beginTransmission(ADDR);
    // Send humidity measurement command, NO HOLD MASTER
    Wire.write(0xF5);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(500);

    // Request 2 bytes of data
    Wire.requestFrom(ADDR, 2);

    // Read 2 bytes of data
    // humidity msb, humidity lsb
    if(Wire.available() == 2)
    {
      data[0] = Wire.read();
      data[1] = Wire.read();
    }

    // Convert the data
    float humidity  = ((data[0] * 256.0) + data[3]);
    humidity = ((125 * humidity) / 65536.0) - 6;

    // Start I2C transmission
    Wire.beginTransmission(ADDR);
    // Send temperature measurement command, NO HOLD MASTER
    Wire.write(0xF3);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(500);

    // Request 2 bytes of data
    Wire.requestFrom(ADDR, 2);

    // Read 2 bytes of data
    // temp msb, temp lsb
    if(Wire.available() == 2)
    {
      //data[0] = Wire.read();
      //data[1] = Wire.read();

      //test[1] = Wire.read();
      //test[0] = Wire.read();
      test2 = test2&0xFF00&Wire.read();
      test2 = test2 | (0x00FF&Wire.read());

    }

    // Convert the data
    //float temp  = ((data[0] * 256.0) + data[1]);
    word w = test[1] + test[0];
    Serial.println(test2, DEC);
    Serial.println(test[1], DEC);
    float ctemp = ((175.72 * w) / 65536.0) - 46.85;
    float ftemp = ctemp * 1.8 + 32;

    // Output data to serial monitor
    Serial.print("Relative humidity : ");
    Serial.print(humidity);
    Serial.println(" % RH");
    Serial.print("Temperature in Celsius : ");
    Serial.print(ctemp);
    Serial.println(" C");
    Serial.print("Temperature in Fahrenheit : ");
    Serial.print(ftemp);
    Serial.println(" F");
    delay(500);
}
