#include "CCS811.h"

int multiWriteRegister(uint8_t offset, uint8_t *inputPointer, uint8_t length)
{
	//define pointer that will point to the external space
	uint8_t i = 0;
	//Set the address
	Wire.beginTransmission(CC811_ADDR);
	Wire.write(offset);
	while ( i < length )  // send data bytes
	{
		Wire.write(*inputPointer); // receive a byte as character
		inputPointer++;
		i++;
	}
	if( Wire.endTransmission() != 0 )
	{
		return 1;
	}
	return 0;
}

int multiReadRegister(uint8_t offset, uint8_t *outputPointer, uint8_t length)
{
	//define pointer that will point to the external space
	uint8_t i = 0;
	uint8_t c = 0;
	//Set the address
	Wire.beginTransmission(CC811_ADDR);
	Wire.write(offset);
	if( Wire.endTransmission() != 0 )
	{
		return 1;
	}
	else  //OK, all worked, keep going
	{
		// request 6 bytes from slave device
		Wire.requestFrom(CC811_ADDR, length);
		while ( (Wire.available()) && (i < length))  // slave may send less than requested
		{
			c = Wire.read(); // receive a byte as character
			*outputPointer = c;
			outputPointer++;
			i++;
		}
		//dump extra
		while(Wire.available())
		{
			Wire.read();
		}
	}


	return 0;
}

int readRegister(uint8_t offset, uint8_t* outputPointer)
{
	//Return value
	uint8_t result;
	uint8_t numBytes = 1;
	Wire.beginTransmission(CC811_ADDR);
	Wire.write(offset);
	if( Wire.endTransmission() != 0 )
	{
	    Serial.println("I2C Error");
      return 1;
	}
	Wire.requestFrom(CC811_ADDR, numBytes);
	while ( Wire.available() ) // slave may send less than requested
	{
		result = Wire.read(); // receive a byte as a proper uint8_t
	}
	*outputPointer = result;

	return 0;
}

int writeRegister(uint8_t offset, uint8_t dataToWrite) {
	Wire.beginTransmission(CC811_ADDR);
	Wire.write(offset);
	Wire.write(dataToWrite);
	if( Wire.endTransmission() != 0 )
	{
		return 1;
	}
	return 0;
}


bool dataAvailable( void )
{
	uint8_t value;
	int returnError = readRegister( CSS811_STATUS, &value );
	if( returnError != 0 )
	{
		return false;
	}
	else
	{
		return (value & 1 << 3);
	}
}

void initCCS811(uint8_t * data, uint8_t value){
	//Reset CC811
	readRegister(CSS811_HW_ID, &value);
	if ( value == 0x81 ) {
		Serial.println("CC811 Detected");
	} else {
		Serial.print("CC811 value :");Serial.println(value);
	}

	multiWriteRegister(CSS811_SW_RESET, data, 4);
	delay(10);
	readRegister( CSS811_STATUS, &value );
	if( value & 1 ) {
		Serial.println("CC811 Status ko");
	}
	Serial.print("CC811 Status :");Serial.println(value);

	Wire.beginTransmission(CC811_ADDR);
	Wire.write(CSS811_APP_START);
	if( Wire.endTransmission() == 0 ) {
		Serial.println("CC811 Started");
	}
	readRegister( CSS811_MEAS_MODE, &value ); //Read what's currently there
	value &= ~(0b00000111 << 4); //Clear DRIVE_MODE bits
	value |= (1 << 4); //Mask in mode
	writeRegister(CSS811_MEAS_MODE, 0x20);	//Set mode 2 : Pulse Heating Mode 10s

	Serial.println("Go ...");
	Serial.println("---------------------");
}

void readCCS811(SigfoxMessage * msg){
	uint8_t data[4];
	uint16_t co2,tvoc;
	Serial.println("Read CC811");
	if (dataAvailable()) {
		multiReadRegister(CSS811_ALG_RESULT_DATA, data, 4);
		co2 = ((uint16_t)data[0] << 8) | data[1];
		tvoc = ((uint16_t)data[2] << 8) | data[3];
		Serial.print("CO2 : ");
		Serial.println(co2);
		Serial.print("tVOC : ");
		Serial.println(tvoc);
		msg->CO2 = co2;
		msg->TVOC = tvoc;
	}
  else {
		Serial.println("CC811 not ready");
	}
	delay(10);
}
