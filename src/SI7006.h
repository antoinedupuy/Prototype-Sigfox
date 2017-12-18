#ifndef SI7006_H
#define SI7006_H

#include "Arduino.h"
#include <Wire.h>

// SI7006-A20 I2C address is 0x40(64)
#define ADDR 0x40

void si7006Init(void);
void si7006Loop(void);

#endif
