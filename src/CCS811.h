#ifndef CCS811_H
#define CCS811_H
#include <stdint.h>
#include <Wire.h>
#include <SigFox.h>
#include "sigfoxNetwork.h"
/*#define CC811_ADDR   0x5A
#define CC811_nWake_PIN 4

#include <Arduino.h>
#include "sigfoxNetwork.h"
#include <SparkFunCCS811.h>

void displayDataCCS811(SigfoxMessage * msg);
void CCS811init();*/

#define CC811_ADDR   0x5A
#define CC811_nWake_PIN 4

#define CSS811_STATUS 0x00
#define CSS811_MEAS_MODE 0x01
#define CSS811_ALG_RESULT_DATA 0x02
#define CSS811_RAW_DATA 0x03
#define CSS811_ENV_DATA 0x05
#define CSS811_NTC 0x06
#define CSS811_THRESHOLDS 0x10
#define CSS811_BASELINE 0x11
#define CSS811_HW_ID 0x20
#define CSS811_HW_VERSION 0x21
#define CSS811_FW_BOOT_VERSION 0x23
#define CSS811_FW_APP_VERSION 0x24
#define CSS811_ERROR_ID 0xE0
#define CSS811_APP_START 0xF4
#define CSS811_SW_RESET 0xFF

int multiWriteRegister(uint8_t offset, uint8_t *inputPointer, uint8_t length);
int multiReadRegister(uint8_t offset, uint8_t *outputPointer, uint8_t length);
bool dataAvailable( void );
int readRegister(uint8_t offset, uint8_t* outputPointer);
int writeRegister(uint8_t offset, uint8_t dataToWrite);
void initCCS811(uint8_t * data, uint8_t value);
void readCCS811(SigfoxMessage * msg);

#endif
